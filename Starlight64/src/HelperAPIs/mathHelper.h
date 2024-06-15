#include <math.h> 
#pragma once
/*
    A simplistic math function for vectors, matrixs, and other game maps Starlight might need. Feel free to add to this!
*/
#pragma region Structs
struct Vector2D
{
    float x, y;

    Vector2D operator+(Vector2D& other)
    {
        return Vector2D{this->x + other.x, this->y + other.y};
    }

    Vector2D operator+(float value)
    {
        return Vector2D{ this->x + value, this->y + value };
    }

    Vector2D operator-(Vector2D& other)
    {
        return Vector2D{ this->x - other.x, this->y - other.y };
    }

    Vector2D operator-(float value)
    {
        return Vector2D{ this->x - value, this->y - value };
    }

    Vector2D operator*(Vector2D& other)
    {
        return Vector2D{ this->x * other.x, this->y * other.y };
    }

    Vector2D operator*(float value)
    {
        return Vector2D{ this->x * value, this->y * value };
    }

};
struct Vector3D
{
    float x, y, z;

    Vector3D operator+(Vector3D& other)
    {
        return Vector3D{ this->x + other.x, this->y + other.y, this->z + other.z };
    }

    Vector3D operator+(float value)
    {
        return Vector3D{ this->x + value, this->y + value, this->z + value };
    }

    Vector3D operator-(Vector3D& other)
    {
        return Vector3D{ this->x - other.x, this->y - other.y, this->z + other.z };
    }

    Vector3D operator-(float value)
    {
        return Vector3D{ this->x - value, this->y - value, this->z - value };
    }

    Vector3D operator*(Vector3D& other)
    {
        return Vector3D{ this->x * other.x, this->y * other.y, this->z * other.z };
    }

    Vector3D operator*(float value)
    {
        return Vector3D{ this->x * value, this->y * value, this->z * value };
    }
};
struct Transform2D
{
    Vector2D pos, rot, scale;
};
struct Transform3D
{
    Vector3D pos, rot, scale;
};
#pragma endregion
