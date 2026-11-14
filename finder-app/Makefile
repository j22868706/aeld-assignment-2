
CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

TARGET = writer
OBJS = writer.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

writer.o: writer.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o

