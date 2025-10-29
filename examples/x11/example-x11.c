#define LIBWINDOW_IMPLEMENTATION
#include "./../../libwindow.h"

#include <stdio.h>

int main() {
    t_window    window;
    bool        exit;

    lw_createWindow(&window, 800, 600, "libwindow - hello, x11!");

    exit = false;
    while (!exit) {
        t_event event;

        while (lw_pollEvents(window, &event)) {
            switch (event.type) {
                case (LW_EVENT_QUIT): { exit = true; } break;

                case (LW_EVENT_RESIZE): { printf("%d %d\n", event.resize.width, event.resize.height); } break;
                case (LW_EVENT_MOVE): { printf("%d %d\n", event.move.x, event.move.y); } break;
            }
        }
    }

    lw_destroyWindow(window);
    return (0);
}
