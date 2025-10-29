# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
MK_NAME		= libwindow
TARGET		= $(MK_ROOT)$(MK_NAME).h

# ========

.PHONY : examples

examples :
	make --directory=$(MK_ROOT)examples/x11
	make --directory=$(MK_ROOT)examples/wayland
	make --directory=$(MK_ROOT)examples/win32

# ========
