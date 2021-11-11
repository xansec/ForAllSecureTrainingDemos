CC=aarch64-linux-gnu-gcc
OUTPUT=fuzzme
QEMU=qemu-aarch64

all:
	$(CC) -o $(OUTPUT) -g -static fuzzme.c
run-qemu:
	$(QEMU) ./$(OUTPUT) ./corpus/bug
clean:
	-rm $(OUTPUT)
