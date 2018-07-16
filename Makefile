OBJECTS=air.o main.o
TARGET=tinyhouse
INCLUDES=-I./lib
CFLAGS=-Os -std=c++11
CXXFLAGS=$(CFLAGS) $(INCLUDES) -D__LINUX__
CC=g++ $(CXXFLAGS)


$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

air.o: lib/air/air.h lib/air/airproto.h lib/air/air.cpp
	$(CC) -c lib/air/air.cpp -o $@ -DGPIO_SUN7I

main.o: src/linux/main.cpp
	$(CC) -c src/linux/main.cpp -o $@


clean:
	rm -f *.o

