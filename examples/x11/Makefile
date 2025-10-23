# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
MK_NAME		= example-x11

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -std=c99 -ggdb3
DFLAGS		= -DLIBWINDOW_X11 -DLIBWINDOW_IMPLEMENTATION
LFLAGS		= -lX11
SRCS		= $(MK_ROOT)$(MK_NAME).c
TARGET		= $(MK_ROOT)$(MK_NAME).out

# ========

.PHONY : all

all :
	$(CC) $(CFLAGS) $(DFLAGS) $(SRCS) -o $(TARGET) $(LFLAGS)

.PHONY : clean

clean:
	rm -f $(TARGET)

# ========
