#ifndef DEFAULTMATERIAL_H
#define DEFAULTMATERIAL_H
#include "core/types/Material.h"
#include "core/math/Matrix4.h"

class DefaultMaterial : public Material
{
public:
	Vector3*	lightDir;

	Texture2D*	albedo;
	Texture2D*	normal;
	Texture2D*	metallic;
	Texture2D*  roughness;
	Texture2D*	ambientOcclusion;

	DefaultMaterial();

};


#endif // !DEFAULTMATERIAL_H