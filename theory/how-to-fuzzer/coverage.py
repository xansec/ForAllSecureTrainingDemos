import random

def crash():
    assert False

def add_coverage(coverage: set, location: int):
    coverage.add(location)

def fuzzme(data: bytes, coverage: set):
    add_coverage(coverage, 0)

    if data[0] != 0x66:
        add_coverage(coverage, 1)
        return

    add_coverage(coverage, 2)

    if data[1] != 0x75:
        add_coverage(coverage, 3)
        return

    add_coverage(coverage, 4)

    if data[2] != 0x7a:
        add_coverage(coverage, 5)
        return

    add_coverage(coverage, 6)

    if data[3] != 0x7a:
        add_coverage(coverage, 7)
        return

    add_coverage(coverage, 8)

    crash()

def generate_testcase():
    return random.randbytes(5)

def main():
    coverage = set()
    while True:
        test_case = generate_testcase()
        new_coverage = set()
        try:
            fuzzme(test_case, new_coverage)
            if len(new_coverage - coverage) > 0:
                print("Test case with new coverage discovered!")
                print(test_case)
                coverage |= new_coverage
        except AssertionError:
            print("Found crashing input!")
            print(test_case)
            return


if __name__ == "__main__":
    main()
