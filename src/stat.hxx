#include "bytes.hxx"

#include <filesystem>
#include <string>
#include <unordered_map>

#include <Zydis/Zydis.h>

class Stat {
public:
    Stat();

    void accumulate_stat(std::filesystem::path const &path);
    void print_stat();

private:
    void accumulate_stat(Byte const *begin, Byte const *end);

    std::unordered_map<std::string, size_t> stats_;

    ZydisDecoder decoder_;
    ZydisFormatter formatter_;
};
