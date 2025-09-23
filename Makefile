# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Source files
SRC = src/main.c src/read.c

# Output executable
OUTDIR = dist
OUT = $(OUTDIR)/tsh

# Default target
all: $(OUTDIR) $(OUT)

$(OUTDIR):
	mkdir -p $(OUTDIR)

# Build executable
$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

# Clean build artifacts
clean:
	rm -f $(OUT)
