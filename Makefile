all: target run clean

.PHONY: all

target:
	gcc -Wall -Werror -g *.c -o main.out
run:
	valgrind --leak-check=full ./main.out < test.txt
clean:
	rm main.out
