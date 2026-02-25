CC       ?= clang
CFLAGS   ?= -Wall -Werror -Wextra -Wpedantic -g -O0
CPPFLAGS ?= -Iinclude
AR		 ?= ar

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

$(OBJS): $(SRCS) | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(DEPS) -MT $@ -c $^ -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILD)
