LIBNAME = libgopro

INCDIR = include
SRCDIR = src
BINDIR = build

LIBTARGET = $(BINDIR)/$(LIBNAME).a

HDRS = $(shell find $(SRCDIR) $(INCDIR) -type f -name *.h)
SRCS = $(shell find $(SRCDIR) -type f -name *.c)
OBJS = $(patsubst $(SRCDIR)/%,$(BINDIR)/%,$(SRCS:.c=.o))

INCLUDES = -I$(SRCDIR) -I$(INCDIR)
DEFINES =

CC = gcc
CFLAGS = -g $(DEFINES) $(INCLUDES) -Wall -Wextra -O2
LDFLAGS =

AR = ar rcs

RM = rm -f


default: lib

all: lib test examples

lib: $(LIBTARGET)

$(LIBTARGET): $(OBJS)
	$(AR) $@ $^

$(BINDIR)/%.o: $(SRCDIR)/%.c $(HDRS)
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

test: lib
	# compile and run tests

examples: lib
	# compile examples

clean:
	$(RM) $(OBJS) $(LIBTARGET)
