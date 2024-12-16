mod commons;
use commons::State;

mod raylib;
use raylib::RaylibDrawHandle;

// mod scene;

use raylib_ffi::{Camera3D, Vector3, enums, colors, UpdateCamera};

#[no_mangle]
pub extern "C" fn init() -> *mut State {
    let camera = Camera3D {
        fovy: 45.0,
        position: Vector3 { x: 0.0, y: 6.0, z: 9.0 },
        projection: enums::CameraProjection::Perspective as i32,
        target: Vector3 { x: 0.0, y: 0.0, z: 0.0 },
        up: Vector3 { x: 0.0, y: 1.0, z: 0.0 }
    };

    let state = Box::new(
        State {
            tick: 0,
            camera,
            cube_position: Vector3 { x: 0.0, y: 0.0, z: 0.0 }
        }
    );
    Box::into_raw(state)
}

#[no_mangle]
pub extern "C" fn drop(_state: *mut State) {
    // assert!(!state.is_null());
    // unsafe { Box::from_raw(state) };
}

#[no_mangle]
pub extern "C" fn update(state: *mut State) {
    assert!(!state.is_null());
    let state = unsafe { &mut *state };
    unsafe { UpdateCamera(&mut state.camera, enums::CameraMode::Orbital as i32); }
    state.cube_position = Vector3 { x: 0.0, y: (state.tick as f64 * 0.04).sin() as f32, z: 0.0 };
    state.tick += 1;
}

#[no_mangle]
pub extern "C" fn _render(state: *mut State, d: *mut RaylibDrawHandle) {
    render(unsafe { &mut *state }, unsafe { &mut *d });
}

fn render(state: &mut State, d: &mut RaylibDrawHandle) {
    d.begin_drawing();
        d.clear_background(colors::BLACK);
        d.draw_fps(10, 10);
        d.draw_text(format!("Ticks: {}", state.tick).as_str(), 10, 30, 20, colors::WHITE);
    d.end_drawing();
}
