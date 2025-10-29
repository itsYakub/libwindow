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
    LW_PROP_NONE                = 0x0000,

    LW_PROP_X11_DISPLAY         = 0x0001,
    LW_PROP_X11_ROOT_ID         = 0x0002,
    LW_PROP_X11_WINDOW_ID       = 0x0003,
    LW_PROP_X11_SCREEN_ID       = 0x0004,

    LW_PROP_WIN32_HWND          = 0x0005,
    LW_PROP_WIN32_HINSTANCE     = 0x0006,

    /* ... */

    LW_PROP_COUNT
};

typedef struct s_window     *t_window;

/* MODULE: Event */

enum {
    LW_EVENT_NONE               = 0x0000,
    LW_EVENT_QUIT               = 0x0001,
    LW_EVENT_KEY                = 0x0002,
    LW_EVENT_BUTTON             = 0x0003,
    LW_EVENT_MOTION             = 0x0004,
    LW_EVENT_RESIZE             = 0x0005,
    LW_EVENT_MOVE               = 0x0006,

    /* ... */
    
    LW_EVENT_COUNT
};

struct s_commonEvent {
    uint64_t    type;
    uint64_t    time;
    t_window    window;
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

struct s_resizeEvent {
    uint64_t    type;
    uint64_t    time;
    t_window    window;
    uint32_t    width;
    uint32_t    height;
};

struct s_moveEvent {
    uint64_t    type;
    uint64_t    time;
    t_window    window;
    uint32_t    x;
    uint32_t    y;
};

typedef struct s_commonEvent    t_commonEvent;
typedef struct s_quitEvent      t_quitEvent;
typedef struct s_keyEvent       t_keyEvent;
typedef struct s_buttonEvent    t_buttonEvent;
typedef struct s_motionEvent    t_motionEvent;
typedef struct s_resizeEvent    t_resizeEvent;
typedef struct s_moveEvent      t_moveEvent;

struct s_event {
    uint32_t            type;
    union {
        t_quitEvent     quit;
        t_keyEvent      key;
        t_buttonEvent   button;
        t_motionEvent   motion;
        t_resizeEvent   resize;
        t_moveEvent     move;
    };
};

typedef struct s_event  t_event;

/* MODULE: Input */

enum {
    LW_BUTTON_NONE              = 0x0000,
    LW_BUTTON_LEFT              = 0x0001, LW_LEFT_BUTTON     = LW_BUTTON_LEFT,
    LW_BUTTON_RIGHT             = 0x0002, LW_RIGHT_BUTTON    = LW_BUTTON_RIGHT,
    LW_BUTTON_MIDDLE            = 0x0003, LW_MIDDLE_BUTTON   = LW_BUTTON_MIDDLE,

    /* ... */
    
    LW_BUTTON_COUNT
};

enum {
    LW_KEY_NONE                 = 0x0000,

    /* ascii table... */        
    LW_KEY_SPACE                = 0x0020,
    LW_KEY_EXCLAM               = 0x0021,
    LW_KEY_DQUOTE               = 0x0022,
    LW_KEY_HASH                 = 0x0023,
    LW_KEY_DOLLAR               = 0x0024,
    LW_KEY_PERCENT              = 0x0025,
    LW_KEY_AMPERSAND            = 0x0026,
    LW_KEY_SQUOTE               = 0x0027,
    LW_KEY_PAREN_OPEN           = 0x0028,
    LW_KEY_PAREN_CLOSE          = 0x0029,
    LW_KEY_ASTERISK             = 0x002a,
    LW_KEY_PLUS                 = 0x002b,
    LW_KEY_COMMA                = 0x002c,
    LW_KEY_DASH                 = 0x002d,
    LW_KEY_PERIOD               = 0x002e,
    LW_KEY_SLASH                = 0x002f,
    LW_KEY_0                    = 0x0030,
    LW_KEY_1                    = 0x0031,
    LW_KEY_2                    = 0x0032,
    LW_KEY_3                    = 0x0033,
    LW_KEY_4                    = 0x0034,
    LW_KEY_5                    = 0x0035,
    LW_KEY_6                    = 0x0036,
    LW_KEY_7                    = 0x0037,
    LW_KEY_8                    = 0x0038,
    LW_KEY_9                    = 0x0039,
    LW_KEY_COLON                = 0x003a,
    LW_KEY_SEMICOLON            = 0x003b,
    LW_KEY_ANGLE_OPEN           = 0x003c,
    LW_KEY_EQUAL                = 0x003d,
    LW_KEY_ANGLE_CLOSE          = 0x003e,
    LW_KEY_QUESTION             = 0x003f,
    LW_KEY_AT                   = 0x0040,
    LW_KEY_A                    = 0x0041,
    LW_KEY_B                    = 0x0042,
    LW_KEY_C                    = 0x0043,
    LW_KEY_D                    = 0x0044,
    LW_KEY_E                    = 0x0045,
    LW_KEY_F                    = 0x0046,
    LW_KEY_G                    = 0x0047,
    LW_KEY_H                    = 0x0048,
    LW_KEY_I                    = 0x0049,
    LW_KEY_J                    = 0x004a,
    LW_KEY_K                    = 0x004b,
    LW_KEY_L                    = 0x004c,
    LW_KEY_M                    = 0x004d,
    LW_KEY_N                    = 0x004e,
    LW_KEY_O                    = 0x004f,
    LW_KEY_P                    = 0x0050,
    LW_KEY_Q                    = 0x0051,
    LW_KEY_R                    = 0x0052,
    LW_KEY_S                    = 0x0053,
    LW_KEY_T                    = 0x0054,
    LW_KEY_U                    = 0x0055,
    LW_KEY_V                    = 0x0056,
    LW_KEY_W                    = 0x0057,
    LW_KEY_X                    = 0x0058,
    LW_KEY_Y                    = 0x0059,
    LW_KEY_Z                    = 0x005a,
    LW_KEY_BRACE_OPEN           = 0x005b,
    LW_KEY_BACKSLASH            = 0x005c,
    LW_KEY_BRACE_CLOSE          = 0x005d,
    LW_KEY_CARET                = 0x005e,
    LW_KEY_UNDERSCORE           = 0x005f,
    LW_KEY_GRAVE                = 0x0060,
    LW_KEY_a                    = 0x0061,
    LW_KEY_b                    = 0x0062,
    LW_KEY_c                    = 0x0063,
    LW_KEY_d                    = 0x0064,
    LW_KEY_e                    = 0x0065,
    LW_KEY_f                    = 0x0066,
    LW_KEY_g                    = 0x0067,
    LW_KEY_h                    = 0x0068,
    LW_KEY_i                    = 0x0069,
    LW_KEY_j                    = 0x006a,
    LW_KEY_k                    = 0x006b,
    LW_KEY_l                    = 0x006c,
    LW_KEY_m                    = 0x006d,
    LW_KEY_n                    = 0x006e,
    LW_KEY_o                    = 0x006f,
    LW_KEY_p                    = 0x0070,
    LW_KEY_q                    = 0x0071,
    LW_KEY_r                    = 0x0072,
    LW_KEY_s                    = 0x0073,
    LW_KEY_t                    = 0x0074,
    LW_KEY_u                    = 0x0075,
    LW_KEY_v                    = 0x0076,
    LW_KEY_w                    = 0x0077,
    LW_KEY_x                    = 0x0078,
    LW_KEY_y                    = 0x0079,
    LW_KEY_z                    = 0x007a,
    LW_KEY_CURLY_OPEN           = 0x007b,
    LW_KEY_BAR                  = 0x007c,
    LW_KEY_CURLY_CLOSE          = 0x007d,
    LW_KEY_TILDE                = 0x007e,

