import random
import sys

def crash():
    assert False

def add_coverage(coverage: set):
    location = sys._getframe().f_back.f_lineno
    coverage.add(location)

def fuzzme(data: bytes, coverage: set):
    add_coverage(coverage)

    delim = b"DICT"

    idx = data.find(delim)

    if idx == -1:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    if idx + len(delim) >= len(data) or data[idx + len(delim)] != 0x66:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    idx = data.find(delim, idx + 1)

    if idx == -1:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    if idx + len(delim) >= len(data) or data[idx + len(delim)] != 0x75:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    idx = data.find(delim, idx + 1)

    if idx == -1:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    if idx + len(delim) >= len(data) or data[idx + len(delim)] != 0x7a:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    idx = data.find(delim, idx + 1)

    if idx == -1:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    if idx + len(delim) >= len(data) or data[idx + len(delim)] != 0x7a:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    crash()

def mutate(testcase: bytearray, dictionary: list):
    mutation = random.choice(["random-overwrite", "random-append", "random-chunk", "dict-overwrite"])
    if mutation == "random-overwrite":
        index = random.randint(0, len(testcase) - 1)
        val = random.randint(0,255)
        testcase[index] = val
    if mutation == "random-append":
        val = random.randint(0,255)
        testcase.append(val)
    if mutation == "random-chunk":
        val = random.randint(0,255)
        n = random.randint(2,16)
        for _ in range(n):
            testcase.append(val)
    if mutation == "dict-overwrite":
        word = random.choice(dictionary)
        if len(word) <= len(testcase):
            idx = random.randint(0, len(testcase) - len(word))
            testcase[idx:idx+len(word)] = word

def generate_testcase(seed: bytes, dictionary: list):
    testcase = bytearray(seed)

    # stack mutations
    for _ in range(random.randint(1, 5)):
        mutate(testcase, dictionary)

    return bytes(testcase)

def main():
    coverage = set()
    corpus = [b'A']
    while True:
        seed = random.choice(corpus)
        test_case = generate_testcase(seed, [b"DICT"])
        new_coverage = set()
        try:
            fuzzme(test_case, new_coverage)
            if len(new_coverage - coverage) > 0:
                print("Test case with new coverage discovered! (lines: {})".format(list(sorted(new_coverage))))
                print(test_case)
                corpus.append(test_case)
                coverage |= new_coverage
        except AssertionError:
            print("Found crashing input!")
            print(test_case)
            return


if __name__ == "__main__":
    main()
