CC = g++
LIB = `pkg-config opencv --cflags --libs`
TARGET = GetDiff

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) -o $(TARGET) $(TARGET).cpp $(LIB)

run:
	./$(TARGET) test110.jpg test115.jpg

clean:
	rm $(TARGET)