    /* extended keycode list... */

    LW_KEY_ESCAPE               = 0x0100,
    LW_KEY_ENTER                = 0x0101,
    LW_KEY_TAB                  = 0x0102,
    LW_KEY_BACKSPACE            = 0x0103,
    LW_KEY_INSERT               = 0x0104,
    LW_KEY_DELETE               = 0x0105,
    LW_KEY_HOME                 = 0x0106,
    LW_KEY_END                  = 0x0107,
    LW_KEY_PAGE_UP              = 0x0108,
    LW_KEY_PAGE_DOWN            = 0x0109,
    LW_KEY_UP                   = 0x010a,
    LW_KEY_DOWN                 = 0x010b,
    LW_KEY_LEFT                 = 0x010c,
    LW_KEY_RIGHT                = 0x010d,
    LW_KEY_CAPSLOCK             = 0x010e,
    LW_KEY_SCROLLLOCK           = 0x010f,
    LW_KEY_PRINTSCREEN          = 0x0110,
    LW_KEY_F1                   = 0x0111,
    LW_KEY_F2                   = 0x0112,
    LW_KEY_F3                   = 0x0113,
    LW_KEY_F4                   = 0x0114,
    LW_KEY_F5                   = 0x0115,
    LW_KEY_F6                   = 0x0116,
    LW_KEY_F7                   = 0x0117,
    LW_KEY_F8                   = 0x0118,
    LW_KEY_F9                   = 0x0119,
    LW_KEY_F10                  = 0x011a,
    LW_KEY_F11                  = 0x011b,
    LW_KEY_F12                  = 0x011c,
    LW_KEY_F13                  = 0x011d,
    LW_KEY_F14                  = 0x011e,
    LW_KEY_F15                  = 0x011f,
    LW_KEY_F16                  = 0x0120,
    LW_KEY_F17                  = 0x0121,
    LW_KEY_F18                  = 0x0122,
    LW_KEY_F19                  = 0x0123,
    LW_KEY_F20                  = 0x0114,
    LW_KEY_F21                  = 0x0115,
    LW_KEY_F22                  = 0x0116,
    LW_KEY_F23                  = 0x0117,
    LW_KEY_F24                  = 0x0118,
    LW_KEY_F25                  = 0x0119,
    LW_KEY_SHIFT_LEFT           = 0x011a,
    LW_KEY_SHIFT_RIGHT          = 0x011b,
    LW_KEY_CTRL_LEFT            = 0x011c,
    LW_KEY_CTRL_RIGHT           = 0x011d,
    LW_KEY_ALT_LEFT             = 0x011e,
    LW_KEY_ALT_RIGHT            = 0x011f,
    LW_KEY_SUPER_LEFT           = 0x0120,
    LW_KEY_0_KP                 = 0x0121,
    LW_KEY_1_KP                 = 0x0122,
    LW_KEY_2_KP                 = 0x0123,
    LW_KEY_3_KP                 = 0x0124,
    LW_KEY_4_KP                 = 0x0125,
    LW_KEY_5_KP                 = 0x0126,
    LW_KEY_6_KP                 = 0x0127,
    LW_KEY_7_KP                 = 0x0128,
    LW_KEY_8_KP                 = 0x0129,
    LW_KEY_9_KP                 = 0x012a,
    LW_KEY_SUPER_RIGHT          = 0x012b,
    LW_KEY_NUMLOCK              = 0x012c,
    LW_KEY_MENU                 = 0x012d,

    /* ... */
    
    LW_KEY_COUNT
};

/* SECTION: API
 * * * * * * * */

/* MODULE: Window */

LIBWINDOW_API bool  lw_createWindow(t_window *, const size_t, const size_t, const char *);
LIBWINDOW_API bool  lw_destroyWindow(t_window);

LIBWINDOW_API bool  lw_showWindow(t_window);
LIBWINDOW_API bool  lw_hideWindow(t_window);

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




# if defined (LIBWINDOW_IMPLEMENTATION)
#
#  /* determine which platform to use... */
#  if !defined (LIBWINDOW_X11) && !defined (LIBWINDOW_WIN32)
#   if defined (__unix__)
#    if !defined (LIBWINDOW_NO_X11)
#     define LIBWINDOW_X11
#    endif /* LIBWINDOW_NO_X11 */
#   endif /* __unix__ */
#   if defined (_WIN32)
#    if !defined (LIBWINDOW_NO_WIN32)
#     define LIBWINDOW_WIN32
#    endif /* LIBWINDOW_NO_WIN32 */
#   endif /* _WIN32 */
#  endif /* LIBWINDOW_X11, LIBWINDOW_WIN32 */
#
#  /* platform-independent includes... */
#  include <stdlib.h>
#  include <time.h>
#  include <string.h>
#
#  /* platform-dependent includes... */
#  if defined (__unix__)
#   include <unistd.h>
#   include <sys/time.h>
#  endif /* __unix__ */
#  if defined (LIBWINDOW_X11)
#   include <X11/X.h>
#   include <X11/Xlib.h>
#   include <X11/Xatom.h>
#   include <X11/Xutil.h>
#   include <X11/XKBlib.h>
#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)
#   include <windows.h>
#   include <windowsx.h>
#  endif /* LIBWINDOW_WIN32 */


/* SECTION: Types
 * * * * * * * * */

/* MODULE: Window */

struct s_window {

#  if defined (LIBWINDOW_X11)

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

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)
    
