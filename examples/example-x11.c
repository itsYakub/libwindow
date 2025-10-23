#include <stdio.h>

#define LIBWINDOW_X11
#define LIBWINDOW_IMPLEMENTATION
#include "./../libwindow.h"

int main() {
    t_window    window;
    bool        exit;

    lw_createWindow(&window, 800, 600, "libwindow - hello, wayland!");

    exit = false;
    while (!exit) {
        t_event event;

        while (lw_pollEvents(window, &event)) {
            if (event.type == LW_EVENT_QUIT) {
                puts("Event: quit");
                exit = true;
            }
        }
    }

    lw_destroyWindow(window);
    return (0);
}
