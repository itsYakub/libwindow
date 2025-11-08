# ========

MK_ROOT		= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
MK_NAME		= libwindow
TARGET		= $(MK_ROOT)$(MK_NAME).h

# ========

.PHONY : all

all : install

.PHONY : install

install : remove
	mkdir /usr/local/include/$(MK_NAME)/
	cp -f $(TARGET) /usr/local/include/$(MK_NAME)/
	ln -s /usr/local/include/$(MK_NAME)/$(MK_NAME).h /usr/local/include/$(MK_NAME).h

.PHONY : remove

remove :
	rm -rf /usr/local/include/$(MK_NAME)
	rm -f /usr/local/include/$(MK_NAME).h

.PHONY : examples

examples :
	make --directory=$(MK_ROOT)examples/x11
	make --directory=$(MK_ROOT)examples/wayland
	make --directory=$(MK_ROOT)examples/win32

# ========