    struct {
        HANDLE      hinstance,
                    hwnd;
        WNDCLASS    wndclass;
    } win32;

#  endif /* LIBWINDOW_WIN32 */

    struct {
        size_t  x, y;
        size_t  width,
                height;
    } data;

    struct {
        /* Let's predefine the size of the queue to 1024, just for now */
        t_event queue[1024];
        size_t  count;
    } eventQueue;
};



/* SECTION: Internal API
 * * * * * * * * * * * */

/* MODULE: Event */

#  if defined (LIBWINDOW_X11)

static bool lw_pollEventsPlatform(t_window);

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

#  endif /* LIBWINDOW_WIN32 */

/* MODULE: Input */

static bool lw_inputPlatformToLibrary(const uint64_t, uint64_t *);

/* SECTION: Global Variables
 * * * * * * * * * * * * * */

/* MODULE: Input */

static const struct s_keymap {
    uint64_t    library,
                platform;
} g_keymap[] = {
    { LW_KEY_NONE,          0x0000 },

#  if defined (LIBWINDOW_X11)

    { LW_KEY_SPACE,         XK_space },
    { LW_KEY_EXCLAM,        XK_exclam },
    { LW_KEY_DQUOTE,        XK_quotedbl },
    { LW_KEY_HASH,          XK_numbersign },
    { LW_KEY_DOLLAR,        XK_dollar },
    { LW_KEY_PERCENT,       XK_percent },
    { LW_KEY_AMPERSAND,     XK_ampersand },
    { LW_KEY_SQUOTE,        XK_apostrophe },
    { LW_KEY_PAREN_OPEN,    XK_parenleft },
    { LW_KEY_PAREN_CLOSE,   XK_parenright },
    { LW_KEY_ASTERISK,      XK_asterisk },
    { LW_KEY_PLUS,          XK_plus },
    { LW_KEY_COMMA,         XK_comma },
    { LW_KEY_DASH,          XK_minus },
    { LW_KEY_PERIOD,        XK_period },
    { LW_KEY_SLASH,         XK_slash },
    { LW_KEY_0,             XK_0 },
    { LW_KEY_1,             XK_1 },
    { LW_KEY_2,             XK_2 },
    { LW_KEY_3,             XK_3 },
    { LW_KEY_4,             XK_4 },
    { LW_KEY_5,             XK_5 },
    { LW_KEY_6,             XK_6 },
    { LW_KEY_7,             XK_7 },
    { LW_KEY_8,             XK_8 },
    { LW_KEY_9,             XK_9 },
    { LW_KEY_COLON,         XK_colon },
    { LW_KEY_SEMICOLON,     XK_semicolon },
    { LW_KEY_ANGLE_OPEN,    XK_less },
    { LW_KEY_EQUAL,         XK_equal },
    { LW_KEY_ANGLE_CLOSE,   XK_greater },
    { LW_KEY_QUESTION,      XK_underscore },
    { LW_KEY_AT,            XK_at },
    { LW_KEY_A,             XK_A },
    { LW_KEY_B,             XK_B },
    { LW_KEY_C,             XK_C },
    { LW_KEY_D,             XK_D },
    { LW_KEY_E,             XK_E },
    { LW_KEY_F,             XK_F },
    { LW_KEY_G,             XK_G },
    { LW_KEY_H,             XK_H },
    { LW_KEY_I,             XK_I },
    { LW_KEY_J,             XK_J },
    { LW_KEY_K,             XK_K },
    { LW_KEY_L,             XK_L },
    { LW_KEY_M,             XK_M },
    { LW_KEY_N,             XK_N },
    { LW_KEY_O,             XK_O },
    { LW_KEY_P,             XK_P },
    { LW_KEY_Q,             XK_Q },
    { LW_KEY_R,             XK_R },
    { LW_KEY_S,             XK_S },
    { LW_KEY_T,             XK_T },
    { LW_KEY_U,             XK_U },
    { LW_KEY_V,             XK_V },
    { LW_KEY_W,             XK_W },
    { LW_KEY_X,             XK_X },
    { LW_KEY_Y,             XK_Y },
    { LW_KEY_Z,             XK_Z },
    { LW_KEY_BRACE_OPEN,    XK_bracketleft },
    { LW_KEY_BACKSLASH,     XK_backslash },
    { LW_KEY_BRACE_CLOSE,   XK_bracketright },
    { LW_KEY_CARET,         XK_asciicircum },
    { LW_KEY_UNDERSCORE,    XK_underscore },
    { LW_KEY_GRAVE,         XK_grave },
    { LW_KEY_a,             XK_a },
    { LW_KEY_b,             XK_b },
    { LW_KEY_c,             XK_c },
    { LW_KEY_d,             XK_d },
    { LW_KEY_e,             XK_e },
    { LW_KEY_f,             XK_f },
    { LW_KEY_g,             XK_g },
    { LW_KEY_h,             XK_h },
    { LW_KEY_i,             XK_i },
    { LW_KEY_j,             XK_j },
    { LW_KEY_k,             XK_k },
    { LW_KEY_l,             XK_l },
    { LW_KEY_m,             XK_m },
    { LW_KEY_n,             XK_n },
    { LW_KEY_o,             XK_o },
    { LW_KEY_p,             XK_p },
    { LW_KEY_q,             XK_q },
    { LW_KEY_r,             XK_r },
    { LW_KEY_s,             XK_s },
    { LW_KEY_t,             XK_t },
    { LW_KEY_u,             XK_u },
    { LW_KEY_v,             XK_v },
    { LW_KEY_w,             XK_w },
    { LW_KEY_x,             XK_x },
    { LW_KEY_y,             XK_y },
    { LW_KEY_z,             XK_z },
    { LW_KEY_CURLY_OPEN,    XK_braceleft },
    { LW_KEY_BAR,           XK_bar },
    { LW_KEY_CURLY_CLOSE,   XK_braceright },
    { LW_KEY_TILDE,         XK_asciitilde },
    { LW_KEY_ESCAPE,        XK_Escape },
    { LW_KEY_ENTER,         XK_Return },
    { LW_KEY_TAB,           XK_Tab },
    { LW_KEY_BACKSPACE,     XK_BackSpace },
    { LW_KEY_INSERT,        XK_Insert },
    { LW_KEY_DELETE,        XK_Delete },
    { LW_KEY_HOME,          XK_Home },
    { LW_KEY_END,           XK_End },
    { LW_KEY_PAGE_UP,       XK_Prior },
    { LW_KEY_PAGE_DOWN,     XK_Next },
    { LW_KEY_UP,            XK_Up },
    { LW_KEY_DOWN,          XK_Down },
    { LW_KEY_LEFT,          XK_Left },
    { LW_KEY_RIGHT,         XK_Right },
    { LW_KEY_CAPSLOCK,      XK_Caps_Lock },
    { LW_KEY_SCROLLLOCK,    XK_Scroll_Lock },
    { LW_KEY_PRINTSCREEN,   XK_Print },
    { LW_KEY_F1,            XK_F1 },
    { LW_KEY_F2,            XK_F2 },
    { LW_KEY_F3,            XK_F3 },
    { LW_KEY_F4,            XK_F4 },
    { LW_KEY_F5,            XK_F5 },
    { LW_KEY_F6,            XK_F6 },
    { LW_KEY_F7,            XK_F7 },
    { LW_KEY_F8,            XK_F8 },
    { LW_KEY_F9,            XK_F9 },
    { LW_KEY_F10,           XK_F10 },
    { LW_KEY_F11,           XK_F11 },
    { LW_KEY_F12,           XK_F12 },
    { LW_KEY_F13,           XK_F13 },
    { LW_KEY_F14,           XK_F14 },
    { LW_KEY_F15,           XK_F15 },
    { LW_KEY_F16,           XK_F16 },
    { LW_KEY_F17,           XK_F17 },
    { LW_KEY_F18,           XK_F18 },
    { LW_KEY_F19,           XK_F19 },
    { LW_KEY_F20,           XK_F20 },
    { LW_KEY_F21,           XK_F21 },
    { LW_KEY_F22,           XK_F22 },
    { LW_KEY_F23,           XK_F23 },
    { LW_KEY_F24,           XK_F24 },
    { LW_KEY_F25,           XK_F25 },
    { LW_KEY_SHIFT_LEFT,    XK_Shift_L },
    { LW_KEY_SHIFT_RIGHT,   XK_Shift_R },
    { LW_KEY_CTRL_LEFT,     XK_Control_L },
    { LW_KEY_CTRL_RIGHT,    XK_Control_R },
    { LW_KEY_ALT_LEFT,      XK_Alt_L },
    { LW_KEY_ALT_RIGHT,     XK_Alt_R },
    { LW_KEY_SUPER_LEFT,    XK_Super_L },
    { LW_KEY_0_KP,          XK_KP_0 },
    { LW_KEY_1_KP,          XK_KP_1 },
    { LW_KEY_2_KP,          XK_KP_2 },
    { LW_KEY_3_KP,          XK_KP_3 },
    { LW_KEY_4_KP,          XK_KP_4 },
    { LW_KEY_5_KP,          XK_KP_5 },
    { LW_KEY_6_KP,          XK_KP_6 },
    { LW_KEY_7_KP,          XK_KP_7 },
    { LW_KEY_8_KP,          XK_KP_8 },
    { LW_KEY_9_KP,          XK_KP_9 },
    { LW_KEY_SUPER_RIGHT,   XK_Super_R },
    { LW_KEY_NUMLOCK,       XK_Num_Lock },
    { LW_KEY_MENU,          XK_Menu },

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

    { LW_KEY_SPACE,         VK_SPACE },
    { LW_KEY_0,             0x0030 },
    { LW_KEY_1,             0x0031 },
    { LW_KEY_2,             0x0032 },
    { LW_KEY_3,             0x0033 },
    { LW_KEY_4,             0x0034 },
    { LW_KEY_5,             0x0035 },
    { LW_KEY_6,             0x0036 },
    { LW_KEY_7,             0x0037 },
    { LW_KEY_8,             0x0038 },
    { LW_KEY_9,             0x0039 },
    { LW_KEY_PAREN_CLOSE,   0x0030 },
    { LW_KEY_EXCLAM,        0x0031 },
    { LW_KEY_AT,            0x0032 },
    { LW_KEY_HASH,          0x0033 },
    { LW_KEY_DOLLAR,        0x0034 },
    { LW_KEY_PERCENT,       0x0035 },
    { LW_KEY_CARET,         0x0036 },
    { LW_KEY_AMPERSAND,     0x0037 },
    { LW_KEY_ASTERISK,      0x0038 },
    { LW_KEY_PAREN_OPEN,    0x0039 },
    { LW_KEY_A,             0x0041 },
    { LW_KEY_B,             0x0042 },
    { LW_KEY_C,             0x0043 },
    { LW_KEY_D,             0x0044 },
    { LW_KEY_E,             0x0045 },
    { LW_KEY_F,             0x0046 },
    { LW_KEY_G,             0x0047 },
    { LW_KEY_H,             0x0048 },
    { LW_KEY_I,             0x0049 },
    { LW_KEY_J,             0x004a },
    { LW_KEY_K,             0x004b },
    { LW_KEY_L,             0x004c },
    { LW_KEY_M,             0x004d },
    { LW_KEY_N,             0x004e },
    { LW_KEY_O,             0x004f },
    { LW_KEY_P,             0x0050 },
    { LW_KEY_Q,             0x0051 },
    { LW_KEY_R,             0x0052 },
    { LW_KEY_S,             0x0053 },
    { LW_KEY_T,             0x0054 },
    { LW_KEY_U,             0x0055 },
    { LW_KEY_V,             0x0056 },
    { LW_KEY_W,             0x0057 },
    { LW_KEY_X,             0x0058 },
    { LW_KEY_Y,             0x0059 },
    { LW_KEY_Z,             0x005a },
    { LW_KEY_a,             0x0041 },
    { LW_KEY_b,             0x0042 },
    { LW_KEY_c,             0x0043 },
    { LW_KEY_d,             0x0044 },
    { LW_KEY_e,             0x0045 },
    { LW_KEY_f,             0x0046 },
    { LW_KEY_g,             0x0047 },
    { LW_KEY_h,             0x0048 },
    { LW_KEY_i,             0x0049 },
    { LW_KEY_j,             0x004a },
    { LW_KEY_k,             0x004b },
    { LW_KEY_l,             0x004c },
    { LW_KEY_m,             0x004d },
    { LW_KEY_n,             0x004e },
    { LW_KEY_o,             0x004f },
    { LW_KEY_p,             0x0050 },
    { LW_KEY_q,             0x0051 },
    { LW_KEY_r,             0x0052 },
    { LW_KEY_s,             0x0053 },
    { LW_KEY_t,             0x0054 },
    { LW_KEY_u,             0x0055 },
    { LW_KEY_v,             0x0056 },
    { LW_KEY_w,             0x0057 },
    { LW_KEY_x,             0x0058 },
    { LW_KEY_y,             0x0059 },
    { LW_KEY_z,             0x005a },
    { LW_KEY_SEMICOLON,     VK_OEM_1 },
    { LW_KEY_SLASH,         VK_OEM_2 },
    { LW_KEY_GRAVE,         VK_OEM_3 },
    { LW_KEY_BRACE_OPEN,    VK_OEM_4 },
    { LW_KEY_BACKSLASH,     VK_OEM_5 },
    { LW_KEY_BRACE_CLOSE,   VK_OEM_6 },
    { LW_KEY_SQUOTE,        VK_OEM_7 },
    { LW_KEY_COLON,         VK_OEM_1 },
    { LW_KEY_QUESTION,      VK_OEM_2 },
    { LW_KEY_TILDE,         VK_OEM_3 },
    { LW_KEY_CURLY_OPEN,    VK_OEM_4 },
    { LW_KEY_BAR,           VK_OEM_5 },
    { LW_KEY_CURLY_CLOSE,   VK_OEM_6 },
    { LW_KEY_DQUOTE,        VK_OEM_7 },
    { LW_KEY_EQUAL,         VK_OEM_PLUS },
    { LW_KEY_DASH,          VK_OEM_MINUS },
    { LW_KEY_COMMA,         VK_OEM_COMMA },
    { LW_KEY_PERIOD,        VK_OEM_PERIOD },
    { LW_KEY_PLUS,          VK_OEM_PLUS },
    { LW_KEY_UNDERSCORE,    VK_OEM_MINUS },
    { LW_KEY_ANGLE_OPEN,    VK_OEM_COMMA },
    { LW_KEY_ANGLE_CLOSE,   VK_OEM_PERIOD },
    { LW_KEY_ESCAPE,        VK_ESCAPE },
    { LW_KEY_ENTER,         VK_RETURN },
    { LW_KEY_TAB,           VK_TAB },
    { LW_KEY_BACKSPACE,     VK_BACK },
    { LW_KEY_INSERT,        VK_INSERT },
    { LW_KEY_DELETE,        VK_DELETE },
    { LW_KEY_HOME,          VK_HOME },
    { LW_KEY_END,           VK_END },
    { LW_KEY_PAGE_UP,       VK_PRIOR },
    { LW_KEY_PAGE_DOWN,     VK_NEXT },
    { LW_KEY_UP,            VK_UP },
    { LW_KEY_DOWN,          VK_DOWN },
    { LW_KEY_LEFT,          VK_LEFT },
    { LW_KEY_RIGHT,         VK_RIGHT },
    { LW_KEY_CAPSLOCK,      VK_CAPITAL },
    { LW_KEY_SCROLLLOCK,    VK_SCROLL },
    { LW_KEY_PRINTSCREEN,   VK_SNAPSHOT },
    { LW_KEY_F1,            VK_F1 },
    { LW_KEY_F2,            VK_F2 },
    { LW_KEY_F3,            VK_F3 },
    { LW_KEY_F4,            VK_F4 },
    { LW_KEY_F5,            VK_F5 },
    { LW_KEY_F6,            VK_F6 },
    { LW_KEY_F7,            VK_F7 },
    { LW_KEY_F8,            VK_F8 },
    { LW_KEY_F9,            VK_F9 },
    { LW_KEY_F10,           VK_F10 },
    { LW_KEY_F11,           VK_F11 },
    { LW_KEY_F12,           VK_F12 },
    { LW_KEY_F13,           VK_F13 },
    { LW_KEY_F14,           VK_F14 },
    { LW_KEY_F15,           VK_F15 },
    { LW_KEY_F16,           VK_F16 },
    { LW_KEY_F17,           VK_F17 },
    { LW_KEY_F18,           VK_F18 },
    { LW_KEY_F19,           VK_F19 },
    { LW_KEY_F20,           VK_F20 },
    { LW_KEY_F21,           VK_F21 },
    { LW_KEY_F22,           VK_F22 },
    { LW_KEY_F23,           VK_F23 },
    { LW_KEY_F24,           VK_F24 },
    { LW_KEY_F25,           LW_KEY_NONE }, /* no equivalent on win32 platform... */
    { LW_KEY_SHIFT_LEFT,    VK_SHIFT },
    { LW_KEY_SHIFT_RIGHT,   VK_SHIFT },
    { LW_KEY_CTRL_LEFT,     VK_CONTROL },
    { LW_KEY_CTRL_RIGHT,    VK_CONTROL },
    { LW_KEY_ALT_LEFT,      VK_MENU },
    { LW_KEY_ALT_RIGHT,     VK_RMENU },
    { LW_KEY_SUPER_LEFT,    VK_LWIN },
    { LW_KEY_0_KP,          VK_NUMPAD0 },
    { LW_KEY_1_KP,          VK_NUMPAD1 },
    { LW_KEY_2_KP,          VK_NUMPAD2 },
    { LW_KEY_3_KP,          VK_NUMPAD3 },
    { LW_KEY_4_KP,          VK_NUMPAD4 },
    { LW_KEY_5_KP,          VK_NUMPAD5 },
    { LW_KEY_6_KP,          VK_NUMPAD6 },
    { LW_KEY_7_KP,          VK_NUMPAD7 },
    { LW_KEY_8_KP,          VK_NUMPAD8 },
    { LW_KEY_9_KP,          VK_NUMPAD9 },
    { LW_KEY_SUPER_RIGHT,   VK_RWIN },
    { LW_KEY_NUMLOCK,       VK_NUMLOCK },
    { LW_KEY_MENU,          VK_MENU },

#  endif /* LIBWINDOW_WIN32 */

    { LW_KEY_COUNT,         0 }
};



