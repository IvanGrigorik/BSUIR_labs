// use std::os::linux::fs::MetadataExt;

use eframe::{
    egui::{
        self,
        plot::{self, BarChart},
        Grid,
    },
    epaint::{Color32, Stroke},
};
use rand::Rng;

use nistrs::{
    freq::frequency_test,
    prelude::{
        block_frequency_test, cumulative_sums_test, fft_test, longest_run_of_ones_test,
        non_overlapping_template_test, overlapping_template_test,
    },
    rank::rank_test,
    runs::runs_test,
    BitsData,
};

enum TestStates {
    Nothing,
    ShowChart,
    ShowTestResults,
}

enum TabsStates {
    Lehmer,
    MiddleMethod,
    ShiftReg,
    BuildIn,
}

struct MyApp {
    // For RNG's
    a_buffer: u64,
    x1_buffer: u64,
    m_buffer: u64,
    random_numbers: Vec<u64>,
    random_numbers_bar: Vec<plot::Bar>,
    r0_buffer: u64,
    r1_buffer: u64,
    shift_buffer: u64,
    count: usize,

    // For tests
    test_state: TestStates,
    tab_state: TabsStates,

    average: u64,
    expected: f64,
    correlation: f64,
    reference_expected: f64,
    reference_correlation: f64,
    tested_vec: Vec<bool>,
    freq_result: String,
    block_freq_result: String,
    cusum_result: String,
    run_ones_result: String,
    run_result: String,
    rank_result: String,
    fft_result: String,
    non_over_result: String,
    over_result: String,
}

impl Default for MyApp {
    fn default() -> Self {
        Self {
            // Default values
            a_buffer: (16807100348768),
            x1_buffer: (18312763567113),
            m_buffer: (46744073740112),
            
            random_numbers: Vec::new(),
            random_numbers_bar: Vec::new(),
            r0_buffer: 121241445515252,
            r1_buffer: 31231455523,
            shift_buffer: 248432131643609289,
            count: 100_000,

            // Ui states
            test_state: TestStates::Nothing,
            tab_state: TabsStates::Lehmer,

            // Tests results and AVG value of whole generated vector
            average: 0,
            expected: 0.,
            correlation: 0.,
            reference_expected: 0.,
            reference_correlation: 0.,
            tested_vec: Vec::new(),
            freq_result: String::new(),
            block_freq_result: String::new(),
            cusum_result: String::new(),
            run_ones_result: String::new(),
            run_result: String::new(),
            rank_result: String::new(),
            fft_result: String::new(),
            non_over_result: String::new(),
            over_result: String::new(),
        }
    }
}

impl MyApp {
    fn u64_edit_field(ui: &mut egui::Ui, value: &mut u64) -> egui::Response {
        let mut tmp_value = format!("{}", value);
        let res = ui.text_edit_singleline(&mut tmp_value);
        if let Ok(result) = tmp_value.parse() {
            *value = result;
        }
        res
    }

    fn usize_edit_field(ui: &mut egui::Ui, value: &mut usize) -> egui::Response {
        let mut tmp_value = format!("{}", value);
        let res = ui.text_edit_singleline(&mut tmp_value);
        if let Ok(result) = tmp_value.parse() {
            *value = result;
        }

        res
    }

    fn clear_numbers(&mut self) {
        self.random_numbers.clear();
        self.random_numbers_bar.clear();
    }

    fn refresh_numbers(&mut self) {
        let max = self.random_numbers.iter().max().unwrap();
        let min = self.random_numbers.iter().min().unwrap();

        const BAR_CHART_MIN: f64 = 0.0;
        const BAR_CHART_MAX: f64 = 255.0;

        let slope = (BAR_CHART_MAX - BAR_CHART_MIN) / ((max - min) as f64);

        let mut bar_chart_counter = [0usize; (u8::MAX as usize) + 1];
        for n in 0..self.random_numbers.len() {
            let mapped_value = BAR_CHART_MIN + slope * ((self.random_numbers[n] - min) as f64);
            let index = mapped_value as usize;
            bar_chart_counter[index] += 1;
        }

        for i in 0..256 {
            self.random_numbers_bar
                .push(plot::Bar::new(i as f64, bar_chart_counter[i] as f64));
        }
    }

    // RNG's
    fn generate_lehmer(&mut self) {
        let a = self.a_buffer as u128;
        let x1 = self.x1_buffer as u128;
        let m = self.m_buffer as u128;
        self.random_numbers.push(x1 as u64);

        for i in 1..self.count {
            let t = a * self.random_numbers[i - 1] as u128;
            let _tmp = t % m;
            self.random_numbers.push(_tmp as u64);
        }
    }

