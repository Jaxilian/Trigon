#ifndef DIRECTIONALLIGHTCOMPONENT_H
#define DIRECTIONALLIGHTCOMPONENT_H
#include "engine/components/Component.h"
#include "core/math/Vector3.h"

class DirectionLightComponent : public Component
{

public:

	Vector3 direction;

	//////////////////////////////////////////////////////////////////////////

	// Constructor / Destructor
	DirectionLightComponent(void);
	virtual ~DirectionLightComponent(void) override;

	//////////////////////////////////////////////////////////////////////////

	virtual void	Load(void) override;
	virtual void	Unload(void) override;
	virtual void	Update(void) override;


	//////////////////////////////////////////////////////////////////////////
};


#endif // !DIRECTIONALLIGHTCOMPONENT_H