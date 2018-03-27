

###############################################################################
# Directory Information
###############################################################################
#HOME_DIR=
PRODUCTS_DIR= $(HOME_DIR)/Products


###############################################################################
# Tool mak
###############################################################################
include Tool_Compile.mak

###############################################################################
# Output DIR
###############################################################################
OUTPUT_DIR = $(PRODUCTS_DIR)/out_$(PROG_NAME)


###############################################################################
# Link file definition
###############################################################################

Link_CMD  = $(HOME_DIR)/Build/DSP2803x_Headers_nonBIOS.cmd
Link_CMD += $(HOME_DIR)/Build/F28035_CLA_C.cmd
export Link_CMD
export Link_FILE

###############################################################################
# Build targets definition
###############################################################################
export SYS_OUT_FILE = $(OUTPUT_DIR)/$(PROG_NAME)$(PROG_REV).out
export SYS_BIN_FILE = $(OUTPUT_DIR)/$(PROG_NAME)$(PROG_REV).bin
export SYS_HEX_FILE = $(OUTPUT_DIR)/$(PROG_NAME)$(PROG_REV).hex
export SYS_MAP_FILE = $(OUTPUT_DIR)/$(PROG_NAME)$(PROG_REV).map
export SYS_S19_FILE = $(OUTPUT_DIR)/$(PROG_NAME)$(PROG_REV).s19
export SYS_CAL_FILE = $(OUTPUT_DIR)/$(PROG_NAME)$(PROG_REV)_Cal.s19
export SYS_Objlst_FILE = $(OUTPUT_DIR)/$(PROG_NAME)$(PROG_REV).cmd
###############################################################################
# Include Math Lib
###############################################################################
USE_LIBRARY = 1

###############################################################################
# Math Libraries
###############################################################################
ifeq ($(USE_LIBRARY),1)

Link_Include_DIR  = -i$(HOME_DIR)/Tools/C28X/include 
Link_Include_DIR += -i$(HOME_DIR)/Tools/C28X/lib 
export Link_Include_DIR

Link_Lib_DIR += -l=$(HOME_DIR)/Tools/C28X/lib/2803x_FlashAPI_BootROMSymbols.lib
Link_Lib_DIR += -l=$(HOME_DIR)/Tools/C28X/lib/rts2800_ml.lib
Link_Lib_DIR += -l=$(HOME_DIR)/Tools/C28X/lib/rts2800_fpu32.lib
Link_Lib_DIR += -l=$(HOME_DIR)/Tools/C28X/lib/instrument.lib
Link_Lib_DIR += -l=$(HOME_DIR)/Tools/C28X/lib/hwio.lib
Link_Lib_DIR += -l=$(HOME_DIR)/Tools/C28X/lib/libc.a
export Link_Lib_DIR

endif

include $(HOME_DIR)/App/App.mak
include $(HOME_DIR)/UDS/UDS.mak

INCDIRS += BOOT/
INCDIRS += Tools/C28X/include 
SUBDIRS += BOOT/

###############################################################################
# Make file defendency
###############################################################################
MAKFILE_DEPENDS += $(HOME_DIR)/Build/Application.mak