    fn generate_middle(&mut self) {
        let mut r0 = self.r0_buffer as u128;
        let mut r1 = self.r1_buffer as u128;

        let mask: u128 = 0xFFFFFFFFFFFFFFFF00000000; // mask to identify middle part of the number
        for _ in 0..self.count {
            let mut new_r = r0 * r1;

            new_r &= mask;
            new_r >>= 32;

            self.random_numbers.push(new_r as u64);

            r0 = r1;
            r1 = new_r;
        }
    }

    fn generate_shift(&mut self) {
        let mut num = self.shift_buffer;
        for _ in 0..self.count {
            // Identify two last bits bit
            let b_0 = num & 1;
            let b_1 = (num & 2) >> 1;
            // Generate new last bit
            let n_bit = (b_0 ^ b_1) << 63;

            // Shift our number and put the last bit
            num >>= 1;
            num |= n_bit;
            self.random_numbers.push(num);
        }
    }

    fn generate_build_in(&mut self) {
        let mut rng = rand::thread_rng();
        for _ in 0..self.count {
            self.random_numbers.push(rng.gen::<u64>());
        }
    }
    // Math functions
    fn compute_expected_value(&self) -> f64 {
        let sum = self.random_numbers.iter().sum::<u64>() as f64;
        let count = self.random_numbers.len() as f64;
        sum / count
    }

    fn compute_reference_expected_value(&self) -> f64 {
        let sum = (self.random_numbers.iter().max().unwrap()
            + self.random_numbers.iter().min().unwrap()) as f64;
        sum / 2.0
    }

    fn compute_reference_variance(&self) -> f64 {
        let expected_value = self.compute_reference_expected_value();
        // let expected_value = self.compute_expected_value(numbers);

        let sum: f64 = self
            .random_numbers
            .iter()
            .map(|x| {
                let diff = (*x as f64) - expected_value;
                diff * diff
            })
            .sum();

        sum / (self.count as f64)
    }

    fn compute_variance(&self) -> f64 {
        let expected_value = self.compute_expected_value();
        // let expected_value = self.compute_expected_value(numbers);

        let sum: f64 = self
            .random_numbers
            .iter()
            .map(|x| {
                let diff = (*x as f64) - expected_value;
                diff * diff
            })
            .sum();

        sum / (self.count as f64)
    }

    // Function that transform random vector to tested
    fn initialize_tested_vector(&mut self) {
        let mut total: u128 = 0;

        for i in 0..self.random_numbers.len() {
            total += self.random_numbers[i] as u128;
        }

        self.average = (total / self.random_numbers.len() as u128) as u64;

        self.tested_vec = self
            .random_numbers
            .iter()
            .map(|x| -> bool { x > &self.average })
            .collect();
    }

    // Nist tests

    fn freq_test(&self, to_test: &Vec<bool>) -> String {
        let str: String = to_test.iter().map(|x| (*x as u8).to_string()).collect();
        let data = BitsData::from_text(str);
        let result = frequency_test(&data);
        format!("Test passed: {}, P-value: {:.6}", result.0, result.1)
    }

    fn block_freq_test(&self, to_test: &Vec<bool>) -> String {
        // TODO: Somehow postpone "str" or "data" to "initialize_tested_vector" and class variables
        let str: String = to_test.iter().map(|x| (*x as u8).to_string()).collect();
        let data = BitsData::from_text(str);
        let result = block_frequency_test(&data, 20).unwrap_or_default();
        format!("Test passed: {}, P-value: {:.6}", result.0, result.1)
    }

    fn cusum_test(&self, to_test: &Vec<bool>) -> String {
        // TODO: Somehow postpone "str" or "data" to "initialize_tested_vector" and class variables
        let str: String = to_test.iter().map(|x| (*x as u8).to_string()).collect();
        let data = BitsData::from_text(str);
        let result = cumulative_sums_test(&data);
        format!("Test passed: {}, P-value: {:.6}", result[0].0, result[0].1)
    }

    fn run_ones_test(&self, to_test: &Vec<bool>) -> String {
        // TODO: Somehow postpone "str" or "data" to "initialize_tested_vector" and class variables
        let str: String = to_test.iter().map(|x| (*x as u8).to_string()).collect();
        let data = BitsData::from_text(str);
        let result = longest_run_of_ones_test(&data).unwrap_or_default();
        format!("Test passed: {}, P-value: {:.6}", result.0, result.1)
    }

    fn run_test(&self, to_test: &Vec<bool>) -> String {
        // TODO: Somehow postpone "str" or "data" to "initialize_tested_vector" and class variables
        let str: String = to_test.iter().map(|x| (*x as u8).to_string()).collect();
        let data = BitsData::from_text(str);
        let result = runs_test(&data);
        format!("Test passed: {}, P-value: {:.6}", result.0, result.1)
    }

