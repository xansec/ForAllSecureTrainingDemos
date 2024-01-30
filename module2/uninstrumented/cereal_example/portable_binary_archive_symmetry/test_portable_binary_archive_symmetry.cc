#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>
#include <filesystem>
#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>

int neverCalled() {
  return 1337;
}

int main(int argc, char *argv[])
{
  //check if file exists
  if (argc < 2)
  {
    std::cout << "Missing input file" << std::endl;
    return -1;
  }
  std::string filename = argv[1];
  if (!std::filesystem::exists(filename))
  {
    std::cout << "Input file does not exist" << std::endl;
    return -1;
  }

  //get file
  std::ifstream file(filename, std::ios::binary);
  file.unsetf(std::ios::skipws);

  //get size
  std::streampos fsize;
  file.seekg(0, std::ios::end);
  fsize = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<uint8_t> o_vector;
  o_vector.reserve(fsize);
  o_vector.insert(o_vector.begin(), std::istream_iterator<uint8_t>(file), std::istream_iterator<uint8_t>());

  std::ostringstream os(std::stringstream::binary);
  {
    cereal::PortableBinaryOutputArchive oar(os);
    oar(cereal::binary_data(o_vector.data(), static_cast<std::size_t>(o_vector.size() * sizeof(uint8_t))));
  }

  std::vector<uint8_t> i_vector(fsize);
  std::istringstream is(os.str(), std::stringstream::binary);
  {
    cereal::PortableBinaryInputArchive iar(is);
    iar(cereal::binary_data(i_vector.data(), static_cast<std::size_t>( i_vector.size() * sizeof(uint8_t))));
  }

  if (i_vector != o_vector) abort();

  return 0;
}
