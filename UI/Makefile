CC = g++
LIB1 = `pkg-config --cflags gtk+-3.0`
LIB2 = `pkg-config --libs gtk+-3.0`
LIB3 = `pkg-config --cflags --libs opencv`
TARGET = ui
OBJECTS = ffillwhole.o shapematch.o

all: $(TARGET).cpp $(OBJECTS)
	$(CC) $(LIB1) -o $(TARGET) $(TARGET).cpp $(OBJECTS) $(LIB2) $(LIB3)

run:
	./$(TARGET)

clean:
	rm $(TARGET) $(OBJECTS)
