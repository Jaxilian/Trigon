#ifndef RENDERERGL_H
#define RENDERERGL_H
#include "Renderer.h"
#include "core/TriCore.h"

enum class RenderError
{
	ShaderNotLoaded,
	ShaderNull,
	MaterialNull,
	NoCamera
};

class RendererGL : public Renderer
{
private:
	unsigned int vertexArrayID;

	
	RenderError error;
	RenderError lastError;

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

	unsigned int	BindVertexBuffer	(	std::vector<float>			vertexBuffer	)	override;

	unsigned int	BindTexture2D		(	Texture2D*					texture			)	override;

	unsigned int	BindIndexBuffer		(	std::vector<unsigned short>	indexBuffer		)	override;


	unsigned int	CreateShaderProgram	(	const char* vertexFile,	 const char* fragmentFile)	override;










	//////////////////////////////////////////////////////////////////////
	//																	//
	//		Data Destructions											//
	//																	//
	//////////////////////////////////////////////////////////////////////

	void			ReleaseBuffer		(	unsigned int	bufferID	) override;

	void			ReleaseTexture2D	(	Texture2D*		texture		) override;

	void			ReleaseShader		(	Shader*			shader		) override;









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




	//////////////////////////////////////////////////////////////////////
	//																	//
	//		Local Fucntions												//
	//																	//
	//////////////////////////////////////////////////////////////////////

	bool UseShader(Shader* program);






};

#endif // !RENDERER_GL
