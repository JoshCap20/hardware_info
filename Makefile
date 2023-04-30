CC = gcc
CFLAGS = -Wall -Wextra
TARGET = hardware_info
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