/* SECTION: API
 * * * * * * * */

/* MODULE: Window */

LIBWINDOW_API bool  lw_createWindow(t_window *result, const size_t width, const size_t height, const char *title) {
    t_window    window;

    window = (t_window) calloc(1, sizeof(struct s_window));
    if (!window) { return (false); }

#  if defined (LIBWINDOW_X11)

    XSetWindowAttributes    attr;

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
    attr.event_mask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | ExposureMask | StructureNotifyMask | ClientMessage;
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

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

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

    ShowWindow(window->win32.hwnd, SW_SHOW);

#  endif /* LIBWINDOW_WIN32 */

    if (!lw_getWindowPosition(window, &window->data.x, &window->data.y)) { return (false); }
    if (!lw_getWindowSize(window, &window->data.width, &window->data.height)) { return (false); }
    *result = window;
    return (true);
}

LIBWINDOW_API bool  lw_destroyWindow(t_window window) {
    /* Safety check... */
    if (!window) { return (false); }

#  if defined (LIBWINDOW_X11)

    /* memory-safe x11 disposal... */
    if (window->xlib.window_id) { XDestroyWindow(window->xlib.display, window->xlib.window_id), window->xlib.window_id = 0; }
    if (window->xlib.display)   { XCloseDisplay(window->xlib.display), window->xlib.display = 0; }

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)
    
    PostQuitMessage(0);

