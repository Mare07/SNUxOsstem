CC = g++
LIB = `pkg-config --cflags --libs opencv`
TARGET = ffilldemo
OBJECTS = ffilldemo.o
DIRARG = ~/Pictures/ct_coronal/

all: $(TARGET).cpp
	$(CC) -o $(TARGET) $(TARGET).cpp $(LIB)

run:
	./$(TARGET) $(DIRARG)

clean:
	rm $(TARGET) $(OBJECTS)
