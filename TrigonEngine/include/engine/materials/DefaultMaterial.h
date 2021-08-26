#ifndef DEFAULTMATERIAL_H
#define DEFAULTMATERIAL_H
#include "core/types/Material.h"
#include "core/math/Matrix4.h"

class DefaultMaterial : public Material
{
public:
	Texture2D* texture;

	DefaultMaterial();

};


#endif // !DEFAULTMATERIAL_H