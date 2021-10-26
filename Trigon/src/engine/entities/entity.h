#ifndef ENTITY_H
#define ENTITY_H
#include "common/model.h"
#include "common/transform.h"

class Entity
{
public:
    Model       model;
    Transform   transform;

};

#endif