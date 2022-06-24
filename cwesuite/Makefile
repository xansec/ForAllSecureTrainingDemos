CC=gcc
CCFLAGS=-w -static
CLANG=clang
CLANGFLAGS=-fsanitizer=address

filename=cwesuite.c
basics=CWE20 CWE121 CWE125b CWE369 CWE476 CWE787b CWE913b
basic_flags=-DBASIC -DCWE20 -DCWE121 -DCWE125b -DCWE369 -DCWE476 -DCWE787b -DCWE913b
advanceds=CWE119 CWE125a CWE131 CWE401 CWE457 CWE590 CWE704 CWE787a CWE913a
advanced_flags=-DADVANCED -DCWE119 -DCWE125a -DCWE131 -DCWE401 -DCWE457 -DCWE590 -DCWE704 -DCWE787a -DCWE913a
#TBD: sanitizers=<...>

.PHONY: docker
docker:
	docker build -t $(USER)/cwesuite .

.PHONY: all
all:
	$(CC) $(CCFLAGS) $(basic_flags) $(advanced_flags) -o all $(filename)

.PHONY: basic
basic:
	$(CC) $(CCFLAGS) $(basic_flags) -o basic $(filename)

CWE20:
	$(CC) $(CCFLAGS) -DBASIC -D$@ -o $@ $(filename)

CWE121:
	$(CC) $(CCFLAGS) -DBASIC -D$@ -o $@ $(filename)

CWE125b:
	$(CC) $(CCFLAGS) -DBASIC -D$@ -o $@ $(filename)

CWE369:
	$(CC) $(CCFLAGS) -DBASIC -D$@ -o $@ $(filename)

CWE476:
	$(CC) $(CCFLAGS) -DBASIC -D$@ -o $@ $(filename)

CWE787b:
	$(CC) $(CCFLAGS) -DBASIC -D$@ -o $@ $(filename)

CWE913b:
	$(CC) $(CCFLAGS) -DBASIC -D$@ -o $@ $(filename)

.PHONY: advanced
	# NOTE: these must be run with advanced triage in Mayhem in order to trigger the CWEs!
advanced:
	$(CC) $(CCFLAGS) $(advanced_flags) -o advanced $(filename)

CWE119:
	$(CC) $(CCFLAGS) -DADVANCED -D$@ -o $@ $(filename)

CWE125a:
	$(CC) $(CCFLAGS) -DADVANCED -D$@ -o $@ $(filename)

CWE131:
	$(CC) $(CCFLAGS) -DADVANCED -D$@ -o $@ $(filename)

CWE401:
	$(CC) $(CCFLAGS) -DADVANCED -D$@ -o $@ $(filename)

CWE457:
	$(CC) $(CCFLAGS) -DADVANCED -D$@ -o $@ $(filename)

CWE590:
	$(CC) $(CCFLAGS) -DADVANCED -D$@ -o $@ $(filename)

CWE704:
	$(CC) $(CCFLAGS) -DADVANCED -D$@ -o $@ $(filename)

CWE787a:
	$(CC) $(CCFLAGS) -DADVANCED -D$@ -o $@ $(filename)

CWE913a:
	$(CC) $(CCFLAGS) -DADVANCED -D$@ -o $@ $(filename)

.PHONY: clean
clean:
	-rm $(basics) $(advanceds) basic advanced all > /dev/null 2>&1
