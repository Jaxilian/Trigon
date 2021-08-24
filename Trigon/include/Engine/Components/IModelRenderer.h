#ifndef IMODELRENDERER_H
#define IMODELRENDERER_H
#include "IComponent.h"
#include "Core/Types/Model.h"

class IModelRenderer : public Component
{
public:
	Model*			model;

	~IModelRenderer(void);

	//////////////////////////////////////////////////////////////////////////

	void	Update	(void) override;
	void	Load	(void) override;
	void	Unload	(void) override;

};

#endif // !IMODELRENDERER_H
