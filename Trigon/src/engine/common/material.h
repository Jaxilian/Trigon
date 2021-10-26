#ifndef MATERIAL_H
#define MATERIAL_H
#include "transform.h"

struct Material
{
   unsigned int programID;
   unsigned int modelID;
   unsigned int viewID;
   unsigned int projID;

   Transform*   transform;

   glm::mat4&
   GetProjection();

   glm::mat4&
   GetView();

   void 
   SetValues();

   void
   BindValues();
};
#endif