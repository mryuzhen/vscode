#include "shader.hpp"
#include <iostream>

CShader &CShader::Use()
{
    glUseProgram(mID);
    return *this;
}
void CShader::Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource)
{
    GLuint sVertex, sFragment, gShader;
    // Vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    CheckCompileError(sVertex, "VERTEX");
    // Fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    CheckCompileError(sFragment, "FRAGMENT");
    // If geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        CheckCompileError(gShader, "GEOMETRY");
    }
    // Shader Program
    mID = glCreateProgram();
    glAttachShader(mID, sVertex);
    glAttachShader(mID, sFragment);
    if (geometrySource != nullptr)
    {
        glAttachShader(mID, gShader);
    }
    glLinkProgram(mID);
    CheckCompileError(mID, "PROGRAM");
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr)
    {
         glDeleteShader(gShader);
    }   
}

void CShader::SetFloat(const GLchar *name, GLfloat value, GLboolean useShader)
{
    if(useShader)
    {
        Use();
    }
    glUniform1f(glGetUniformLocation(mID, name), value);
}
void CShader::SetInteger(const GLchar *name, GLint value, GLboolean useShader)
{
    if(useShader)
    {
        Use();
    }
    glUniform1i(glGetUniformLocation(mID, name), value);
}
void CShader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader)
{
    if(useShader)
    {
        Use();
    }
    glUniform2f(glGetUniformLocation(mID, name), x, y);
}
void CShader::SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader)
{
    if(useShader)
    {
        Use();
    }
    glUniform2f(glGetUniformLocation(mID, name), value.x, value.y);
}
void CShader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
    if(useShader)
    {
        Use();
    }
    glUniform3f(glGetUniformLocation(mID, name), x, y, z);
}
void CShader::SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader)
{
    if(useShader)
    {
        Use();
    }
    glUniform3f(glGetUniformLocation(mID, name), value.x, value.y, value.z);
}
void CShader::CShader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
    if(useShader)
    {
        Use();
    }
    glUniform4f(glGetUniformLocation(mID, name), x, y, z, w);
}

void CShader::SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader)
{
    if(useShader)
    {
        Use();
    }
    glUniform4f(glGetUniformLocation(mID, name), value.x, value.y, value.z, value.w);
}
void CShader::SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
{
    if (useShader)
    {
        Use();
    }
    glUniformMatrix4fv(glGetUniformLocation(mID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
void CShader::CheckCompileError(GLuint object, std::string type)
{
    GLuint success;
    GLchar info[1024];
    if(type == "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, (GLint*)&success);
        if(!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, info);
            std::cout << "Error : Shader error type:"  << info  << "\n-----------------!!!" << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, (GLint*)&success);
        if(!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, info);
            std::cout << "Error : Program error type:"  << info  << "\n-----------------!!!" << std::endl;
        }
    }
    
}