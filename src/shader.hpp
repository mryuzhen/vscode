#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <string>

enum class CShaderType {
    VERTEX,
    FRAGMENT,
    GEOMETRY,
    TESSELLATIONCONTROL,
    TESSELLATIONEVALUATION,
    COMPUTE
 };

class CShader {
private:
    GLuint mShaderID;
    CShaderType mShaderType;
    bool bCompiled;
    std::string mSrcCode;
    GLchar mInfoLog[512];
public:
    CShader(CShaderType shaderType);
    virtual ~CShader(){glDeleteShader(mShaderID);mShaderID = 0;}

    bool IsCompiled(){return bCompiled;}
    GLuint ShaderID(){return mShaderID;}
    CShaderType ShaderType(){return mShaderType;}
    std::string SourceCode(){return mSrcCode;}
    const GLchar *InfoLog(){return mInfoLog;}

    bool CompileSourceCode(const GLchar *source);
    bool CompileSourceCode(const std::string & source);

    bool CompileSourceFile(const GLchar *sourceFile);
    bool CompileSourceFile(const std::string & sourceFile);
private:
    std::string ReadShaderfile(const GLchar *filePath);
    bool CompileShader(GLenum type, const char * code);
    GLenum DecideShaderType();
};

#endif