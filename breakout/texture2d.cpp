#include "texture2d.hpp"

CTexture2d::CTexture2d() 
    : mWidth(0), mHeight(0), mInternalFormat(GL_RGB), 
    mImageFormat(GL_RGB), mWrapS(GL_REPEAT),mWrapT(GL_REPEAT),
    mFilterMin(GL_LINEAR), mFilterMax(GL_LINEAR)
{
    glGenTextures(1, &mID);
}
CTexture2d::~CTexture2d()
{
    glDeleteTextures(1, &mID);
}

void CTexture2d::Generate(GLuint width, GLuint height, unsigned char *data)
{
    mWidth = width;
    mHeight = height;

    glBindTexture(GL_TEXTURE_2D, mID);
    glTexImage2D(GL_TEXTURE_2D, 0, mInternalFormat, width, height, 0, mImageFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mFilterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mFilterMax);

    glBindTexture(GL_TEXTURE_2D, 0);
}
void CTexture2d::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, mID);
}