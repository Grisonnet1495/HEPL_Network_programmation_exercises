#include <stdio.h>  /* for perror() */
#include <stdlib.h> /* for exit() */
#include "LibSer.h"

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}
