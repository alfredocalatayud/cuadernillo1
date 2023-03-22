OBJ=main.o tcomplejo.o
COMP=g++
OPC=-g

main: $(OBJ)
	$(COMP) $(OPC) $(OBJ) -o main

main.o: main.cpp tcomplejo.h
	$(COMP) $(OPC) -c main.cpp

tcomplejo.o: tcomplejo.h tcomplejo.cpp
	$(COMP) $(OPC) -c tcomplejo.cpp