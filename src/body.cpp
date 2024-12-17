// body.cpp
#include "body.hpp"
#include <iostream>
#include <functional>

Vec3 max_velocity = Vec3(25.0, 25.0, 100.0);
const float SCALE_FACTOR = 1e6f;  // 1 pixel = 1 million meters (example)


using force_function = std::function<Vec3(const Body&, const Body&)>;

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


float Body::get_gravity() const {
    return gravity;
}

void Body::set_pos(const Vec3& position) {
    this->pos = position;
}

void Body::set_velocity(const Vec3& velocity) {
    this->velocity = velocity;
}

const void Body::set_gravity(const float gravity) {
    this->gravity = gravity;
}

void Body::update_pos(double dt) {
    Vec3 vel = get_velocity();

    if(this->gravity != 0.0f) {
        vel.y += gravity * dt;
        set_velocity(vel);
    }
    pos = pos.add(velocity.mul(dt * 20)); // pos += velocity * dt
    set_pos(pos);
    // Vec3 scaled_pos = pos.div(SCALE_FACTOR);
    // set_pos(scaled_pos);
}

void Body::apply_attraction_force(Vec3 sun_pos, float sun_mass, float dt) {
    Vec3 direction = sun_pos.sub(pos);
    printf("sun_direction: x = %f, y = %f\n", direction.x, direction.y);

    float distance = direction.length();  // Distance to the sun
    printf("distance_to_sun: %f\n", distance);
        
        if (distance > 0.5f) {  // Prevent division by zero
            direction = direction.normalize(); // Get the unit vector in direction of the sun
            printf("direction_normalized: x = %f, y = %f\n", direction.x, direction.y);
            
            // Calculate the force magnitude
            float force_magnitude = (gravity * mass * sun_mass) / (distance * distance);
            
            // Force vector (direction times the magnitude)
            Vec3 force = direction.mul(force_magnitude);

            // Update velocity based on force (F = ma => a = F / m)
            Vec3 acceleration = force.div(mass);
            if (velocity.length() > max_velocity.length()) {
                set_velocity(velocity.normalize().mul(max_velocity.length()));
            }
            else {
                set_velocity((get_velocity().add(acceleration.mul(dt))).mul(0.96));
            }
            // Update position based on new velocity 
            pos = pos.add(velocity.mul(dt).mul(0.95));
            printf("\n\tpos(x = %f, y = %f)\n", pos.x, pos.y);
        }

}



