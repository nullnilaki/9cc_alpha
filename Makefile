9cc: 9cc.c
	cc -o 9cc 9cc.c

test: 9cc
	./test.sh

clean:
	rm -f 9cc *.o *~ tmp*
