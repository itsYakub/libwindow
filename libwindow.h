#if defined (__cplusplus)
# pragma once
#endif /* __cplusplus */
#if !defined (_libwindow_h_)
# define _libwindow_h_
#
# include <stddef.h>
# include <stdint.h>
# if !defined (__cplusplus)
#  include <stdbool.h>
# endif /* __cplusplus*/
#
# if !defined (LIBWINDOW_API)
#  if defined (__cplusplus)
#   define LIBWINDOW_API extern "C"
#  else
#   define LIBWINDOW_API extern
#  endif /* __cplusplus */
# endif /* LIBWINDOW_API */

/* SECTION: Types
 * * * * * * * * */

/* MODULE: Window */

enum {
    LW_PROP_NONE = 0,

    LW_PROP_X11_DISPLAY,
    LW_PROP_X11_ROOT_ID,
    LW_PROP_X11_WINDOW_ID,
    LW_PROP_X11_SCREEN_ID,

    LW_PROP_WIN32_HWND,
    LW_PROP_WIN32_HINSTANCE,
    LW_PROP_WIN32_HDC,

    /* ... */
    LW_PROP_COUNT
};

typedef struct s_window     *t_window;

/* MODULE: Event */

enum {
    LW_EVENT_NONE = 0,
    LW_EVENT_QUIT,
    LW_EVENT_KEY,
    LW_EVENT_BUTTON,
    LW_EVENT_MOTION,

    /* ... */
    LW_EVENT_COUNT
};

struct s_quitEvent {
    uint64_t    type;
    uint64_t    time;
    t_window    window;
};

struct s_keyEvent {
    uint64_t    type;
    uint64_t    time;
    t_window    window;
    uint32_t    key;
    uint8_t     state;
};

struct s_buttonEvent {
    uint64_t    type;
    uint64_t    time;
    t_window    window;
    uint32_t    button;
    uint32_t    x;
    uint32_t    y;
    uint8_t     state;
};

struct s_motionEvent {
    uint64_t    type;
    uint64_t    time;
    t_window    window;
    uint32_t    x, xrel;
    uint32_t    y, yrel;
};

typedef struct s_quitEvent      t_quitEvent;
typedef struct s_keyEvent       t_keyEvent;
typedef struct s_buttonEvent    t_buttonEvent;
typedef struct s_motionEvent    t_motionEvent;

struct s_event {
    uint32_t        type;
    union {
        t_quitEvent     quit;
        t_keyEvent      key;
        t_buttonEvent   button;
        t_motionEvent   motion;
    };
};

typedef struct s_event  t_event;

/* MODULE: Input */

enum {
    LW_BUTTON_NONE = 0,
    LW_BUTTON_LEFT = 1, LW_LEFT_BUTTON = LW_BUTTON_LEFT,
    LW_BUTTON_RIGHT = 2, LW_RIGHT_BUTTON = LW_BUTTON_RIGHT,
    LW_BUTTON_MIDDLE = 3, LW_MIDDLE_BUTTON = LW_BUTTON_MIDDLE,

    /* ... */
    LW_BUTTON_COUNT
};

/* SECTION: API
 * * * * * * * */

/* MODULE: Window */

LIBWINDOW_API bool  lw_createWindow(t_window *, const size_t, const size_t, const char *);
LIBWINDOW_API bool  lw_destroyWindow(t_window);

LIBWINDOW_API bool  lw_getWindowSize(t_window, size_t *, size_t *);
LIBWINDOW_API bool  lw_setWindowSize(t_window, const size_t, const size_t);
LIBWINDOW_API bool  lw_setWindowMinSize(t_window, const size_t, const size_t);
LIBWINDOW_API bool  lw_setWindowMaxSize(t_window, const size_t, const size_t);

LIBWINDOW_API bool  lw_getWindowPosition(t_window, size_t *, size_t *);
LIBWINDOW_API bool  lw_setWindowPosition(t_window, const size_t, const size_t);

LIBWINDOW_API bool  lw_getWindowTitle(t_window, char *, const size_t);
LIBWINDOW_API bool  lw_setWindowTitle(t_window, const char *);

