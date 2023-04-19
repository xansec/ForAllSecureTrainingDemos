INCLUDE=./lib
OUT=./out
SRC=./src
TEST=./test
FUZZ=./mayhem
CC=gcc
CFLAGS=-g -Wall -I$(INCLUDE)

all: main test fuzz 

main: out
	$(CC) $(CFLAGS) -o $(OUT)/calculator $(SRC)/main.c $(SRC)/calculator.c

test: out
	$(CC) $(CFLAGS) -o $(OUT)/test_calculator $(TEST)/test_calculator.c $(SRC)/calculator.c

fuzz: out
	$(CC) $(CFLAGS) -o $(OUT)/fuzz_calculator $(FUZZ)/fuzz_calculator.c $(SRC)/calculator.c
out:
	mkdir $(OUT)
clean:
	-rm -rf $(OUT)
