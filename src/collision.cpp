#include "collision.hpp"


void check_collision(Body& body, int window_width, int window_height, int object_width, int object_height) {
    Vec3 pos = body.get_pos();
    Vec3 vel = body.get_velocity();
    

    // Left bound
    if(pos.x <= 0) {
        pos.x = 0;
        vel.x = -vel.x;
    }

    // Right bound
    if(pos.x + object_width >= window_width) {
        pos.x = window_width - object_width;
        vel.x = -vel.x;
    }

    // Top bound
    if(pos.y <= 0) {
        pos.y = 0;
        vel.y = -vel.y;
    }

    // Bottom bound
    if(pos.y + object_height >= window_height) {
        pos.y = window_height - object_height;
        vel.y = -vel.y;
    }

    body.set_pos(pos);
    body.set_velocity(vel);
}
