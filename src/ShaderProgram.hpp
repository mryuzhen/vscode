#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "shader.hpp"
#include <list>

class CShaderProgram
{
private:
    GLuint mProgramID;
    std::list<CShader*> mShader;
    bool bLinked;
    GLchar mInfoLog[512];
public:
    CShaderProgram();
    virtual ~CShaderProgram();

    bool AddShader(CShader *shader);
    bool AddShaderFromSourceCode(CShaderType shaderType, const GLchar * source);
    bool AddShaderFromSourceCode(CShaderType shaderType, const std::string & source);

    bool AddShaderFromSourceFile(CShaderType shaderType, const GLchar * source);
    bool AddShaderFromSourceFile(CShaderType shaderType, const std::string & source);

    bool Create();

    bool Bind();

    virtual bool Link();
    bool IsLink(){return bLinked;}

    void RemoveAllShaders();
    void RemoveShader(CShader *shader);
    void Release();

    GLuint ProgramID(){return mProgramID;}
    const GLchar *InfoLog(){return mInfoLog;}
private:
    bool AttachShader();
};

#endif