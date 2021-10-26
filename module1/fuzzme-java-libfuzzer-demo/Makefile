CC=javac

all:
	mkdir -p build
	$(CC) -d build FuzzMe.java
	cd build
	jar cvf FuzzMe.jar *

clean:
	-rm -rf build FuzzMe.jar

