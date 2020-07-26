#pragma once

#include "bytes.hxx"

#include <filesystem>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

class PE {
public:
    template<typename T>
    class Range {
    public:
        Range(T const *begin, T const *end)
            : begin_(begin)
            , end_(end)
        {
        }

        inline T const *begin() const { return begin_; }
        inline T const *end() const { return end_; }

    private:
        T const *begin_;
        T const *end_;
    };

    using Sections = Range<IMAGE_SECTION_HEADER>;

    PE(std::filesystem::path const &path);

    Byte const *data() const;
    IMAGE_DOS_HEADER const *image_dos_header() const;
    IMAGE_FILE_HEADER const *image_file_header() const;
    Sections image_sections() const;

private:
    IMAGE_NT_HEADERS const *image_nt_headers() const;
    IMAGE_SECTION_HEADER const *image_first_section() const;

    Bytes bytes_;
};
