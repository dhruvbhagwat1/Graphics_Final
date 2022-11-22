/*
 *  Workshop 1
 *  Computer Graphics course
 *  Dept Computing Science, Umea University
 *  Stefan Johansson, stefanj@cs.umu.se
 */

#include "geometryrender.h"
#include "glfwcallbackmanager.h"

OpenGLWindow* glfwCallbackManager::app = nullptr;

int main(int argc, char **argv)
{
    GeometryRender app("Introduction to computer graphics - project", 1920, 1080);
    glfwCallbackManager::initCallbacks(&app);
    app.initialize();

    app.start();
}