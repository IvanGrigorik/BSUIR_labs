use eframe::egui;
use egui::*;

#[derive(Default)]
struct MyApp {
    text: String,
}

impl eframe::App for MyApp {
    
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Press/Hold/Release example. Press A to test.");
            if ui.button("Clear").clicked() {
                self.text.clear();
            }
            ScrollArea::vertical()
                .auto_shrink([false; 2])
                .stick_to_bottom(true)
                .show(ui, |ui| {
                    ui.label(&self.text);
                });

            if ctx.input(|i| i.key_pressed(Key::A)) {
                self.text.push_str("\nPressed");
            }
            if ctx.input(|i| i.key_down(Key::A)) {
                self.text.push_str("\nHeld");
                ui.ctx().request_repaint(); // make sure we note the holding.
            }
            if ctx.input(|i| i.key_released(Key::A)) {
                self.text.push_str("\nReleased");
            }
        });
    }
}
fn main() -> Result<(), eframe::Error> {
    let options = eframe::NativeOptions::default();
    eframe::run_native("app_name", options, Box::new(|_cc| Box::<MyApp>::default()))
}
