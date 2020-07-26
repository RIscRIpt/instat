#include "stat.hxx"

#include <iostream>

int wmain(int argc, wchar_t *argv[])
{
    if (argc != 2) {
        std::cerr << "recontext.exe <filename>\n";
        return EXIT_FAILURE;
    }

#ifdef NDEBUG
    try
#endif
    {
        Stat s;
        s.accumulate_stat(argv[1]);
        s.print_stat();
    }
#ifdef NDEBUG
    catch (std::exception const &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
#endif

    return EXIT_SUCCESS;
}
