CC=gcc
OUTPUT=fuzzme

all:
	$(CC) -o $(OUTPUT) -Wno-div-by-zero -fno-stack-protector -zexecstack -no-pie fuzzme.c

clean:
	-rm $(OUTPUT)
