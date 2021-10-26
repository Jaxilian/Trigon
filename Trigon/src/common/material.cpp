#include "material.h"
#include "wgl/wgl.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "loader/loader.h"

glm::mat4 origin                = glm::mat4(1.0f);
glm::mat4 defaultPerspective    = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
glm::mat4 tempCameraPos         = glm::lookAt(
								glm::vec3(8,6,-6), // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						        );

glm::vec3 Material::lightDir = glm::vec3(0.0f, 0.45f, 0.0f);

void
Material::onCreation()
{
    M = wgl::getUniformLocation(programID, "M");
    V = wgl::getUniformLocation(programID, "V");
    P = wgl::getUniformLocation(programID, "P");
    L = wgl::getUniformLocation(programID, "L");

    albedo = wgl::getUniformLocation(programID, "albedo");

    modelmanager::LoadTex("textures/CobbleWall.png", &albedoTexture);
    wgl::bindTexture(&albedoTexture);
    modelmanager::clearTexture(&albedoTexture);
}

void
Material::OnDraw(Mesh* mesh)
{
    if(!mesh->parent.transform) wgl::setMat4Uniform(M, origin);
    
    wgl::setMat4Uniform(M, origin);
    wgl::setMat4Uniform(P, defaultPerspective);
    wgl::setMat4Uniform(V, tempCameraPos);
    wgl::setVec3Uniform(L, lightDir);
    wgl::setTex2Uniform(albedo, albedoTexture);
}