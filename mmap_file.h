#ifndef LARGEFILE_MMAPFILE_H_
#define LARGEFILE_MMAPFILE_H_

#include <unistd.h>
#include "common.h"

namespace baichen
{
  namespace largefile
  {
    struct MMapOption
   {
     int32_t max_mmap_size_;
     int32_t first_mmap_size_;
     int32_t per_mmap_size_;
   };

    class MMapFile
    {
     public:
      MMapFile();
      
      explicit MMapFile(const int fd); 
      MMapFile(const MMapOption& mmap_option,const int fd);   
      
      ~MMapFile();

      bool sync_file();
      bool map_file(const bool write = false);   //map file to memory
      void* get_data() const;                    // get mapped mmem addr
      int32_t get_size() const;                //get mapped data size

      bool munmap_file();   //unmap              
      bool remap_file();    // re-do the mapping

    private:
      bool ensure_file_size(const int32_t size);
      int32_t size_;
      int fd_;
      void* data_;
      struct MMapOption mmap_file_option_;
      

    };

  }



}






#endif
