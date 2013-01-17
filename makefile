# by petter wahlman, https://twitter.com/badeip

CC      = gcc

SRCDIR  = ./src
OBJDIR  = ./obj
BINDIR  = ./bin
INCLUDE = ./include

BINARY  = $(BINDIR)/brute

CFLAGS  = -I $(INCLUDE) -g -Wall -std=c99 -O3
LDFLAGS =

VPATH   = $(SRCDIR)

BINARY_OBJ = \
	$(OBJDIR)/brute.o \

$(OBJDIR)/%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

.PHONY:
all:    make_dirs $(BINARY)

$(BINARY): $(BINARY_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY:
clean:
	@/bin/rm -rvf \
		$(BINARY) \
		$(BINARY_OBJ) \

.PHONY:
make_dirs:
	@mkdir -p $(OBJDIR) $(BINDIR)

.PHONY:
install: all
	@cp -v $(BINARY) ~/bin \

