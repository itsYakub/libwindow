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
                case (LW_EVENT_KEY): {
                    printf("%d\n", event.key.key);
                } break;
                case (LW_EVENT_BUTTON): {
                    printf("%d\n", event.button.button);
                } break;
                case (LW_EVENT_MOTION): {
                    printf("%d %d\n", event.motion.x, event.motion.y);
                } break;
            }
        }
    }

    lw_destroyWindow(window);
    return (0);
}
