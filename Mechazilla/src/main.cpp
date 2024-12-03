<<<<<<< HEAD
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
=======
#include "vector"
#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_math.h"
#include "bn_fixed.h"
#include "bn_sprite_items_mechazilla.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_stage1.h"
#include "bn_regular_bg_items_stage2.h"
#include "bn_regular_bg_items_stage3.h"
#include "bn_keypad.h"
#include "bn_sprite_items_rocket.h"
#include "bn_optional.h"
#include "bn_random.h"
#include "bn_regular_bg_items_goodintro.h"

const int FRAME_LIMIT = 60;

enum class GameStage {
    STAGE1,
    STAGE2,
    STAGE3
};

class Booster
{
private:
    bn::fixed x, y;          
    bn::fixed vx, vy;        
    bn::fixed ax, ay;        
    bn::fixed theta_r;       
    bn::fixed omega_r;       
    bn::fixed alpha_r;       
    bn::fixed theta_v;       
    bn::fixed mass;          
    bn::fixed inertia;       
    bn::fixed height;        
    static constexpr bn::fixed GRAVITY = 0.5;   
    static constexpr bn::fixed MOVE_SPEED = 3;
    static constexpr bn::fixed WIND_FORCE = 0.08;  // Increased wind force
    static constexpr bn::fixed TURBULENCE = 0.1;  // Increased turbulence
    bn::random random;

public:
    Booster(bn::fixed initial_x, bn::fixed initial_y, bn::fixed booster_mass, bn::fixed booster_inertia, bn::fixed booster_height)
        : x(initial_x), y(initial_y), vx(0), vy(0), ax(0), ay(GRAVITY), theta_r(0), omega_r(0), alpha_r(0), theta_v(0),
          mass(booster_mass), inertia(booster_inertia), height(booster_height)
    {
    }

    void move_left()
    {
        vx = -MOVE_SPEED;
    }

    void move_right()
    {
        vx = MOVE_SPEED;
    }

    void stop_horizontal()
    {
        vx = 0;
    }

    void update(bn::fixed dt)
    {
        // Apply gravity
        vy += ay * dt;

        // Update position
        x += vx * dt;
        y += vy * dt;

        // Update rotation
        omega_r += alpha_r * dt;
        theta_r += omega_r * dt;
    }

    void reset_position(bn::fixed new_x, bn::fixed new_y)
    {
        x = new_x;
        y = new_y;
        vx = 0;
        vy = 0;
        theta_r = 0;
        omega_r = 0;
        alpha_r = 0;
    }

    bn::fixed get_x() const { return x; }
    bn::fixed get_y() const { return y; }
    bn::fixed get_theta_r() const { return theta_r; }

    void apply_wind(bool direction)
    {
        if(direction)
        {
            vx += WIND_FORCE * 2;  // Stronger push right
        }
        else
        {
            vx -= WIND_FORCE * 2;  // Stronger push left
        }
    }

    void apply_turbulence()
    {
        // Only affect horizontal movement with stronger effect
        vx += (random.get() % 200 - 100) * TURBULENCE / 100;  // Increased range and strength
    }
};

