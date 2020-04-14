#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "gameobject.h"
#include "rendersprite.hpp"
#include "resource_manager.hpp"

class CGameLevel
{
private:
    void init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
public:
    std::vector<CGameObject> mBricks;

    void Laod(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
    void Draw(CRenderSprite &renderer);

    GLboolean IsCompleted();
    
public:
    CGameLevel(/* args */){}
    ~CGameLevel(){}
};

#endif