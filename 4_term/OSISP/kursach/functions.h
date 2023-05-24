#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


struct Flags {
    char *in_file;
    char *out_file;
    int block_size;
    int seek;
    int skip;
    int progressFlag;
    int uppercaseflag;
    int lowercaseflag;
};


char* toLowerCase(char* buf, int size) {
    for(int i = 0; i < size; i++) {
        buf[i] = tolower(buf[i]);
    }
    return buf;
}

char* toUpperCase(char* buf, int size) {
    for(int i = 0; i < size; i++) {
        buf[i] = toupper(buf[i]);
    }
    return buf;
}

struct Flags parseCMD(int argc, char *argv[]) {

    struct Flags options;

    options.block_size = 8;
    options.seek = 0;
    options.skip = 0;
    options.progressFlag = 0;
    options.lowercaseflag = 0;
    options.uppercaseflag = 0;

    options.in_file = argv[1];
    options.out_file = argv[2];

    for(int i = 3; i < argc; i++ ) {
        if(argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'b':
                    options.block_size = atoi(argv[i+1]);
                    break;

                case 's': {
                    if(argv[i][2] == 'k') {
                        options.skip = atoi(argv[i+1]);
                    }
                    else {
                        options.seek = atoi(argv[i+1]);
                    }
                }; break;

                case 'p':
                    options.progressFlag = 1;
                    break;

                case 'l':
                    options.lowercaseflag = 1;
                    break;
                    
                case 'u':
                    options.uppercaseflag = 1;
                    break;
                
                default:
                    break;
            }
        }   
    }

    return options;
}