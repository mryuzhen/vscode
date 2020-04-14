#ifndef TEXTURE2D_HPP
# define TEXTURE2D_HPP
#include <glad/glad.h>
#include <glfw/glfw3.h>

class CTexture2d
{
public:
    GLuint mID;
    GLuint mWidth,mHeight;
    GLuint mInternalFormat;
    GLuint mImageFormat;
    GLuint mWrapS;
    GLuint mWrapT;
    GLuint mFilterMin;
    GLuint mFilterMax;
public:
    CTexture2d();
    virtual ~CTexture2d();

    void Generate(GLuint width, GLuint height, unsigned char *data);
    void Bind() const;
};

#endif
