#include <stdio.h>
#include <string.h>
#include "processor.h"

const char *VER = "0.0.1";

void printHelp();
int parseHelp(char*);

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int len = strlen(argv[1]);
        if (len <= 2){
            char c = argv[1][len-1]; //last non-null char
            if (c == 'h' || c == 'H') {
                printHelp();
                return -1;
            }
        }
        if(parseHelp(argv[1])){
            printHelp();
            return -1;
        }

        FILE *fin;
        fin = fopen(argv[1], "r");
        byte bin[16];
        fread(bin, 1, 16, fin);
        fclose(fin);

        initialize();
        loadRAM(bin);
        reset();
        printf("%s\n", run());
    }
    if(argc == 1){
        initialize();
        byte prog[16] = {0x09, 0x1a,0x1b,0x2c,0xe0,0xf0,0,0,0,0x10,0x14,0x18,0x20,0,0,0};
        loadRAM(prog);
        reset();
        printf("%s\n", run());
    }
    else
        printHelp();
    printf("ok");
    return 0;
}

void printHelp(){

    printf("SAP-1 emulator. Please run this program again with a compiled SAP assembly file.\n");
    printf("ex: ./sap1 foo.hex");
}

int parseHelp(char *v){
    int len = strlen(v);
    if(len < 5)  //5 to leave a leading character for / or - etc TODO
        return 0;

    //look for 'help' at the end of the string
    if(v[len-1]=='p'||v[len-1]=='P')
        if(v[len-2]=='l'||v[len-2]=='L')
            if(v[len-3]=='e'||v[len-3]=='E')
                if(v[len-4]=='h'||v[len-4]=='H')
                    return 1;

    return 0;
}
