#ifndef BN_SPRITE_ITEMS_PIVOT_H
#define BN_SPRITE_ITEMS_PIVOT_H

#include "bn_sprite_item.h"

//{{BLOCK(pivot_bn_gfx)

//======================================================================
//
//	pivot_bn_gfx, 32x32@4, 
//	+ palette 16 entries, not compressed
//	+ 16 tiles not compressed
//	Total size: 32 + 512 = 544
//
//	Time-stamp: 2024-11-12, 17:35:21
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PIVOT_BN_GFX_H
#define GRIT_PIVOT_BN_GFX_H

#define pivot_bn_gfxTilesLen 512
extern const bn::tile pivot_bn_gfxTiles[16];

#define pivot_bn_gfxPalLen 32
extern const bn::color pivot_bn_gfxPal[16];

#endif // GRIT_PIVOT_BN_GFX_H

//}}BLOCK(pivot_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item pivot(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(pivot_bn_gfxTiles, 16), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(pivot_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

