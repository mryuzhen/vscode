#include "ShaderProgram.hpp"
#include "shader.hpp"
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
CShaderProgram::CShaderProgram(/* args */)
{
    mProgramID = 0;
    mShader.clear();
    bLinked = false;
    mInfoLog[0] = '\0';
}

CShaderProgram::~CShaderProgram()
{
    mProgramID = 0;
    mShader.clear();
    bLinked = false;
    mInfoLog[0] = '\0';
}

bool CShaderProgram::AddShader(CShader *shader)
{
    if(shader == NULL)
    {
        return false;
    }
    if(glIsShader(shader->ShaderID()))
    {
        mShader.push_back(shader);
        return true;
    }
    return false;
}
bool CShaderProgram::AddShaderFromSourceCode(CShaderType shaderType, const GLchar * source)
{
    return false;
}
bool CShaderProgram::AddShaderFromSourceCode(CShaderType shaderType, const std::string & source)
{
    return false;
}

bool CShaderProgram::AddShaderFromSourceFile(CShaderType shaderType, const GLchar * source)
{
    return false;
}
bool CShaderProgram::AddShaderFromSourceFile(CShaderType shaderType, const std::string & source)
{
    return false;
}

bool CShaderProgram::Create()
{
    mProgramID = glCreateProgram();
    return (mProgramID > 0) ? true : false;
}

bool CShaderProgram::Bind()
{
    glUseProgram(mProgramID);
    return true;
}

bool CShaderProgram::Link()
{
    int success;
    bLinked = false;

    if(!AttachShader())
    {
        bLinked = false;
        return false;
    }
    glLinkProgram(mProgramID);
    glGetProgramiv(mProgramID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(mProgramID, 512, NULL, mInfoLog);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << mInfoLog << std::endl;
        return false;
    }
    bLinked = true;
    return true;
}

void CShaderProgram::RemoveAllShaders()
{

}
void CShaderProgram::RemoveShader(CShader *shader)
{
    std::list<CShader*>::iterator it;
    for(it = mShader.begin(); it != mShader.end();)
    {
        CShader* pShader = (CShader*)(*it);
        if(pShader == shader)
        {
            it = mShader.erase(it);
        }
        else
        {
            it++;
        }        
    }
}
void CShaderProgram::Release()
{

}

bool CShaderProgram::AttachShader()
{
    for(std::list<CShader*>::iterator it = mShader.begin(); it != mShader.end(); it ++)
    {
        CShader* pShader = (CShader*)(*it);
        GLuint id = pShader->ShaderID();
        if(glIsShader(id))
        {
            glAttachShader(mProgramID, id); 
        }             
    }
    return true;
}