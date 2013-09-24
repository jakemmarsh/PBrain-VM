//
//  FileReader.c
//  PBrain-VM
//
//  by Jake Marsh
//

// INCLUDE HEADER FILE
#include "FileReader.h"

// INCLUDE NECESSARY LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int open_file(const char * fileName) {
    int fp;
    
    fp = open(fileName, O_RDONLY);
    printf("Open is: %d\n", fp);
    
    // if error in read or EOF
    if (fp < 0) {
        printf("Bus Error 22\n");
        exit(0);
    }
    
    return fp;
}