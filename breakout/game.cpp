#include "game.hpp"
#include "rendersprite.hpp"
#include "resource_manager.hpp"

CRenderSprite *renderSprite;
CGameObject * player;

CGame::CGame(GLuint width, GLuint height)
    : mState(GameState::GAME_ACTIVE), mKeys(), mWidth(width), mHeight(height)
{

}

CGame::~CGame()
{
    delete renderSprite;
    delete player;
}

void CGame::InitGame()
{
    CResource_manager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(mWidth), static_cast<GLfloat>(mHeight), 0.0f, -1.0f, 1.0f);

    CResource_manager::GetShader("sprite").Use().SetInteger("image", 0);
    CResource_manager::GetShader("sprite").Use().SetMatrix4("projection", projection);

    CResource_manager::LoadTexture("texture/background.jpg", GL_FALSE, "background");
    CResource_manager::LoadTexture("texture/awesomeface.png", GL_TRUE, "face");
    CResource_manager::LoadTexture("texture/block.png", GL_FALSE, "block");
    CResource_manager::LoadTexture("texture/block_solid.png", GL_FALSE, "block_solid");
    CResource_manager::LoadTexture("texture/paddle.png", GL_TRUE, "paddle");

    renderSprite = new CRenderSprite(CResource_manager::GetShader("sprite"));

    CGameLevel one, two, three, four;
    one.Laod("levels/one.lvl", mWidth, mHeight * 0.5);
    two.Laod("levels/two.lvl", mWidth, mHeight * 0.5);
    three.Laod("levels/three.lvl", mWidth, mHeight * 0.5);
    four.Laod("levels/four.lvl", mWidth, mHeight * 0.5);
    mLevel = 0;
    mLevels.push_back(one);
    mLevels.push_back(two);
    mLevels.push_back(three);
    mLevels.push_back(four);

    glm::vec2 playerPos = glm::vec2(mWidth/2 - PLAYER_SIZE.x/2, mHeight - PLAYER_SIZE.y);
    player = new CGameObject(playerPos, PLAYER_SIZE, CResource_manager::GetTexture("paddle"));
}

void CGame::ProcessInput(GLfloat dt)
{
    if(mState == GameState::GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        if(mKeys[GLFW_KEY_A])
        {
            if(player->mPosition.x >= 0)
            {
                player->mPosition.x -= velocity;
            }
        }
        if(mKeys[GLFW_KEY_D])
        {
            if(player->mPosition.x <= mWidth - player->mSize.x)
            {
                player->mPosition.x += velocity;
            }
        }
    }
}

void CGame::Update(GLfloat dt)
{

}

void CGame::Render()
{
    renderSprite->DrawSprite(CResource_manager::GetTexture("face"), glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    if(mState == GameState::GAME_ACTIVE)
    {
        renderSprite->DrawSprite(CResource_manager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(mWidth, mHeight), 0.0f);
        mLevels[mLevel].Draw(*renderSprite);
        player->Draw(*renderSprite);
    }
}