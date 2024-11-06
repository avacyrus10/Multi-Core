CC=gcc
CFLAGS=-g -Wall -std=gnu11 -Iinclude
LDFLAGS=-lpthread

SRCDIR=src
BUILDDIR=build
TESTDIR=test

EXECUTABLE=$(BUILDDIR)/main
EXECUTABLEOBJECT=$(EXECUTABLE).o
TEST=$(BUILDDIR)/test
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(filter-out $(EXECUTABLEOBJECT), $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES)))
TESTSOURCES=$(wildcard $(TESTDIR)/*.c)

all: $(TEST) $(EXECUTABLE)

test: $(TEST)
	$(TEST)

run: $(EXECUTABLE)
	$(EXECUTABLE)

$(TEST): $(OBJECTS) $(TESTSOURCES) | $(BUILDDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(EXECUTABLE): $(EXECUTABLEOBJECT) $(OBJECTS) | $(BUILDDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(TESTSOURCES) | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(BUILDDIR):
	mkdir -p $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: all test run clean
