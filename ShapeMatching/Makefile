CC = g++
LIB = `pkg-config opencv --cflags --libs`
TARGET = test
OBJECTS = shapematch.o
ARG1 = ff109.png #floodfill109.png
ARG2 = ff110.png #floodfill110.png
ARG3 = ct.110.jpg

all: $(TARGET).cpp $(OBJECTS)
	$(CC) -o $(TARGET) $(TARGET).cpp $(OBJECTS) $(LIB)

run:
	./$(TARGET) $(ARG1) $(ARG2) $(ARG3)

clean:
	rm $(TARGET) $(OBJECTS)
