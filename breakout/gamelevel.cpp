#include "gamelevel.h"

#include <fstream>
#include <sstream>

void CGameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight)
{
    GLuint width = tileData[0].size();
    GLuint height = tileData.size();

    GLfloat unitWidth = levelWidth / static_cast<GLfloat>(width);
    GLfloat unitheight = levelHeight / static_cast<GLfloat>(height);

    for(GLuint y = 0; y < height; ++y)
    {
        for(GLuint x = 0; x < width; ++x)
        {
           if(tileData[y][x] == 1)
           {
               glm::vec2 pos(unitWidth * x, unitheight * y);
               glm::vec2 size(unitWidth, unitheight);
               CGameObject obj(pos, size, CResource_manager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
               obj.mbSolid = GL_TRUE;
               mBricks.push_back(obj);
           } 
           else if(tileData[y][x] > 1)
           {
               glm::vec3 color = glm::vec3(1.0f);
               if(tileData[y][x] == 2)
               {
                   color = glm::vec3(0.2f, 0.6f, 1.0f);
                
               }
               else if (tileData[y][x] == 3)  
               {
                   color = glm::vec3(0.0f, 0.7f, 0.0f);
               }
               else if (tileData[y][x] == 4)
               {     
                   color = glm::vec3(0.8f, 0.8f, 0.4f);
               }
                else if (tileData[y][x] == 5)
               {     
                   color = glm::vec3(1.0f, 0.5f, 0.0f);
               }

               glm::vec2 pos(unitWidth * x, unitheight * y);
               glm::vec2 size(unitWidth, unitheight);
               mBricks.push_back(CGameObject(pos, size, CResource_manager::GetTexture("block"), color));
           }
        }
    }
}

void CGameLevel::Laod(const GLchar *file, GLuint levelWidth, GLuint levelHeight)
{
    mBricks.clear();
    GLuint tileCode;
    CGameLevel level;

    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<GLuint>> tileData;

    if(fstream)
    {
        while(std::getline(fstream, line))
        {
            std::istringstream sstream(line);
            std::vector<GLuint> row;
            while(sstream >> tileCode)
            {
                row.push_back(tileCode);
            }
            tileData.push_back(row);
        }
        if(tileData.size() > 0)
        {
            init(tileData, levelWidth, levelHeight);
        }
    }
}

void CGameLevel::Draw(CRenderSprite &renderer)
{
    for(CGameObject &tile : mBricks)
    {
        if(!tile.mbDestroyed)
        {
            tile.Draw(renderer);
        }
    }
}

GLboolean CGameLevel::IsCompleted()
{
    for(CGameObject &tile : mBricks)
    {
        if(!tile.mbSolid && !tile.mbDestroyed)
        {
            return GL_FALSE;
        }
    }
    return GL_TRUE;
}
