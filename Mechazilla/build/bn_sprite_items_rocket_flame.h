#ifndef BN_SPRITE_ITEMS_ROCKET_FLAME_H
#define BN_SPRITE_ITEMS_ROCKET_FLAME_H

#include "bn_sprite_item.h"

//{{BLOCK(rocket_flame_bn_gfx)

//======================================================================
//
//	rocket_flame_bn_gfx, 64x64@8, 
//	+ palette 32 entries, not compressed
//	+ 64 tiles not compressed
//	Total size: 64 + 4096 = 4160
//
//	Time-stamp: 2024-12-03, 02:42:02
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ROCKET_FLAME_BN_GFX_H
#define GRIT_ROCKET_FLAME_BN_GFX_H

#define rocket_flame_bn_gfxTilesLen 4096
extern const bn::tile rocket_flame_bn_gfxTiles[128];

#define rocket_flame_bn_gfxPalLen 64
extern const bn::color rocket_flame_bn_gfxPal[32];

#endif // GRIT_ROCKET_FLAME_BN_GFX_H

//}}BLOCK(rocket_flame_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item rocket_flame(sprite_shape_size(sprite_shape::WIDE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(rocket_flame_bn_gfxTiles, 128), bpp_mode::BPP_8, compression_type::NONE, 2), 
            sprite_palette_item(span<const color>(rocket_flame_bn_gfxPal, 32), bpp_mode::BPP_8, compression_type::NONE));
}

#endif

