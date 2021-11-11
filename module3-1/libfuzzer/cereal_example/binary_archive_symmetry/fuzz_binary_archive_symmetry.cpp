#include <string>
#include <sstream>
#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
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
