#ifndef WGL_H
#define WGL_H
#include "common/material.h"
#include <memory>
#include "common/color.h"
#include "common/model.h"
#include "common/Texture2D.h"

namespace wgl
{
    void                        create();
    void                        release();
    void                        setBgColor(Color color);
    std::shared_ptr<Material>   createMaterial(std::string vertPath, std::string fragPath, std::string name);
    void                        bindModel(Model*    model);
    void                        unbindModel(Model*  model);
    void                        bindTexture(Texture2D* texture);
    void                        destroyMaterial(Material* mat);
    void                        releaseTexture(unsigned int id);
    void                        clear();
    void                        drawModel(Model* model);

    u_int32_t                   getUniformLocation(u_int32_t programID, std::string location);
    void                        setMat4Uniform(u_int32_t location, glm::mat4& matRef);
    void                        setVec3Uniform(u_int32_t location, glm::vec3& vecRef);
    void                        setTex2Uniforms(std::vector<Texture2D>* textures);
    void                        setFloatUniform(u_int32_t location, float& value);
}


#endif