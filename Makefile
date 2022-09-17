TARGET = linesLib.exe
CC = g++
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.c, %.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o : %.c
	$(CC) -c $< -o $@

clean :
	del $(TARGET) *.o