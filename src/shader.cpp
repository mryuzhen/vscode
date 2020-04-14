#include "shader.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

CShader::CShader(CShaderType shaderType)
{
    mShaderID = 0;
    mShaderType = shaderType;
    bCompiled = false;
    mSrcCode = "";
    mInfoLog[0] = '\0';   
}

GLenum CShader::DecideShaderType()
{
    GLenum shadertype = GL_VERTEX_SHADER;
    switch(mShaderType)
    {
        case CShaderType::VERTEX:
        {
            shadertype = GL_VERTEX_SHADER;
            break;
        }
        case CShaderType::FRAGMENT:
        {
            shadertype = GL_FRAGMENT_SHADER;
            break;
        }
        case CShaderType::GEOMETRY:
        {
            shadertype = GL_GEOMETRY_SHADER;
            break;
        }
        case CShaderType::TESSELLATIONCONTROL:
        {
            shadertype = GL_TESS_CONTROL_SHADER;
            break;
        }
        case CShaderType::TESSELLATIONEVALUATION:
        {
            shadertype = GL_TESS_EVALUATION_SHADER;
            break;
        }
        case CShaderType::COMPUTE:
        {
            shadertype = GL_COMPUTE_SHADER;
            break;
        }
    }
    return shadertype;
}

bool CShader::CompileSourceCode(const GLchar *source)
{
    if(source && source[0] != '\0')
    {
        mSrcCode = source;
        return CompileShader(DecideShaderType(), source);
    }
    return false;
}

bool CShader::CompileSourceCode(const std::string & source)
{
    if(!source.empty())
    {
        mSrcCode = source;
        return CompileSourceCode(source.c_str());
    }
    return false;
}

bool CShader::CompileSourceFile(const GLchar *sourceFile)
{
    if(!sourceFile || sourceFile[0] == '\0')
    {
        return false;
    }
    std::string  code = ReadShaderfile(sourceFile);
    std::cout << code << std::endl;
    
    return CompileSourceCode(code);
}

bool CShader::CompileSourceFile(const std::string & sourceFile)
{
    return CompileSourceFile(sourceFile.c_str());
}

bool CShader::CompileShader(GLenum type, const char * code)
{
    int success;
    bool ret = true;

    mShaderID = glCreateShader(type);
    if(!mShaderID)
    {
        return false;
    }
    glShaderSource(mShaderID, 1, &code, NULL);
    glCompileShader(mShaderID);
    glGetShaderiv(mShaderID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(mShaderID, 512, NULL, mInfoLog);
        std::cerr << "Shader :\t" << mInfoLog << std::endl;
        ret = false;
    }
    bCompiled = ret;
    return bCompiled;    
}

std::string CShader::ReadShaderfile(const GLchar *filePath)
{
    std::string code = "";
    std::ifstream file;

    file.exceptions(std::ifstream::badbit);

    try
    {
        file.open(filePath);
        std::stringstream fileStream;
        fileStream << file.rdbuf();

        file.close();
        code = fileStream.str();
    }
    catch(const std::ifstream::failure &e)
    {
        std::cerr << e.what() << '\n';
        code = "";
    }

    return code;    
}