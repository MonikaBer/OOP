all: pixels;

imp.o:
	g++ --std=c++11 -g -c -o imp.o imp.cpp 
        
picture.o:
	g++ --std=c++11 -g -c -o picture.o picture/picture.cpp
           
main.o:
	g++ --std=c++11 -g -c -o main.o main.cpp
      
tests.o:
	g++ --std=c++11 -g -c -o tests.o tests.cpp      
         
pixels: imp.o picture.o main.o
	g++ -g -o pixels imp.o picture.o main.o
	./pixels ./resources
    
tests: imp.o picture.o tests.o
	g++ -g -o tests imp.o picture.o tests.o
	./tests
      
clean:
	rm -rf *.o pixels tests
