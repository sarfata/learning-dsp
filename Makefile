CC = gcc
CFLAGS = -Wall -std=c99 -g

$(TARGET).o: $(TARGET).c $(TARGET).h
		$(CC) -c $(CFLAGS) $< -o $@

all: fftfun

fftfun: main.o wave.o dft.o
		$(CC) $(CFLAGS) -o fftfun main.o wave.o dft.o

clean:
		rm -f fftfun *.o
