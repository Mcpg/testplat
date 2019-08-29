
CC = wcc
CFLAGS = -2 -bt=dos -ms -oh -we

AS = nasm
LD = wlink
PYTHON = python

ifeq ($(OS),Windows_NT)
	RM = del /s /q
	MKDIR = mkdir
else
	RM = rm -f
	MKDIR = mkdir -p
endif