LIBWINDOW_API void  *lw_getWindowProp(t_window, const uint64_t);

/* MODULE: Event */

LIBWINDOW_API bool  lw_pollEvents(t_window, t_event *);
LIBWINDOW_API bool  lw_pushEvent(t_window, t_event *);
LIBWINDOW_API bool  lw_popEvent(t_window, t_event *);
LIBWINDOW_API bool  lw_flushEvent(t_window);

/* MODULE: Time */

LIBWINDOW_API uint64_t  lw_getTime(void);
LIBWINDOW_API bool      lw_waitTime(uint64_t);

// #define LIBWINDOW_IMPLEMENTATION
// #define LIBWINDOW_WIN32

# if defined LIBWINDOW_IMPLEMENTATION
#  include <stdlib.h>
#  include <time.h>
#  include <string.h>
#  if defined (__linux__)
#   include <unistd.h>
#   include <sys/time.h>
#  endif /* __linux__ */
#
#  /* Platform-specific headers... */
#  if defined (LIBWINDOW_X11)
#   include <X11/X.h>
#   include <X11/Xlib.h>
#   include <X11/Xatom.h>
#   include <X11/Xutil.h>
#   include <X11/XKBlib.h>
#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)
#   include <windows.h>
#  endif /* LIBWINDOW_WIN32 */
#
#  /* Platform-specific types... */
#  if defined (LIBWINDOW_X11)

/* SECTION: Types
 * * * * * * * * */

/* MODULE: Window */

struct s_window {
    struct {
        Display *display;
        XID     root_id,
                window_id,
                screen_id;
    } xlib;

    struct {
        XVisualInfo visual;
    } xutil;

    struct {
        XID     wm_delete_window;
    } xatom;

    struct {
        /* Let's predefine the size of the queue to 1024, just for now */
        t_event queue[1024];
        size_t  count;
    } eventQueue;
};

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

struct s_window {
    struct {
        HANDLE      hinstance;
        HANDLE      hwnd;
        WNDCLASS    wndclass;
    } win32;

    struct {
        /* Let's predefine the size of the queue to 1024, just for now */
        t_event queue[1024];
        size_t  count;
    } eventQueue;
};

#  endif /* LIBWINDOW_WIN32 */
#
#  /* Platform-specific implementation... */
#  if defined (LIBWINDOW_X11)

/* SECTION: Internal API
 * * * * * * * * * * * */

/* MODULE: Event */

static bool lw_pollEventsPlatform(t_window);



/* SECTION: API
 * * * * * * * */

/* MODULE: Window */

LIBWINDOW_API bool  lw_createWindow(t_window *result, const size_t width, const size_t height, const char *title) {
    XSetWindowAttributes    attr;
    t_window                window;

    window = (t_window) calloc(1, sizeof(struct s_window));
    if (!window) { return (false); }

    window->xlib.display = XOpenDisplay(0);
    if (!window->xlib.display) { return (false); }
    
    window->xlib.root_id = XDefaultRootWindow(window->xlib.display);
    if (!window->xlib.root_id) { return (false); }

    window->xlib.screen_id = XDefaultScreen(window->xlib.display);

    window->xutil.visual.visual = XDefaultVisual(window->xlib.display, window->xlib.screen_id);
    if (!window->xutil.visual.visual) { return (false); }
    if (!XMatchVisualInfo(window->xlib.display, window->xlib.screen_id, 24, TrueColor, &window->xutil.visual)) { return (false); }

    attr = (XSetWindowAttributes) { 0 };
    attr.background_pixel = 0;
    attr.event_mask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | ExposureMask | ClientMessage;
    attr.colormap = XCreateColormap(window->xlib.display, window->xlib.root_id, window->xutil.visual.visual, AllocNone);
    if (!attr.colormap) { return (false); }

    window->xlib.window_id = XCreateWindow(window->xlib.display, window->xlib.root_id, 0, 0, width, height, 0, window->xutil.visual.depth, InputOutput, window->xutil.visual.visual, CWColormap | CWBorderPixel | CWBackPixel | CWEventMask, &attr); 
    if (!window->xlib.window_id) { return (false); }

    window->xatom.wm_delete_window = XInternAtom(window->xlib.display, "WM_DELETE_WINDOW", false);
    if (!window->xatom.wm_delete_window) { return (false); }

    XSetWMProtocols(window->xlib.display, window->xlib.window_id, &window->xatom.wm_delete_window, 1);
    XSelectInput(window->xlib.display, window->xlib.window_id, attr.event_mask);
    XStoreName(window->xlib.display, window->xlib.window_id, title);
    XMapWindow(window->xlib.display, window->xlib.window_id);

    *result = window;
    return (true);
}

