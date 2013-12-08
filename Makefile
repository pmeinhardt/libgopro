CC = gcc
AR = ar rcs
RM = rm -f
PROVE = prove -e ''

CFLAGS = -g -O2 -Wall
LDFLAGS =

LIBNAME = gopro

INCDIR = include
SRCDIR = src
BINDIR = build
TSTDIR = test
EXADIR = examples

LIBTARGET = $(BINDIR)/lib$(LIBNAME).a

INCLUDES = -I$(INCDIR)
DEFINES =

HEADERS = $(shell find $(SRCDIR) $(INCDIR) -type f -name *.h)
SOURCES = $(shell find $(SRCDIR) -type f -name *.c)
OBJECTS = $(patsubst $(SRCDIR)/%,$(BINDIR)/%,$(SOURCES:.c=.o))

LIB_CFLAGS = $(CFLAGS) -Wextra -I$(SRCDIR) $(INCLUDES)
LIB_LDFLAGS = $(LDFLAGS)

TEST_SOURCES = $(shell find $(TSTDIR) -type f -name test-*.c)
TEST_DEPS = $(TSTDIR)/libtap/tap.c
TESTS = $(patsubst $(TSTDIR)/%,$(BINDIR)/%,$(TEST_SOURCES:.c=))

TEST_CFLAGS = $(CFLAGS) -I$(SRCDIR) $(INCLUDES) -I$(TSTDIR)/libtap
TEST_LDFLAGS = $(LDFLAGS) -L$(BINDIR) -l$(LIBNAME) -lcurl

EXAMPLE_SOURCES = $(shell find $(EXADIR) -type f -name *.c)
EXAMPLES = $(patsubst $(EXADIR)/%,$(BINDIR)/%,$(EXAMPLE_SOURCES:.c=))

EXAMPLE_CFLAGS = $(CFLAGS) $(INCLUDES)
EXAMPLE_LDFLAGS = $(LDFLAGS) -L$(BINDIR) -l$(LIBNAME) -lcurl

SYMBOLS = $(addsuffix .dSYM,$(TESTS) $(EXAMPLES))


default: lib

all: lib test examples

lib: $(LIBTARGET)

$(LIBTARGET): $(OBJECTS)
	$(AR) $@ $^

$(BINDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(LIB_CFLAGS) $(LIB_LDFLAGS) -c -o $@ $<

test: lib $(TESTS)
	$(PROVE) $(TESTS)

$(BINDIR)/%: $(TSTDIR)/%.c $(TEST_DEPS)
	$(CC) $(TEST_CFLAGS) $(TEST_LDFLAGS) -o $@ $^

examples: lib $(EXAMPLES)

$(BINDIR)/%: $(EXADIR)/%.c
	$(CC) $(EXAMPLE_CFLAGS) $(EXAMPLE_LDFLAGS) -o $@ $^

clean:
	$(RM) -r $(SYMBOLS)
	$(RM) $(LIBTARGET)
	$(RM) $(OBJECTS)
	$(RM) $(TESTS)
	$(RM) $(EXAMPLES)
