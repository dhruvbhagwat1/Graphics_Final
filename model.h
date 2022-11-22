#pragma once

// or: C++20 std::numbers::pi with #include <numbers>
#include <cmath>

#include "matrix.h"
#include "identitymat.h"

class Model
{
    private:
        float m_x, m_y, m_z, m_roation_x, m_roation_y, m_roation_z;
        Matrix<float> m_translation_matrix, m_x_rotation_matrix, m_y_rotation_matrix, m_z_rotation_matrix;
        Matrix<float> m_model_matrix;

        void update_model_matrix();

    public:
        Model(float x, float y, float z, float roation_x, float roation_y, float roation_z);
        Model();

        Matrix<float> matrix() const;

        float x() const;
        float y() const;
        float z() const;
        float roation_x() const;
        float roation_y() const;
        float roation_z() const;

        void translate_to(float x, float y, float z);
        void translate_x_to(float x);
        void translate_y_to(float y);
        void translate_z_to(float z);
        void translate_by(float x_distance, float y_distance, float z_distance);
        void translate_x_by(float distance);
        void translate_y_by(float distance);
        void translate_z_by(float distance);

        void rotate_to(float x_degrees, float y_degrees, float z_degrees);
        void rotate_x_to(float degrees);
        void rotate_y_to(float degrees);
        void rotate_z_to(float degrees);
        void rotate_by(float x_degrees, float y_degrees, float z_degrees);
        void rotate_x_by(float degrees);
        void rotate_y_by(float degrees);
        void rotate_z_by(float degrees);
};