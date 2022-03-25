#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char* myvar = getenv("MYVAR");

    if(myvar)
	    printf(myvar); 
	    //do something
    else
        printf("ERROR: Please set $MYVAR");                

    return 0;
}
