mysql: main.o data.o admin.o 
	g++ -o mysql main.o data.o admin.o 
data.o: data.cpp
	g++ -c -o data.o data.cpp
admin.o: admin.cpp
	g++ -c -o admin.o admin.cpp	
main.o: main.cpp
	g++ -c -o main.o main.cpp
clean:
	rm mysql *.o
