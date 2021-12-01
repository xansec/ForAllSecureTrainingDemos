RUSTC=rustc

all: base libfuzzer

base: 
	$(RUSTC) -o ./fuzzme-base fuzzme-base.rs
libfuzzer:
	-cargo init
	cargo fuzz init --fuzz-dir ./fuzz -t fuzzme-libfuzzer
	cargo fuzz build --verbose

honggfuzz:
	-cargo init
	echo "honggfuzz = \"0.5\"" >> Cargo.toml 
	cp fuzzme-honggfuzz.rs src/main.rs 
	RUSTFLAGS="-Znew-llvm-pass-manager=no" cargo hfuzz build 

clean:
	-rm -rf ./fuzzme-base ./fuzz Cargo.toml Cargo.lock ./src ./hfuzz_target ./hfuzz_workspace
