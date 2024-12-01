#ifndef BN_AFFINE_BG_ITEMS_BLUE_SMALL_H
#define BN_AFFINE_BG_ITEMS_BLUE_SMALL_H

#include "bn_affine_bg_item.h"

//{{BLOCK(blue_small_bn_gfx)

//======================================================================
//
//	blue_small_bn_gfx, 128x128@8, 
//	+ palette 32 entries, not compressed
//	+ 95 tiles (t reduced) not compressed
//	+ affine map, not compressed, 16x16 
//	Total size: 64 + 6080 + 256 = 6400
//
//	Time-stamp: 2024-11-12, 17:35:21
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BLUE_SMALL_BN_GFX_H
#define GRIT_BLUE_SMALL_BN_GFX_H

#define blue_small_bn_gfxTilesLen 6080
extern const bn::tile blue_small_bn_gfxTiles[190];

#define blue_small_bn_gfxMapLen 256
extern const bn::affine_bg_map_cell blue_small_bn_gfxMap[256];

#define blue_small_bn_gfxPalLen 64
extern const bn::color blue_small_bn_gfxPal[32];

#endif // GRIT_BLUE_SMALL_BN_GFX_H

//}}BLOCK(blue_small_bn_gfx)

namespace bn::affine_bg_items
{
    constexpr inline affine_bg_item blue_small(
            affine_bg_tiles_item(span<const tile>(blue_small_bn_gfxTiles, 190), compression_type::NONE), 
            bg_palette_item(span<const color>(blue_small_bn_gfxPal, 32), bpp_mode::BPP_8, compression_type::NONE),
            affine_bg_map_item(blue_small_bn_gfxMap[0], size(16, 16), compression_type::NONE, 1, false));
}

#endif

