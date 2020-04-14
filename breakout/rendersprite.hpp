#ifndef RENDERSPRITE_HPP
#define RENDERSPRITE_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "texture2d.hpp"

class CRenderSprite
{
private:
    CShader mShader;
    GLuint mQuadVAO;

    void InitRenderData();
public:
    CRenderSprite(CShader &shader);
    virtual ~CRenderSprite();

    void DrawSprite(CTexture2d texture, glm::vec2 position,
                    glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
                    glm::vec3 color = glm::vec3(1.0f));
};

#endif