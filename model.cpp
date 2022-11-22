
#include "model.h"

Model::Model(float x, float y, float z, float roation_x, float roation_y, float roation_z) :
    m_model_matrix(4, 4),
    m_translation_matrix(4, 4),
    m_x_rotation_matrix(4, 4),
    m_y_rotation_matrix(4, 4),
    m_z_rotation_matrix(4, 4)
{
    m_translation_matrix = getIdentityMatrix<float>(4);
    m_x_rotation_matrix = getIdentityMatrix<float>(4);
    m_y_rotation_matrix = getIdentityMatrix<float>(4);
    m_z_rotation_matrix = getIdentityMatrix<float>(4);

    translate_to(x, y, z);
    rotate_to(roation_x, roation_y, roation_z);
}

Model::Model() : Model(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f)
{
}


void Model::update_model_matrix()
{
    m_model_matrix = m_translation_matrix * m_x_rotation_matrix * m_y_rotation_matrix * m_z_rotation_matrix;
}


Matrix<float> Model::matrix() const { return(m_model_matrix); }


float Model::x() const { return(m_x); }
float Model::y() const { return(m_y); }
float Model::z() const { return(m_z); }
float Model::roation_x() const { return(m_roation_x); }
float Model::roation_y() const { return(m_roation_y); }
float Model::roation_z() const { return(m_roation_z); }


void Model::translate_to(float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;

    m_translation_matrix(1, 4) = m_x;
    m_translation_matrix(2, 4) = m_y;
    m_translation_matrix(3, 4) = m_z;

    update_model_matrix();
}

void Model::translate_x_to(float x) { translate_to(x, m_y, m_z); }

void Model::translate_y_to(float y) { translate_to(m_x, y, m_z); }

void Model::translate_z_to(float z) { translate_to(m_x, m_y, z); }

void Model::translate_by(float x_distance, float y_distance, float z_distance)
{
    translate_to(m_x + x_distance, m_y + y_distance, m_z + z_distance);
}

void Model::translate_x_by(float distance) { translate_to(m_x + distance, m_y, m_z); }

void Model::translate_y_by(float distance) { translate_to(m_x, m_y + distance, m_z); }

void Model::translate_z_by(float distance) { translate_to(m_x, m_y, m_z + distance); }


void Model::rotate_to(float x_degrees, float y_degrees, float z_degrees)
{
    x_degrees = std::fmod(x_degrees, 360);
    y_degrees = std::fmod(y_degrees, 360);
    z_degrees = std::fmod(z_degrees, 360);

    m_roation_x = x_degrees;
    m_roation_y = y_degrees;
    m_roation_z = z_degrees;

    float sin = std::sin(x_degrees * (M_PI / 180));
    float cos = std::cos(x_degrees * (M_PI / 180));
    m_x_rotation_matrix(2, 2) = cos;
    m_x_rotation_matrix(2, 3) = -sin;
    m_x_rotation_matrix(3, 2) = sin;
    m_x_rotation_matrix(3, 3) = cos;

    sin = std::sin(y_degrees * (M_PI / 180));
    cos = std::cos(y_degrees * (M_PI / 180));
    m_y_rotation_matrix(1, 1) = cos;
    m_y_rotation_matrix(1, 3) = sin;
    m_y_rotation_matrix(3, 1) = -sin;
    m_y_rotation_matrix(3, 3) = cos;

    sin = std::sin(z_degrees  * (M_PI / 180));
    cos = std::cos(z_degrees  * (M_PI / 180));
    m_z_rotation_matrix(1, 1) = cos;
    m_z_rotation_matrix(1, 2) = -sin;
    m_z_rotation_matrix(2, 1) = sin;
    m_z_rotation_matrix(2, 2) = cos;

    update_model_matrix();
}

void Model::rotate_x_to(float degrees)
{
    degrees = std::fmod(degrees, 360);

    m_roation_x = degrees;

    float sin = std::sin(degrees * (M_PI / 180));
    float cos = std::cos(degrees * (M_PI / 180));
    m_x_rotation_matrix(2, 2) = cos;
    m_x_rotation_matrix(2, 3) = -sin;
    m_x_rotation_matrix(3, 2) = sin;
    m_x_rotation_matrix(3, 3) = cos;

    update_model_matrix();
}

void Model::rotate_y_to(float degrees)
{
    degrees = std::fmod(degrees, 360);

    m_roation_y = degrees;

    float sin = std::sin(degrees * (M_PI / 180));
    float cos = std::cos(degrees * (M_PI / 180));
    m_y_rotation_matrix(1, 1) = cos;
    m_y_rotation_matrix(1, 3) = sin;
    m_y_rotation_matrix(3, 1) = -sin;
    m_y_rotation_matrix(3, 3) = cos;

    update_model_matrix();
}

void Model::rotate_z_to(float degrees)
{
    degrees = std::fmod(degrees, 360);

    m_roation_z = degrees;

    float sin = std::sin(degrees * (M_PI / 180));
    float cos = std::cos(degrees * (M_PI / 180));
    m_z_rotation_matrix(1, 1) = cos;
    m_z_rotation_matrix(1, 2) = -sin;
    m_z_rotation_matrix(2, 1) = sin;
    m_z_rotation_matrix(2, 2) = cos;

    update_model_matrix();
}

void Model::rotate_by(float x_degrees, float y_degrees, float z_degrees)
{
    rotate_to(m_roation_x + x_degrees, m_roation_y + y_degrees, m_roation_z + z_degrees);
}

void Model::rotate_x_by(float degrees) { rotate_x_to(m_roation_x + degrees); }

void Model::rotate_y_by(float degrees) { rotate_y_to(m_roation_y + degrees); }

void Model::rotate_z_by(float degrees) { rotate_z_to(m_roation_z + degrees); }