import random

def crash():
    assert False

def fuzzme(data: bytes):
    if data[0] != 0x66:
        return
    if data[1] != 0x75:
        return
    if data[2] != 0x7a:
        return
    if data[3] != 0x7a:
        return

    crash()

def generate_testcase():
    # we can make this better by knowing what our fuzzme expects (relate to blind protocol fuzzers)
    return random.randbytes(5)

def main():
    while True:
        test_case = generate_testcase()
        try:
            fuzzme(test_case)
        except AssertionError:
            print("Found crashing input!")
            print(test_case)
            return


if __name__ == "__main__":
    main()
