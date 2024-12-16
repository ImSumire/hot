<div align="center">
    <pre>
        )            
     ( /(          ) 
     )\())      ( /( 
    ((_)\   (   )\())
     _((_)  )\ (_))/ 
    | || | ((_)| |_  
    | __ |/ _ \|  _| 
    |_||_|\___/ \__| 
    ︵‿︵‿୨♡୧‿︵‿︵
    hot-reloading in Rust
  </pre>

  [![License: GNU](https://img.shields.io/badge/License-GNU-ed9acb?style=for-the-badge)](https://www.gnu.org/)
  [![Rust: 1.83.0](https://img.shields.io/badge/Rust-1.83.0-edd29a?style=for-the-badge)](https://www.rust-lang.org/)

</div>

# Usage
For the moment you can use it as is, but it's part of my future game framework. Although the core is still in C++, the framwork will be in Rust. It uses Raylib and for the moment I've only managed to send pointers to functions that affect the display to get the context of the core, but I'm going to do everything I can to make it work without it.

1. To build it: `scripts/build.rs`
2. To run it: `scripts/run.rs`
3. Change something in `src/lib.rs` and save it
4. Re-compile: `scripts/build.rs`. Magic! The changes appear in the window! (or crashed if you made a bad change)
