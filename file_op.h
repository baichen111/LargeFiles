#ifndef LARGE_FILE_OP_H
#define LARGE_FILE_OP_H

#include "common.h"

namespace baichen
{
    namespace largefile
    {
        class FileOperation
        {
        public:
            FileOperation(const std::string &file_name, const int open_flags = O_RDWR | O_LARGEFILE);
            ~FileOperation();

            int open_file();
            void close_file();

            int flush_file(); // flush data to disk
            int unlink_file();

            virtual int pread_file(char *buf, const int32_t nbytes, const int64_t offset);
            virtual int pwrite_file(char *buf, const int32_t nbytes, const int64_t offset);
            int write_file(char *buf, const int32_t nbytes); // seek

            int64_t get_file_size();

            int ftruncate_file(const int64_t length);
            int seek_file(const int64_t offset);

            int get_fd() const
            {
                return fd_;
            }

        protected:
            int fd_;
            int open_flags_;
            char *file_name_;

            static const mode_t OPEN_MODE = 0644;
            static const int MAX_DISK_TIMES = 5;

            int check_file();


        };
    }
}

#endif