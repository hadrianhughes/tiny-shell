# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g \
				 -I/opt/homebrew/opt/readline/include

LDFLAGS = -L/opt/homebrew/opt/readline/lib
LDLIBS = -lreadline -lncurses

# Source files
SRC = src/main.c src/read.c src/tsh.c

# Output executable
OUTDIR = dist
OUT = $(OUTDIR)/tsh

# Default target
all: $(OUTDIR) $(OUT)

$(OUTDIR):
	mkdir -p $(OUTDIR)

# Build executable
$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LDFLAGS) $(LDLIBS)

# Clean build artifacts
clean:
	rm -f $(OUT)
