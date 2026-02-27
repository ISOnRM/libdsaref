CC       ?= clang
CFLAGS   ?= -std=c99 -Wall -Werror -Wextra -Wpedantic -g -O0
CPPFLAGS ?= -I../include
LDFLAGS  ?= -L../build
LDLIBS   ?= -ldsaref

BUILD := build

SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=$(BUILD)/%.o)
DEPS := $(OBJS:.o=.d)
BINS := $(SRCS:%.c=$(BUILD)/%)

.PHONY: all clean
all: $(BINS)

$(BUILD):
	mkdir -p $@

$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $< -o $@

$(BUILD)/%: $(BUILD)/%.o
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILD)