// include/vec3.hpp
#ifndef VEC3_HPP
#define VEC3_HPP
#include <iostream>

class Vec3 {
    public:
        float x, y, z;

        // Constructor
        Vec3(float x = 0, float y = 0, float z = 0);

        // Subscript operator (const and non-const versions)
        float& operator[](int index) {
            if (index == 0) return x;
            if (index == 1) return y;
            if (index == 2) return z;
            throw std::out_of_range("Index out of range. Vec3 only has indices 0, 1, 2.");
        }

        const float& operator[](int index) const {
            if (index == 0) return x;
            if (index == 1) return y;
            if (index == 2) return z;
            throw std::out_of_range("Index out of range. Vec3 only has indices 0, 1, 2.");
        }
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
