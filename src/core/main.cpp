// Thanks to: https://seletz.github.io/posts/hotreload-gamecode-in-c/

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

#include "raylib.h"
#include "reload.hpp"

typedef struct {
    unsigned long long tick;
    Camera3D camera;
    Vector3 cubePosition;
} State;

typedef struct Rl {
    void (*BeginDrawing)();
    void (*ClearBackground)(Color);
    void (*DrawFPS)(int, int);
    void (*EndDrawing)();
    void (*DrawText)(const char*, int, int, int, Color);
} Rl;

Rl rl = (Rl){
    .BeginDrawing=BeginDrawing,
    .ClearBackground=ClearBackground,
    .DrawFPS=DrawFPS,
    .EndDrawing=EndDrawing,
    .DrawText=DrawText,
};

typedef State* (*Init)();
typedef void (*Drop)(State* state);
typedef void (*Update)(State* state);
typedef void (*Render)(State* state, Rl* rl);  // , void (*begin)(), void (*end)(), void (*clear)(), void(*fps)()

Init init = NULL;
Drop drop = NULL;
Update update = NULL;
Render render = NULL;

State* state = NULL;

int reloading() {
    static SymbolTable symtab[] = {
        { "init", (void**)&init },
        { "drop", (void**)&drop },
        { "update", (void**)&update },
        { "_render", (void**)&render },
        { 0 }
    };
    static long last = 0L;

    const char* path = "./target/debug/libhot.so";

    long current = GetFileModTime(path);

    if (current > last) {
        last = current;
        return reload((char*)path, symtab);
    }
    
    return 1;
}

int main(void) {
    const int W = 1280;
    const int H = 720;

    if (reloading() != 0)
        return 1;
    printf("Lib loaded!\n");

    state = init();

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(W, H, "Hot Queen Reloading");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        reloading();

        update(state);
        render(state, &rl);
    }

    CloseWindow();

    drop(state);
    state = NULL;
}
