# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
MK_NAME		= libwindow
TARGET		= $(MK_ROOT)$(MK_NAME).h

# ========

.PHONY : examples

examples :
	make -C $(MK_ROOT)examples/x11
	make -C $(MK_ROOT)examples/win32

# ========
