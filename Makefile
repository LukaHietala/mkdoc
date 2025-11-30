CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lmd4c-html
TARGET = build/mkdoc

all: $(TARGET)

$(TARGET): main.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -rf build

.PHONY: all clean