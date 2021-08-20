#ifndef DEFAULTMATERIAL_H
#define DEFAULTMATERIAL_H

#include "Core/Types/Material.h"
#include "Core/Camera.h"

class DefaultMaterial : public Material
{
public:
	 static 
     DefaultMaterial* instance;

	 Texture2D* texture;
	 Matrix4*   modelMatrix;
	 Matrix4*   cameraMatrix;
	 Matrix4*	projection;

	 void UpdateValues(Camera* camera, Matrix4* modelMatrix);

	 DefaultMaterial();
	~DefaultMaterial();
};

#endif // !DEFAULTMATERIAL_H
