#cross complier
# CC=/home/test1/Downloads/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-gcc
CC =gcc
#complier flags
CFLAGS = -lrt -pthread

#source file
SRCS = main.c

#Target binary file
TARGET = tcp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

clean:
	rm -f $(TARGET)

.PHONY: all clean