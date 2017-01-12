CC=gcc
TARGET=main

$(TARGET): $(TARGET).c
	@gcc $(TARGET).c -o $(TARGET)
	@echo "Made $(TARGET)"

.PHONY: clean
clean:
	@rm -f $(TARGET) *.o
	@echo "Directory cleaned."
