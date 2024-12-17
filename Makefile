all:
	gcc -Wall --pedantic src/*.c -o gauss

test: all
	gauss dane/A dane/b
