#
#             LUFA Library
#     Copyright (C) Dean Camera, 2015.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

DMBS_BUILD_MODULES         += KEYSTROKES
DMBS_BUILD_TARGETS         +=
DMBS_BUILD_MANDATORY_VARS  += KEYSTROKES_PATH
DMBS_BUILD_OPTIONAL_VARS   +=
DMBS_BUILD_PROVIDED_VARS   += KEYSTROKES_SRC
DMBS_BUILD_PROVIDED_MACROS +=

SHELL = /bin/sh

ERROR_IF_UNSET   ?= $(if $(filter undefined, $(origin $(strip $(1)))), $(error Makefile $(strip $(1)) value not set))
ERROR_IF_EMPTY   ?= $(if $(strip $($(strip $(1)))), , $(error Makefile $(strip $(1)) option cannot be blank))
ERROR_IF_NONBOOL ?= $(if $(filter Y N, $($(strip $(1)))), , $(error Makefile $(strip $(1)) option must be Y or N))

# Sanity check user supplied values
$(foreach MANDATORY_VAR, $(KEYSTROKES_BUILD_MANDATORY_VARS), $(call ERROR_IF_UNSET, $(MANDATORY_VAR)))
$(call ERROR_IF_EMPTY, KEYSTROKES_PATH)

MCU          ?= atmega32u4
ARCH         ?= AVR8
BOARD        ?= NONE
F_CPU        ?= 16000000
F_USB        ?= $(F_CPU)
OPTIMIZATION ?= s
JUMP_TABLES  ?= Y

# Common Keystrokes C/C++ includes/definitions
KEYSTROKES_CXX_INCLUDES = -I. -I$(patsubst %/,%,$(KEYSTROKES_PATH))/.. -I$(KEYSTROKES_PATH)/Config/ -I$(KEYSTROKES_PATH)
KEYSTROKES_CXX_DEFINES  = -DARCH=ARCH_$(ARCH) -DBOARD=BOARD_$(BOARD) -DF_USB=$(F_USB)UL -DUSE_LUFA_CONFIG_HEADER
KEYSTROKES_CXX_FLAGS = -flto

# Keystrokes specific standard build options
C_FLAGS   += $(KEYSTROKES_CXX_INCLUDES) $(KEYSTROKES_CXX_DEFINES) $(KEYSTROKES_CXX_FLAGS)
CPP_FLAGS += $(KEYSTROKES_CXX_INCLUDES) $(KEYSTROKES_CXX_DEFINES) $(KEYSTROKES_CXX_FLAGS)

KEYSTROKES_SRC = $(KEYSTROKES_PATH)/main.c \
	 			  $(KEYSTROKES_PATH)/descriptors.c \
				  $(LUFA_SRC_USB) \
				  $(LUFA_SRC_USBCLASS) \
				  $(KEYSTROKES_PATH)/keys.c \
				  $(KEYSTROKES_PATH)/actions.c \
				  $(KEYSTROKES_PATH)/matrix.c \
				  $(KEYSTROKES_PATH)/modifiers.c \
				  $(KEYSTROKES_PATH)/timer.c \
				  $(KEYSTROKES_PATH)/reset.c \
				  $(KEYSTROKES_PATH)/layers.c \
				  $(KEYSTROKES_PATH)/keystrokes.c \
				  $(KEYSTROKES_PATH)/leader_key.c \
				  $(KEYSTROKES_PATH)/twi.c \
				  $(KEYSTROKES_PATH)/leds.c

KEYSTROKES_SRC_ERGODOX := $(KEYSTROKES_PATH)/drivers/ergodox.c

LUFA_PATH = $(KEYSTROKES_PATH)/lufa/LUFA

# Include LUFA-specific DMBS extension modules
DMBS_LUFA_PATH ?= $(LUFA_PATH)/Build/LUFA
include $(DMBS_LUFA_PATH)/lufa-sources.mk
include $(DMBS_LUFA_PATH)/lufa-gcc.mk

# Include common DMBS build system modules
DMBS_PATH ?= $(LUFA_PATH)/Build/DMBS/DMBS
include $(DMBS_PATH)/core.mk
include $(DMBS_PATH)/cppcheck.mk
include $(DMBS_PATH)/doxygen.mk
include $(DMBS_PATH)/dfu.mk
include $(DMBS_PATH)/gcc.mk
include $(DMBS_PATH)/hid.mk
include $(DMBS_PATH)/avrdude.mk
include $(DMBS_PATH)/atprogram.mk
