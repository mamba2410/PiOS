###########################################################################################################
# Compiler, flags and names
###########################################################################################################
TOOLCHAIN_PREFIX = aarch64-linux-gnu
CC = $(TOOLCHAIN_PREFIX)-gcc
AS = $(TOOLCHAIN_PREFIX)-gcc
LD = $(TOOLCHAIN_PREFIX)-ld
AR = $(TOOLCHAIM_PREFIX)-ar
GLOBAL_CC_FLAGS = -ffreestanding -Wall -nostdlib -nostartfiles -mgeneral-regs-only -MMD -fno-stack-protector
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

# This is for things like in-house libraries
# For example, if code for the library libsub.so is in
# the same source as this, and main needs it
#
# Example of adding a subdirectory that compiles to a shared object
# Should probably put user-generated library files in different directory

#SUB_BIN = $(LIB_D)/libsub.so
#SUB_LD_FLAGS = $(GLOBAL_LD_FLAGS) -shared
#SUB_CC_FLAGS = $(GLOBAL_CC_FLAGS) -fPIC
#SUB_SRC_D    = $(MAIN_OBJ_D)/sub
#SUB_HEAD_D   = $(MAIN_HEAD_D)/sub
#SUB_OBJ_D    = $(MAIN_OBJ_D)/sub
#SUB_SOURCES  = $(wildcard $(SUB_SRC_D)/*.$(SRC_EXT))
#SUB_HEADERS  = $(wildcard $(SUB_HEAD_D)/*.$(HEAD_EXT))
#SUB_OBJECTS  = $(patsubst $(SUB_SRC_D)/%.$(SRC_EXT), $(SUB_OBJ_D)/%.$(OBJ_EXT), $(SUB_SOURCES))
#
#$(SUB_OBJ_DIR)/%.$(OBJ_EXT): $(SUB_SRC_D)/%.$(SRC_EXT)
#	$(CC) $(SUB_CC_FLAGS) -I'$(SUB_HEAD_D)' -c $< -o $@
#
#sub: $(SUB_OBJECTS) $(SUB_HEADERS)
#	$(LD) $(SUB_OBJECTS) $(SUB_LD_FLAGS) -o $(SUB_BIN)

