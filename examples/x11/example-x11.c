#include "./../../libwindow.h"

int main() {
    t_window    window;
    bool        exit;

    lw_createWindow(&window, 800, 600, "libwindow - hello, x11!");

    exit = false;
    while (!exit) {
        t_event event;

        while (lw_pollEvents(window, &event)) {
            if (event.type == LW_EVENT_QUIT) {
                exit = true;
            }
        }
    }

    lw_destroyWindow(window);
    return (0);
}
