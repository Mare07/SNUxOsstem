CC = g++
LIB = `pkg-config --cflags --libs opencv`
#TARGET = ffillwhole
TARGET = test
OBJECTS = ffillwhole.o shapematch.o
DIRARG = ~/Pictures/ct_coronal/

all: $(TARGET).cpp $(OBJECTS)
	$(CC) -o $(TARGET) $(TARGET).cpp $(OBJECTS) $(LIB)

run:
	./$(TARGET) #$(DIRARG)

clean:
	rm $(TARGET) $(OBJECTS)
