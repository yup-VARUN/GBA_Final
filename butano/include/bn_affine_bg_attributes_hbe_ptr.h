/*
 * Copyright (c) 2020-2024 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BN_AFFINE_BG_ATTRIBUTES_HBE_PTR_H
#define BN_AFFINE_BG_ATTRIBUTES_HBE_PTR_H

/**
 * @file
 * bn::affine_bg_attributes_hbe_ptr header file.
 *
 * @ingroup affine_bg
 * @ingroup hblank_effect
 */

#include "bn_span.h"
#include "bn_affine_bg_ptr.h"
#include "bn_hbe_ptr.h"

namespace bn
{

/**
 * @brief std::shared_ptr like smart pointer that retains shared ownership of a H-Blank effect
 * which changes the attributes to commit to the GBA register of an affine background in each screen horizontal line.
 *
 * @ingroup affine_bg
 * @ingroup hblank_effect
 */
class affine_bg_attributes_hbe_ptr : public hbe_ptr
{

public:
    /**
     * @brief Creates an affine_bg_attributes_hbe_ptr which changes the attributes to commit
     * to the GBA register of an affine background in each screen horizontal line.
     * @param bg Affine background to be modified.
     * @param attributes_ref Reference to an array of 160 affine_bg_attributes objects
     * with the attributes to commit to the GBA register of the given affine background
     * in each screen horizontal line.
     *
     * The attributes are not copied but referenced, so they should outlive
     * the affine_bg_attributes_hbe_ptr to avoid dangling references.
     *
     * @return The requested affine_bg_attributes_hbe_ptr.
     */
    [[nodiscard]] static affine_bg_attributes_hbe_ptr create(
            affine_bg_ptr bg, const span<const affine_bg_attributes>& attributes_ref);

    /**
     * @brief Creates an affine_bg_attributes_hbe_ptr which changes the attributes to commit
     * to the GBA register of an affine background in each screen horizontal line.
     * @param bg Affine background to be modified.
     * @param attributes_ref Reference to an array of 160 affine_bg_attributes objects
     * with the attributes to commit to the GBA register of the given affine background
     * in each screen horizontal line.
     *
     * The attributes are not copied but referenced, so they should outlive
     * the affine_bg_attributes_hbe_ptr to avoid dangling references.
     *
     * @return The requested affine_bg_attributes_hbe_ptr if it could be allocated; bn::nullopt otherwise.
     */
    [[nodiscard]] static optional<affine_bg_attributes_hbe_ptr> create_optional(
            affine_bg_ptr bg, const span<const affine_bg_attributes>& attributes_ref);

    /**
     * @brief Returns the affine background modified by this H-Blank effect.
     */
    [[nodiscard]] const affine_bg_ptr& bg() const
    {
        return _bg;
    }

    /**
     * @brief Returns the referenced array of 160 affine_bg_attributes objects
     * with the attributes to commit to the GBA register of the managed affine background
     * in each screen horizontal line.
     *
     * The attributes are not copied but referenced, so they should outlive
     * the affine_bg_attributes_hbe_ptr to avoid dangling references.
     */
    [[nodiscard]] span<const affine_bg_attributes> attributes_ref() const;

    /**
     * @brief Sets the reference to an array of 160 affine_bg_attributes objects
     * with the attributes to commit to the GBA register of the managed affine background
     * in each screen horizontal line.
     *
     * The attributes are not copied but referenced, so they should outlive
     * the affine_bg_attributes_hbe_ptr to avoid dangling references.
     */
    void set_attributes_ref(const span<const affine_bg_attributes>& attributes_ref);

    /**
     * @brief Rereads the content of the referenced attributes to the GBA register of the managed affine background
     * in each screen horizontal line.
     *
     * The attributes are not copied but referenced, so they should outlive
     * the affine_bg_attributes_hbe_ptr to avoid dangling references.
     */
    void reload_attributes_ref();

    /**
     * @brief Exchanges the contents of this affine_bg_attributes_hbe_ptr with those of the other one.
     * @param other affine_bg_attributes_hbe_ptr to exchange the contents with.
     */
    void swap(affine_bg_attributes_hbe_ptr& other);

    /**
     * @brief Exchanges the contents of an affine_bg_attributes_hbe_ptr with those of another one.
     * @param a First affine_bg_attributes_hbe_ptr to exchange the contents with.
     * @param b Second affine_bg_attributes_hbe_ptr to exchange the contents with.
     */
    friend void swap(affine_bg_attributes_hbe_ptr& a, affine_bg_attributes_hbe_ptr& b)
    {
        a.swap(b);
    }

private:
    affine_bg_ptr _bg;

    affine_bg_attributes_hbe_ptr(int id, affine_bg_ptr&& bg);
};

}

#endif
