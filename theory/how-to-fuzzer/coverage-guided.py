import random
import sys

def crash():
    assert False

def add_coverage(coverage: set):
    location = sys._getframe().f_back.f_lineno
    coverage.add(location)

def fuzzme(data: bytes, coverage: set):
    add_coverage(coverage)

    if len(data) < 4:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    if data[0] != 0x66:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    if data[1] != 0x75:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    if data[2] != 0x7a:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    if data[3] != 0x7a:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    crash()

def generate_testcase(seed: bytes):
    testcase = bytearray(seed)

    mutation = random.choice(["random-overwrite", "random-append", "random-chunk"])
    if mutation == "random-overwrite":
        index = random.randint(0, len(testcase) - 1)
        val = random.randint(0,255)
        testcase[index] = val
    if mutation == "random-append":
        val = random.randint(0,255)
        testcase.append(val)
    if mutation == "random-chunk":
        val = random.randint(0,255)
        n = random.randint(2,64)
        for _ in range(n):
            testcase.append(val)

    return bytes(testcase)

def main():
    coverage = set()
    corpus = [b'A']
    while True:
        seed = random.choice(corpus)
        test_case = generate_testcase(seed)
        new_coverage = set()
        try:
            fuzzme(test_case, new_coverage)
            if len(new_coverage - coverage) > 0:
                print("Test case with new coverage discovered!")
                print(test_case)
                corpus.append(test_case)
                coverage |= new_coverage
        except AssertionError:
            print("Found crashing input!")
            print(test_case)
            return


if __name__ == "__main__":
    main()
