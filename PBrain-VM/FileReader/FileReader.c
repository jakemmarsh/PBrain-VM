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

int openFile(const char * fileName, int openType) {
    int fp;
    
    fp = open(fileName, openType) ; //always check the return value.
    printf("Open is %d\n", fp) ;
    
    if (fp < 0) //error in read or EOF
    {printf("Bus Error 22\n") ;
        exit(0) ;
    }
    
    return fp;
}