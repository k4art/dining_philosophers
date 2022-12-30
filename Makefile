SRCS      = $(wildcard *.c)
OBJS     := $(SRCS:.c=.o)
BUILDDIR ?= build
OBJS     := $(addprefix $(BUILDDIR)/, $(OBJS))

program: $(OBJS)
	gcc -o $@ $^

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	gcc -DDEBUG -c $^ -o $@

clean:
	rm -rf $(BUILDDIR)
