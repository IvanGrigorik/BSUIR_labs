use eframe::egui::{
    self,
    plot::{self, BarChart},
    Grid,
};

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
}

struct MyApp {
    a_buffer: u64,
    x1_buffer: u64,
    m_buffer: u64,
    random_numbers: Vec<u64>,
    random_numbers_bar: Vec<plot::Bar>,
    test_state: TestStates,
    tab_state: TabsStates,

    average: u64,
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
            a_buffer: (16_807),
            x1_buffer: (18),
            m_buffer: (2_147_483_647),
            random_numbers: Vec::new(),
            random_numbers_bar: Vec::new(),

            // Ui states
            test_state: TestStates::Nothing,
            tab_state: TabsStates::MiddleMethod,

            // Tests results and AVG value of whole generated vector
            average: 0,
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
    fn integer_edit_field(ui: &mut egui::Ui, value: &mut u64) -> egui::Response {
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
        for i in 0..256 {
            self.random_numbers_bar
                .push(plot::Bar::new(i as f64, self.random_numbers[i] as f64));
        }
    }

    fn generate_lehmer(&mut self) {
        let a = self.a_buffer as u128;
        let x1 = self.x1_buffer as u128;
        let m = self.m_buffer as u128;
        self.random_numbers.push(x1 as u64);

        for i in 1..100_000 {
            let t = a * self.random_numbers[i - 1] as u128;
            let _tmp = t % m;
            self.random_numbers.push(_tmp as u64);
        }
    }

    fn generate_middle(&mut self) {}

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
        let result = block_frequency_test(&data, 20).unwrap();
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
        let result = longest_run_of_ones_test(&data).unwrap();
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
        let result = rank_test(&data).unwrap();
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
        let result = non_overlapping_template_test(&data, 10).unwrap();
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
        egui::CentralPanel::default().show(ctx, |ui| {
            ctx.set_pixels_per_point(1.5);
            Grid::new("tab_grid").min_col_width(20.).max_col_width(100.).show(ui, |ui| {
                if ui.button("Lehmer").clicked() {
                    self.tab_state = TabsStates::Lehmer;
                } else if ui.button("Middle").clicked() {
                    self.tab_state = TabsStates::MiddleMethod;
                }
            });

            match self.tab_state {
                TabsStates::Lehmer => {
                    ui.heading("Lehmer generator");

                    // Input grid
                    Grid::new("input_grid")
                        .min_col_width(20.0)
                        .max_col_width(180.0)
                        .striped(true)
                        .show(ui, |ui| {
                            let a_label = ui.label("a: ");
                            MyApp::integer_edit_field(ui, &mut self.a_buffer)
                                .labelled_by(a_label.id);
                            ui.label(format!("a: {}", self.a_buffer));
                            ui.end_row();

                            let x1_label = ui.label("X1: ");
                            MyApp::integer_edit_field(ui, &mut self.x1_buffer)
                                .labelled_by(x1_label.id);
                            ui.label(format!("X1: {}", self.x1_buffer));
                            ui.end_row();

                            let m_label = ui.label("Mod m: ");
                            MyApp::integer_edit_field(ui, &mut self.m_buffer)
                                .labelled_by(m_label.id);
                            ui.label(format!("M: {}", self.m_buffer));
                            ui.end_row();
                        });

                    if ui.button("Generate!").clicked() {
                        self.clear_numbers();
                        self.generate_lehmer();
                        self.refresh_numbers();
                        self.test_state = TestStates::ShowChart;
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
                    }

                    match self.test_state {
                        TestStates::ShowChart => {
                            let plot = plot::Plot::new("Histogram: ");
                            plot.show(ui, |plot_ui| {
                                plot_ui.bar_chart(BarChart::new(self.random_numbers_bar.clone()))
                            });
                        }

                        TestStates::ShowTestResults => {
                            Grid::new("tests")
                                .min_col_width(10.)
                                .max_col_width(500.)
                                .striped(true)
                                .show(ui, |ui| {
                                    ui.set_width(100.);

                                    ui.label(format!("Frequency test: {}", self.freq_result));
                                    ui.end_row();
                                    ui.label(format!("Cumulative sum test: {}", self.cusum_result));
                                    ui.end_row();
                                    ui.label(format!("Run test: {}", self.run_result));
                                    ui.end_row();
                                    ui.label(format!("Run ones test: {}", self.run_ones_result));
                                    ui.end_row();
                                    ui.label(format!("Matrix rank test: {}", self.rank_result));
                                    ui.end_row();
                                    ui.label(format!("FFT test: {}", self.fft_result));
                                    ui.end_row();
                                    ui.label(format!(
                                        "Overlapping template test: {}",
                                        self.over_result
                                    ));
                                    ui.end_row();
                                    ui.label(format!(
                                        "Non overlapping template test: {}",
                                        self.non_over_result
                                    ));
                                });
                        }

                        _ => (),
                    }
                }

                TabsStates::MiddleMethod => {}

                TabsStates::ShiftReg => {}
            }
        });
    }
}
fn main() -> Result<(), eframe::Error> {
    let options = eframe::NativeOptions::default();
    eframe::run_native("app_name", options, Box::new(|_cc| Box::<MyApp>::default()))
}
