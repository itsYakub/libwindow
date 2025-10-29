#define LIBWINDOW_WAYLAND
#define LIBWINDOW_IMPLEMENTATION
#include "./../../libwindow.h"

int main() {
    t_window    window;

    lw_createWindow(&window, 800, 600, "libwindow - hello, wayland!");
    lw_destroyWindow(window);
    return (0);
}
