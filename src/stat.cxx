#include "stat.hxx"
#include "zyan_error.hxx"

#include "pe.hxx"

#include <iostream>

Stat::Stat()
{
    ZYAN_THROW(ZydisDecoderInit(&decoder_,
                                ZYDIS_MACHINE_MODE_LONG_64,
                                ZYDIS_ADDRESS_WIDTH_64));
    ZYAN_THROW(ZydisFormatterInit(&formatter_, ZYDIS_FORMATTER_STYLE_INTEL));
}

void Stat::accumulate_stat(std::filesystem::path const &path)
{
    PE pe(path);
    for (auto const &section : pe.image_sections()) {
        if (!(section.Characteristics & IMAGE_SCN_CNT_CODE)) {
            continue;
        }
        auto section_begin = pe.data() + section.PointerToRawData;
        auto section_end =
            section_begin
            + std::min(section.SizeOfRawData, section.Misc.VirtualSize);
        accumulate_stat(section_begin, section_end);
    }
}

void Stat::accumulate_stat(Byte const *begin, Byte const *end)
{
    ZydisDecodedInstruction instruction;
    std::vector<char> buffer(256);
    while (begin < end) {
        auto status = ZydisDecoderDecodeBuffer(&decoder_, begin, end - begin, &instruction);
        if (ZYAN_FAILED(status)) {
            begin++;
            continue;
        }
        ZYAN_THROW(ZydisFormatterFormatInstruction(&formatter_,
                                                   &instruction,
                                                   buffer.data(),
                                                   buffer.size(),
                                                   0));
        if (auto mnemonic_end = std::find(buffer.begin(), buffer.end(), ' ');
            mnemonic_end != buffer.end()) {
            *mnemonic_end = '\0';
        }
        stats_[buffer.data()]++;
        begin += instruction.length;
    }

}

void Stat::print_stat()
{
    using entry = std::pair<std::string, size_t>;
    std::vector<entry> sorted_stats;
    for (auto const &[mnemonic, count] : stats_) {
        sorted_stats.emplace_back(mnemonic, count);
    }
    std::sort(
        sorted_stats.begin(),
        sorted_stats.end(),
        [](entry const &a, entry const &b) { return a.second > b.second; });
    for (auto const &[mnemonic, count] : sorted_stats) {
        std::cout << mnemonic << ':' << count << '\n';
    }
}
