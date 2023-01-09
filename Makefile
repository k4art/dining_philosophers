SRCS      = $(wildcard *.c)
OBJS     := $(SRCS:.c=.o)
BUILDDIR ?= build
OBJS     := $(addprefix $(BUILDDIR)/, $(OBJS))

CFLAGS = -Werror

debug: CFLAGS += -g
debug: CFLAGS += -DDEBUG
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
