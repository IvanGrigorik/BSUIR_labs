use eframe::{
    egui::{
        self,
        plot::{self, BarChart},
        Grid,
    },
    epaint::{Color32, Stroke},
};
use rand_distr::{Distribution, Gamma, StandardNormal, Triangular};

enum TestStates {
    None,
    ShowChart,
}

enum TabsStates {
    Lehmer,
    MiddleMethod,
}

struct MyApp {
    // For RNG's
    a_buffer: u64,
    x1_buffer: u64,
    m_buffer: u64,
    random_numbers: Vec<f64>,
    random_numbers_bar: Vec<plot::Bar>,
    r0_buffer: u64,
    r1_buffer: u64,
    count: usize,

    // For tests
    test_state: TestStates,
    tab_state: TabsStates,

    expected: f64,
    correlation: f64,
    reference_expected: f64,
    reference_correlation: f64,
}

impl Default for MyApp {
    fn default() -> Self {
        Self {
            // Default values
            a_buffer: (367865493213),
            x1_buffer: (554298501938),
            m_buffer: (4674407374011),

            random_numbers: Vec::new(),
            random_numbers_bar: Vec::new(),
            r0_buffer: 121241445515252,
            r1_buffer: 31231455523,
            count: 100_000,

            // Ui states
            test_state: TestStates::None,
            tab_state: TabsStates::Lehmer,

            // Tests results and AVG value of whole generated vector
            expected: 0.,
            correlation: 0.,
            reference_expected: 0.,
            reference_correlation: 0.,
        }
    }
}

impl MyApp {
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
        let min = self
            .random_numbers
            .iter()
            .fold(f64::INFINITY, |x, &y| x.min(y));
        let max = self
            .random_numbers
            .iter()
            .fold(f64::NEG_INFINITY, |x, &y| x.max(y));

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
        self.random_numbers.push(x1 as f64);

