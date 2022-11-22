#include "openglwindow.h"

double cursor_init_x = 0;
double cursor_init_y = 0;

// Class for bridging between the C callback functions in glfw and C++ object
class glfwCallbackManager
{
    static OpenGLWindow* app;

    static void errorCallback(int error, const char* description)
    {
        if(app) 
	    app->errorCallback(error,description);
    }
    
    static void resizeCallback(GLFWwindow* window, int width, int height)
    {
        if(app) 
	    app->resizeCallback(window,width,height);
    }

    // keyboard input
    static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (app) {
            if (action == GLFW_PRESS || action == GLFW_REPEAT) {
                switch (key) {
                    case (GLFW_KEY_L):
                        app->translateModel(Vec2(0.25f, 0.0f));
                        break;
                    case (GLFW_KEY_J):
                        app->translateModel(Vec2(-0.25f, 0.0f));
                        break;
                    case (GLFW_KEY_I):
                        app->translateModel(Vec2(0.0f, 0.25f));
                        break;
                    case (GLFW_KEY_K):
                        app->translateModel(Vec2(0.0f, -0.25f));
                        break;
                    case (GLFW_KEY_U):
                        app->rotateModel(Vec3(0.0f, 0.0f, 10.0f));
                        break;
                    case (GLFW_KEY_O):
                        app->rotateModel(Vec3(0.0f, 0.0f, -10.0f));
                        break;
                    case (GLFW_KEY_LEFT):
                        app->rotateModel(Vec3(0.0f, -10.0f, 0.0f));
                        break;
                    case (GLFW_KEY_RIGHT):
                        app->rotateModel(Vec3(0.0f, 10.0f, 0.0f));
                        break;
                    case (GLFW_KEY_UP):
                        app->rotateModel(Vec3(10.0f, 0.0f, 0.0f));
                        break;
                    case (GLFW_KEY_DOWN):
                        app->rotateModel(Vec3(-10.0f, 0.0f, 0.0f));
                        break;
                }
            }
        }
    }

    // mouse input
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (app) {
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
                glfwGetCursorPos(window, &cursor_init_x, &cursor_init_y);
                glfwSetCursorPosCallback(window, cursor_position_callback);
            }
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
                glfwSetCursorPosCallback(window, NULL);
            }
        }
    }

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        double change_x = (xpos - cursor_init_x) / app->getWidth();
        double change_y = (ypos - cursor_init_y) * -1 / app->getHeight();
        cursor_init_x = xpos;
        cursor_init_y = ypos;

        //printf ("x: %f\ny: %f \n", change_x, change_y);

        app->translateModel(Vec2(change_x * 2, change_y * 2));
    }


    
public:
    static void initCallbacks(OpenGLWindow* glfwapp)
    {
        app = glfwapp;
        
        glfwSetErrorCallback(errorCallback);
        glfwSetFramebufferSizeCallback(app->window() , resizeCallback);

        // keyboard input
        glfwSetKeyCallback(app->window(), keyboard_callback);

        // mouse input
        glfwSetMouseButtonCallback(app->window(), mouse_button_callback);
    }
};
