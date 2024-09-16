// body.cpp
#include "body.hpp"
#include <iostream>

Body::Body(double mass, const Vec3& pos, const Vec3& velocity)
    : mass(mass), pos(pos), velocity(velocity) {}

double Body::get_mass() const {
    return mass;
}

const Vec3& Body::get_pos() const {
    return pos;
}

const Vec3& Body::get_velocity() const {
    return velocity;
}

void Body::set_pos(const Vec3& position) {
    this->pos = position;
}

void Body::set_velocity(const Vec3& velocity) {
    this->velocity = velocity;
}

void Body::update_pos(double dt) {
    pos = pos.add(velocity.mul(dt)); // pos += velocity * dt
}


