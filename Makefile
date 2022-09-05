CFLAGS := -std=c99 -O2 -DCONTEST -s -static -lm
FILE := smalltank
CC := gcc
default:
	${CC} ${CFLAGS} ${FILE}.c -o ${FILE} 
clean:
	rm ${FILE}
	rm ${FILE}.out
install:
	${CC} ${CFLAGS} ${FILE}.c -o ${FILE}
