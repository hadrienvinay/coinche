#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include "prototypes.h"

int main (int argc,  char *argv[])
{
    init();
    // create a new window
    menu();
    free_all();
    // all is well ;)
    printf("Exited cleanly\n");
    return EXIT_SUCCESS;
}
