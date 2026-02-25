CC       ?= clang
CFLAGS   ?= -Wall -Werror -Wextra -Wpedantic -g -O0
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

$(OBJS): $(SRCS) | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -MF $(DEPS) -c $< -o $@

$(BINS): $(OBJS)
	$(CC) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILD)