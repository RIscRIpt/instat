#pragma once

#include <filesystem>
#include <vector>

using Byte = unsigned char;

class Bytes {
public:
    using Container = std::vector<Byte>;

    Bytes(std::filesystem::path const &path);

    Container::value_type const *data() const;

private:
    Container bytes_;
};
