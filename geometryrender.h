/*
 *  Workshop 1
 *  Computer Graphics course
 *  Dept Computing Science, Umea University
 *  Stefan Johansson, stefanj@cs.umu.se
 */
#pragma once

#include "matrix.h"
#include "model.h"

#include "openglwindow.h"

typedef float Mat4x4[16];

class GeometryRender : public OpenGLWindow
{
public:
    template<typename... ARGS>
    GeometryRender(ARGS&&... args)
        : OpenGLWindow{ std::forward<ARGS>(args)... },
        matView(4, 4, this->matView_initData, 16),
        matProjection(4, 4, this->matProjection_initData, 16)
    {
    }

    void initialize();
    virtual void display() override;

    // translate from keyboard input
    virtual void translateModel(Vec2 transformation_vector);
    virtual void rotateModel(Vec3 rotation_vector);

    virtual void draw();

private:
    GLuint program;

    // OpenGL buffers
    GLuint vao;
    GLuint vBuffer;
    GLuint iBuffer;

    // OpenGL attribute locations
    GLuint locVertices;


    Model model;

    Mat4x4 matView_initData = {
        1.0, 0.0, 0.0, 0.0, 
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
        };
    Matrix<float> matView;

    Mat4x4 matProjection_initData = {
        1.0, 0.0, 0.0, 0.0, 
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
        };
    Matrix<float> matProjection;
    
    GLuint locModel;

    // Geometry data
    std::vector<Vec4> vertices;
    std::vector<unsigned int> indices;

    void debugShader(void) const;

    void loadGeometry(void);
};
