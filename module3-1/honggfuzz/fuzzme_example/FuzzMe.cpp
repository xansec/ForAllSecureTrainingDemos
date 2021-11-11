#include "HonggfuzzTestOneInput.hpp"

bool FuzzMe(const uint8_t *data, size_t size)
{
    return size >= 3 &&
        data[0] == 'F' &&
        data[1] == 'U' &&
        data[2] == 'Z' &&
        data[3] == 'Z'; //buffer overread
}

int dontcallme() {
	//I am never called, muahahaha!
	return 42;
}

/**
* \brief Fuzzing entry-point.
* \param[in] data: the fuzzed input buffer.
* \param[in] size: the size of the bffer.
*/
int HonggfuzzTestOneInput(const uint8_t *data, size_t size)
{
    FuzzMe(data, size);

    return 0;
}
