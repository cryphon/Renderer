#include "vec3.hpp"
#include <cmath>
#include <iostream>

Vec3::Vec3(float x, float y, float z): x(x), y(y), z(z) {}

// Vector add
Vec3 Vec3::add(const Vec3& other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::sub(const Vec3& other) const {
    return Vec3(x - other.x, y - other.y, z - other.z);
}

// Scalar multiplication
Vec3 Vec3::mul(float scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

float Vec3::dot(const Vec3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3& other) const {
    return Vec3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
            );
}

// Magnitude of vector
float Vec3::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Normalize vector
Vec3 Vec3::normalize() const {
    float mag = magnitude();
    return Vec3(x / mag, y / mag, z / mag);
}

void Vec3::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")\n";
}







