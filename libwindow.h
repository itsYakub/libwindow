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



/* SECTION: API
 * * * * * * * */

/* MODULE: Window  */
/* * * * * * * * * */

typedef struct s_window     *t_window;

LIBWINDOW_API bool  lw_createWindow(t_window *, const size_t, const size_t, const char *);
LIBWINDOW_API bool  lw_destroyWindow(t_window);

/* MODULE: Event */
/* * * * * * * * */

enum {
    LW_EVENT_NONE = 0,
    LW_EVENT_QUIT,
    LW_EVENT_USER,

    /* ... */
    LW_EVENT_COUNT
};

struct s_eventQuit {
    uint32_t    type;
    uint32_t    time;
};

typedef struct s_eventQuit  t_eventQuit;

struct s_eventUser {
    uint32_t    type;
    uint32_t    time;

    union {
        uint8_t     b[64];
        uint16_t    s[32];
        uint32_t    i[16];
        uint64_t    l[8];
    } data;
};

typedef struct s_eventUser  t_eventUser;

struct s_event {
    uint32_t        type;
    union {
        t_eventQuit quit;
        t_eventUser user;
    };
};

typedef struct s_event      t_event;

LIBWINDOW_API bool  lw_pollEvents(t_window, t_event *);
LIBWINDOW_API bool  lw_pushEvent(t_window, t_event *);
LIBWINDOW_API bool  lw_popEvent(t_window, t_event *);
LIBWINDOW_API bool  lw_flushEvent(t_window);

# if defined LIBWINDOW_IMPLEMENTATION
#  include <stdlib.h>
#  include <string.h>
#
#  if defined (LIBWINDOW_X11)
#   include <X11/X.h>
#   include <X11/Xlib.h>
#   include <X11/Xatom.h>
#   include <X11/Xutil.h>
#   if defined (LIBWINDOW_OPENGL)
#    include <GL/glx.h>
#    include <GL/glxext.h>
#   endif /* LIBWINDOW_OPENGL */

struct s_window {
    struct {
        Display *display;
        XID     root_id,
                window_id;
    } xlib;

    struct {
        XID     wm_delete_window;
    } xatom;

    struct {
        /* Let's predefine the size of the queue to 128, just for now */
        t_event queue[128];
        size_t  count;
    } eventQueue;
};

typedef struct s_window *t_window;

/* SECTION: Internal API
 * * * * * * * * * * * */

static bool lw_pollEventsWindow(t_window, t_event *);
static bool lw_pollEventsPlatform(t_window);

/* SECTION: API
 * * * * * * * */

/* MODULE: Window  */
/* * * * * * * * * */

LIBWINDOW_API bool  lw_createWindow(t_window *result, const size_t width, const size_t height, const char *title) {
    t_window    window;

    window = (t_window) calloc(1, sizeof(struct s_window));
    if (!window) { return (false); }

    window->xlib.display = XOpenDisplay(0);
    if (!window->xlib.display) { return (false); }
    
    window->xlib.root_id = XDefaultRootWindow(window->xlib.display);
    if (!window->xlib.root_id) { return (false); }

    window->xlib.window_id = XCreateSimpleWindow(window->xlib.display, window->xlib.root_id, 0, 0, width, height, 0, 0, 0);
    if (!window->xlib.window_id) { return (false); }

    window->xatom.wm_delete_window = XInternAtom(window->xlib.display, "WM_DELETE_WINDOW", false);
    if (!window->xatom.wm_delete_window) { return (false); }

    XSetWMProtocols(window->xlib.display, window->xlib.window_id, &window->xatom.wm_delete_window, 1);
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

/* MODULE: Event */
/* * * * * * * * */

LIBWINDOW_API bool  lw_pollEvents(t_window window, t_event *event) {
    /* Safety check... */
    if (!window) { return (false); }

    /* Step 1: Polling events from 'window' queue... */
    if (lw_pollEventsWindow(window, event)) { return (true); }

    /* Step 2: Polling events from platform's queue... */
    lw_pollEventsPlatform(window);
    memset(event, 0, sizeof(t_event));
    return (false);
}

LIBWINDOW_API bool  lw_pushEvent(t_window window, t_event *event) {
    /* Safety checks... */
    if (!window || !event || !event->type) { return (false); }
    if (window->eventQueue.count >= 128) { return (false); }

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

/* SECTION: Internal API
 * * * * * * * * * * * */

static bool lw_pollEventsWindow(t_window window, t_event *event) {
    /* Simple scenario:
     * - if safety checks fail, we return false;
     * - if there're no events (queue size is 0), we return false;
     * - if event was popped from the top of the queue, we return true;
     * */
    return (lw_popEvent(window, event));
}

static bool lw_pollEventsPlatform(t_window window) {
    XEvent  event;

    if (!window) { return (false); }
    while (XPending(window->xlib.display)) {
        XNextEvent(window->xlib.display, &event);
        
        switch (event.type) {
            case (ClientMessage): {
                if (event.xclient.data.l[0] == (long) window->xatom.wm_delete_window) {
                    t_event event;

                    event.type = LW_EVENT_QUIT;
                    lw_pushEvent(window, &event);
                }
            } break;
        }
    }
    return (true);
}

#  endif /* LIBWINDOW_X11 */
# endif /* LIBWINDOW_IMPLEMENTATION */
#endif /* _libwindow_h_ */