LIBWINDOW_API bool  lw_destroyWindow(t_window window) {
    /* Safety check... */
    if (!window) { return (false); }

    /* memory-safe x11 disposal... */
    if (window->xlib.window_id) { XDestroyWindow(window->xlib.display, window->xlib.window_id), window->xlib.window_id = 0; }
    if (window->xlib.display)   { XCloseDisplay(window->xlib.display), window->xlib.display = 0; }

    free(window);
    return (true);
}

LIBWINDOW_API bool  lw_getWindowSize(t_window window, size_t *width, size_t *height) {
    XWindowAttributes   attr;

    /* Safety check... */
    if (!window) { return (false); }
    if (!XGetWindowAttributes(window->xlib.display, window->xlib.window_id, &attr)) { return (false); }
    if (width) { *width = attr.width; }
    if (height) { *height = attr.height; }
    return (true);
}

LIBWINDOW_API bool  lw_setWindowSize(t_window window, const size_t width, const size_t height) {
    /* Safety check... */
    if (!window) { return (false); }
    if (!XResizeWindow(window->xlib.display, window->xlib.window_id, width, height)) { return (false); }
    return (true);
}

LIBWINDOW_API bool  lw_setWindowMinSize(t_window window, const size_t width, const size_t height) {
    XSizeHints  hints;
    int64_t     supp;

    /* Safety check... */
    if (!window) { return (false); }
    
    XGetWMNormalHints(window->xlib.display, window->xlib.window_id, &hints, &supp);
    hints.flags = PMinSize;
    hints.min_width = width > 0 ? width : 1;
    hints.min_height = height > 0 ? height : 1;
    XSetWMNormalHints(window->xlib.display, window->xlib.window_id, &hints);
    return (true);
}

LIBWINDOW_API bool  lw_setWindowMaxSize(t_window window, const size_t width, const size_t height) {
    XSizeHints  hints;
    int64_t     supp;

    /* Safety check... */
    if (!window) { return (false); }
    
    XGetWMNormalHints(window->xlib.display, window->xlib.window_id, &hints, &supp);
    hints.flags = PMaxSize;
    hints.max_width = width > 0 ? width : 1;
    hints.max_height = height > 0 ? height : 1;
    XSetWMNormalHints(window->xlib.display, window->xlib.window_id, &hints);
    return (true);
}

LIBWINDOW_API bool  lw_getWindowPosition(t_window window, size_t *x, size_t *y) {
    XWindowAttributes   attr;

    /* Safety check... */
    if (!window) { return (false); }
    if (!XGetWindowAttributes(window->xlib.display, window->xlib.window_id, &attr)) { return (false); }
    if (x) { *x = attr.x; }
    if (y) { *y = attr.y; }
    return (true);
}

LIBWINDOW_API bool  lw_setWindowPosition(t_window window, const size_t x, const size_t y) {
    XSizeHints  hints;
    int64_t     supp;

    /* Safety check... */
    if (!window) { return (false); }
    
    XGetWMNormalHints(window->xlib.display, window->xlib.window_id, &hints, &supp);
    hints.flags = PPosition;
    hints.x = x;
    hints.y = y;
    XSetWMNormalHints(window->xlib.display, window->xlib.window_id, &hints);
    return (true);
}

