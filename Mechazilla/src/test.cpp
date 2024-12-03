#include "bn_core.h"
#include "bn_display.h"
#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_builder.h"
#include "bn_keypad.h"



//////////////////// RENDERING AND MOVING SPRITES ////////////////////

// Add these includes for the sprite items
#include "bmp_name.h"

// declaring movable sprites:
bn::sprite_ptr name;
// at that pointer's address create the sprite object
name(bn::sprite_items::bmp_name.create_sprite(X, Y));

////// OR : //////

bn::sprite_ptr name = bn::sprite_items::bmp_name.create_sprite(X, Y);

// updating position:
left_paddle.set_position(10, left_paddle_y);


////////////////////  ROTATING SPRITES ////////////////////
#include <butano/butano.h>

// Set the rotation angle in radians
float theta = 45.0f * bn::pi / 180.0f; // 45 degrees in radians

// Rotate the sprite
name.set_rotation(theta);


////////////////////  BUTTON PRESSES ////////////////////
Button press:
// Update player-controlled right paddle
if(bn::keypad::up_held() && right_paddle_y > PADDLE_HEIGHT / 2) {
    right_paddle_y -= PADDLE_SPEED;
}


// Update the game state and render the frame
bn::core::update();