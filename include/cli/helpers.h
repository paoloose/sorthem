#pragma once
#include <iostream>

#if defined(_WIN32)
#  include <io.h>
#  define isatty _isatty
#  define popen _popen
#  define pclose _pclose
#  define STDIN_FILENO 0
#  define TMP_FILE "C:\\Windows\\Temp\\sorthem_operations.tmp"
#else
#  include <unistd.h>
#  define TMP_FILE "/tmp/sorthem_operations.tmp"
#endif

void exit_if_bad_usage() {
    // if user didn't pipe the output of a program
    if (isatty(STDIN_FILENO)) {

#if not defined(DEBUG)
        std::cerr << "Bad usage: no output has been piped\n\n";
        std::cerr << "pipe the output of your sorting program to visualize it\n";
        std::cerr << "Example: ./sort_program | sorthem\n";
        exit(1);
#else
    // This process will be used when debugging (without needing to pipe a program)
#   define DEBUGGING_PROCESS_CMD "node ./examples/bubble_sort.js"

        std::cout << "Note: sorthem is running in debug mode\n";

        FILE* process = popen(DEBUGGING_PROCESS_CMD, "r");
        FILE* output = fopen(TMP_FILE, "w");

        char buffer[BUFSIZ];
        while (fgets(buffer, BUFSIZ, process)) {
            fputs(buffer, output);
        }

        pclose(process);
        fclose(output);
        freopen(TMP_FILE, "r", stdin);
#endif
    }
}
