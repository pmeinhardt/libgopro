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

TSDIR = test
TSSRCS = $(shell find $(TSDIR) -path $(TSDIR)/clar -prune -o -type f -name *.c -print)
TSTARGET = $(BINDIR)/tests
TSINCLUDES = $(INCLUDES) -I$(TSDIR) -I$(TSDIR)/clar
TSCFLAGS = $(TSINCLUDES) -L$(BINDIR) -lgopro -lcurl

build: $(LIBTARGET)

$(LIBTARGET): $(OBJS)
	$(AR) $@ $^

$(BINDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

clar:
	test/clar/generate.py test

$(TSTARGET): $(TSSRCS)
	$(CC) $(TSCFLAGS) -o $@ $^ test/clar/clar.c

test: $(LIBTARGET) $(TSTARGET)
	@$(TSTARGET)

examples: $(LIBTARGET)
	# compile examples

clean:
	$(RM) $(OBJS) $(LIBTARGET) $(TSTARGET)
