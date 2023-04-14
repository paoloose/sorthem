#pragma once
#include <iostream>

#if defined(_WIN32)
#  include <io.h>
#  define isatty _isatty
#  define STDIN_FILENO 0
#else
#  include <unistd.h>
#endif

void exit_if_bad_usage() {
    if (isatty(STDIN_FILENO)) {
        // if user didn't pipe the output of a program
        std::cerr << "Bad usage: no output has been piped\n";
        std::cerr << "pipe the output of your sorting program to visualize it\n";
        std::cerr << "Example: ./sort_program | sorthem\n";
        exit(-1);
    }
}
