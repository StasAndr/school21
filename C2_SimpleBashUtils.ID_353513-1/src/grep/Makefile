CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 
DOPFLAFS = -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable
TARGET = s21_grep
SOURCES = cat.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: clean