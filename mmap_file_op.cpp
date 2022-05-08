#include "mmap_file_op.h"
#include "common.h"

static int debug = 1;

namespace baichen
{
    namespace largefile
    {
        int MMapFileOperation::mmap_file(const MMapOption &mmap_option)
        {
            if (mmap_option.max_mmap_size_ < mmap_option.first_mmap_size_)
            {
                return TFS_ERROR;
            }
            if (mmap_option.max_mmap_size_ <= 0)
            {
                return TFS_ERROR;
            }

            int fd = check_file();
            if (fd < 0)
            {
                fprintf(stderr, "MMapFileOperation::mmap_file - check file failed!");
                return TFS_ERROR;
            }

            if (!is_mapped_)
            {
                if (map_file_)
                {
                    delete (map_file_);
                }
                map_file_ = new MMapFile(mmap_option, fd);
                is_mapped_ = map_file_->map_file(true);
            }

            if (is_mapped_)
            {
                return TFS_SUCCESS;
            }
            else
            {
                return TFS_ERROR;
            }
        }

        int MMapFileOperation::munmap_file()
        {
            if (is_mapped_ && map_file_ != NULL)
            {
                delete (map_file_);
                is_mapped_ = false;
            }
            return TFS_SUCCESS;
        }

        void *MMapFileOperation::get_map_data() const
        {
            if (is_mapped_)
            {
                return map_file_->get_data();
            }
            return NULL;
        }

        int MMapFileOperation::pread_file(char *buf, const int32_t size, const int64_t offset)
        {
            // 1. memory is already mapped
            if (is_mapped_ && (offset + size) > map_file_->get_size())
            {
                if (debug)
                    fprintf(stdout, "MMapFileOperation : pread ,size : %d,offset:%" __PRI64_PREFIX "d,map size %d",
                            size, offset, map_file_->get_size());
                map_file_->remap_file();
            }

            if (is_mapped_ && (offset + size) <= map_file_->get_size())
            {
                memcpy(buf, (char *)map_file_->get_data() + offset, size);
                return TFS_SUCCESS;
            }
            // 2. if memory is not mapped
            return FileOperation::pread_file(buf, size, offset); // call parent method for reading
        }

        int MMapFileOperation::pwrite_file(char *buf, const int32_t size, const int64_t offset)
        {
            // 1. memory is already mapped
            if (is_mapped_ && (offset + size) > map_file_->get_size())
            {
                if (debug)
                    fprintf(stdout, "MMapFileOperation : pwrite ,size : %d,offset:%" __PRI64_PREFIX "d,map size %d",
                            size, offset, map_file_->get_size());
                map_file_->remap_file();
            }

            if (is_mapped_ && (offset + size) <= map_file_->get_size())
            {
                memcpy((char *)map_file_->get_data() + offset, buf, size);
                return TFS_SUCCESS;
            }
            // 2.memory is not mapped
            return FileOperation::pwrite_file(buf, size, offset);
        }

        int MMapFileOperation::flush_file()
        {
            if (is_mapped_)
            {
                if (map_file_->sync_file())
                {
                    return TFS_SUCCESS;
                }
                else
                {
                    TFS_ERROR;
                }
            }

            return FileOperation::flush_file();
        }

    }
}