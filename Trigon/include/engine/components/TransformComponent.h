#ifndef TRANSFORMCOMPONENT
#define TRANSFORMCOMPONENT
#include "Component.h"
#include "core/math/Matrix4.h"

class TransformComponent : public Component
{

public:
	Matrix4 matrix;

	// Constructor / Destructor
	TransformComponent(void);
	virtual ~TransformComponent(void) override;



	//////////////////////////////////////////////////////////////////////////

	virtual void	Load(void) override;
	virtual void	Unload(void) override;
	virtual void	Update(void) override;

	/////////////////////////////////////////////////////////////////////////

	Vector3		GetPosition();
	Vector3		GetScale();

	/////////////////////////////////////////////////////////////////////////

	void		Scale(Vector3 value);
	void		Translate(Vector3 position);
	void		LookAt(Vector3 target, Vector3 up);
	void		Rotate(Vector3 angles);
	void		SetRotation(Vector3 orientation);
	void		SetPosition(Vector3 pos);
	void		ApplyChanges();

};

#endif // !TRANSFORMCOMPONENT
