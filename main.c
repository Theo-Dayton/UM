/********************************************************************
* main.c
* Assignment: UM (HW6)
* Authors: Yuehan (Eunice) Dai (ydai05), Grace Ye (gye01)
* Date: 11/23/21
* Summary: This is the implementation of main, which handles
*          command line arguments
********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <except.h>
#include "um.h"

/*
* Name: main
* Purpose: Deals with um program's command line arguments
* Input: Command line argument count, command line argument values
* Output: None
*/
int main(int argc, char *argv[])
{
    if (argc <= 2) {
        if (argc == 1) {
            perror("No UM file provided\n");
            exit(EXIT_FAILURE);
        } else { //argc == 2
            FILE *fp = fopen(argv[1], "r");
            assert(fp != NULL);
            startUM(fp);
            fclose(fp);
        }
    } else {
        perror("TOO MANY ARGUMENTS\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS; 
}