#include "rendersprite.hpp"
#include <glad/glad.h>
#include "shader.hpp"
#include "texture2d.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

CRenderSprite::CRenderSprite(CShader &shader)
{
    mShader = shader;
    InitRenderData();
}
CRenderSprite::~CRenderSprite()
{
    glDeleteVertexArrays(1, &mQuadVAO);
}

void CRenderSprite::DrawSprite(CTexture2d texture, glm::vec2 position,
                glm::vec2 size, GLfloat rotate,
                glm::vec3 color)
{
    mShader.Use();
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5 * size.x, 0.5 * size.y, 0.0f));

    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::translate(model, glm::vec3(-0.5 * size.x, -0.5 * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    mShader.SetMatrix4("model", model);
    mShader.SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(mQuadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void CRenderSprite::InitRenderData()
{
    GLuint VBO;
    GLfloat vertics[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &mQuadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertics), vertics, GL_STATIC_DRAW);

    glBindVertexArray(mQuadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}