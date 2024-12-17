#include "collision.hpp"


void check_collision(Body& body, int window_width, int window_height, int object_width, int object_height) {
    Vec3 pos = body.get_pos();
    Vec3 vel = body.get_velocity();
    
    float radius = object_width / 2.0f;  // Use radius for consistent collision detection

    // Left bound - check against radius
    if(pos.x - radius <= 0) {
        pos.x = radius;  // Place exactly at left border plus radius
        vel.x = -vel.x * 0.8f;  // Add same bounce energy loss as bottom
    }

    // Right bound - check against radius
    if(pos.x + radius >= window_width) {
        pos.x = window_width - radius;  // Place exactly at right border minus radius
        vel.x = -vel.x * 0.8f;
    }

    // Top bound - check against radius
    if(pos.y - radius <= 0) {
        pos.y = radius;
        vel.y = -vel.y * 0.8f;
    }

    // Bottom bound - check against radius
    if(pos.y + radius >= window_height) {
        pos.y = window_height - radius;
        vel.y = -vel.y * 0.8f;
    }

    body.set_pos(pos);
    body.set_velocity(vel);
}
