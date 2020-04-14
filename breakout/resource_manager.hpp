#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <string>
#include <glad/glad.h>
#include "texture2d.hpp"
#include "shader.hpp"

class CResource_manager
{
public:
    static std::map<std::string, CShader> mShaders;
    static std::map<std::string, CTexture2d> mTextures;

    static CShader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
    static CShader GetShader(std::string name);

    static CTexture2d LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
    static CTexture2d GetTexture(std::string name);

    static void Clear();
private:
    CResource_manager(/* args */){}
    virtual ~CResource_manager(){}

    static CShader LoadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
    static CTexture2d LoadTextureFromFile(const GLchar *file, GLboolean alpha);
};

#endif