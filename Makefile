LIBNAME = libgopro

SRCDIR = src
BINDIR = build

LIBTARGET = $(BINDIR)/$(LIBNAME).a

SRCS = $(shell find $(SRCDIR) -type f -name *.c)
OBJS = $(patsubst $(SRCDIR)/%,$(BINDIR)/%,$(SRCS:.c=.o))

INCLUDES = -Isrc -Iinclude
DEFINES =

CC = gcc
CFLAGS = -g $(DEFINES) $(INCLUDES) -Wall -Wextra -O2
LDFLAGS =

AR = ar rcs

RM = rm -f

build: $(LIBTARGET)

$(LIBTARGET): $(OBJS)
	$(AR) $@ $^

$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

test: build
	# compile and run tests

clean:
	$(RM) $(OBJS) $(LIBTARGET)

examples: examples/gopro.c $(LIBTARGET)
	# $(CC) $< -o $(BINDIR)/gopro -Iinclude -Lbuild -lgopro
