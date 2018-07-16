OBJECTS=air.o main.o sender.o
TARGET=tinyhouse
INCLUDES=-I./lib
LIBS=-L/usr/local/lib -lrf24-sunxi
CFLAGS=-Os -std=c++11
CXXFLAGS=$(CFLAGS) $(INCLUDES) $(LIBS) -D__LINUX__ -DGPIO_SUN7I
CC=g++ $(CXXFLAGS)


$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

air.o: lib/air/air.h lib/air/airproto.h lib/air/air.cpp
	$(CC) -c lib/air/air.cpp -o $@

sender.o: lib/air/air.h lib/air/airproto.h lib/air/air.cpp
	$(CC) -c lib/sender/sender.cpp -o $@

main.o: lib/sender/sender.h lib/sender/sender.cpp lib/air/airproto.h
	$(CC) -c src/linux/main.cpp -o $@


clean:
	rm -f $(OBJECTS)