#  endif /* LIBWINDOW_WIN32 */

    free(window);
    return (true);
}

LIBWINDOW_API bool  lw_showWindow(t_window window) {
    /* Safety check... */
    if (!window) { return (false); }

#  if defined (LIBWINDOW_X11)

    XMapWindow(window->xlib.display, window->xlib.window_id);

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

    ShowWindow(window->win32.hwnd, SW_SHOW);

#  endif /* LIBWINDOW_WIN32 */

    return (true);
}

LIBWINDOW_API bool  lw_hideWindow(t_window window) {
    /* Safety check... */
    if (!window) { return (false); }

#  if defined (LIBWINDOW_X11)

    XUnmapWindow(window->xlib.display, window->xlib.window_id);

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

    ShowWindow(window->win32.hwnd, SW_HIDE);

#  endif /* LIBWINDOW_WIN32 */

    return (true);
}

LIBWINDOW_API bool  lw_getWindowSize(t_window window, size_t *width, size_t *height) {
    /* Safety check... */
    if (!window) { return (false); }

#  if defined (LIBWINDOW_X11)
    
    XWindowAttributes   attr;
    
    if (!XGetWindowAttributes(window->xlib.display, window->xlib.window_id, &attr)) { return (false); }
    if (width) { *width = attr.width; }
    if (height) { *height = attr.height; }

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

    RECT    area;

    if (!GetClientRect(window->win32.hwnd, &area)) { return (false); }
    if (width) { *width = area.right; }
    if (height) { *height = area.bottom; }

#  endif /* LIBWINDOW_WIN32 */
    
    return (true);
}

