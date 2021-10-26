#ifndef modelmanager_h
#define modelmanager_h
#include <vector>
#include "common/model.h"

namespace modelmanager
{
    bool LoadObj(const char* path,const char* matPath, Model* model);
}

#endif