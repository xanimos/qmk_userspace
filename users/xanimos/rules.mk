ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled/oled_basic.c
	OPT_DEFS += -DOLED_ENABLE
	ifeq ($(strip $(LUNA_ENABLE)), yes)
		SRC += oled/luna.c
		OPT_DEFS += -DLUNA_ENABLE
	endif
endif

ifeq ($(strip $(MOUSEKEY_ENABLE)), yes)
	ifeq ($(strip $(MOUSE_JIGGLE_ENABLE)), yes)
		SRC += mouse_util.c
		OPT_DEFS += -DMOUSE_JIGGLE_ENABLE
	endif
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)),yes)
	SRC += tap_dance.c
endif
SRC += xanimos.c
