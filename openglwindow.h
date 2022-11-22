/*
 *  Workshop 1
 *  Computer Graphics course
 *  Dept Computing Science, Umea University
 *  Stefan Johansson, stefanj@cs.umu.se
 */
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "3dstudio.h"

class OpenGLWindow
{
public:
    OpenGLWindow(std::string title, int width, int height);
    ~OpenGLWindow();

    GLFWwindow* window() const;
    virtual void errorCallback(int error, const char* desc);
    virtual void resizeCallback(GLFWwindow* window, int width, int height);

    void start();
    virtual void initialize() = 0;
    virtual void display() = 0;
    void displayNow();

    // anarchy
    int getWidth() {return width();}
    int getHeight() {return height();}

    virtual void translateModel(Vec2 transformation_vector) = 0;
    virtual void rotateModel(Vec3 rotation_vector) = 0;

protected:
    bool checkOpenGLError() const;
    int width() const;
    int height() const;

    std::string readShaderSource(const std::string shaderFile) const;
    GLuint initProgram(const std::string vShaderFile, const std::string fShaderFile) const;

    void reshape(const int width, const int height) const;

private:
    GLFWwindow* glfwWindow;
    int windowWidth = 0;
    int windowHeight = 0;
};
