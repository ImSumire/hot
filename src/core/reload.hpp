#pragma once


#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>


typedef struct SymbolTable {
  const char *symbol;  // name of the symbol
  void **ptr;    // address to be updated
} SymbolTable;


int reload(char *path, SymbolTable *symtab) {
    printf("Reloading...\n");
    static void *dll = NULL;

    // fprintf(stderr, "DLL_NAME: %s\n", path);

    if (dll) {
        // fprintf(stderr, "CLOSING DLL Handle %p\n", dll);
        dlclose(dll);
        dll = NULL;
    }

    int attempts = 0;
    const int MAX_ATTEMPTS = 20;

    while (attempts < MAX_ATTEMPTS) {
        dll = dlopen(path, RTLD_LAZY | RTLD_LOCAL);
        if (dll)
            break;
        
        usleep(10 * 1000);
        attempts++;
    }

    if (!dll) {
        fprintf(stderr, "ERROR: Could not open shared library %s: %s\n", path, dlerror());
        return 1;
    }

    while (symtab->symbol) {
        void *sym = dlsym(dll, symtab->symbol);
        if (!sym) {
            fprintf(stderr, "ERROR: Could not open symbol: %s: %s\n", symtab->symbol, dlerror());

            return 2;
        }

        // fprintf(stderr, "RELOAD: found symbol %s -> %p\n", symtab->symbol, symtab->ptr);

        *symtab->ptr = sym;
        symtab++;
    }

    return 0;
}
