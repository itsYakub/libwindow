# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
MK_NAME		= example-wayland

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -std=c99 -ggdb3
LFLAGS		= -lwayland-client
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
