CC       ?= cc
AR       ?= ar
CFLAGS   ?= -Wall -Werror -Wextra -Wpedantic -g -O0
CPPFLAGS ?= -Iinclude

BUILD := build

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:src/%.c=$(BUILD)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean
all: $(BUILD)/libdsaref.a

$(BUILD):
	mkdir -p $@

$(BUILD)/libdsaref.a: $(OBJS) | $(BUILD)
	$(AR) rcs $@ $^

$(BUILD)/%.o: src/%.c | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILD)