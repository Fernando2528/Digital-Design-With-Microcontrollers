#include "config.h"
#include "app.h"

// V1 Version Funcional Modulada

int main(void) {
    App_Init();
    while (1) {
        App_Task();
    }
}