LIBWINDOW_API bool  lw_setWindowSize(t_window window, const size_t width, const size_t height) {
    /* Safety check... */
    if (!window) { return (false); }

#  if defined (LIBWINDOW_X11)

    if (!XResizeWindow(window->xlib.display, window->xlib.window_id, width, height)) { return (false); }

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

    (void) width;
    (void) height;

#  endif /* LIBWINDOW_WIN32 */
    
    /* update internal window values... */
    window->data.width = width;
    window->data.height = height;

    return (true);
}

LIBWINDOW_API bool  lw_setWindowMinSize(t_window window, const size_t width, const size_t height) {
    /* Safety check... */
    if (!window) { return (false); }

#  if defined (LIBWINDOW_X11)

    XSizeHints  hints;
    int64_t     supp;
    
    XGetWMNormalHints(window->xlib.display, window->xlib.window_id, &hints, &supp);
    hints.flags = PMinSize;
    hints.min_width = width > 0 ? width : 1;
    hints.min_height = height > 0 ? height : 1;
    XSetWMNormalHints(window->xlib.display, window->xlib.window_id, &hints);

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

    (void) width;
    (void) height;

#  endif /* LIBWINDOW_WIN32 */

    return (true);
}

LIBWINDOW_API bool  lw_setWindowMaxSize(t_window window, const size_t width, const size_t height) {
    /* Safety check... */
    if (!window) { return (false); }

#  if defined (LIBWINDOW_X11)
    
    XSizeHints  hints;
    int64_t     supp;

    XGetWMNormalHints(window->xlib.display, window->xlib.window_id, &hints, &supp);
    hints.flags = PMaxSize;
    hints.max_width = width > 0 ? width : 1;
    hints.max_height = height > 0 ? height : 1;
    XSetWMNormalHints(window->xlib.display, window->xlib.window_id, &hints);

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

    (void) width;
    (void) height;

#  endif /* LIBWINDOW_WIN32 */

    return (true);
}