LIBWINDOW_API bool  lw_getWindowTitle(t_window window, char *title, const size_t size) {
    char    *fetch;

    /* Safety check... */
    if (!window) { return (false); }
    if (!XFetchName(window->xlib.display, window->xlib.window_id, &fetch)) { return (false); }
    title = strncpy(title, fetch, size);
    title[size - 1] = 0;
    XFree(fetch);
    return (true);
}

LIBWINDOW_API bool  lw_setWindowTitle(t_window window, const char *title) {
    /* Safety check... */
    if (!window) { return (false); }
    if (!XStoreName(window->xlib.display, window->xlib.window_id, title)) { return (false); }
    return (true);
}

LIBWINDOW_API void  *lw_getWindowProp(t_window window, const uint64_t prop) {
    /* Safety check... */
    if (!window) { return (0); }

    switch (prop) {
        case (LW_PROP_X11_DISPLAY): { return (window->xlib.display); }
        case (LW_PROP_X11_ROOT_ID): { return (&window->xlib.root_id); }
        case (LW_PROP_X11_WINDOW_ID): { return (&window->xlib.window_id); }
        case (LW_PROP_X11_SCREEN_ID): { return (&window->xlib.screen_id); }
    }

    return (0);
}



/* MODULE: Event */

LIBWINDOW_API bool  lw_pollEvents(t_window window, t_event *event) {
    /* Safety check... */
    if (!window) { return (false); }

    /* Step 1: Polling events from 'window' queue... */
    if (lw_popEvent(window, event)) { return (true); }

    /* Step 2: Polling events from platform's queue... */
    lw_pollEventsPlatform(window);
    memset(event, 0, sizeof(t_event));
    return (false);
}

LIBWINDOW_API bool  lw_pushEvent(t_window window, t_event *event) {
    /* Safety checks... */
    if (!window || !event || !event->type) { return (false); }
    if (window->eventQueue.count >= 1024) { return (false); }

    /* Push the event to the end of the queue... */
    window->eventQueue.queue[window->eventQueue.count++] = *event;
    return (true);
}

LIBWINDOW_API bool  lw_popEvent(t_window window, t_event *result) {
    /* Safety checks... */
    if (!window || !result) { return (false); }
    if (!window->eventQueue.count) { return (false); }

    /* Pop an event from the start of the queue... */
    memcpy(result, &window->eventQueue.queue[0], sizeof(t_event));

    /* ...and move all the previous events by one backwards (with setting the last element to 'none'). */
    memmove(&window->eventQueue.queue[0], &window->eventQueue.queue[1], window->eventQueue.count-- * sizeof(t_event));
    memset(&window->eventQueue.queue[window->eventQueue.count], 0, sizeof(t_event));

    return (true);
}

LIBWINDOW_API bool  lw_flushEvent(t_window window) {
    /* Safety check... */
    if (!window) { return (false); }
    if (!XFlush(window->xlib.display)) { return (false); }
    return (true);
}



/* MODULE: Time */