# Memory library, statically linked
MEMORY_BIN		= libmemory.a
MEMORY_CC_FLAGS	= $(GLOBAL_CC_FLAGS) -fPIC
MEMORY_LD_FLAGS	= $(GLOBAL_LD_FLAGS)
MEMORY_AS_FLAGS	= $(GLOBAL_AS_FLAGS)
MEMORY_SRC_D   	= ../src/memory
MEMORY_INC_D   	= ../include/memory
MEMORY_OBJ_D   	= ./objects
MEMORY_C_SR		= $(wildcard $(MEMORY_SRC_D)/*.c)
MEMORY_S_SRC	= $(wildcard $(MEMORY_SRC_D)/*.S)
MEMORY_INC		= $(wildcard $(MEMORY_INC_D)/*.h)
MEMORY_C_OBJ	= $(patsubst $(MEMORY_SRC_D)/%.c, $(MEMORY_OBJ_D)/%_c.o, $(MEMORY_C_SRC))
MEMORY_S_OBJ	= $(patsubst $(MEMORY_SRC_D)/%.S, $(MEMORY_OBJ_D)/%_S.o, $(MEMORY_S_SRC))

$(MEMORY_OBJ_D)/%_S.o:	$(MEMORY_SRC_D)/%.S
	$(AS) $(MEMORY_AS_FLAGS) -I'$(MEMORY_INC_D)' -c $< -o $@

$(MEMORY_OBJ_D)/%_c.o:	$(MEMORY_SRC_D)/%.c
	$(CC) $(MEMORY_CC_FLAGS) -I'$(MEMORY_INC_D)' -c $< -o $@ 

memory: $(MEMORY_C_OBJ) $(MEMORY_S_OBJ) $(MEMORY_INC)
	$(AR) rcs $(LIB_D)/$(MEMORY_BIN) $(MEMORY_C_OBJ) $(MEMORY_S_OBJ)

# Serial library, statically linked
SERIAL_BIN		= libserial.a
SERIAL_CC_FLAGS	= $(GLOBAL_CC_FLAGS) -fPIC
SERIAL_LD_FLAGS	= $(GLOBAL_LD_FLAGS)
SERIAL_AS_FLAGS	= $(GLOBAL_AS_FLAGS)
SERIAL_SRC_D   	= ../src/serial
SERIAL_INC_D   	= ../include
SERIAL_OBJ_D   	= ./objects
SERIAL_C_SRC	= $(wildcard $(SERIAL_SRC_D)/*.c)
SERIAL_S_SRC	= $(wildcard $(SERIAL_SRC_D)/*.S)
SERIAL_INC		= $(wildcard $(SERIAL_INC_D)/*.h)
SERIAL_C_OBJ	= $(patsubst $(SERIAL_SRC_D)/%.c, $(SERIAL_OBJ_D)/%_c.o, $(SERIAL_C_SRC))
SERIAL_S_OBJ	= $(patsubst $(SERIAL_SRC_D)/%.S, $(SERIAL_OBJ_D)/%_S.o, $(SERIAL_S_SRC))

$(SERIAL_OBJ_D)/%_S.o:	$(SERIAL_SRC_D)/%.S
	$(AS) $(SERIAL_AS_FLAGS) -I'$(SERIAL_INC_D)' -c $< -o $@

$(SERIAL_OBJ_D)/%_c.o:	$(SERIAL_SRC_D)/%.c
	$(CC) $(SERIAL_CC_FLAGS) -I'$(SERIAL_INC_D)' -c $< -o $@ 

serial: $(SERIAL_C_OBJ) $(SERIAL_S_OBJ) $(SERIAL_INC)
	$(AR) rcs $(LIB_D)/$(SERIAL_BIN) $(SERIAL_C_OBJ) $(SERIAL_S_OBJ)

# MMIO library, statically linked
MMIO_BIN		= libmmio.a
MMIO_CC_FLAGS	= $(GLOBAL_CC_FLAGS) -fPIC
MMIO_LD_FLAGS	= $(GLOBAL_LD_FLAGS)
MMIO_AS_FLAGS	= $(GLOBAL_AS_FLAGS)
MMIO_SRC_D   	= ../src/mmio
MMIO_INC_D   	= ../include
MMIO_OBJ_D   	= ./objects
MMIO_C_SRC		= $(wildcard $(MMIO_SRC_D)/*.c)
MMIO_S_SRC		= $(wildcard $(MMIO_SRC_D)/*.S)
MMIO_INC		= $(wildcard $(MMIO_INC_D)/*.h)
MMIO_C_OBJ		= $(patsubst $(MMIO_SRC_D)/%.c, $(MMIO_OBJ_D)/%_c.o, $(MMIO_C_SRC))
MMIO_S_OBJ		= $(patsubst $(MMIO_SRC_D)/%.S, $(MMIO_OBJ_D)/%_S.o, $(MMIO_S_SRC))

$(MMIO_OBJ_D)/%_S.o:	$(MMIO_SRC_D)/%.S
	$(AS) $(MMIO_AS_FLAGS) -I'$(MMIO_INC_D)' -c $< -o $@

$(MMIO_OBJ_D)/%_c.o:	$(MMIO_SRC_D)/%.c
	$(CC) $(MMIO_CC_FLAGS) -I'$(MMIO_INC_D)' -c $< -o $@ 

mmio: $(MMIO_C_OBJ) $(MMIO_S_OBJ) $(MMIO_INC)
	$(AR) rcs $(LIB_D)/$(MMIO_BIN) $(MMIO_C_OBJ) $(MMIO_S_OBJ)

# SYSTEM library, statically linked
SYSTEM_BIN		= libsystem.a
SYSTEM_CC_FLAGS	= $(GLOBAL_CC_FLAGS) -fPIC
SYSTEM_LD_FLAGS	= $(GLOBAL_LD_FLAGS)
SYSTEM_AS_FLAGS	= $(GLOBAL_AS_FLAGS)
SYSTEM_SRC_D   	= ../src/system
SYSTEM_INC_D   	= ../include
SYSTEM_OBJ_D   	= ./objects
SYSTEM_C_SRC	= $(wildcard $(SYSTEM_SRC_D)/*.c)
SYSTEM_S_SRC	= $(wildcard $(SYSTEM_SRC_D)/*.S)
SYSTEM_INC		= $(wildcard $(SYSTEM_INC_D)/*.h)
SYSTEM_C_OBJ	= $(patsubst $(SYSTEM_SRC_D)/%.c, $(SYSTEM_OBJ_D)/%_c.o, $(SYSTEM_C_SRC))
SYSTEM_S_OBJ	= $(patsubst $(SYSTEM_SRC_D)/%.S, $(SYSTEM_OBJ_D)/%_S.o, $(SYSTEM_S_SRC))

$(SYSTEM_OBJ_D)/%_S.o:	$(SYSTEM_SRC_D)/%.S
	$(AS) $(SYSTEM_AS_FLAGS) -I'$(SYSTEM_INC_D)' -c $< -o $@

$(SYSTEM_OBJ_D)/%_c.o:	$(SYSTEM_SRC_D)/%.c
	$(CC) $(SYSTEM_CC_FLAGS) -I'$(SYSTEM_INC_D)' -c $< -o $@ 

system: $(SYSTEM_C_OBJ) $(SYSTEM_S_OBJ) $(SYSTEM_INC)
	$(AR) rcs $(LIB_D)/$(SYSTEM_BIN) $(SYSTEM_C_OBJ) $(SYSTEM_S_OBJ)

###########################################################################################################
# Main recipe
###########################################################################################################

# If main relies on any libraries, add them to the LD_FLAGS variable
# Remember to add in-house libraries as dependencies to main recipe,
# ie make them before try
# Do not include extension as theres an object copy neededing to link
MAIN_BIN		= kernel8
MAIN_CC_FLAGS	= $(GLOBAL_CC_FLAGS)
MAIN_LD_FLAGS	= $(GLOBAL_LD_FLAGS) -L'$(LIB_D)' -T linker.ld -lmemory -lserial -lmmio -lsystem
MAIN_AS_FLAGS	= $(GLOBAL_AS_FLAGS)
MAIN_SRC_D    	= ../src
MAIN_INC_D   	= ../include
MAIN_OBJ_D    	= ./objects
MAIN_C_SRC		= $(wildcard $(MAIN_SRC_D)/*.c)
MAIN_S_SRC		= $(wildcard $(MAIN_SRC_D)/*.S)
MAIN_INC	  	= $(wildcard $(MAIN_INC_D)/*.h)
MAIN_C_OBJ 		= $(patsubst $(MAIN_SRC_D)/%.c, $(MAIN_OBJ_D)/%_c.o, $(MAIN_C_SRC))
#MAIN_C_OBJ		+= $(MEMORY_C_OBJ) $(SERIAL_C_OBJ) $(MMIO_C_OBJ) $(SYSTEM_C_OBJ)
MAIN_S_OBJ		= $(patsubst $(MAIN_SRC_D)/%.S, $(MAIN_OBJ_D)/%_S.o, $(MAIN_S_SRC))
#MAIN_S_OBJ		+= $(MEMORY_S_OBJ) $(SERIAL_S_OBJ) $(MMIO_S_OBJ) $(SYSTEM_S_OBJ)

$(MAIN_OBJ_D)/%_S.o:	$(MAIN_SRC_D)/%.S
	$(AS) $(MAIN_AS_FLAGS) -I'$(MAIN_INC_D)' -c $< -o $@

$(MAIN_OBJ_D)/%_c.o:	$(MAIN_SRC_D)/%.c
	$(CC) $(MAIN_CC_FLAGS) -I'$(MAIN_INC_D)' -c $< -o $@ 

main: $(MAIN_C_OBJ) $(MAIN_S_OBJ) $(MAIN_INC) linker.ld memory serial mmio system
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
	rm -rf $(LIB_D)/*.a
	[ -f "./$(MAIN_BIN).img" ] && rm $(MAIN_BIN).img
	[ -f "./$(MAIN_BIN).elf" ] && rm $(MAIN_BIN).elf
	@echo ""

# Recipe for rebuilding. Just an easy way to run "make clean; make build"
rebuild: clean build
	@echo "Rebuilt binary"

