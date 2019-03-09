all: chess;

imp.o:
	g++ --std=c++17 -g -c -o imp.o imp.cpp 
        
piece.o:
	g++ --std=c++17 -g -c -o piece.o piece/piece.cpp
     
alg.o:
	g++ --std=c++17 -g -c -o alg.o algorithm/alg.cpp
      
arrangement.o:
	g++ --std=c++17 -g -c -o arrangement.o algorithm/arrangement.cpp

tests.o:
	g++ --std=c++17 -g -c -o tests.o tests/tests.cpp

main.o:
	g++ --std=c++17 -g -c -o main.o main.cpp
         
chess: imp.o piece.o alg.o arrangement.o tests.o main.o
	g++ -g -o chess imp.o piece.o alg.o arrangement.o tests.o main.o
	./chess
      
clean:
	rm -rf *.o chess
