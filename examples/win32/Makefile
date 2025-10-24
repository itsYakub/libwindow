# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
MK_NAME		= example-win32

CC			= x86_64-w64-mingw32-gcc
CFLAGS		= -Wall -Wextra -Werror -std=c99 -ggdb3
DFLAGS		= -DLIBWINDOW_WIN32 -DLIBWINDOW_IMPLEMENTATION
LFLAGS		= -lgdi32 -lwinmm
SRCS		= $(MK_ROOT)$(MK_NAME).c
TARGET		= $(MK_ROOT)$(MK_NAME).exe

# ========

.PHONY : all

all :
	$(CC) $(CFLAGS) $(DFLAGS) $(SRCS) -o $(TARGET) $(LFLAGS)

.PHONY : clean

clean:
	rm -f $(TARGET)

# ========
