#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture2d.hpp"
#include "rendersprite.hpp"

class CGameObject
{
private:
public:
    glm::vec2 mPosition, mSize, mVelocity;
    glm::vec3 mColor;
    GLfloat mRotation;
    GLboolean mbSolid;
    GLboolean mbDestroyed;

    CTexture2d mSprite;
    /* data */
public:
    CGameObject();
    CGameObject(glm::vec2 pos, glm::vec2 size, CTexture2d sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    ~CGameObject();

    virtual void Draw(CRenderSprite &renderer);
};

#endif