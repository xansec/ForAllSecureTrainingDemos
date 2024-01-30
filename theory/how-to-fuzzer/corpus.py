import random
import sys
import os

def crash():
    assert False

def add_coverage(coverage: set):
    location = sys._getframe().f_back.f_lineno
    coverage.add(location)

def fuzzme(data: bytes, coverage: set):
    add_coverage(coverage)

    if len(data) < 8:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    if data[:4] != b'CORP':
        add_coverage(coverage)
        return

    add_coverage(coverage)

    if data[4] != 0x66:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    if data[5] != 0x75:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    if data[6] != 0x7a:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    if data[7] != 0x7a:
        add_coverage(coverage)
        return

    add_coverage(coverage)

    crash()

def generate_testcase(seed: bytes, dictionary: list):
    testcase = bytearray(seed)

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

    return bytes(testcase)

def load_corpus(corpus_dir):
    corpus = []
    for f in os.listdir(corpus_dir):
        path = os.path.join(corpus_dir, f)
        if not os.path.isfile(path):
            continue
        testcase = open(path, "rb").read()
        corpus.append(testcase)
    return corpus

def main(corpus_dir):
    coverage = set()
    corpus = [b'A'] + load_corpus(corpus_dir)
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
    if len(sys.argv) < 2:
        print("usage: {} <corpus dir>".format(sys.argv[0]))
        sys.exit(1)
    main(sys.argv[1])
