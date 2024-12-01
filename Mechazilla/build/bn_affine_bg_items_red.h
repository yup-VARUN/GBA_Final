#ifndef BN_AFFINE_BG_ITEMS_RED_H
#define BN_AFFINE_BG_ITEMS_RED_H

#include "bn_affine_bg_item.h"

//{{BLOCK(red_bn_gfx)

//======================================================================
//
//	red_bn_gfx, 256x256@8, 
//	+ palette 16 entries, not compressed
//	+ 101 tiles (t reduced) not compressed
//	+ affine map, not compressed, 32x32 
//	Total size: 32 + 6464 + 1024 = 7520
//
//	Time-stamp: 2024-11-12, 17:35:21
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_RED_BN_GFX_H
#define GRIT_RED_BN_GFX_H

#define red_bn_gfxTilesLen 6464
extern const bn::tile red_bn_gfxTiles[202];

#define red_bn_gfxMapLen 1024
extern const bn::affine_bg_map_cell red_bn_gfxMap[1024];

#define red_bn_gfxPalLen 32
extern const bn::color red_bn_gfxPal[16];

#endif // GRIT_RED_BN_GFX_H

//}}BLOCK(red_bn_gfx)

namespace bn::affine_bg_items
{
    constexpr inline affine_bg_item red(
            affine_bg_tiles_item(span<const tile>(red_bn_gfxTiles, 202), compression_type::NONE), 
            bg_palette_item(span<const color>(red_bn_gfxPal, 16), bpp_mode::BPP_8, compression_type::NONE),
            affine_bg_map_item(red_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