LIBWINDOW_API bool  lw_getWindowPosition(t_window window, size_t *x, size_t *y) {
    /* Safety check... */
    if (!window) { return (false); }

#  if defined (LIBWINDOW_X11)
    
    XWindowAttributes   attr;

    if (!XGetWindowAttributes(window->xlib.display, window->xlib.window_id, &attr)) { return (false); }
    if (x) { *x = attr.x; }
    if (y) { *y = attr.y; }

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

    RECT    area;

    if (!GetClientRect(window->win32.hwnd, &area)) { return (false); }
    if (x) { *x = area.left; }
    if (y) { *y = area.top; }

#  endif /* LIBWINDOW_WIN32 */

    return (true);
}

LIBWINDOW_API bool  lw_setWindowPosition(t_window window, const size_t x, const size_t y) {
    /* Safety check... */
    if (!window) { return (false); } 

#  if defined (LIBWINDOW_X11)
    
    XSizeHints  hints;
    int64_t     supp;

    XGetWMNormalHints(window->xlib.display, window->xlib.window_id, &hints, &supp);
    hints.flags = PPosition;
    hints.x = x;
    hints.y = y;
    XSetWMNormalHints(window->xlib.display, window->xlib.window_id, &hints);

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

    (void) x;
    (void) y;

#  endif /* LIBWINDOW_WIN32 */

    return (true);
}

LIBWINDOW_API bool  lw_getWindowTitle(t_window window, char *title, const size_t size) {
    /* Safety check... */
    if (!window) { return (false); }

#  if defined (LIBWINDOW_X11)
    
    char    *fetch;

    if (!XFetchName(window->xlib.display, window->xlib.window_id, &fetch)) { return (false); }
    title = strncpy(title, fetch, size);
    title[size - 1] = 0;
    XFree(fetch);

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

    (void) title;
    (void) size;

#  endif /* LIBWINDOW_WIN32 */

    return (true);
}

LIBWINDOW_API bool  lw_setWindowTitle(t_window window, const char *title) {
    /* Safety check... */
    if (!window) { return (false); }

#  if defined (LIBWINDOW_X11)
    
    if (!XStoreName(window->xlib.display, window->xlib.window_id, title)) { return (false); }

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

    (void) title;

#  endif /* LIBWINDOW_WIN32 */

    return (true);
}

LIBWINDOW_API void  *lw_getWindowProp(t_window window, const uint64_t prop) {
    /* Safety check... */
    if (!window) { return (0); }

    switch (prop) {

#  if defined (LIBWINDOW_X11)
    
        case (LW_PROP_X11_DISPLAY): { return (window->xlib.display); }
        case (LW_PROP_X11_ROOT_ID): { return (&window->xlib.root_id); }
        case (LW_PROP_X11_WINDOW_ID): { return (&window->xlib.window_id); }
        case (LW_PROP_X11_SCREEN_ID): { return (&window->xlib.screen_id); }

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)
        
        case (LW_PROP_WIN32_HWND): { return (window->win32.hwnd); }
        case (LW_PROP_WIN32_HINSTANCE): { return (window->win32.hinstance); }

#  endif /* LIBWINDOW_WIN32 */

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

#  if defined (LIBWINDOW_X11)

    lw_pollEventsPlatform(window);

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)
    
    MSG msg;
        
    while (PeekMessage(&msg, window->win32.hwnd, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

#  endif /* LIBWINDOW_WIN32 */

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

#  if defined (LIBWINDOW_X11)
    
    if (!XFlush(window->xlib.display)) { return (false); }

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

#  endif /* LIBWINDOW_WIN32 */
        
    return (true);
}

/* MODULE: Time */

LIBWINDOW_API uint64_t  lw_getTime(void) {

#  if defined (LIBWINDOW_X11)

    struct timeval  time;
    
    gettimeofday(&time, 0);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)
    
    SYSTEMTIME  systemtime;

    GetSystemTime(&systemtime);
    return (systemtime.wMilliseconds);

#  endif /* LIBWINDOW_WIN32 */
        
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

#  if defined (LIBWINDOW_X11)

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
                uint64_t    key;

                key = LW_KEY_NONE;
                if (!lw_inputPlatformToLibrary(XkbKeycodeToKeysym(window->xlib.display, xevent.xkey.keycode, 0, xevent.xkey.state & ShiftMask ? 1 : 0), &key)) { break; }

                event = (t_event) {
                    .type = LW_EVENT_KEY,
                    .key = (t_keyEvent) {
                        .type = LW_EVENT_KEY,
                        .time = lw_getTime(),
                        .window = window,
                        .key = key,
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

            case (ConfigureNotify): {
                t_event event;

                /* Process window resize event... */
                if (xevent.xconfigure.width != (int) window->data.width || xevent.xconfigure.height != (int) window->data.height) {
                    event = (t_event) {
                        .type = LW_EVENT_RESIZE,
                        .resize = (t_resizeEvent) {
                            .type = LW_EVENT_RESIZE,
                            .time = lw_getTime(),
                            .window = window,
                            .width = window->data.width = xevent.xconfigure.width,
                            .height = window->data.height = xevent.xconfigure.height,
                        }
                    };
                }
                /* Process window movement event... */
                else if (xevent.xconfigure.x != (int) window->data.x || xevent.xconfigure.y != (int) window->data.y) {
                    event = (t_event) {
                        .type = LW_EVENT_MOVE,
                        .move = (t_moveEvent) {
                            .type = LW_EVENT_MOVE,
                            .time = lw_getTime(),
                            .window = window,
                            .x = window->data.x = xevent.xconfigure.x,
                            .y = window->data.y = xevent.xconfigure.y,
                        }
                    };
                }
                lw_pushEvent(window, &event);
            } break;
        }
    }
    return (true);
}

