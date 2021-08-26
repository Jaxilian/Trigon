#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "core/types/TriTypes.h"


class Renderer
{

private:
static Renderer* m_pInstance;

public:



	//////////////////////////////////////////////////////////////////////
	//																	//
	//		Creations of instances										//
	//																	//
	//////////////////////////////////////////////////////////////////////



	virtual void CreateInstance	(	void	) {};

	virtual void CreateContext	(	void	) {};












	//////////////////////////////////////////////////////////////////////
	//																	//
	//		Data Creations												//
	//																	//
	//////////////////////////////////////////////////////////////////////

	virtual unsigned int	BindVertexBuffer	(	std::vector<float>			vertexBuffer					) { return 0; };

	virtual unsigned int	BindTexture2D		(	Texture2D*					texture							) { return 0; };

	virtual unsigned int	BindIndexBuffer		(	std::vector<unsigned short>	indexBuffer						) { return 0; };

	virtual unsigned int	CreateShaderProgram	(	const char* vertexFile, const char* fragmentFile	) { return 0; };










	//////////////////////////////////////////////////////////////////////
	//																	//
	//		Data Destructions											//
	//																	//
	//////////////////////////////////////////////////////////////////////

	virtual void			ReleaseBuffer		(	unsigned int	bufferID	) {};

	virtual void			ReleaseTexture2D	(	Texture2D*		texture		) {};

	virtual void			ReleaseShader		(	Shader*			shader		) {};









	//////////////////////////////////////////////////////////////////////
	//																	//
	//		Render States												//
	//																	//
	//////////////////////////////////////////////////////////////////////

	virtual void			ClearViewport		(			void			) {};
	virtual void			Draw				(	const	Model*	model	) {};

	virtual unsigned int	GetUniformLocation	(	unsigned int shaderID,	const char* name	) { return 0; };


	static void				SetInstance			(	Renderer* instance		);
	static Renderer*		GetInstance			(			void			);


	//////////////////////////////////////////////////////////////////////
	//																	//
	//		Relase Instance												//
	//																	//
	//////////////////////////////////////////////////////////////////////

	virtual void ReleaseInstance	(	void	) {};






	
};

#endif // !RENDERER
