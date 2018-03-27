###############################################################################
#       Tool_Compile.mak

###############################################################################

config_CPU_Type=TI_C2000

config_Compiler_Vendor=option_TI_C28X


TOOLS_PATH ?= $(HOME_DIR)/Tools/Utilities
###############################################################################
# export TOOLS_PATH so other make process can use this macro.
###############################################################################
export TOOLS_PATH

###############################################################################
# Make Tools
###############################################################################

RM 	= $(TOOLS_PATH)/rm
export RM



MOVE 	?= $(TOOLS_PATH)/mv
export MOVE

ECHO 	?= $(TOOLS_PATH)/echo
export ECHO


MAKE_DIR ?=$(TOOLS_PATH)/mkdir -p
export MAKE_DIR


PTP 	?= $(TOOLS_PATH)/ptp
export PTP


CALG	?= $(TOOLS_PATH)/CalCreate
export CALG


export S19toBin ?=$(TOOLS_PATH)/S19toBin

ifeq ($(SMAKE),YES)
USE_MULTIPLE_CORES = 1
JOBS = 16
else
USE_MULTIPLE_CORES = 0
endif



PRODUCTS_DIR= $(HOME_DIR)/Products



###############################################################################
# Setup the make files which are included in the build
###############################################################################
MAKFILE_DEPENDS += $(HOME_DIR)/Tools/Tool_Compile.mak
