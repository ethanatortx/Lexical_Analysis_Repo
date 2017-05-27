CC = g++
CFLAGS = -std=c++14 -I..
SRCS = txtParser.h newsType.h txtParser.cpp newsType.cpp main.cpp

main.o: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o main.o

clean:
	del "main.o"