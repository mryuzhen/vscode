#include "gameobject.h"

CGameObject::CGameObject()
        :  mPosition(0, 0), mSize(1, 1), mVelocity(0.0f), mColor(1.0f), 
        mRotation(0.0f), mSprite(), mbSolid(false), mbDestroyed(false)
{

}
CGameObject::CGameObject(glm::vec2 pos, glm::vec2 size, CTexture2d sprite, glm::vec3 color, glm::vec2 velocity)
        :  mPosition(pos), mSize(size), mVelocity(velocity), mColor(color), 
        mRotation(0.0f), mSprite(sprite), mbSolid(false), mbDestroyed(false)
{

}
CGameObject::~CGameObject()
{

}

void CGameObject::Draw(CRenderSprite &renderer)
{
    renderer.DrawSprite(mSprite, mPosition, mSize, mRotation);
}