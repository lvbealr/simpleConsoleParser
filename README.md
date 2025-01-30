# simpleConsoleParser

## Usage
#### `consoleParser.h`
```c
// INSERT OPTIONS CREATING HERE. Ex.:
#define INITIALIZE_OPTION_LIST() {
    CREATE_OPTION(options, "dumpFolder", 2, 'd', 0); \
}
...
// CREATE STRUCTURE FIELDS IF NECESSARY TO RECORD DATA. Ex.:
struct _OPTIONS_ {
    const char *dumpFile = {};
};
...

// SET YOUR OWN VALUE OF MAX_OPTIONS_COUNT!
static const size_t MAX_OPTIONS_COUNT  = 1;
// CREATE NECESSARY OBJECTS! Ex.:
static const size_t MAX_DUMP_FILE_NAME = 50;
...

// INITIALIZE STRUCTURE FIELDS! Ex.:
parseError __OPTIONS_DATA_INITIALIZE__() {
    __OPTIONS_DATA__.dumpFile = (char *)calloc(MAX_DUMP_FILE_NAME, sizeof(char));
    customWarning(__OPTIONS_DATA__.dumpFile != NULL, parseError::CALLOC_ERROR);
    
    return parseError::NO_ERRORS;
}

// CLEAR THE FIELD OF THE STRUCTURE, FREE VIRTUAL MEMORY IF NECESSARY! Ex.:
parseError __OPTIONS_DATA_DESTRUCT__() {
//    FREE_(__OPTIONS_DATA__.dumpFile);
    return parseError::NO_ERRORS;
}

parseError parseConsole(int argc, char *argv[]) {
    ...
    // SET YOUR OWN VALUE OF optString! (use bash >> man getopt). Ex.:
    const char *optString = "d:";
    ...
    
    while ((gotOption = getopt_long(argc, argv, optString, options, NULL))
            != parseError::NO_MORE_OPTIONS) {
        ...
        // COME UP WITH YOUR OWN INSTRUCTIONS FOR VARIOUS FLAGS
        // (IMPORTANT! WRITE DATA TO THE __OPTIONS_DATA__ STRUCTURE). Ex.:
        switch (gotOption) {
             case 'd': {
                 strncpy((char *)__OPTIONS_DATA__.dumpFile, optarg, MAX_DUMP_FILE_NAME);
                 break;
             }
             ...
             default:
                 break;
        }
    }
    
    return parseError::NO_ERRORS;
}

#endif // CONSOLE_PARSER_H_
```

#### `main.cpp`
```c
int main(int argc, char *argv[]) {
    __OPTIONS_DATA_INITIALIZE__();
    parseConsole(argc, argv);
    __OPTIONS_DATA_DESTRUCT__();
    ...
}
```