LIBWINDOW_API uint64_t  lw_getTime(void) {
    struct timeval  time;

    gettimeofday(&time, 0);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

LIBWINDOW_API bool  lw_waitTime(uint64_t ms) {
    uint64_t    t;

    t = lw_getTime();
    while ((lw_getTime() - t) < ms);

    return (true);
}



/* SECTION: Internal API
 * * * * * * * * * * * */

/* MODULE: Event */

static bool lw_pollEventsPlatform(t_window window) {
    XEvent  xevent;

    if (!window) { return (false); }
    while (XPending(window->xlib.display)) {
        XNextEvent(window->xlib.display, &xevent);
        
        switch (xevent.type) {
            case (ClientMessage): {
                if (xevent.xclient.data.l[0] == (long) window->xatom.wm_delete_window) {
                    t_event event;

                    event = (t_event) {
                        .type = LW_EVENT_QUIT,
                        .quit = (t_quitEvent) {
                            .type = LW_EVENT_QUIT,
                            .time = lw_getTime(),
                            .window = window,
                        }
                    };
                    lw_pushEvent(window, &event);
                }
            } break;

            case (KeyPress):
            case (KeyRelease): {
                t_event     event;
                uint32_t    key;

                key = XkbKeycodeToKeysym(window->xlib.display, xevent.xkey.keycode, 0, xevent.xkey.state & ShiftMask ? 1 : 0);
                event = (t_event) {
                    .type = LW_EVENT_KEY,
                    .key = (t_keyEvent) {
                        .type = LW_EVENT_KEY,
                        .time = lw_getTime(),
                        .window = window,
                        .key = key, /* temporary solution (until I implement a keymap map) */
                        .state = xevent.xkey.state == KeyPress ? true : false,
                    }
                };
                lw_pushEvent(window, &event);
            } break;

            case (ButtonPress):
            case (ButtonRelease): {
                t_event event;

                /* Handle scroll event... */
                if (xevent.xbutton.button == 4 || xevent.xbutton.button == 5) {
                    /* Implement scrolling here... */
                    event = (t_event) { 0 };
                }
                /* Handle input event... */
                else {
                    uint8_t button;
                    
                    if (xevent.xbutton.button == 1) { button = LW_BUTTON_LEFT; }
                    else if (xevent.xbutton.button == 2) { button = LW_BUTTON_MIDDLE; }
                    else if (xevent.xbutton.button == 3) { button = LW_BUTTON_RIGHT; }
                    event = (t_event) {
                        .type = LW_EVENT_BUTTON,
                        .button = (t_buttonEvent) {
                            .type = LW_EVENT_BUTTON,
                            .time = lw_getTime(),
                            .window = window,
                            .button = button,
                            .x = (uint32_t) xevent.xbutton.x,
                            .y = (uint32_t) xevent.xbutton.y,
                            .state = xevent.xkey.state == KeyPress ? true : false,
                        }
                    };
                }
                lw_pushEvent(window, &event);

            } break;

            case (MotionNotify): {
                t_event event;
                
                event = (t_event) {
                    .type = LW_EVENT_MOTION,
                    .motion = (t_motionEvent) {
                        .type = LW_EVENT_MOTION,
                        .time = lw_getTime(),
                        .window = window,
                        .x = (uint32_t) xevent.xmotion.x,
                        .xrel = (uint32_t) xevent.xmotion.x_root,
                        .y = (uint32_t) xevent.xmotion.y,
                        .yrel = (uint32_t) xevent.xmotion.y_root,
                    }
                };
                lw_pushEvent(window, &event);
            } break;
        }
    }
    return (true);
}

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

/* SECTION: Internal API
 * * * * * * * * * * * */

/* MODULE: Window */

static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);



/* SECTION: API
 * * * * * * * */

/* MODULE: Window */

LIBWINDOW_API bool  lw_createWindow(t_window *result, const size_t width, const size_t height, const char *title) {
    STARTUPINFO startupinfo;
    t_window    window;

    window = (t_window) calloc(1, sizeof(struct s_window));
    if (!window) { return (false); }

    window->win32.hinstance = GetModuleHandle(0);
    if (!window->win32.hinstance) { return (false); }

    window->win32.wndclass = (WNDCLASS) { 0 };
    window->win32.wndclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
    window->win32.wndclass.lpfnWndProc = WindowProc;
    window->win32.wndclass.hInstance = window->win32.hinstance;
    window->win32.wndclass.lpszClassName = title;
    if (!RegisterClass(&window->win32.wndclass)) { return (false); }

    window->win32.hwnd = CreateWindowEx(0, window->win32.wndclass.lpszClassName, title, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, window->win32.hinstance, window);
    if (!window->win32.hwnd) { return (false); }

    GetStartupInfo(&startupinfo);
    ShowWindow(window->win32.hwnd, startupinfo.wShowWindow);

    *result = window;
    return (true);
}

LIBWINDOW_API bool  lw_destroyWindow(t_window window) {
    /* Safety check... */
    if (!window) { return (false); }

    PostQuitMessage(0);
    free(window);
    return (true);
}

LIBWINDOW_API bool  lw_getWindowSize(t_window, size_t *, size_t *);
LIBWINDOW_API bool  lw_setWindowSize(t_window, const size_t, const size_t);
LIBWINDOW_API bool  lw_setWindowMinSize(t_window, const size_t, const size_t);
LIBWINDOW_API bool  lw_setWindowMaxSize(t_window, const size_t, const size_t);

