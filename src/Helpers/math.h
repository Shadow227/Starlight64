#include <math.h> 
/*
    This file is simple math functions that the Starlight 64 game engine will need!
    I need to research how to do operators better and might change some of these functions into
    operators but that will either happen later tonight or on another day.
    This file will ONLY hold math functions! And any extra math I need will most likely be added here.
    =Note: I am not an API creator and I am still learning, if this is messy I am sorry.
*/
#pragma region Structs
struct Vector2D
{
    float x, y;
};
struct Vector3D
{
    float x,y,z;
};
struct Transform2D
{
    Vector2D pos,rot,scale;
};
struct Transform3D
{
    Vector3D pos,rot,scale;
};
#pragma endregion

#pragma region Functions
//Vector Math
float Magnitude2D(Vector2D vector)
{
    return sqrt((pow(vector.x, 2) + pow(vector.y,2)));
}
float Magnitude3D(Vector3D vector)
{
    return sqrt((pow(vector.x, 2) + pow(vector.y,2) + pow(vector.z,2)));
}
Vector2D addVector2D(Vector2D vec1, Vector2D vec2)
{
    return Vector2D{vec1.x + vec2.x, vec1.y + vec2.y};
}
Vector3D addVector3D(Vector3D vec1, Vector3D vec2)
{
    return Vector3D{vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z};
}


#pragma endregion