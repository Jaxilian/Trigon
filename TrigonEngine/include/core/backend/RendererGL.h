#ifndef RENDERERGL_H
#define RENDERERGL_H
#include "Renderer.h"
#include "core/TriCore.h"

class RendererGL : public Renderer
{
private:
	unsigned int vertexArrayID;

public:

	//////////////////////////////////////////////////////////////////////
	//																	//
	//		Creations of instances										//
	//																	//
	//////////////////////////////////////////////////////////////////////



	void CreateInstance	(	void	)	override;

	void CreateContext	(	void	)	override;












	//////////////////////////////////////////////////////////////////////
	//																	//
	//		Data Creations												//
	//																	//
	//////////////////////////////////////////////////////////////////////

	unsigned int	BindVertexBuffer	(	std::vector<float>	vertexBuffer	)	override;

	unsigned int	BindTexture2D		(	Texture2D*			texture			)	override;

	unsigned int	BindIndexBuffer		(	std::vector<int>	indexBuffer		)	override;


	unsigned int	CreateShaderProgram	(	const char* vertexFile,	 const char* fragmentFile)	override;










	//////////////////////////////////////////////////////////////////////
	//																	//
	//		Data Destructions											//
	//																	//
	//////////////////////////////////////////////////////////////////////

	void			ReleaseBuffer	(	unsigned int	bufferID	) override;

	void			UnbindTexture2D	(	Texture2D*		texture		) override;

	void			UnbindShader	(	Shader*			shader		) override;









	//////////////////////////////////////////////////////////////////////
	//																	//
	//		Render States												//
	//																	//
	//////////////////////////////////////////////////////////////////////

	void			ClearViewport		(			void			) override;

	void			Draw				(	const	Model* model	) override;


	unsigned int	GetUniformLocation	(	unsigned int shaderID,	const char* name	) override;








	//////////////////////////////////////////////////////////////////////
	//																	//
	//		Relase Instance												//
	//																	//
	//////////////////////////////////////////////////////////////////////

	void ReleaseInstance	(	void	)	 override;












};

#endif // !RENDERER_GL