        for i in 1..self.count {
            let t = a * self.random_numbers[i - 1] as u128;
            let _tmp = t % m;
            self.random_numbers.push(_tmp as f64);
        }
    }

    fn generate_gaussian(&mut self) {
        let mut random = rand::thread_rng();
        let distribution = StandardNormal;

        self.random_numbers_bar.clear();
        self.random_numbers
            .iter_mut()
            .for_each(|x| *x = distribution.sample(&mut random));

        self.refresh_numbers();
    }

    fn generate_exponential(&mut self) {
        let mut random = rand::thread_rng();
        let distribution = rand_distr::Exp1;

        self.random_numbers_bar.clear();
        self.random_numbers
            .iter_mut()
            .for_each(|x| *x = distribution.sample(&mut random));

        self.refresh_numbers();
    }

    fn generate_gamma(&mut self) {
        let mut random = rand::thread_rng();
        let distribution = Gamma::new(9.0, 0.5).unwrap();

        self.random_numbers_bar.clear();
        self.random_numbers
            .iter_mut()
            .for_each(|x| *x = distribution.sample(&mut random));

        self.refresh_numbers();
    }
    fn generate_triangular(&mut self) {
        let mut random = rand::thread_rng();
        let mut tmp_vector: Vec<u64> = Vec::with_capacity(self.count);
        tmp_vector.resize(self.count, 0);

        let distribution = Triangular::new(0., 1., 0.).unwrap();

        self.random_numbers_bar.clear();
        self.random_numbers
            .iter_mut()
            .for_each(|x| *x = distribution.sample(&mut random));

        self.refresh_numbers();
    }

    fn generate_simpson(&mut self) {
        let mut random = rand::thread_rng();
        let mut tmp_vector: Vec<u64> = Vec::with_capacity(self.count);
        tmp_vector.resize(self.count, 0);

        let distribution = Triangular::new(0.0, 1.0, 0.5).unwrap();

        self.random_numbers_bar.clear();
        self.random_numbers
            .iter_mut()
            .for_each(|x| *x = distribution.sample(&mut random));

        self.refresh_numbers();
    }

    fn generate_middle(&mut self) {
        let mut r0 = self.r0_buffer as u128;
        let mut r1 = self.r1_buffer as u128;

        let mask: u128 = 0xFFFFFFFFFFFFFFFF00000000; // mask to identify middle part of the number
        for _ in 0..self.count {
            let mut new_r = r0 * r1;

            new_r &= mask;
            new_r >>= 32;

            self.random_numbers.push(new_r as f64);

            r0 = r1;
            r1 = new_r;
        }
    }

    // Math functions
    fn compute_expected_value(&self) -> f64 {
        let sum = self.random_numbers.iter().map(|x| *x as u128).sum::<u128>() as f64;
        let count = self.random_numbers.len() as f64;
        sum / count
    }

    fn compute_reference_expected_value(&self) -> f64 {
        let min = self
            .random_numbers
            .iter()
            .fold(f64::INFINITY, |x, &y| x.min(y));
        let max = self
            .random_numbers
            .iter()
            .fold(f64::NEG_INFINITY, |x, &y| x.max(y));
        let sum = max + min;
        sum / 2.0
    }

    fn compute_reference_variance(&self) -> f64 {
        let expected_value = self.compute_reference_expected_value();

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

            // Tabs
            ui.horizontal(|ui| {
                if ui.button("Lehmer").clicked() {
                    self.tab_state = TabsStates::Lehmer;
                    self.test_state = TestStates::None;
                } else if ui.button("Middle").clicked() {
                    self.tab_state = TabsStates::MiddleMethod;
                    self.test_state = TestStates::None;
                }

                let sample_size = ui.label("Sample size: ");
                MyApp::usize_edit_field(ui, &mut self.count).labelled_by(sample_size.id);
            });

            // Values group
            ui.group(|ui| {
                Grid::new("tabs").show(ui, |ui| {
                    ui.label(format!("Мат. ожидание: {}", self.expected));
                    ui.label(format!("Дисперсия: {}", self.correlation));
                    ui.end_row();

                    ui.label(format!("Теор. мат. ожидание: {}", self.reference_expected));
                    ui.label(format!(
                        "Теор. дисперсия: {}",
                        self.reference_correlation
                    ));
                });
            });

            // Tabs internal logic
            ui.group(|ui| {
                match self.tab_state {
                    TabsStates::Lehmer => {
                        ui.heading("Lehmer generator");

                        // Input grid
                        Grid::new("lehmer_input_grid")
                            .min_col_width(20.0)
                            .max_col_width(180.0)
                            .striped(true)
                            .show(ui, |ui| {
                                ui.label(format!("a: {}", 16807100348768423212));
                                ui.end_row();

                                ui.label(format!("X1: {}", 18312763567113557112));
                                ui.end_row();

                                ui.label(format!("M: {}", 4674407374011241223));
                                ui.end_row();
                            });

                        if ui.button("Generate!").clicked() {
                            self.clear_numbers();
                            self.generate_lehmer();
                            self.refresh_numbers();
                            self.test_state = TestStates::ShowChart;

                            self.correlation = self.compute_variance();
                            self.expected = self.compute_expected_value();
                            self.reference_correlation = self.compute_reference_variance();
                            self.reference_expected = self.compute_reference_expected_value();
                        }
                    }

                    TabsStates::MiddleMethod => {
                        ui.heading("Middle multiply method generator");

                        Grid::new("middle_input_grid")
                            .min_col_width(20.0)
                            .max_col_width(180.0)
                            .striped(true)
                            .show(ui, |ui| {
                                ui.label(format!("R0: {}", self.r0_buffer));
                                ui.end_row();

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
                }
            });

            match self.test_state {
                TestStates::ShowChart => {
                    let plot = plot::Plot::new("Histogram: ");

                    Grid::new("chart_and_distr")
                        .max_col_width(600.)
                        .show(ui, |ui| {
                            ui.set_height(205.);
                            ui.set_width(500.);
                            plot.show(ui, |plot_ui| {
                                plot_ui.bar_chart(
                                    BarChart::new(self.random_numbers_bar.clone())
                                        .color(Color32::from_rgb(0xFC, 0xA3, 0x11)),
                                )
                            });
                            ui.vertical(|ui| {
                                ui.label("Distribution option:");
                                ui.end_row();

                                let mut need_to_refresh = false;

                                if ui.button("Uniform").clicked() {
                                    self.clear_numbers();
                                    self.generate_lehmer();
                                    self.refresh_numbers();
                                    need_to_refresh = true;
                                }
                                if ui.button("Gaussian").clicked() {
                                    self.generate_gaussian();
                                    need_to_refresh = true;
                                }
                                if ui.button("Exponential").clicked() {
                                    self.generate_exponential();
                                    need_to_refresh = true;
                                }
                                if ui.button("Gamma").clicked() {
                                    self.generate_gamma();
                                    need_to_refresh = true;
                                }
                                if ui.button("Triangular").clicked() {
                                    self.generate_triangular();
                                    need_to_refresh = true;
                                }
                                if ui.button("Simpson's").clicked() {
                                    self.generate_simpson();
                                    need_to_refresh = true;
                                }

                                if need_to_refresh == true {
                                    self.correlation = self.compute_variance();
                                    self.expected = self.compute_expected_value();
                                    self.reference_correlation = self.compute_reference_variance();
                                    self.reference_expected =
                                        self.compute_reference_expected_value();
                                }

                            })

                            // ui.vertical(|ui| {

                            // })
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
