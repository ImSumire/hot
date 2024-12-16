use raylib_ffi::Color;

#[repr(C)]
pub struct RaylibDrawHandle {
    begin_drawing: extern "C" fn(),
    clear_background: extern "C" fn(Color),
    draw_fps: extern "C" fn(i32, i32),
    end_drawing: extern "C" fn(),
    draw_text: extern "C" fn(*const i8, i32, i32, i32, Color),
}

impl RaylibDrawHandle {
    pub fn begin_drawing(&self) {
        (self.begin_drawing)();
    }

    pub fn clear_background(&self, color: Color) {
        (self.clear_background)(color);
    }

    pub fn draw_fps(&self, x: i32, y: i32) {
        (self.draw_fps)(x, y);
    }

    pub fn end_drawing(&self) {
        (self.end_drawing)();
    }

    pub fn draw_text(&self, text: &str, x: i32, y: i32, font_size: i32, color: Color) {
        let text = std::ffi::CString::new(text).unwrap();
        (self.draw_text)(text.as_ptr(), x, y, font_size, color);
    }
}