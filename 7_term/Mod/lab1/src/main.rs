use eframe::egui::{
    self,
    plot::{self, BarChart},
    Grid,
};

enum States {
    Nothing,
    ShowChart,
}

struct MyApp {
    a_buffer: u64,
    x1_buffer: u64,
    m_buffer: u64,
    random_numbers: Vec<u64>,
    random_numbers_bar: Vec<plot::Bar>,
    state: States,
}

impl Default for MyApp {
    fn default() -> Self {
        Self {
            a_buffer: (0),
            x1_buffer: (0),
            m_buffer: (0),
            random_numbers: Vec::new(),
            random_numbers_bar: Vec::new(),
            state: (States::Nothing),
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

    fn refresh_numbers(&mut self) {
        self.random_numbers.clear();
        self.random_numbers.push(self.a_buffer);
        self.random_numbers.push(self.x1_buffer);
        self.random_numbers.push(self.m_buffer);
        self.random_numbers.push(12);
        self.random_numbers_bar = self
            .random_numbers
            .iter()
            .enumerate()
            .map(|(i, n)| plot::Bar::new(i as f64, *n as f64))
            .collect();
    }
}

impl eframe::App for MyApp {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Lehmer generator");
            ctx.set_pixels_per_point(1.5);
            // Input grid
            Grid::new("input_grid")
                .min_col_width(20.0)
                .max_col_width(180.0)
                .striped(true)
                .show(ui, |ui| {
                    ui.set_width(20.0);
                    let a_label = ui.label("a: ");
                    MyApp::integer_edit_field(ui, &mut self.a_buffer).labelled_by(a_label.id);

                    ui.label(format!("a: {}", self.a_buffer));
                    ui.end_row();

                    let x1_label = ui.label("X1: ");
                    MyApp::integer_edit_field(ui, &mut self.x1_buffer).labelled_by(x1_label.id);
                    ui.label(format!("X1: {}", self.x1_buffer));
                    ui.end_row();

                    let m_label = ui.label("Mod m: ");
                    MyApp::integer_edit_field(ui, &mut self.m_buffer).labelled_by(m_label.id);
                    ui.label(format!("M: {}", self.m_buffer));
                    ui.end_row();
                });

            if ui.button("Generate!").clicked() {
                self.refresh_numbers();
                self.state = States::ShowChart;
            }

            match self.state {
                States::ShowChart => {
                    let plot = plot::Plot::new("Histogram: ");
                    plot.show(ui, |plot_ui| {
                        plot_ui.bar_chart(BarChart::new(self.random_numbers_bar.clone()))
                    });
                }

                _ => (),
            }
            {}
        });
    }
}
fn main() -> Result<(), eframe::Error> {
    let options = eframe::NativeOptions::default();
    eframe::run_native("app_name", options, Box::new(|_cc| Box::<MyApp>::default()))
}
