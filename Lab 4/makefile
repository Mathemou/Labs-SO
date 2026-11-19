CC = gcc
CFLAGS = -Wall -Wextra -std=c11

.PHONY: all run clean

TARGET ?= lab4

all: lab3 lab4 lab5

lab3: lab3.c
	$(CC) $(CFLAGS) $< -o $@

lab4: lab4.c
	$(CC) $(CFLAGS) $< -o $@

lab5: lab5.c
	$(CC) $(CFLAGS) $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f lab3 lab4 lab5
