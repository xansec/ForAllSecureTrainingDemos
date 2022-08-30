#include <string>
#include <sstream>
#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>
#include "HonggfuzzTestOneInput.hpp"

int HonggfuzzTestOneInput(const uint8_t *data, size_t size)
{
	std::string o_string(data, data+size);
	std::ostringstream os;
	{
		cereal::BinaryOutputArchive oar(os);
		oar(o_string);
	}

	std::string i_string;
	std::istringstream is(os.str());
	{
		cereal::BinaryInputArchive iar(is);
		iar(i_string);
	}
	if (i_string != o_string) abort();

	return 0;
}

extern "C" int HF_ITER(const uint8_t** data, size_t* size);

int main(void) {
	for (;;) {
		size_t size;
		const uint8_t *data;

		HF_ITER(&data, &size);

		HonggfuzzTestOneInput(data, size);
	}
}
