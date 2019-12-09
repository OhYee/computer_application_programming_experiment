############################################
#         Makefile for c projects          #
#              oyohyee@oyohyee.com         #
############################################
#
# Make a file in source folder, and input:
# 
# MAIN_FILE := <Output file name>
# EXTRA_DIRS := <Other source folder>
# OUTPUT_DIR = <Output folder>
# FLAGS = <Extra flags>
# include <Path to this file>
#

ifeq ($(OUTPUT_DIR),)
	OUTPUT_DIR = ./
endif

RM = rm -f
PS = c

CC = gcc
CFLAGS = -g -Wall --std=c99 -O3
CFLAGS += $(FLAGS)

MAIN_FILE_PATH = $(OUTPUT_DIR)$(MAIN_FILE)
PROGRAM = $(MAIN_FILE).out
PROGRAM_PATH = $(OUTPUT_DIR)$(PROGRAM)

ifeq ($(SYSTEM),WINDOWS)
	CC = x86_64-w64-mingw32-gcc
	PROGRAM = $(MAIN_FILE).exe
endif

ifeq ($(S64),)
	CFLAGS += -m32
else
	CFLAGS += -m64
endif

PWD = `pwd`
SUBDIRS = $(foreach d,$(EXTRA_DIRS),$(shell ls $(d) -F | grep "\/" | sed "s:^:$(d):" | grep -v "test")) 
DIRS = $(SUBDIRS) $(EXTRA_DIRS)

SOURCE = $(foreach d,$(DIRS),$(wildcard $(d)*.$(PS)))
ifneq ($(MAIN_FILE),)
	SOURCE += $(MAIN_FILE_PATH).$(PS)
endif
OBJS:=$(patsubst %.$(PS),%.o,$(SOURCE))
DEPS:=$(patsubst %.o,%.d,$(OBJS))
MISSING_DEPS:=$(filter-out $(wildcard $(DEPS)),$(DEPS))
MISSING_DEPS_SOURCE:=$(wildcard $(patsubst %.d,%.$(PS),$(MISS_DEPS)))

.PHONY:all clean info build run
all:
	-@$(MAKE) -s run && $(MAKE) -s clean
build: $(PROGRAM_PATH)
run: build
	@cd $(OUTPUT_DIR) && ./$(PROGRAM)
$(PROGRAM_PATH):$(SOURCE:.$(PS)=.o)
	@$(CC) $(CFLAGS) -o "$(PROGRAM_PATH)" $(OBJS)
%.o:%.c
	@$(CC) $(CFLAGS) -c -o "$@" "$<"
%.d:%.c
	@$(CC) $< -MM -MP -MT "$*.o" -MF "$*.d"
-include $(DEPS)

clean:
	-@$(RM) $(DEPS)
	-@$(RM) $(OBJS)
	-@$(RM) $(PROGRAM_PATH)

info:
	@echo "CC:                       $(CC)"
	@echo "CFLAGS:                   $(CFLAGS)"
	@echo "RM:                       $(RM)"
	@echo ""
	@echo "pwd:                      $(PWD)"
	@echo "EXTRA_DIRS:               $(EXTRA_DIRS)"
	@echo "SUBDIRS:                  $(SUBDIRS)"
	@echo "DIRS:                     $(DIRS)"
	@echo "OUTPUT_DIR:               $(OUTPUT_DIR)"
	@echo ""
	@echo "MAIN_FILE:                $(MAIN_FILE)"
	@echo "PROGRAM:                  $(PROGRAM)"
	@echo "PROGRAM_PATH:             $(PROGRAM_PATH)"
	@echo "SOURCE:                   $(SOURCE)"
	@echo "OBJS:                     $(OBJS)"
	@echo "DEPS:                     $(DEPS) "
	@echo "MISSING_DEPS:             $(MISSING_DEPS)"
	@echo "MISSING_DEPS_SOURCE: 	 $(MISSING_DEPS_SOURCE)"