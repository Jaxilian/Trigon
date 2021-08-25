#ifndef MODELCOMPONENT_H
#define MODELCOMPONENT_H
#include "Component.h"
#include "core/types/Model.h"
class ModelComponent : public Component
{

public:
	Model* model;

	//////////////////////////////////////////////////////////////////////////

	// Constructor / Destructor
			 ModelComponent(Model* model);
	virtual ~ModelComponent(void) override;

	//////////////////////////////////////////////////////////////////////////

	virtual void	Load(void) override;
	virtual void	Unload(void) override;
	virtual void	Update(void) override;

	void Draw();

	//////////////////////////////////////////////////////////////////////////

};

#endif // !MODELCOMPONENT_H


