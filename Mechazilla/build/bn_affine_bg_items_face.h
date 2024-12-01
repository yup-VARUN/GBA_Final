#ifndef BN_AFFINE_BG_ITEMS_FACE_H
#define BN_AFFINE_BG_ITEMS_FACE_H

#include "bn_affine_bg_item.h"

//{{BLOCK(face_bn_gfx)

//======================================================================
//
//	face_bn_gfx, 128x512@8, 
//	+ palette 16 entries, not compressed
//	+ 108 tiles (t reduced) not compressed
//	+ affine map, not compressed, 16x64 
//	Total size: 32 + 6912 + 1024 = 7968
//
//	Time-stamp: 2024-11-12, 17:35:21
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FACE_BN_GFX_H
#define GRIT_FACE_BN_GFX_H

#define face_bn_gfxTilesLen 6912
extern const bn::tile face_bn_gfxTiles[216];

#define face_bn_gfxMapLen 1024
extern const bn::affine_bg_map_cell face_bn_gfxMap[1024];

#define face_bn_gfxPalLen 32
extern const bn::color face_bn_gfxPal[16];

#endif // GRIT_FACE_BN_GFX_H

//}}BLOCK(face_bn_gfx)

namespace bn::affine_bg_items
{
    constexpr inline affine_bg_item face(
            affine_bg_tiles_item(span<const tile>(face_bn_gfxTiles, 216), compression_type::NONE), 
            bg_palette_item(span<const color>(face_bn_gfxPal, 16), bpp_mode::BPP_8, compression_type::NONE),
            affine_bg_map_item(face_bn_gfxMap[0], size(16, 16), compression_type::NONE, 4, false));
}

#endif

