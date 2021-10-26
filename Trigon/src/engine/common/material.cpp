#include "material.h"
#include "camera.h"
#include "glad/gl.h"

glm::mat4& Material::GetProjection()
{
    return Camera::getCurrentCamera()->projection;
}

glm::mat4&  Material::GetView(){return Camera::getCurrentCamera()->view;}

void 
Material::SetValues()
{
    glUseProgram(programID);

    glUniformMatrix4fv(modelID, 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);
    glUniformMatrix4fv(viewID, 1, GL_FALSE,  &glm::lookAt(glm::vec3(40,30,-30),glm::vec3(0,0,0),glm::vec3(0,1,0))[0][0]);
    glUniformMatrix4fv(projID, 1, GL_FALSE,  &glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f)[0][0]);
}

void
Material::BindValues()
{
    modelID     = glGetUniformLocation(programID, "M");
	viewID      = glGetUniformLocation(programID, "V");
	projID      = glGetUniformLocation(programID, "P");
}