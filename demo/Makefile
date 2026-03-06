CC       ?= clang
CFLAGS   ?= -std=c99 -Wall -Werror -Wextra -Wpedantic -g -O0
CPPFLAGS ?= -I../include

BUILD := build
LIB   := ../build/libdsaref.a

SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=$(BUILD)/%.o)
DEPS := $(OBJS:.o=.d)
BINS := $(SRCS:%.c=$(BUILD)/%)

.PHONY: all clean lib
all: $(BINS)

$(BUILD):
	mkdir -p $@

$(LIB):
	$(MAKE) -C .. build/libdsaref.a

$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) -MT $@ -c $< -o $@

$(BUILD)/%: $(BUILD)/%.o $(LIB)
	$(CC) $(CFLAGS) $< $(LIB) -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILD)