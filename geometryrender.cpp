/*
 *  Workshop 1
 *  Computer Graphics course
 *  Dept Computing Science, Umea University
 *  Stefan Johansson, stefanj@cs.umu.se
 */

#include "geometryrender.h"

// Initialize OpenGL
void GeometryRender::initialize()
{
    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Create and initialize a program object with shaders
    program = initProgram("vshader.glsl", "fshader.glsl");
    // Installs the program object as part of current rendering state
    glUseProgram(program);

    // Creat a vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create vertex buffer in the shared display list space and
    // bind it as VertexBuffer (GL_ARRAY_BUFFER)
    glGenBuffers( 1, &vBuffer);
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer);

    /* Create buffer in the shared display list space and 
       bind it as GL_ELEMENT_ARRAY_BUFFER */
    glGenBuffers(1, &iBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBuffer);

    // Get locations of the attributes in the shader
    locVertices = glGetAttribLocation( program, "vertex");

    // stuff with the model matrix
    locModel = glGetUniformLocation(program,"M");

    glBindVertexArray(0);
    glUseProgram(0);

    loadGeometry();

}

void GeometryRender::loadGeometry(void)
{
    // Define vertices in array
    vertices.push_back(Vec4(-0.5f, -0.75f, 0.0f, 1.0f));
    vertices.push_back(Vec4( 0.0f,  0.75f, 0.0f, 1.0f));
    vertices.push_back(Vec4( 0.5f, -0.75f, 0.0f, 1.0f));

    // second triangle vertex
    //vertices.push_back(Vec4( 0.75f, 0.75f, 0.0f, 1.0f));

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    // second triangle indeces

    //indices.push_back(1);
    //indices.push_back(2);
    //indices.push_back(3);

    glUseProgram(program);
    glBindVertexArray(vao);

    // Set the pointers of locVertices to the right places
    glVertexAttribPointer(locVertices, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(locVertices);

    // stuff with the model matrix
    glUniformMatrix4fv(locModel, 1, GL_TRUE, (matProjection*matView*model.matrix()).data());

    // Load object data to the array buffer and index array
    size_t vSize = vertices.size()*sizeof(Vec4);
    size_t iSize = indices.size()*sizeof(unsigned int);
    glBufferData( GL_ARRAY_BUFFER, vSize, vertices.data(), GL_STATIC_DRAW );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, iSize, indices.data(), GL_STATIC_DRAW );

    glBindVertexArray(0);
    glUseProgram(0);
}

// Check if any error has been reported from the shader
void GeometryRender::debugShader(void) const
{
    GLint  logSize;
    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize );
    if (logSize > 0) {
        std::cerr << "Failure in shader "  << std::endl;
        char logMsg[logSize+1];
        glGetProgramInfoLog( program, logSize, nullptr, &(logMsg[0]) );
        std::cerr << "Shader info log: " << logMsg << std::endl;
    }

}

// Render object
void GeometryRender::display()
{
    glUseProgram(program);
    glBindVertexArray(vao);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Call OpenGL to draw the triangle
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, BUFFER_OFFSET(0));

    // Not to be called in release...
    debugShader();

    glBindVertexArray(0);
    glUseProgram(0);

}

void
GeometryRender::translateModel(Vec2 transformation_vector)
{
    model.translate_by(transformation_vector.values[0], transformation_vector.values[1], 0);

    draw();
}

void
GeometryRender::rotateModel(Vec3 rotation_vector)
{
    model.rotate_by(rotation_vector.values[0], rotation_vector.values[1], rotation_vector.values[2]);

    draw();
}

void
GeometryRender::draw()
{
    //std::cout << (matProjection*matView*model.matrix()).toString() << std::endl;
    glUseProgram(program);
    glUniformMatrix4fv(locModel, 1, GL_TRUE, (matProjection*matView*model.matrix()).data());
    glUseProgram(0);

    displayNow();
}