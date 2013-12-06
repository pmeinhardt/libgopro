LIBNAME = gopro

INCDIR = include
SRCDIR = src
BINDIR = build
TSTDIR = test
EXADIR = examples

LIBTARGET = $(BINDIR)/lib$(LIBNAME).a

HDRS = $(shell find $(SRCDIR) $(INCDIR) -type f -name *.h)
SRCS = $(shell find $(SRCDIR) -type f -name *.c)
OBJS = $(patsubst $(SRCDIR)/%,$(BINDIR)/%,$(SRCS:.c=.o))

TSTSRCS = $(shell find $(TSTDIR) -type f -name test-*.c)
TSTBINS = $(patsubst $(TSTDIR)/%,$(BINDIR)/%,$(TSTSRCS:.c=))
TSTDEPS = $(TSTDIR)/libtap/tap.c

EXASRCS = $(shell find $(EXADIR) -type f -name *.c)
EXABINS = $(patsubst $(EXADIR)/%,$(BINDIR)/%,$(EXASRCS:.c=))
EXADEPS = -lcurl

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

test: lib $(TSTBINS)
	prove -e '' -v $(TSTBINS)

$(BINDIR)/%: $(TSTDIR)/%.c $(TSTDEPS)
	$(CC) $(INCLUDES) -I$(TSTDIR)/libtap -L$(BINDIR) -l$(LIBNAME) -o $@ $^

examples: lib $(EXABINS)

$(BINDIR)/%: $(EXADIR)/%.c
	$(CC) $(INCLUDES) $(EXADEPS) -L$(BINDIR) -l$(LIBNAME) -o $@ $^

clean:
	$(RM) $(OBJS) $(LIBTARGET) $(TSTBINS) $(EXABINS)
