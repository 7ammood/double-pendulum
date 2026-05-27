CC = C:/msys64/ucrt64/bin/g++.exe
TARGET = game.exe
CFLAGS = -Wall
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) main.cpp -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean:
	del $(TARGET)