int main()
{
    bn::core::init();

    // Initialize intro background with goodintro
    bn::optional<bn::regular_bg_ptr> intro_bg = bn::regular_bg_items::goodintro.create_bg(0, 0);

    // Wait for A button press to start game
    while(!bn::keypad::a_pressed())
    {
        bn::core::update();
    }

    // Clear intro screen
    intro_bg.reset();

    // Initialize stage1 background after intro
    GameStage current_stage = GameStage::STAGE1;
    bn::optional<bn::regular_bg_ptr> bg1 = bn::regular_bg_items::stage1.create_bg(0, 0);
    bn::optional<bn::regular_bg_ptr> bg2;
    bn::optional<bn::regular_bg_ptr> bg3;

    // Screen dimensions (GBA screen is 240x160)
    const bn::fixed screen_width = 240;
    const bn::fixed screen_height = 160;
    const bn::fixed sprite_width = 32;

    // Start position: center horizontally (0), top of screen (-80)
    const bn::fixed start_x = 0;
    const bn::fixed start_y = -80;

    // Initialize random number generator
    bn::random random;

    // Booster initialization
    Booster booster(start_x, start_y, 100, 50, 20);
    bn::sprite_ptr booster_sprite = bn::sprite_items::rocket.create_sprite(start_x, start_y);
    booster_sprite.set_rotation_angle(0);

    // Create Mechazilla sprite with initial random position
    bn::fixed mechazilla_x = (random.get() % 160) - 80;
    bn::sprite_ptr mechazilla_sprite = bn::sprite_items::mechazilla.create_sprite(mechazilla_x, 48);

    // Add wind direction toggle with faster changes
    bool wind_right = true;
    int wind_counter = 0;
    const int WIND_CHANGE_RATE = 30;

    while (true)
    {
        // Handle rocket movement based on current stage
        switch(current_stage)
        {
            case GameStage::STAGE1:
                // Basic movement
                if(bn::keypad::left_held() && booster.get_x() > -120)
                {
                    booster.move_left();
                }
                else if(bn::keypad::right_held() && booster.get_x() < 120)
                {
                    booster.move_right();
                }
                else
                {
                    booster.stop_horizontal();
                }
                break;

            case GameStage::STAGE2:
                // Stage 2: Stronger wind effect
                if(bn::keypad::left_held() && booster.get_x() > -120)
                {
                    booster.move_left();
                }
                else if(bn::keypad::right_held() && booster.get_x() < 120)
                {
                    booster.move_right();
                }
                else
                {
                    booster.stop_horizontal();
                }
                
                // More frequent wind changes
                wind_counter++;
                if(wind_counter >= WIND_CHANGE_RATE)
                {
                    wind_counter = 0;
                    wind_right = !wind_right;
                }
                booster.apply_wind(wind_right);
                break;

            case GameStage::STAGE3:
                // Stage 3: Wind and strong horizontal turbulence
                if(bn::keypad::left_held() && booster.get_x() > -120)
                {
                    booster.move_left();
                }
                else if(bn::keypad::right_held() && booster.get_x() < 120)
                {
                    booster.move_right();
                }
                else
                {
                    booster.stop_horizontal();
                }
                
                booster.apply_wind(wind_right);
                booster.apply_turbulence();  // Now only affects horizontal movement
                break;
        }

        // Update rocket physics
        booster.update(0.1);
        booster_sprite.set_position(booster.get_x(), booster.get_y());
        booster_sprite.set_rotation_angle(booster.get_theta_r());

        // Check for collision between rocket and current Mechazilla position
        if(abs(booster.get_x() - mechazilla_sprite.x()) < 16 && abs(booster.get_y() - 48) < 16)
        {
            // Collision detected! Move to next stage
            switch(current_stage)
            {
                case GameStage::STAGE1:
                    bg1.reset();
                    bg2 = bn::regular_bg_items::stage2.create_bg(0, 0);
                    current_stage = GameStage::STAGE2;
                    mechazilla_x = (random.get() % 160) - 80;
                    mechazilla_sprite.set_x(mechazilla_x);
                    booster.reset_position(start_x, start_y);
                    break;
                    
                case GameStage::STAGE2:
                    bg2.reset();
                    bg3 = bn::regular_bg_items::stage3.create_bg(0, 0);
                    current_stage = GameStage::STAGE3;
                    mechazilla_x = (random.get() % 160) - 80;
                    mechazilla_sprite.set_x(mechazilla_x);
                    booster.reset_position(start_x, start_y);
                    break;
                    
                case GameStage::STAGE3:
                    // Freeze the final scene
                    while(true)
                    {
                        bn::core::update();  // Keep updating the screen
                    }
            }
        }
        else if(booster.get_y() > 80)
        {
            booster.reset_position(start_x, start_y);
        }

        bn::core::update();
    }

    return 0;
}
>>>>>>> c23646f (new push rocket pls work)
