.SUFFIXES: .c .o

export PROJECT_ROOT = .

CC = gcc
#CFLAGS = -g -O0 -msse2 -Wall -I/usr/include/ -Iinclude
CFLAGS = -g -O0 -Wall -I/usr/include/ -Iinclude

SRC_DIR = src/

LIBS = 
OBJS = main.o $(SRC_DIR)timer.o $(SRC_DIR)load_latency.o $(SRC_DIR)store_buffer.o $(SRC_DIR)load_buffer.o $(SRC_DIR)reorder.o $(SRC_DIR)prefetch.o
SRCS = main.c $(SRC_DIR)timer.c $(SRC_DIR)load_latency.c $(SRC_DIR)store_buffer.c $(SRC_DIR)load_buffer.c $(SRC_DIR)reorder.c $(SRC_DIR)prefetch.c
TARGET = cache

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(LIBS) $(OBJS)

dep : gccmakedep $(SRCS)

clean:
	rm -rf cache
	rm -f *.o
	rm -f data.txt
	rm -f my_plot.png
	rm -f src/*.o

