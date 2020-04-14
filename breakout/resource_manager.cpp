#include "resource_manager.hpp"
#include <iostream>
#include "shader.hpp"
#include <fstream>
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

std::map<std::string, CShader> CResource_manager::mShaders;
std::map<std::string, CTexture2d> CResource_manager::mTextures;

CShader CResource_manager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
    mShaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return mShaders[name];
}
CShader CResource_manager::GetShader(std::string name)
{
    return mShaders[name];
}

CTexture2d CResource_manager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
    mTextures[name] = LoadTextureFromFile(file, alpha);
    return mTextures[name];
}
CTexture2d CResource_manager::GetTexture(std::string name)
{
    return mTextures[name];
}

void CResource_manager::Clear()
{
    for(auto &iter : mShaders)
    {
        glDeleteProgram(iter.second.mID);
    }
    for(auto &iter : mTextures)
    {
        glDeleteTextures(1, &iter.second.mID);
    }
}
CShader CResource_manager::LoadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    // 2. Now create shader object from source code
    CShader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}
CTexture2d CResource_manager::LoadTextureFromFile(const GLchar *file, GLboolean alpha)
{
     CTexture2d texture;
    if (alpha)
    {
        texture.mInternalFormat = GL_RGBA;
        texture.mImageFormat = GL_RGBA;
    }
    // Load image
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(file, &width, &height, &nrChannels, texture.mImageFormat == GL_RGBA ? STBI_rgb_alpha : STBI_rgb);
    if(data)
    {
        if(nrChannels == 3)
        {
            texture.mImageFormat = GL_RGB;
        }
        texture.Generate(width, height, data);
    }
    else
    {
        std::cerr << "........................." << std::endl;
    }
    stbi_image_free(data);

    return texture;
}