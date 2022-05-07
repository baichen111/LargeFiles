#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

namespace baichen
{
    namespace largefile
    {
        const int32_t TFS_SUCCESS = 0;
        const int32_t EXIT_DISK_OPER_INCOMPLETE = -8012; // read or write length is less than required
    }
}

#endif