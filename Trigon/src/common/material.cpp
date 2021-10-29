#include "material.h"
#include "wgl/wgl.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "loader/loader.h"

glm::mat4 origin                = glm::mat4(1.0f);
glm::mat4 defaultPerspective    = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
glm::mat4 tempCameraPos         = glm::lookAt(
								glm::vec3(0,0,5), // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						        );

glm::vec3 Material::lightDir = glm::vec3(1.0f, 1.45f, 1.0f);
float   Material::emission = 1.0f;

void
Material::onCreation()
{
    // Load constants
    M = wgl::getUniformLocation(programID, "M");
    V = wgl::getUniformLocation(programID, "V");
    P = wgl::getUniformLocation(programID, "P");
    L = wgl::getUniformLocation(programID, "L");

    emissionStength = wgl::getUniformLocation(programID, "emissionStength");


    // Load albedo
    textures.push_back(Texture2D());
    textures.at(0).glTextureLocation = wgl::getUniformLocation( programID ,"albedo");

    modelmanager::LoadTex("textures/LavaRock_A.png", &textures.at(0));
    wgl::bindTexture(&textures.at(0));

    modelmanager::clearTexture(&textures.at(0));


    // Load normal
    textures.push_back(Texture2D());
    textures.at(1).glTextureLocation = wgl::getUniformLocation( programID ,"normal");

    modelmanager::LoadTex("textures/LavaRock_N.png", &textures.at(1));
    wgl::bindTexture(&textures.at(1));

    modelmanager::clearTexture(&textures.at(1));

     // Load AO
    textures.push_back(Texture2D());
    textures.at(2).glTextureLocation = wgl::getUniformLocation( programID ,"ao");

    modelmanager::LoadTex("textures/LavaRock_AO.png", &textures.at(2));
    wgl::bindTexture(&textures.at(2));

    modelmanager::clearTexture(&textures.at(2));

    // Load Emission
    textures.push_back(Texture2D());
    textures.at(3).glTextureLocation = wgl::getUniformLocation( programID ,"emission");

    modelmanager::LoadTex("textures/LavaRock_E.png", &textures.at(3));
    wgl::bindTexture(&textures.at(3));

    modelmanager::clearTexture(&textures.at(3));
}

void
Material::OnDraw(Mesh* mesh)
{
    if(!mesh->parent.transform) wgl::setMat4Uniform(M, origin);
    else wgl::setMat4Uniform(M, origin);
    
    wgl::setMat4Uniform(P, defaultPerspective);
    wgl::setMat4Uniform(V, tempCameraPos);
    wgl::setVec3Uniform(L, lightDir);
    wgl::setTex2Uniforms(&textures);
    wgl::setFloatUniform(emissionStength,emission);
}