    fn rank_test(&self, to_test: &Vec<bool>) -> String {
        // TODO: Somehow postpone "str" or "data" to "initialize_tested_vector" and class variables
        let str: String = to_test.iter().map(|x| (*x as u8).to_string()).collect();
        let data = BitsData::from_text(str);
        let result = rank_test(&data).unwrap_or_default();
        format!("Test passed: {}, P-value: {:.6}", result.0, result.1)
    }

    fn fft_test(&self, to_test: &Vec<bool>) -> String {
        // TODO: Somehow postpone "str" or "data" to "initialize_tested_vector" and class variables
        let str: String = to_test.iter().map(|x| (*x as u8).to_string()).collect();
        let data = BitsData::from_text(str);
        let result = fft_test(&data);
        format!("Test passed: {}, P-value: {:.6}", result.0, result.1)
    }

    fn non_over_test(&self, to_test: &Vec<bool>) -> String {
        // TODO: Somehow postpone "str" or "data" to "initialize_tested_vector" and class variables
        let str: String = to_test.iter().map(|x| (*x as u8).to_string()).collect();
        let data = BitsData::from_text(str);
        let result = non_overlapping_template_test(&data, 10).unwrap_or_default();
        format!("Test passed: {}, P-value: {:.6}", result[0].0, result[0].1)
    }

    fn over_test(&self, to_test: &Vec<bool>) -> String {
        // TODO: Somehow postpone "str" or "data" to "initialize_tested_vector" and class variables
        let str: String = to_test.iter().map(|x| (*x as u8).to_string()).collect();
        let data = BitsData::from_text(str);
        let result = overlapping_template_test(&data, 10);
        format!("Test passed: {}, P-value: {:.6}", result.0, result.1)
    }
}

impl eframe::App for MyApp {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        let mut style = (*ctx.style()).clone();

        style.visuals.extreme_bg_color = egui::Color32::from_rgb(14, 21, 0x1D);
        style.visuals.collapsing_header_frame = true;
        style.visuals.widgets.noninteractive.fg_stroke =
            Stroke::new(10.0, Color32::from_rgb(0xE5, 0xE5, 0xE5));

        ctx.set_style(style);

