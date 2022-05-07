#include "file_op.h"
#include "common.h"

using namespace std;
using namespace baichen;

int main()
{
    const char *filename = "file_op.txt";
    largefile::FileOperation *fileOP = new largefile::FileOperation(filename, O_CREAT | O_RDWR | O_LARGEFILE);
    int fd = fileOP->open_file();
    if (fd < 0)
    {
        fprintf(stderr, "Open file %s failed. Reason: %s\n", filename, strerror(-fd));
        exit(-1);
    }

    char buffer[65];
    memset(buffer, '8', 64);
    int ret = fileOP->pwrite_file(buffer, 64, 1024);
    if (ret < 0)
    {
        fprintf(stderr, "pwrite file %s failed. Reason: %s\n", filename, strerror(-ret));
    }
    memset(buffer, 0, 64);
    ret = fileOP->pread_file(buffer, 64, 1024);
    if (ret < 0)
    {
        fprintf(stderr, "pread file %s failed. Reason: %s\n", filename, strerror(-ret));
    }
    else
    {
        buffer[64] = '\0';
        printf("Read: %s\n", buffer);
    }

    memset(buffer, '9', 64);
    ret = fileOP->write_file(buffer, 64);
    if (ret < 0)
    {
        fprintf(stderr, "write file %s failed. Reason: %s\n", filename, strerror(-ret));
    }
    fileOP->close_file();

    return 0;
}