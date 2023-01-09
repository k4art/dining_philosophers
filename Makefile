SRCS      = $(wildcard *.c)
OBJS     := $(SRCS:.c=.o)
BUILDDIR ?= build
OBJS     := $(addprefix $(BUILDDIR)/, $(OBJS))

CFLAGS = -Werror

LOG_ONLY_DINING ?= 0

ifneq ($(LOG_ONLY_DINING), 0)
	CFLAGS += -DLOG_ONLY_DINING
endif

debug: CFLAGS += -g
debug: CFLAGS += -DDEBUG
debug: CFLAGS += -DLOG_ENABLED
debug: program

release: CFLAGS += -O3
release: program

program: $(OBJS)
	gcc -o $@ $^

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	gcc $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(BUILDDIR)