        egui::CentralPanel::default().show(ctx, |ui| {
            ctx.set_pixels_per_point(2.45);

            // Pseudo-tabs
            Grid::new("tab_grid")
                .min_col_width(10.)
                .max_col_width(100.)
                .show(ui, |ui| {
                    if ui.button("Lehmer").clicked() {
                        self.tab_state = TabsStates::Lehmer;
                    } else if ui.button("Middle").clicked() {
                        self.tab_state = TabsStates::MiddleMethod;
                    } else if ui.button("LFSR").clicked() {
                        self.tab_state = TabsStates::ShiftReg;
                    } else if ui.button("Build-in").clicked() {
                        self.tab_state = TabsStates::BuildIn;
                    }
                    ui.end_row();
                    let sample_size = ui.label("Sample size: ");
                    MyApp::usize_edit_field(ui, &mut self.count).labelled_by(sample_size.id);
                });

            // Tabs internal logic
            match self.tab_state {
                TabsStates::Lehmer => {
                    ui.heading("Lehmer generator");

                    // Input grid
                    Grid::new("lehmer_input_grid")
                        .min_col_width(20.0)
                        .max_col_width(180.0)
                        .striped(true)
                        .show(ui, |ui| {
                            let a_label = ui.label("a: ");
                            MyApp::u64_edit_field(ui, &mut self.a_buffer).labelled_by(a_label.id);
                            ui.label(format!("a: {}", self.a_buffer));
                            ui.end_row();

                            let x1_label: egui::Response = ui.label("X1: ");
                            MyApp::u64_edit_field(ui, &mut self.x1_buffer).labelled_by(x1_label.id);
                            ui.label(format!("X1: {}", self.x1_buffer));
                            ui.end_row();

                            let m_label = ui.label("Mod m: ");
                            MyApp::u64_edit_field(ui, &mut self.m_buffer).labelled_by(m_label.id);
                            ui.label(format!("M: {}", self.m_buffer));
                            ui.end_row();
                        });

                    if ui.button("Generate!").clicked() {
                        self.clear_numbers();
                        self.generate_lehmer();
                        self.refresh_numbers();
                        self.test_state = TestStates::ShowChart;
                    }
                }

                TabsStates::MiddleMethod => {
                    ui.heading("Middle multiply method generator");

                    Grid::new("middle_input_grid")
                        .min_col_width(20.0)
                        .max_col_width(180.0)
                        .striped(true)
                        .show(ui, |ui| {
                            let r0_buffer = ui.label("R0: ");
                            MyApp::u64_edit_field(ui, &mut self.r0_buffer)
                                .labelled_by(r0_buffer.id);
                            ui.label(format!("R0: {}", self.r0_buffer));
                            ui.end_row();

                            let r1_buffer = ui.label("R1: ");
                            MyApp::u64_edit_field(ui, &mut self.r1_buffer)
                                .labelled_by(r1_buffer.id);
                            ui.label(format!("R1: {}", self.r1_buffer));
                            ui.end_row();
                        });

                    if ui.button("Generate!").clicked() {
                        self.clear_numbers();
                        self.generate_middle();
                        self.refresh_numbers();
                        self.test_state = TestStates::ShowChart;
                    }
                }

                TabsStates::ShiftReg => {
                    ui.heading("LFSR-based generator");

                    Grid::new("lfsr_input_grid")
                        .min_col_width(20.0)
                        .max_col_width(180.0)
                        .striped(true)
                        .show(ui, |ui| {
                            let first_num = ui.label("First number: ");
                            MyApp::u64_edit_field(ui, &mut self.shift_buffer)
                                .labelled_by(first_num.id);

                            ui.label(format!("Init number: {}", self.shift_buffer));
                            ui.end_row();
                        });

                    if ui.button("Generate!").clicked() {
                        self.clear_numbers();
                        self.generate_shift();
                        self.refresh_numbers();
                        self.test_state = TestStates::ShowChart;
                    }
                }

                TabsStates::BuildIn => {
                    ui.heading("Build-in random generator");

                    if ui.button("Generate!").clicked() {
                        self.clear_numbers();
                        self.generate_build_in();
                        self.refresh_numbers();
                        self.test_state = TestStates::ShowChart;
                    }
                }
            }

            if ui.button("Test!").clicked() {
                self.initialize_tested_vector();
                self.freq_result = self.freq_test(&self.tested_vec);
                self.block_freq_result = self.block_freq_test(&self.tested_vec);
                self.cusum_result = self.cusum_test(&self.tested_vec);
                self.run_ones_result = self.run_ones_test(&self.tested_vec);
                self.run_result = self.run_test(&self.tested_vec);
                self.rank_result = self.rank_test(&self.tested_vec);
                self.fft_result = self.fft_test(&self.tested_vec);
                self.non_over_result = self.non_over_test(&self.tested_vec);
                self.over_result = self.over_test(&self.tested_vec);

                self.test_state = TestStates::ShowTestResults;

                self.correlation = self.compute_variance();
                self.expected = self.compute_expected_value();
                self.reference_correlation = self.compute_reference_variance();
                self.reference_expected = self.compute_reference_expected_value();
            }

            match self.test_state {
                TestStates::ShowChart => {
                    let plot = plot::Plot::new("Histogram: ");
                    plot.show(ui, |plot_ui| {
                        plot_ui.bar_chart(
                            BarChart::new(self.random_numbers_bar.clone())
                                .color(Color32::from_rgb(0xFC, 0xA3, 0x11)),
                        )
                    });
                }

                TestStates::ShowTestResults => {
                    Grid::new("tests")
                        .min_col_width(10.)
                        .max_col_width(500.)
                        .striped(true)
                        .show(ui, |ui| {
                            ui.set_width(100.);

                            ui.label(format!("Test 1: {}", self.freq_result));
                            ui.end_row();
                            ui.label(format!("Test 2: {}", self.cusum_result));
                            ui.end_row();
                            ui.label(format!("Test 3: {}", self.run_result));
                            ui.end_row();
                            ui.label(format!("Test 4: {}", self.run_ones_result));
                            ui.end_row();
                            ui.label(format!("Test 5: {}", self.rank_result));
                            ui.end_row();
                            ui.label(format!("Test 6: {}", self.fft_result));
                            ui.end_row();
                            ui.label(format!("Test 7: {}", self.over_result));
                            ui.end_row();
                            ui.label(format!("Test 8: {}", self.non_over_result));

                            ui.end_row();
                            ui.end_row();
                            ui.label(format!("Expected: {}", self.expected));
                            ui.label(format!("Reference expected: {}", self.reference_expected));
                            ui.end_row();
                            ui.label(format!("Correlation: {}", self.correlation));
                            ui.label(format!("Reference correlation: {}", self.reference_correlation));
                        });
                }

                _ => (),
            }
        });
    }
}
fn main() -> Result<(), eframe::Error> {
    let options = eframe::NativeOptions::default();
    eframe::run_native("RNG's", options, Box::new(|_cc| Box::<MyApp>::default()))
}
