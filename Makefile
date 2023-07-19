all:
	g++ *.cpp -o main -fsanitize=address -g
	./main