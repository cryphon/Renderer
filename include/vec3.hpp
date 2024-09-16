// include/vec3.hpp
#ifndef VEC3_HPP
#define VEC3_HPP

class Vec3 {
    public:
        float x, y, z;
        
        // Constructor
        Vec3(float x = 0, float y = 0, float z = 0);
        // Vector addition
    Vec3 add(const Vec3& other) const;

    // Vector subtraction
    Vec3 sub(const Vec3& other) const;

    // Scalar multiplication
    Vec3 mul(float scalar) const;

    // Dot product
    float dot(const Vec3& other) const;

    // Cross product
    Vec3 cross(const Vec3& other) const;

    // Magnitude of the vector
    float magnitude() const;

    // Normalize the vector
    Vec3 normalize() const;

    // Print
    void print() const;
};

#endif //VEC3_HPP
