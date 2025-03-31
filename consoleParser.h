/* ############################################################################################################### */
/* Do not forget to INITIALIZE and DESTROY the __OPTIONS_DATA__ structure after use in main() (or where necessary) */
/* ############################################################################################################### */

#ifndef CONSOLE_PARSER_H_
#define CONSOLE_PARSER_H_

#include <cstdlib>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdint.h>

#include "customWarning.h"

#define FREE_(ptr) { \
    free(ptr);       \
    ptr = NULL;      \
}

#define CREATE_OPTION(optionsBuffer, flagName, hasArgValue, shortName, flagValue) { \
  customWarning(optionsCount < MAX_OPTIONS_COUNT, parseError::NO_MORE_OPTIONS);     \
                                                                                    \
  optionsBuffer[optionsCount].name    = flagName;                                   \
  optionsBuffer[optionsCount].has_arg = hasArgValue;                                \
  optionsBuffer[optionsCount].val     = shortName;                                  \
  optionsBuffer[optionsCount].flag    = flagValue;                                  \
                                                                                    \
  optionsCount++;                                                                   \
}

#define INITIALIZE_OPTION_LIST() {                 \
    CREATE_OPTION(options, "count", 2, 'c', 0);    \
    CREATE_OPTION(options, "maxValue", 2, 'm', 0); \
}

#ifndef _NDEBUG
  #define PRINT_OPTION() printf("Option: [-%c]\t %s\n", gotOption, optarg)
#else
    #define PRINT_OPTION()
#endif // _NDEBUG

struct _OPTIONS_ {
    size_t elementsCount;
    uint32_t maxValue;
};

enum class parseError {
    NO_MORE_OPTIONS = -1,
    NO_ERRORS       =  0,
    CALLOC_ERROR    =  1
};

static const size_t MAX_OPTIONS_COUNT = 2;

static _OPTIONS_ __OPTIONS_DATA__ = {};

static parseError __OPTIONS_DATA_INITIALIZE__() {
    __OPTIONS_DATA__.elementsCount = {};
    __OPTIONS_DATA__.maxValue      = {};

    return parseError::NO_ERRORS;
}

static parseError __OPTIONS_DATA_DESTRUCT__() {
    __OPTIONS_DATA__.elementsCount = {};
    __OPTIONS_DATA__.maxValue      = {};

    return parseError::NO_ERRORS;
}

static parseError parseConsole(int argc, char *argv[]) {
    size_t optionsCount                 = 0;
    option options[MAX_OPTIONS_COUNT]   = {};
    const char *optString               = "";

    INITIALIZE_OPTION_LIST();

    int gotOption = 0;

    while ((gotOption = getopt_long(argc, argv, optString, options, NULL))
            != (int) parseError::NO_MORE_OPTIONS) {
        PRINT_OPTION();

        switch (gotOption) {
        	case 'c': {
            	__OPTIONS_DATA__.elementsCount = strtoul(optarg, NULL, 10);
                break;
            }

            case 'm': {
              	__OPTIONS_DATA__.maxValue = strtoul(optarg, NULL, 10);
                break;
            }

            default:
                break;
        }
    }

    return parseError::NO_ERRORS;
}

#endif // CONSOLE_PARSER_H_