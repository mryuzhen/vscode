#ifndef GAME_HPP
# define GAME_HPP
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <vector>

#include "gamelevel.h"

enum class GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

const glm::vec2 PLAYER_SIZE(100, 20);
const GLfloat PLAYER_VELOCITY(500.0f);

class CGame
{
public:
    CGame(GLuint width, GLuint height);
    virtual ~CGame();

    void InitGame();
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
    GameState mState;
    GLuint mWidth, mHeight;
    GLboolean mKeys[1024];

    std::vector<CGameLevel> mLevels;
    GLuint mLevel;
};

#endif