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
    # generate testcase here
    pass

def main():
    while True:
        # fuzz!
        pass


if __name__ == "__main__":
    main()