#  endif /* LIBWINDOW_X11 */
#  if defined (LIBWINDOW_WIN32)

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    t_window    window;

    window = 0;
    /* retrieve the pointer to the window object... */
    switch (uMsg) {
        case (WM_CREATE):
        case (WM_NCCREATE): {
            CREATESTRUCT    *pCreateStruct;

            pCreateStruct = (CREATESTRUCT *) lParam;
            window = (t_window) pCreateStruct->lpCreateParams;
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR) window);
        } break;

        default: {
            LONG_PTR    lPtr;

            lPtr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
            window = (t_window) lPtr;
        } break;
    }

    /* process windows messages... */
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
        } return (0);

        case (WM_KEYDOWN):
        case (WM_SYSKEYDOWN): {
            t_event     event;
            uint64_t    key;

            key = LW_KEY_NONE;
            if (!lw_inputPlatformToLibrary(LOWORD(wParam), &key)) { break; }
            event = (t_event) {
                .type = LW_EVENT_KEY,
                .key = (t_keyEvent) {
                    .type = LW_EVENT_KEY,
                    .time = lw_getTime(),
                    .window = window,
                    .key = key,
                    .state = true,
                }
            };
            lw_pushEvent(window, &event);
        } break;

        case (WM_KEYUP):
        case (WM_SYSKEYUP): {
            t_event     event;
            uint64_t    key;

            key = LW_KEY_NONE;
            if (!lw_inputPlatformToLibrary(LOWORD(wParam), &key)) { break; }
            event = (t_event) {
                .type = LW_EVENT_KEY,
                .key = (t_keyEvent) {
                    .type = LW_EVENT_KEY,
                    .time = lw_getTime(),
                    .window = window,
                    .key = key,
                    .state = false,
                }
            };
            lw_pushEvent(window, &event);
        } break;

        case (WM_LBUTTONDOWN):
        case (WM_RBUTTONDOWN):
        case (WM_MBUTTONDOWN): {
            t_event event;
            uint8_t button;
            
            if (uMsg == WM_LBUTTONDOWN) { button = LW_BUTTON_LEFT; }
            else if (uMsg == WM_MBUTTONDOWN) { button = LW_BUTTON_MIDDLE; }
            else if (uMsg == WM_RBUTTONDOWN) { button = LW_BUTTON_RIGHT; }
            event = (t_event) {
                .type = LW_EVENT_BUTTON,
                .button = (t_buttonEvent) {
                    .type = LW_EVENT_BUTTON,
                    .time = lw_getTime(),
                    .window = window,
                    .button = button,
                    .x = (uint32_t) GET_X_LPARAM(lParam),
                    .y = (uint32_t) GET_Y_LPARAM(lParam),
                    .state = true,
                }
            };
            lw_pushEvent(window, &event);
        } break;
        
        case (WM_LBUTTONUP):
        case (WM_RBUTTONUP):
        case (WM_MBUTTONUP): {
            t_event event;
            uint8_t button;
            
            if (uMsg == WM_LBUTTONDOWN) { button = LW_BUTTON_LEFT; }
            else if (uMsg == WM_MBUTTONDOWN) { button = LW_BUTTON_MIDDLE; }
            else if (uMsg == WM_RBUTTONDOWN) { button = LW_BUTTON_RIGHT; }
            event = (t_event) {
                .type = LW_EVENT_BUTTON,
                .button = (t_buttonEvent) {
                    .type = LW_EVENT_BUTTON,
                    .time = lw_getTime(),
                    .window = window,
                    .button = button,
                    .x = (uint32_t) GET_X_LPARAM(lParam),
                    .y = (uint32_t) GET_Y_LPARAM(lParam),
                    .state = false,
                }
            };
            lw_pushEvent(window, &event);
        } break;

        case (WM_MOUSEMOVE): {
            t_event event;
            
            event = (t_event) {
                .type = LW_EVENT_MOTION,
                .motion = (t_motionEvent) {
                    .type = LW_EVENT_MOTION,
                    .time = lw_getTime(),
                    .window = window,
                    .x = (uint32_t) GET_X_LPARAM(lParam),
                    .xrel = (uint32_t) GET_X_LPARAM(lParam),
                    .y = (uint32_t) GET_Y_LPARAM(lParam),
                    .yrel = (uint32_t) GET_Y_LPARAM(lParam),
                }
            };
            lw_pushEvent(window, &event);
        } break;

        case (WM_SIZE):
        case (WM_SIZING): {
            t_event     event;
            
            switch (wParam) {
                /* Handle minimize event... */
                case (SIZE_MINIMIZED): { } break;

                /* Handle maximize event... */
                case (SIZE_MAXIMIZED): { } break;

                /* Handle resize event... */
                default: {
                    event = (t_event) {
                        .type = LW_EVENT_RESIZE,
                        .resize = (t_resizeEvent) {
                            .type = LW_EVENT_RESIZE,
                            .time = lw_getTime(),
                            .window = window,
                            .width = window->data.width = LOWORD(lParam),
                            .height = window->data.height = HIWORD(lParam),
                        }
                    };
                } break;
            }
            lw_pushEvent(window, &event);
        } break;

        case (WM_MOVE):
        case (WM_MOVING): {
            t_event     event;
           
            event = (t_event) {
                .type = LW_EVENT_MOVE,
                .move = (t_moveEvent) {
                    .type = LW_EVENT_MOVE,
                    .time = lw_getTime(),
                    .window = window,
                    .x = window->data.x = LOWORD(lParam),
                    .y = window->data.y = HIWORD(lParam),
                }
            };
            lw_pushEvent(window, &event);
        } break;
    }
    return (DefWindowProc(hWnd, uMsg, wParam, lParam));
}

#  endif /* LIBWINDOW_WIN32 */

/* MODULE: Input */

static bool lw_inputPlatformToLibrary(const uint64_t platform, uint64_t *library) {
    for (size_t i = 0; g_keymap[i].library != LW_KEY_COUNT; i++) {
        if (g_keymap[i].platform == platform) {
            if (library) { *library = g_keymap[i].library; }

            return (true);
        }
    }

    return (false);
}

# endif /* LIBWINDOW_IMPLEMENTATION */
#endif /* _libwindow_h_ */
