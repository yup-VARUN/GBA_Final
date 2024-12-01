#ifndef BN_AFFINE_BG_ITEMS_BLUE_H
#define BN_AFFINE_BG_ITEMS_BLUE_H

#include "bn_affine_bg_item.h"

//{{BLOCK(blue_bn_gfx)

//======================================================================
//
//	blue_bn_gfx, 256x256@8, 
//	+ palette 32 entries, not compressed
//	+ 99 tiles (t reduced) not compressed
//	+ affine map, not compressed, 32x32 
//	Total size: 64 + 6336 + 1024 = 7424
//
//	Time-stamp: 2024-11-12, 17:35:21
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BLUE_BN_GFX_H
#define GRIT_BLUE_BN_GFX_H

#define blue_bn_gfxTilesLen 6336
extern const bn::tile blue_bn_gfxTiles[198];

#define blue_bn_gfxMapLen 1024
extern const bn::affine_bg_map_cell blue_bn_gfxMap[1024];

#define blue_bn_gfxPalLen 64
extern const bn::color blue_bn_gfxPal[32];

#endif // GRIT_BLUE_BN_GFX_H

//}}BLOCK(blue_bn_gfx)

namespace bn::affine_bg_items
{
    constexpr inline affine_bg_item blue(
            affine_bg_tiles_item(span<const tile>(blue_bn_gfxTiles, 198), compression_type::NONE), 
            bg_palette_item(span<const color>(blue_bn_gfxPal, 32), bpp_mode::BPP_8, compression_type::NONE),
            affine_bg_map_item(blue_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

