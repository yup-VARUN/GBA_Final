/*
 * Copyright (c) 2020-2024 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"

#include "bn_affine_bg_items_face.h"
#include "bn_affine_bg_items_red_small.h"
#include "bn_affine_bg_items_blue_small.h"

namespace
{
    void affine_bgs_visibility_scene(bn::sprite_text_generator& text_generator)
    {
        constexpr bn::string_view info_text_lines[] = {
            "A: hide/show BG",
            "",
            "START: go to next scene",
        };

        common::info info("Affine BGs visibility", info_text_lines, text_generator);

        bn::affine_bg_ptr red_bg = bn::affine_bg_items::red.create_bg(0, 0);

        while(! bn::keypad::start_pressed())
        {
            if(bn::keypad::a_pressed())
            {
                red_bg.set_visible(! red_bg.visible());
            }

            info.update();
            bn::core::update();
        }
    }

    void affine_bgs_visibility_actions_scene(bn::sprite_text_generator& text_generator)
    {
        constexpr bn::string_view info_text_lines[] = {
            "START: go to next scene",
        };

        common::info info("Affine BGs visibility actions", info_text_lines, text_generator);

        bn::affine_bg_ptr blue_bg = bn::affine_bg_items::blue.create_bg(0, 0);
        bn::affine_bg_visible_toggle_action action(blue_bg, 60);

        while(! bn::keypad::start_pressed())
        {
            action.update();
            info.update();
            bn::core::update();
        }
    }

    void affine_bgs_position_scene(bn::sprite_text_generator& text_generator)
    {
        constexpr bn::string_view info_text_lines[] = {
            "PAD: move BG",
            "",
            "START: go to next scene",
        };

        common::info info("Affine BGs position", info_text_lines, text_generator);

        bn::affine_bg_ptr red_bg = bn::affine_bg_items::red.create_bg(0, 0);

        while(! bn::keypad::start_pressed())
        {
            if(bn::keypad::left_held())
            {
                red_bg.set_x(red_bg.x() - 1);
            }
            else if(bn::keypad::right_held())
            {
                red_bg.set_x(red_bg.x() + 1);
            }

            if(bn::keypad::up_held())
            {
                red_bg.set_y(red_bg.y() - 1);
            }
            else if(bn::keypad::down_held())
            {
                red_bg.set_y(red_bg.y() + 1);
            }

            info.update();
            bn::core::update();
        }
    }
}

int main()
{
    bn::core::init();

    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    bn::bg_palettes::set_transparent_color(bn::color(16, 16, 16));

    while(true)
    {
        affine_bgs_visibility_scene(text_generator);
        bn::core::update();

        affine_bgs_visibility_actions_scene(text_generator);
        bn::core::update();

        affine_bgs_position_scene(text_generator);
        bn::core::update();
    }
}
