all:
	g++ *.cpp Code/*.cpp -o main -fsanitize=address -g
	./main