LIBWINDOW_API bool  lw_getWindowPosition(t_window, size_t *, size_t *);
LIBWINDOW_API bool  lw_setWindowPosition(t_window, const size_t, const size_t);

LIBWINDOW_API bool  lw_getWindowTitle(t_window, char *, const size_t);
LIBWINDOW_API bool  lw_setWindowTitle(t_window, const char *);

LIBWINDOW_API void  *lw_getWindowProp(t_window window, const uint64_t prop) {
    /* Safety check... */
    if (!window) { return (0); }

    switch (prop) {
        case (LW_PROP_WIN32_HWND): { return (window->win32.hwnd); }
        case (LW_PROP_WIN32_HINSTANCE): { return (window->win32.hinstance); }
    }

    return (0);
}

/* MODULE: Event */

LIBWINDOW_API bool  lw_pollEvents(t_window window, t_event *event) {
    MSG msg;

    /* Safety check... */
    if (!window) { return (false); }

    /* Step 1: Polling events from 'window' queue... */
    if (lw_popEvent(window, event)) { return (true); }

    /* Step 2: Polling events from platform's queue... */
    while (GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    memset(event, 0, sizeof(t_event));
    return (false);
}

LIBWINDOW_API bool  lw_pushEvent(t_window window, t_event *event) {
    /* Safety checks... */
    if (!window || !event || !event->type) { return (false); }
    if (window->eventQueue.count >= 1024) { return (false); }

    /* Push the event to the end of the queue... */
    window->eventQueue.queue[window->eventQueue.count++] = *event;
    return (true);
}

LIBWINDOW_API bool  lw_popEvent(t_window window, t_event *result) {
    /* Safety checks... */
    if (!window || !result) { return (false); }
    if (!window->eventQueue.count) { return (false); }

    /* Pop an event from the start of the queue... */
    memcpy(result, &window->eventQueue.queue[0], sizeof(t_event));

    /* ...and move all the previous events by one backwards (with setting the last element to 'none'). */
    memmove(&window->eventQueue.queue[0], &window->eventQueue.queue[1], window->eventQueue.count-- * sizeof(t_event));
    memset(&window->eventQueue.queue[window->eventQueue.count], 0, sizeof(t_event));

    return (true);
}

LIBWINDOW_API bool  lw_flushEvent(t_window);

/* MODULE: Time */

LIBWINDOW_API uint64_t  lw_getTime(void) {
    SYSTEMTIME  systemtime;

    GetSystemTime(&systemtime);
    return (systemtime.wMilliseconds);
}

LIBWINDOW_API bool  lw_waitTime(uint64_t ms) {
    uint64_t    t;

    t = lw_getTime();
    while ((lw_getTime() - t) < ms);

    return (true);
}



/* SECTION: Internal API
 * * * * * * * * * * * */

/* MODULE: Window */

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT     result;
    t_window    window;

    result = 0;
    window = 0;
    if (uMsg == WM_CREATE) {
        CREATESTRUCT    *pCreateStruct;

        pCreateStruct = (CREATESTRUCT *) lParam;
        window = (t_window) pCreateStruct->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR) window);
    }
    else {
        LONG_PTR    lPtr;

        lPtr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
        window = (t_window) lPtr;
    }

    switch (uMsg) {
        case (WM_CLOSE):
        case (WM_DESTROY): {
            t_event event;

            event = (t_event) {
                .type = LW_EVENT_QUIT,
                .quit = (t_quitEvent) {
                    .type = LW_EVENT_QUIT,
                    .time = lw_getTime(),
                    .window = window,
                }
            };
            lw_pushEvent(window, &event);
        } break;

        default: { result = DefWindowProc(window->win32.hwnd, uMsg, wParam, lParam); } break;
    }
    return (result);
}

#  endif /* LIBWINDOW_WIN32 */
# endif /* LIBWINDOW_IMPLEMENTATION */
#endif /* _libwindow_h_ */
