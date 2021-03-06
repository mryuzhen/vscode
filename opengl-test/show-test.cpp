#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <shader.hpp>
#include <ShaderProgram.hpp>

#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup") //去除console窗口

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void key_callback(GLFWwindow *pwindow, int key, int scancode, int action, int mode)
{
    if((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
    {
        glfwSetWindowShouldClose(pwindow, GL_TRUE);
    }
}

const GLchar* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
const GLchar* fragmentShaderSource = "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main()
{
        // glfw: initialize and configure
        // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //uncomment this statement to fix compilation on OS X
#endif
        // glfw window creation
        // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,"LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
    }
    glfwMakeContextCurrent(window);
        // glad: load all OpenGL function pointers
        // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glfwSetKeyCallback(window, key_callback);


    CShader vertex_shader(CShaderType::VERTEX);
    CShader fragment_shader(CShaderType::FRAGMENT);

    bool ret = vertex_shader.CompileSourceCode(vertexShaderSource);
    if(!ret)
    {
        std::cout << "Failed to compile vertex shader!!" << std::endl;
        return -1;
    }
    ret = fragment_shader.CompileSourceCode(fragmentShaderSource);
    if(!ret)
    {
        std::cout << "Failed to compile fragment shader!!!" << std::endl;
        return -1;
    }

    CShaderProgram shaderPro;
    shaderPro.AddShader(&vertex_shader);
    shaderPro.AddShader(&fragment_shader);
    shaderPro.Create();
    shaderPro.Link();

    GLfloat vertex[] = {
        0.5f, 0.5f, 0.0f, 
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,                       
        -0.5f, 0.5f, 0.0f};

    GLuint indices[] = {
        0, 1, 3, 
        1, 2, 3};

    GLuint VBO, VAO, EBO;
//1
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
//2
    glBindVertexArray(VAO);
//3
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
//4
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
//5
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
        // render loop
        // -----------
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shaderPro.Bind();
        glBindVertexArray(VAO);

        //glPointSize(15.0);
        //glDrawArrays(GL_POINTS, 0, 4);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
        // glfw: swap buffers and poll IO events (keyspressed/released, mouse moved etc.)
        // ---------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
        // glfw: terminate, clearing all previously allocated GLFWresources.
        //---------------------------------------------------------------
    glfwTerminate();
    return 0;
}
