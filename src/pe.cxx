#include "pe.hxx"

PE::PE(std::filesystem::path const &path)
    : bytes_(Bytes(path))
{
    auto file_header = image_file_header();
    if (file_header->Machine != IMAGE_FILE_MACHINE_AMD64) {
        throw std::runtime_error("unsupported architecture");
    }
}

Byte const *PE::data() const
{
    return bytes_.data();
}

IMAGE_DOS_HEADER const *PE::image_dos_header() const
{
    return reinterpret_cast<IMAGE_DOS_HEADER const *>(data());
}

IMAGE_NT_HEADERS const *PE::image_nt_headers() const
{
    return reinterpret_cast<IMAGE_NT_HEADERS const *>(
        data() + image_dos_header()->e_lfanew);
}

IMAGE_SECTION_HEADER const *PE::image_first_section() const
{
    return IMAGE_FIRST_SECTION(image_nt_headers());
}

IMAGE_FILE_HEADER const *PE::image_file_header() const
{
    return &image_nt_headers()->FileHeader;
}

PE::Sections PE::image_sections() const
{
    IMAGE_SECTION_HEADER const *begin = image_first_section();
    return Sections(begin, begin + image_file_header()->NumberOfSections);
}
