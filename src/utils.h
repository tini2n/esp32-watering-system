#ifndef FileSystemUtils_h
#define FileSystemUtils_h

#include <FS.h>

namespace fsutils
{

    void listDir(fs::FS &fs, const char *dirname, uint8_t levels);

}

#endif