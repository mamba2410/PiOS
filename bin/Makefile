###########################################################################################################
# Compiler, flags and names
###########################################################################################################
TOOLCHAIN_PREFIX = aarch64-linux-gnu
CC = $(TOOLCHAIN_PREFIX)-gcc
AS = $(TOOLCHAIN_PREFIX)-gcc
LD = $(TOOLCHAIN_PREFIX)-ld
AR = $(TOOLCHAIM_PREFIX)-ar
GLOBAL_CC_FLAGS = -ffreestanding -Wall -nostdlib -nostartfiles -mgeneral-regs-only -MMD -fno-stack-protector
#GLOBAL_CC_FLAGS = -ffreestanding -Wall -nostdlib -nostartfiles -mgeneral-regs-only -MMD
GLOBAL_AS_FLAGS = -MMD
GLOBAL_LD_FLAGS =
LIB_D = ./libs

###########################################################################################################
# Build number tracking
###########################################################################################################

BUILD_NUMBER_D = ./metadata
include $(BUILD_NUMBER_D)/BuildNumber.mak

###########################################################################################################
# Subdirectory recipes
###########################################################################################################

# Memory module
MEMORY_BIN		= libmem.a
MEMORY_CC_FLAGS	= $(GLOBAL_CC_FLAGS)
MEMORY_LD_FLAGS	= $(GLOBAL_LD_FLAGS)
MEMORY_AS_FLAGS	= $(GLOBAL_AS_FLAGS)
MEMORY_SRC_D   	= ../src/memory
MEMORY_INC_D   	= ../include
MEMORY_OBJ_D   	= ./objects
MEMORY_C_SRC	= $(wildcard $(MEMORY_SRC_D)/*.c)
MEMORY_S_SRC	= $(wildcard $(MEMORY_SRC_D)/*.S)
MEMORY_INC		= $(wildcard $(MEMORY_INC_D)/*.h)
MEMORY_C_OBJ	= $(patsubst $(MEMORY_SRC_D)/%.c, $(MEMORY_OBJ_D)/%_c.o, $(MEMORY_C_SRC))
MEMORY_S_OBJ	= $(patsubst $(MEMORY_SRC_D)/%.S, $(MEMORY_OBJ_D)/%_S.o, $(MEMORY_S_SRC))

$(MEMORY_OBJ_D)/%_S.o:	$(MEMORY_SRC_D)/%.S
	$(AS) $(MEMORY_AS_FLAGS) -I'$(MEMORY_INC_D)' -c $< -o $@

$(MEMORY_OBJ_D)/%_c.o:	$(MEMORY_SRC_D)/%.c
	$(CC) $(MEMORY_CC_FLAGS) -I'$(MEMORY_INC_D)' -c $< -o $@ 

$(MEMORY_BIN): $(MEMORY_C_OBJ) $(MEMORY_S_OBJ) $(MEMORY_INC)
	$(AR) rcs $(LIB_D)/$(MEMORY_BIN) $(MEMORY_C_OBJ) $(MEMORY_S_OBJ)

# peripherals module
PERIPHERALS_BIN			= libperipherals.a
PERIPHERALS_CC_FLAGS	= $(GLOBAL_CC_FLAGS) 
PERIPHERALS_LD_FLAGS	= $(GLOBAL_LD_FLAGS)
PERIPHERALS_AS_FLAGS	= $(GLOBAL_AS_FLAGS)
PERIPHERALS_SRC_D   	= ../src/peripherals
PERIPHERALS_INC_D   	= ../include
PERIPHERALS_OBJ_D   	= ./objects
PERIPHERALS_C_SRC		= $(wildcard $(PERIPHERALS_SRC_D)/*.c)
PERIPHERALS_S_SRC		= $(wildcard $(PERIPHERALS_SRC_D)/*.S)
PERIPHERALS_INC			= $(wildcard $(PERIPHERALS_INC_D)/*.h)
PERIPHERALS_C_OBJ		= $(patsubst $(PERIPHERALS_SRC_D)/%.c, $(PERIPHERALS_OBJ_D)/%_c.o, $(PERIPHERALS_C_SRC))
PERIPHERALS_S_OBJ		= $(patsubst $(PERIPHERALS_SRC_D)/%.S, $(PERIPHERALS_OBJ_D)/%_S.o, $(PERIPHERALS_S_SRC))

$(PERIPHERALS_OBJ_D)/%_S.o:	$(PERIPHERALS_SRC_D)/%.S
	$(AS) $(PERIPHERALS_AS_FLAGS) -I'$(PERIPHERALS_INC_D)' -c $< -o $@

$(PERIPHERALS_OBJ_D)/%_c.o:	$(PERIPHERALS_SRC_D)/%.c
	$(CC) $(PERIPHERALS_CC_FLAGS) -I'$(PERIPHERALS_INC_D)' -c $< -o $@ 

$(PERIPHERALS_BIN): $(PERIPHERALS_C_OBJ) $(PERIPHERALS_S_OBJ) $(PERIPHERALS_INC)
	$(AR) rcs $(LIB_D)/$(PERIPHERALS_BIN) $(PERIPHERALS_C_OBJ) $(PERIPHERALS_S_OBJ)


# PROC module
PROC_BIN		= libproc.a
PROC_CC_FLAGS	= $(GLOBAL_CC_FLAGS)
PROC_LD_FLAGS	= $(GLOBAL_LD_FLAGS)
PROC_AS_FLAGS	= $(GLOBAL_AS_FLAGS)
PROC_SRC_D   	= ../src/proc
PROC_INC_D   	= ../include
PROC_OBJ_D   	= ./objects
PROC_C_SRC		= $(wildcard $(PROC_SRC_D)/*.c)
PROC_S_SRC		= $(wildcard $(PROC_SRC_D)/*.S)
PROC_INC		= $(wildcard $(PROC_INC_D)/*.h)
PROC_C_OBJ		= $(patsubst $(PROC_SRC_D)/%.c, $(PROC_OBJ_D)/%_c.o, $(PROC_C_SRC))
PROC_S_OBJ		= $(patsubst $(PROC_SRC_D)/%.S, $(PROC_OBJ_D)/%_S.o, $(PROC_S_SRC))

$(PROC_OBJ_D)/%_S.o:	$(PROC_SRC_D)/%.S
	$(AS) $(PROC_AS_FLAGS) -I'$(PROC_INC_D)' -c $< -o $@

$(PROC_OBJ_D)/%_c.o:	$(PROC_SRC_D)/%.c
	$(CC) $(PROC_CC_FLAGS) -I'$(PROC_INC_D)' -c $< -o $@ 

$(PROC_BIN): $(PROC_C_OBJ) $(PROC_S_OBJ) $(PROC_INC)
	$(AR) rcs $(LIB_D)/$(PROC_BIN) $(PROC_C_OBJ) $(PROC_S_OBJ)

# MISC module
MISC_BIN		= libmisc.a
MISC_CC_FLAGS	= $(GLOBAL_CC_FLAGS)
MISC_LD_FLAGS	= $(GLOBAL_LD_FLAGS)
MISC_AS_FLAGS	= $(GLOBAL_AS_FLAGS)
MISC_SRC_D   	= ../src/misc
MISC_INC_D   	= ../include
MISC_OBJ_D   	= ./objects
MISC_C_SRC	= $(wildcard $(MISC_SRC_D)/*.c)
MISC_S_SRC	= $(wildcard $(MISC_SRC_D)/*.S)
MISC_INC		= $(wildcard $(MISC_INC_D)/*.h)
MISC_C_OBJ	= $(patsubst $(MISC_SRC_D)/%.c, $(MISC_OBJ_D)/%_c.o, $(MISC_C_SRC))
MISC_S_OBJ	= $(patsubst $(MISC_SRC_D)/%.S, $(MISC_OBJ_D)/%_S.o, $(MISC_S_SRC))

$(MISC_OBJ_D)/%_S.o:	$(MISC_SRC_D)/%.S
	$(AS) $(MISC_AS_FLAGS) -I'$(MISC_INC_D)' -c $< -o $@

$(MISC_OBJ_D)/%_c.o:	$(MISC_SRC_D)/%.c
	$(CC) $(MISC_CC_FLAGS) -I'$(MISC_INC_D)' -c $< -o $@ 

$(MISC_BIN): $(MISC_C_OBJ) $(MISC_S_OBJ) $(MISC_INC)
	$(AR) rcs $(LIB_D)/$(MISC_BIN) $(MISC_C_OBJ) $(MISC_S_OBJ)

###########################################################################################################
# Main recipe
###########################################################################################################

# Link library dependencies after the library that needs it, try not to make things circular
# Do not include extension as theres an object copy neededing to link
MAIN_BIN		= kernel8
MAIN_CC_FLAGS	= $(GLOBAL_CC_FLAGS)
MAIN_LD_FLAGS	= $(GLOBAL_LD_FLAGS) -L'$(LIB_D)' -T linker.ld -lmisc -lperipherals -lproc -lmem
MAIN_AS_FLAGS	= $(GLOBAL_AS_FLAGS)
MAIN_SRC_D    	= ../src
MAIN_INC_D   	= ../include
MAIN_OBJ_D    	= ./objects
MAIN_C_SRC		= $(wildcard $(MAIN_SRC_D)/*.c)
MAIN_S_SRC		= $(wildcard $(MAIN_SRC_D)/*.S)
MAIN_INC	  	= $(wildcard $(MAIN_INC_D)/*.h)
MAIN_C_OBJ 		= $(patsubst $(MAIN_SRC_D)/%.c, $(MAIN_OBJ_D)/%_c.o, $(MAIN_C_SRC))
MAIN_S_OBJ		= $(patsubst $(MAIN_SRC_D)/%.S, $(MAIN_OBJ_D)/%_S.o, $(MAIN_S_SRC))

$(MAIN_OBJ_D)/%_S.o:	$(MAIN_SRC_D)/%.S
	$(AS) $(MAIN_AS_FLAGS) -I'$(MAIN_INC_D)' -c $< -o $@

$(MAIN_OBJ_D)/%_c.o:	$(MAIN_SRC_D)/%.c
	$(CC) $(MAIN_CC_FLAGS) -I'$(MAIN_INC_D)' -c $< -o $@ 

main: $(MAIN_C_OBJ) $(MAIN_S_OBJ) $(MAIN_INC) linker.ld $(MEMORY_BIN) $(PROC_BIN) $(PERIPHERALS_BIN) $(MISC_BIN)
	$(LD) $(MAIN_C_OBJ) $(MAIN_S_OBJ) $(MAIN_LD_FLAGS) -o $(MAIN_BIN).elf
	$(TOOLCHAIN_PREFIX)-objcopy $(MAIN_BIN).elf -O binary $(MAIN_BIN).img

###########################################################################################################
# General recipes
###########################################################################################################

# Recipe for building, (re-)links the executable and triggers the build number
.DEFAULT_GOAL = build
build: main build_number
	@echo "Build complete"

# Recipe for cleaning. Removes all objects and binaries
clean:
	rm -rf $(MAIN_OBJ_D)/*.o
	rm -rf $(LIB_D)/*
	[ -f "./$(MAIN_BIN).img" ] && rm $(MAIN_BIN).img
	[ -f "./$(MAIN_BIN).elf" ] && rm $(MAIN_BIN).elf
	@echo ""

# Recipe for rebuilding. Just an easy way to run "make clean; make build"
rebuild: clean build
	@echo "Rebuilt binary"

