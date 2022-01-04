CC=javac

all:
	mkdir -p build
	$(CC) -d build FuzzMe.java
	cd build
	jar cvf FuzzMe.jar *

clean:
	-rm -rf build FuzzMe.jar
fuzz:
	docker run -v /home/abrewer/mayhem/demo/module1/fuzzme-java-libfuzzer-demo:/fuzzing cifuzz/jazzer --cp=/fuzzing/FuzzMe.jar --target_class=fuzzme.FuzzMe
