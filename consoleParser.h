/* ############################################################################################################### */
/* Do not forget to INITIALIZE and DESTROY the __OPTIONS_DATA__ structure after use in main() (or where necessary) */
/* ############################################################################################################### */

#ifndef CONSOLE_PARSER_H_
#define CONSOLE_PARSER_H_

#include <cstdlib>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

#include "customWarning.h"

#define FREE_(ptr) { \
    free(ptr);       \
    ptr = NULL;      \
}

#define CREATE_OPTION(optionsBuffer, flagName, hasArgValue, shortName, flagValue) { \
  customWarning(optionsCount < MAX_OPTIONS_COUNT, (void) 1);                        \
                                                                                    \
  optionsBuffer[optionsCount].name    = flagName;                                   \
  optionsBuffer[optionsCount].has_arg = hasArgValue;                                \
  optionsBuffer[optionsCount].val     = shortName;                                  \
  optionsBuffer[optionsCount].flag    = flagValue;                                  \
                                                                                    \
  optionsCount++;                                                                   \
}                                                                                   \

#define INITIALIZE_OPTION_LIST() {}

#ifndef _NDEBUG
  #define PRINT_OPTION() printf("Option: [-%c]\t %s\n", gotOption, optarg)
#else
    #define PRINT_OPTION()
#endif // _NDEBUG

struct _OPTIONS_ {};

enum class parseError {
    NO_MORE_OPTIONS = -1,
    NO_ERRORS       =  0,
    CALLOC_ERROR    =  1
};

static const size_t MAX_OPTIONS_COUNT  = 1;

static _OPTIONS_ __OPTIONS_DATA__ = {};

parseError __OPTIONS_DATA_INITIALIZE__() {
    return parseError::NO_ERRORS;
}

parseError __OPTIONS_DATA_DESTRUCT__() {
    return parseError::NO_ERRORS;
}

parseError parseConsole(int argc, char *argv[]) {
    size_t optionsCount                 = 0;
    option options[MAX_OPTIONS_COUNT]   = {};
    const char *optString               = "";

    INITIALIZE_OPTION_LIST();

    int gotOption = 0;

    while ((gotOption = getopt_long(argc, argv, optString, options, NULL))
            != (int) parseError::NO_MORE_OPTIONS) {
        PRINT_OPTION();

        switch (gotOption) {
            default:
                break;
        }
    }

    return parseError::NO_ERRORS;
}

#endif // CONSOLE_PARSER_H_