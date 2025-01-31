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

#define CREATE_OPTION(optionsBuffer, flagName, hasArgValue, shortName, flagValue)        { \
  customWarning(optionsCount < MAX_OPTIONS_COUNT, parseError::MAX_OPTIONS_NUMBER_REACHED); \
                                                                                           \
  optionsBuffer[optionsCount].name    = flagName;                                          \
  optionsBuffer[optionsCount].has_arg = hasArgValue;                                       \
  optionsBuffer[optionsCount].val     = shortName;                                         \
  optionsBuffer[optionsCount].flag    = flagValue;                                         \
                                                                                           \
  optionsCount++;                                                                          \
}                                                                                          \

#define INITIALIZE_OPTION_LIST() {                   \
    CREATE_OPTION(options, "dumpFolder", 2, 'd', 0); \
}

#ifndef _NDEBUG
  #define PRINT_OPTION() printf("Option: [-%c]\t %s\n", gotOption, optarg)
#else
    #define PRINT_OPTION()
#endif // _NDEBUG

struct _OPTIONS_ {
    char *dumpFolderName = {};
};

enum class parseError {
    NO_MORE_OPTIONS            = -1,
    NO_ERRORS                  =  0,
    CALLOC_ERROR               =  1,
    MAX_OPTIONS_NUMBER_REACHED =  2
};

static const size_t MAX_OPTIONS_COUNT  = 1;

static _OPTIONS_ __OPTIONS_DATA__ = {};

static const char *DEFAULT_DUMP_FOLDER_NAME = "dumpFolder";

parseError __OPTIONS_DATA_INITIALIZE__() {
    __OPTIONS_DATA__.dumpFolderName = (char *)calloc(MAX_DUMP_FOLDER_NAME, sizeof(char));
    customWarning(__OPTIONS_DATA__.dumpFolderName != NULL, parseError::CALLOC_ERROR);

    return parseError::NO_ERRORS;
}

parseError __OPTIONS_DATA_DESTRUCT__() {
    FREE_(__OPTIONS_DATA__.dumpFolderName);

    return parseError::NO_ERRORS;
}

parseError parseConsole(int argc, char *argv[]) {
    size_t optionsCount                 = 0;
    option options[MAX_OPTIONS_COUNT]   = {};
    const char *optString               = "d:";

    // INITIALIZE BY DEFAULT VALUES //
    strncpy(__OPTIONS_DATA__.dumpFolderName, DEFAULT_DUMP_FOLDER_NAME, MAX_DUMP_FOLDER_NAME);
    // INITIALIZE BY DEFAULT VALUES //

    INITIALIZE_OPTION_LIST();

    int gotOption = 0;

    while ((gotOption = getopt_long(argc, argv, optString, options, NULL))
            != (int) parseError::NO_MORE_OPTIONS) {
        PRINT_OPTION();

        switch (gotOption) {
            case 'd': {
                __OPTIONS_DATA__.dumpFolderName = {};
                strncpy(__OPTIONS_DATA__.dumpFolderName, optarg, MAX_DUMP_FOLDER_NAME);
                break;
            }

            default:
                break;
        }
    }

    return parseError::NO_ERRORS;
}

#endif // CONSOLE_PARSER_H_