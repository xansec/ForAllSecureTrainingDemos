#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

int HonggfuzzTestOneInput(const uint8_t* data, size_t size);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* unsanitized_data, size_t size)
{
    /* honggfuzz doesn't ASan-itize the unsanitized_data function arg.
     * Copying the unsanitized_data buffer into a container ensures that
     * ASan will analyze the copy-destination container.
     */
    const std::vector<uint8_t> data_vector{unsanitized_data, unsanitized_data + size};
    const uint8_t* data = data_vector.data();
    return HonggfuzzTestOneInput(data, size);
}
