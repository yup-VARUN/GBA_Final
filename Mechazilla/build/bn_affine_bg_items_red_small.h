#ifndef BN_AFFINE_BG_ITEMS_RED_SMALL_H
#define BN_AFFINE_BG_ITEMS_RED_SMALL_H

#include "bn_affine_bg_item.h"

//{{BLOCK(red_small_bn_gfx)

//======================================================================
//
//	red_small_bn_gfx, 128x128@8, 
//	+ palette 16 entries, not compressed
//	+ 100 tiles (t reduced) not compressed
//	+ affine map, not compressed, 16x16 
//	Total size: 32 + 6400 + 256 = 6688
//
//	Time-stamp: 2024-11-12, 17:35:21
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_RED_SMALL_BN_GFX_H
#define GRIT_RED_SMALL_BN_GFX_H

#define red_small_bn_gfxTilesLen 6400
extern const bn::tile red_small_bn_gfxTiles[200];

#define red_small_bn_gfxMapLen 256
extern const bn::affine_bg_map_cell red_small_bn_gfxMap[256];

#define red_small_bn_gfxPalLen 32
extern const bn::color red_small_bn_gfxPal[16];

#endif // GRIT_RED_SMALL_BN_GFX_H

//}}BLOCK(red_small_bn_gfx)

namespace bn::affine_bg_items
{
    constexpr inline affine_bg_item red_small(
            affine_bg_tiles_item(span<const tile>(red_small_bn_gfxTiles, 200), compression_type::NONE), 
            bg_palette_item(span<const color>(red_small_bn_gfxPal, 16), bpp_mode::BPP_8, compression_type::NONE),
            affine_bg_map_item(red_small_bn_gfxMap[0], size(16, 16), compression_type::NONE, 1, false));
}

#endif

