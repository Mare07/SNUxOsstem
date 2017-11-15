CC = g++
LIB1 = `pkg-config --cflags gtk+-3.0`
LIB2 = `pkg-config --libs gtk+-3.0`
TARGET = ui

all: $(TARGET).cpp
	$(CC) $(LIB1) -o $(TARGET) $(TARGET).cpp $(LIB2)

run:
	./$(TARGET)

clean:
	rm $(TARGET)
