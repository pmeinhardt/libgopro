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

test: $(LIBTARGET)
	# compile and run tests

examples: $(LIBTARGET)
	# compile examples

clean:
	$(RM) $(OBJS) $(LIBTARGET)
