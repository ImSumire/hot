use raylib_ffi::{Camera3D, Vector3};

#[repr(C)]
pub struct State {
    pub tick: u64,
    pub camera: Camera3D,
    pub cube_position: Vector3,
}
