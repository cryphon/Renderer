#include "body.hpp"


Vec3 max_velocity = Vec3(25.0, 25.0, 100.0);

class Planet : Body {
    void apply_attraction_force(Vec3 sun_pos, float sun_mass, float dt) {
        
        Vec3 vel = get_velocity();
        Vec3 pos = get_pos();
        float mass = get_mass();
        float gravity = get_gravity();


        Vec3 direction = sun_pos.sub(pos);
        float distance = direction.length();

        if(distance > 0.5f) {
            direction = direction.normalize();
            float force_magnitude = (gravity * mass * sun_mass) / (distance * distance);
            Vec3 force = direction.mul(force_magnitude);

            Vec3 acceleration = force.div(mass);
            if(vel.length() > max_velocity.length()) {
                set_velocity(vel.normalize().mul(max_velocity.length()));
            }
            else {
                set_velocity((vel.add(acceleration.mul(dt))).mul(0.96));
            }

            pos = pos.add(vel.mul(dt).mul(0.95));
        }
    }
};
