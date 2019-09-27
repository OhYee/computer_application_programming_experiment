############################################
#         Makefile for c projects          #
#              oyohyee@oyohyee.com         #
############################################
#
# Make a file in source folder, and input:
# 
# PROGRAM := <Output file name>
# ROOT := <Root of the file>
# EXTRA_DIRS := <Other source folder>
# include <Path to this file>
#

ifeq ($(ROOT),)
	ROOT = ./
endif

ifeq ($(OUTPUT_DIR),)
	ROOT = ./
endif

RM = rm -f
PS = c

CC = gcc
CFLAGS = -g -Wall --std=c99 -O3

MAIN_FILE_PATH = $(ROOT)$(MAIN_FILE)
PROGRAM = $(MAIN_FILE_PATH).out

ifeq ($(SYSTEM),WINDOWS)
	CC = x86_64-w64-mingw32-gcc
	PROGRAM = $(MAIN_FILE_PATH).exe
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


ifeq ($(MAIN_FILE),)

.PHONY:all clean info test
all: 
	-@$(MAKE) -s test && $(MAKE) -s clean
test:
	-@$(MAKE) -C ./test -s run;

else

.PHONY:all clean info build run
all:
	-@$(MAKE) -s run && $(MAKE) -s clean
build: $(PROGRAM)
run: build
	@cd $(OUTPUT_DIR) && $(PROGRAM)
$(PROGRAM):$(SOURCE:.$(PS)=.o)
	@$(CC) $(CFLAGS) -o "$(OUTPUT_DIR)$(PROGRAM)" $(OBJS)
%.o:%.c
	@$(CC) $(CFLAGS) -c -o "$@" "$<"
%.d:%.c
	@$(CC) $< -MM -MP -MT "$*.o" -MF "$*.d"
-include $(DEPS)

endif

clean:
	-@$(RM) $(DEPS)
	-@$(RM) $(OBJS)
	-@$(RM) $(OUTPUT_DIR)$(PROGRAM)

info:
	@echo "CC:                       $(CC)"
	@echo "CFLAGS:                   $(CFLAGS)"
	@echo "RM:                       $(RM)"
	@echo ""
	@echo "root:                     $(ROOT)"
	@echo "pwd:                      $(PWD)"
	@echo "EXTRA_DIRS:               $(EXTRA_DIRS)"
	@echo "SUBDIRS:                  $(SUBDIRS)"
	@echo "DIRS:                     $(DIRS)"
	@echo ""
	@echo "MAIN_FILE:                $(MAIN_FILE)"
	@echo "PROGRAM:                  $(PROGRAM)"
	@echo "SOURCE:                   $(SOURCE)"
	@echo "OBJS:                     $(OBJS)"
	@echo "DEPS:                     $(DEPS) "
	@echo "MISSING_DEPS:             $(MISSING_DEPS)"
	@echo "MISSING_DEPS_SOURCE: 	 $(MISSING_DEPS_SOURCE)"