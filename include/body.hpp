#ifndef BODY_HPP // BODY_HPP
#define BODY_HPP

#include "vec3.hpp"

class Body {
    public:
        int width, height;
        Body(double mass, const Vec3& pos, const Vec3& velocity, int width, int height);
        
        double get_mass() const;
        const Vec3& get_pos() const;
        const Vec3& get_velocity() const;

        void set_pos(const Vec3& pos);
        void set_velocity(const Vec3& velocity);
        void set_gravity(const float gravity = NULL);

        void update_pos(double dt);

    private:
        double mass;
        Vec3 pos;  // 3D position vector (x, y, z)
        Vec3 velocity;  // 3D velocity vector (vx, vy, vz)
        float gravity;
};


#endif // BODY_HPP
