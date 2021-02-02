.SUFFIXES: .c .o

export PROJECT_ROOT = .

CC = gcc
#CFLAGS = -g -O0 -msse2 -Wall -I/usr/include/ -Iinclude
CFLAGS = -g -O0 -Wall -I/usr/include/ -Iinclude

SRC_DIR = src/

LIBS = 
OBJS = main.o $(SRC_DIR)timer.o $(SRC_DIR)reorder.o
SRCS = main.c $(SRC_DIR)timer.c $(SRC_DIR)reorder.c
TARGET = reorder

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(LIBS) $(OBJS)

dep : gccmakedep $(SRCS)

clean:
	rm -f output.csv
	rm -f reorder
	rm -f *.o
	rm -f my_plot.png
	rm -f src/*.o

