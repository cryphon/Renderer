// body.cpp
#include "body.hpp"
#include <iostream>

Body::Body(double mass, const Vec3& pos, const Vec3& velocity, int width, int height)
    : mass(mass), pos(pos), velocity(velocity), width(width), height(height) {}

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

void Body::set_gravity(const float gravity) {
    this->gravity = gravity;
}

void Body::update_pos(double dt) {
    Vec3 vel = get_velocity();

    if(this->gravity != 0.0f) {
        vel.y += gravity * dt;
        set_velocity(vel);
    }
    pos = pos.add(velocity.mul(dt)); // pos += velocity * dt
}


