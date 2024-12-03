// #include <butano/butano.h>
#include "vector"
#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_math.h"
#include "bn_fixed.h"
#include "bn_sprite_items_mechazilla.h" // Include your sprite assets here
#include "bn_display.h"
#include "bn_sprite_builder.h"
#include "bn_keypad.h"

// #include "bn_sound_items_explosion.h"
// #include "bn_sound_items_flame.h"

constexpr int SCREEN_WIDTH = 240;
constexpr int SCREEN_HEIGHT = 160;
constexpr float vy = 2;
constexpr float vx = 0;

class Booster
{
private:
    bn::fixed dt = 0.1;         // Discrete Timestep Length
    ////// ROCKET: /////////
    bn::fixed xr, yr;           // Position
    bn::fixed vx, vy;           // Velocity
    bn::fixed ax, ay;           // Acceleration
    bn::fixed theta_r;          // Orientation
    bn::fixed omega_r;          // Angular velocity
    bn::fixed alpha_r;          // Angular acceleration
    
    /////// FLAME: /////////
    bn::fixed xf, yf;           //Position

    bn::fixed theta_v = 0.0f;   // Thrust vector angle relative to the rocket
    bn::fixed theta_t = 0.0f;   // Absolute Angle of the thrust(wrt x-axis)
    const bn::fixed mass;       // Mass of the booster
    const bn::fixed inertia;    // Moment of inertia
    const bn::fixed height;     // Height of the booster
    const bn::fixed g = 0.2;    // Gravitational Acceleration from earth

public:
    Booster(bn::fixed initial_x, bn::fixed initial_y, bn::fixed booster_mass, bn::fixed booster_inertia, bn::fixed booster_height)
        : x(initial_x), y(initial_y), vx(0), vy(0), ax(0), ay(0), theta_r(0), omega_r(0), alpha_r(0), theta_v(0),
          mass(booster_mass), inertia(booster_inertia), height(booster_height), g(0.2)
    {
    }

    void init()
    {
        ///////////////////// Initializing all the sprites ////////////////////
        bn::sprite_ptr rocket = bn::sprite_items::rocket.create_sprite(x, y);
        bn::sprite_ptr flame = bn::sprite_items::flame_sprite.create_sprite(x, y + height/2);
        rocket.set_position(x, y);
        flame.set_position(x, y + height/2);
    }

    void update(bn::fixed thrust)
    {        
        //////// ROCKET: ////////

        // Button presses to control the theta_v:
        if (!bn::input::left_pressed() && !bn::input::right_pressed()) {
            // No buttons pressed, set theta_v to 0 degrees
            theta_v = 0.0f;
        } else if (bn::input::left_pressed()) {
            // Left button pressed, set theta_v to -15 degrees
            theta_v = -15.0f * bn::pi / 180.0f;
        } else if (bn::input::right_pressed()) {
            // Right button pressed, set theta_v to 15 degrees
            theta_v = 15.0f * bn::pi / 180.0f;
        }

        theta_t = theta_r - theta_v;

        // Update rotational parameters
        bn::fixed torque = (height / 2) * thrust * bn::sin(theta_t);
        alpha_r = torque / inertia;
        
        omega_r += alpha_r * dt;
        theta_r += omega_r * dt;

        // Update translational parameters
        // 1. Acceleration:
        ax = (thrust * bn::sin(theta_t)) / mass;
        ay = (thrust * bn::cos(theta_t)) / mass;
        // 2. Velocities:
        vx += ax * dt;
        vy += (ay - g) * dt;
        // 3. positions:
        xr += vx * dt;
        yr += vy * dt;

        //////// FLAME: ///////
        xf = xr + height * bn::cos(theta_r);
        yf = yr + height * bn::sin(theta_r);

        /////////////// UPDATING SPRITES ///////////////
        rocket.set_position(xr, yr);
        rocket.set_rotation(theta_r);
        flame.set_position(xf, yf);
        flame.set_rotation(theta_t);
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
    bn::core::init(SCREEN_WIDTH, SCREEN_HEIGHT);

    // // Create a text generator
    // bn::text_generator text_generator(4, 4);

    // // Set the text properties
    // text_generator.set_font(bn::font_actions::load_font_actions("font"));
    // text_generator.set_center_alignment();
    // text_generator.set_bg_color(bn::color::white);
    // text_generator.set_fg_color(bn::color::black);

    // // Display a text heading
    // text_generator.generate(120, 20, "Rocket Landing Game");
 
    Booster booster(10, 10, 10, 10, 10);
    booster.init();
    while(true)
    {
        booster.update();
        bn::core::update();
    }

    return 0;
}