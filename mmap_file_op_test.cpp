#include "mmap_file_op.h"
#include <iostream>

using namespace std;
using namespace baichen;
const static largefile::MMapOption mmap_option = {10240000, 4096, 4096};

int main()
{
    int ret = 0;
    const char *filename = "mmap_file_op.txt";
    largefile::MMapFileOperation *mmfo = new largefile::MMapFileOperation(filename);
    int fd = mmfo->open_file();
    if (fd < 0)
    {
        fprintf(stderr, "open file %s failed .Reason:%s\n", filename, strerror(-fd));
        exit(-1);
    }

    ret = mmfo->mmap_file(mmap_option);
    if (ret == largefile::TFS_ERROR)
    {
        fprintf(stderr, "mmap file failed. Reason:%s\n", strerror(errno));
        mmfo->close_file();
        exit(-2);
    }

    // write
    char buffer[128 + 1];
    memset(buffer, '6', 128);
    ret = mmfo->pwrite_file(buffer, 128, 8);

    // read
    memset(buffer, 0, 128); // empty the buffer
    ret = mmfo->pread_file(buffer, 128, 8);
    buffer[128] = '\0';
    printf("read: %s\n", buffer);

    ret = mmfo->flush_file();
    if (ret == largefile::TFS_ERROR)
    {
        fprintf(stderr, "flush file failed. Reason: %s\n", strerror(errno));
    }

    memset(buffer,'8',128);
    ret = mmfo->pwrite_file(buffer, 128, 4000);
    mmfo->munmap_file();
    mmfo->close_file();

    return 0;
}