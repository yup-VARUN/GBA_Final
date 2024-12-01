#ifndef BN_SPRITE_ITEMS_TURTLE_H
#define BN_SPRITE_ITEMS_TURTLE_H

#include "bn_sprite_item.h"

//{{BLOCK(turtle_bn_gfx)

//======================================================================
//
//	turtle_bn_gfx, 64x32@4, 
//	+ palette 16 entries, not compressed
//	+ 32 tiles not compressed
//	Total size: 32 + 1024 = 1056
//
//	Time-stamp: 2024-11-12, 17:35:21
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TURTLE_BN_GFX_H
#define GRIT_TURTLE_BN_GFX_H

#define turtle_bn_gfxTilesLen 1024
extern const bn::tile turtle_bn_gfxTiles[32];

#define turtle_bn_gfxPalLen 32
extern const bn::color turtle_bn_gfxPal[16];

#endif // GRIT_TURTLE_BN_GFX_H

//}}BLOCK(turtle_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item turtle(sprite_shape_size(sprite_shape::WIDE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(turtle_bn_gfxTiles, 32), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(turtle_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

