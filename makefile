all:
	g++ -Wall -lpthread -latomic programs/*.cpp -o main.elf
format:
	clang-format -style=file -i programs/*
clean:
	rm -f *.o main.elf