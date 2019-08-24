
include ../config.mk

SRC_DIR = src
BIN_DIR = bin

TARGET = ../gamedir/GAME.EXE

C_OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.obj,$(wildcard $(SRC_DIR)/*.c))
ASM_OBJECTS = $(patsubst $(SRC_DIR)/%.asm,$(BIN_DIR)/%.obj,$(wildcard $(SRC_DIR)/*.asm))

.PHONY: all clean

all: $(TARGET)

ifeq ($(OS),Windows_NT)
clean:
	$(RM) $(subst /,\,$(patsubst %,"%",$(C_OBJECTS)) $(patsubst %,"%",$(ASM_OBJECTS)))
else
clean:
	$(RM) $(patsubst %,"%",$(C_OBJECTS)) $(patsubst %,"%",$(ASM_OBJECTS))
endif

$(TARGET): $(C_OBJECTS) $(ASM_OBJECTS)
	@-$(MKDIR) "$(patsubst %/,%,$(dir $@))"
	$(LD) name $@ system dos file { $^ }

$(BIN_DIR)/%.obj: $(SRC_DIR)/%.c
	@-$(MKDIR) "$(patsubst %/,%,$(dir $@))"
	$(CC) $(CFLAGS) -fo="$@" "$<"

$(BIN_DIR)/%.obj: $(SRC_DIR)/%.asm
	@-$(MKDIR) "$(patsubst %/,%,$(dir $@))"
	$(AS) -f obj -o $@ $<
