#ifndef BODY_HPP // BODY_HPP
#define BODY_HPP

#include "vec3.hpp"
#include <vector>
class Body {
    public:
        int width, height;
        Body(double mass, const Vec3& pos, const Vec3& velocity, int width, int height);
        
        double get_mass() const;
        const Vec3& get_pos() const;
        const Vec3& get_velocity() const;
        float get_gravity() const;

        void set_pos(const Vec3& pos);
        void set_velocity(const Vec3& velocity);
        const void set_gravity(const float gravity = NULL);
        
        void apply_attraction_force(Vec3 sun_pos, float sun_mass, float dt);
        void update_pos(double dt);

    private:
        double mass;
        Vec3 pos;  // 3D position vector (x, y, z)
        Vec3 velocity;  // 3D velocity vector (vx, vy, vz)
        float gravity;
};


#endif // BODY_HPP
