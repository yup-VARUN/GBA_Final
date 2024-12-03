#include "vector"
#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_math.h"
#include "bn_fixed.h"
#include "bn_sprite_items_mechazilla.h" // Include your sprite assets here
// #include "bn_sound_items_explosion.h"
// #include "bn_sound_items_flame.h"

class Booster
{
private:
    bn::fixed x, y;          // Position
    bn::fixed vx, vy;        // Velocity
    bn::fixed ax, ay;        // Acceleration
    bn::fixed theta_r;       // Orientation of the rocket
    bn::fixed omega_r;       // Angular velocity
    bn::fixed alpha_r;       // Angular acceleration
    bn::fixed theta_v;       // Thrust vector angle relative to the rocket
    const bn::fixed mass;    // Mass of the booster
    const bn::fixed inertia; // Moment of inertia
    const bn::fixed height;  // Height of the booster

public:
    Booster(bn::fixed initial_x, bn::fixed initial_y, bn::fixed booster_mass, bn::fixed booster_inertia, bn::fixed booster_height)
        : x(initial_x), y(initial_y), vx(0), vy(0), ax(0), ay(0), theta_r(0), omega_r(0), alpha_r(0), theta_v(0),
          mass(booster_mass), inertia(booster_inertia), height(booster_height)
    {
    }

    void apply_thrust(bn::fixed thrust, bn::fixed theta_v_input)
    {
        theta_v = theta_v_input;
        bn::fixed theta_t = theta_r - theta_v;

        ax = (thrust * bn::sin(theta_t)) / mass;
        ay = (thrust * bn::cos(theta_t)) / mass;

        bn::fixed torque = (height / 2) * thrust * bn::sin(theta_t);
        alpha_r = torque / inertia;
    }

    void update(bn::fixed dt)
    {
        // Update translational parameters
        vx += ax * dt;
        vy += ay * dt;
        x += vx * dt;
        y += vy * dt;

        // Update rotational parameters
        omega_r += alpha_r * dt;
        theta_r += omega_r * dt;
    }

    bool is_landed(bn::fixed screen_width, bn::fixed screen_height)
    {
        // Check if landed safely
        return (y >= screen_height - height / 2) &&
               (bn::abs(vx) < 1 && bn::abs(vy) < 1 && bn::abs(omega_r) < 0.1);
    }

    bool is_crashed(bn::fixed screen_width, bn::fixed screen_height)
    {
        // Check if crashed
        return (y >= screen_height - height / 2) &&
               (bn::abs(vx) >= 1 || bn::abs(vy) >= 1 || bn::abs(omega_r) >= 0.1);
    }

    bn::fixed get_x() const { return x; }
    bn::fixed get_y() const { return y; }
    bn::fixed get_theta_r() const { return theta_r; }
};

int main()
{
    bn::core::init();

    // Screen dimensions
    const bn::fixed screen_width = 240;
    const bn::fixed screen_height = 160;

    // Booster initialization
    Booster booster(screen_width / 2, 20, 100, 50, 20);
    bn::sprite_ptr booster_sprite = bn::sprite_items::mechazilla.create_sprite(booster.get_x(), booster.get_y());

    // Simulation parameters
    const bn::fixed dt = 0.1;
    // std::vector<bn::fixed, 100> thrust_curve = {5, 5, 5, 0, 0}; // Example thrust values
    std::vector<bn::fixed> thrust_curve = {5, 5, 5, 0, 0}; // Dynamically sized vector

    int thrust_index = 0;

    // Game loop
    while (true)
    {
        if (thrust_index < thrust_curve.size())
        {
            booster.apply_thrust(thrust_curve[thrust_index], 0); // Assuming no thrust vectoring
            thrust_index++;
        }

        booster.update(dt);

        booster_sprite.set_position(booster.get_x(), booster.get_y());
        booster_sprite.set_rotation_angle(booster.get_theta_r());

        if (booster.is_landed(screen_width, screen_height))
        {
            // bn::sound_items::flame.play();
            break; // Winning condition
        }
        else if (booster.is_crashed(screen_width, screen_height))
        {
            // bn::sound_items::explosion.play();
            break; // Losing condition
        }

        bn::core::update();
    }

    return 0;
}
