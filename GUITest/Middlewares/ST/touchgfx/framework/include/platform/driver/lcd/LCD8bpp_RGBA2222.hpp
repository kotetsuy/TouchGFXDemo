/**
  ******************************************************************************
  * This file is part of the TouchGFX 4.13.0 distribution.
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#ifndef LCD8BPP_RGBA2222_HPP
#define LCD8BPP_RGBA2222_HPP

#include <stdarg.h>
#include <touchgfx/Bitmap.hpp>
#include <touchgfx/Font.hpp>
#include <touchgfx/TextProvider.hpp>
#include <touchgfx/TextureMapTypes.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/hal/Types.hpp>
#include <touchgfx/lcd/LCD.hpp>

namespace touchgfx
{
#undef LCD

/**
 * @class LCD8bpp_RGBA2222 LCD8bpp_RGBA2222.hpp platform/driver/lcd/LCD8bpp_RGBA2222.hpp
 *
 * @brief This class contains the various low-level drawing routines for drawing bitmaps.
 *
 *        This class contains the various low-level drawing routines for drawing bitmaps, texts
 *        and rectangles on 16 bits per pixel displays.
 *
 * @note All coordinates are expected to be in absolute coordinates!
 *
 * @see LCD
 */
class LCD8bpp_RGBA2222 : public LCD
{
public:
    LCD8bpp_RGBA2222();

    virtual ~LCD8bpp_RGBA2222()
    {
    }

    /**
     * @fn virtual void LCD8bpp_RGBA2222::init();
     *
     * @brief Performs initialization.
     *
     *        Performs initialization.
     */
    virtual void init();

    /**
     * @fn virtual void LCD8bpp_RGBA2222::drawPartialBitmap(const Bitmap& bitmap, int16_t x, int16_t y, const Rect& rect, uint8_t alpha = 255, bool useOptimized = true);
     *
     * @brief Draws a portion of a bitmap.
     *
     * @param bitmap       The bitmap to draw.
     * @param x            The absolute x coordinate to place pixel (0, 0) on the screen.
     * @param y            The absolute y coordinate to place pixel (0, 0) on the screen.
     * @param rect         A rectangle describing what region of the bitmap is to be drawn.
     * @param alpha        Optional alpha value. Default is 255 (solid).
     * @param useOptimized if false, do not attempt to substitute (parts of) this bitmap with
     *                     faster fillrects.
     */
    virtual void drawPartialBitmap(const Bitmap& bitmap, int16_t x, int16_t y, const Rect& rect, uint8_t alpha = 255, bool useOptimized = true);

    /**
     * @fn virtual void LCD8bpp_RGBA2222::blitCopy(const uint16_t* sourceData, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels);
     *
     * @brief Blits a 2D source-array to the framebuffer.
     *
     *        Blits a 2D source-array to the framebuffer perfoming alpha-blending (and
     *        tranparency keying) as specified Performs a software blend if HAL does not
     *        support BLIT_COPY_WITH_ALPHA and alpha != 255.
     *
     * @param sourceData           The source-array pointer (points to the beginning of the
     *                             data).  The sourceData must be stored as 16-bits RGB565
     *                             values.
     * @param source               The location and dimension of the source.
     * @param blitRect             A rectangle describing what region is to be drawn.
     * @param alpha                The alpha value to use for blending (255 = solid, no blending)
     * @param hasTransparentPixels If true, this data copy contains transparent pixels and
     *                             require hardware support for that to be enabled.
     */
    virtual void blitCopy(const uint16_t* sourceData, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels);

    /**
     * @fn virtual void LCD8bpp_RGBA2222::blitCopy(const uint8_t* sourceData, Bitmap::BitmapFormat sourceFormat, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels);
     *
     * @brief Blits a 2D source-array to the framebuffer while converting the format.
     *
     *        Blits a 2D source-array to the framebuffer perfoming alpha-blending (and
     *        tranparency keying) as specified. Performs a software blend if HAL does not
     *        support BLIT_COPY_WITH_ALPHA and alpha != 255. LCD16 supports source data
     *        formats: RGB565 and ARGB8888.
     *
     * @param sourceData           The source-array pointer (points to the beginning of the
     *                             data). The sourceData must be stored in a format suitable for
     *                             the selected display.
     * @param sourceFormat         The bitmap format used in the source data.
     * @param source               The location and dimension of the source.
     * @param blitRect             A rectangle describing what region is to be drawn.
     * @param alpha                The alpha value to use for blending (255 = solid, no blending)
     * @param hasTransparentPixels If true, this data copy contains transparent pixels and
     *                             require hardware support for that to be enabled.
     */
    virtual void blitCopy(const uint8_t* sourceData, Bitmap::BitmapFormat sourceFormat, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels);

    /**
     * @fn virtual uint16_t* LCD8bpp_RGBA2222::copyFrameBufferRegionToMemory(const Rect& visRegion, const Rect& absRegion, const BitmapId bitmapId);
     *
     * @brief Copies part of the frame buffer region to memory.
     *
     *        Copies part of the framebuffer region to memory. The memory is given as BitmapId,
     *        which can be BITMAP_ANIMATION_STORAGE. The two regions given are the visible region
     *        and the absolute region on screen. This is used to copy only a part of an area. This
     *        might be the case if a SnapshotWidget is placed inside a Container where parts of the
     *        SnapshowWidget is outside the area defined by the Container. The visible region must
     *        be completely inside the absolute region.
     *
     * @note There is only one instance of animation storage. The content of the animation storage
     *       outside the given region is undefined.
     *
     * @param visRegion The visible region.
     * @param absRegion The absolute region.
     * @param bitmapId  Identifier for the bitmap.
     *
     * @returns Null if it fails, else a pointer to the data in the given bitmap.
     *
     * @see blitCopy
     */
    virtual uint16_t* copyFrameBufferRegionToMemory(const Rect& visRegion, const Rect& absRegion, const BitmapId bitmapId);

    /**
     * @fn virtual void LCD8bpp_RGBA2222::fillRect(const Rect& rect, colortype color, uint8_t alpha = 255);
     *
     * @brief Draws a filled rectangle in the specified color.
     *
     *        Draws a filled rectangle in the specified color.
     *
     * @param rect  The rectangle to draw in absolute coordinates.
     * @param color The rectangle color.
     * @param alpha The rectangle opacity (255=solid)
     */
    virtual void fillRect(const Rect& rect, colortype color, uint8_t alpha = 255);

    /**
     * @fn virtual uint8_t LCD8bpp_RGBA2222::bitDepth() const
     *
     * @brief Number of bits per pixel used by the display.
     *
     *        Number of bits per pixel used by the display.
     *
     * @return 8.
     */
    virtual uint8_t bitDepth() const
    {
        return 8;
    }

    /**
     * @fn virtual Bitmap::BitmapFormat LCD8bpp_RGBA2222::framebufferFormat() const
     *
     * @brief Framebuffer format used by the display
     *
     *        Framebuffer format used by the display
     *
     * @return Bitmap::RGBA2222.
     */
    virtual Bitmap::BitmapFormat framebufferFormat() const
    {
        return Bitmap::RGBA2222;
    }

    /**
     * @fn virtual uint16_t LCD8bpp_RGBA2222::framebufferStride() const
     *
     * @brief Framebuffer stride in bytes
     *
     *        Framebuffer stride in bytes. The distance (in bytes) from the start of one
     *        framebuffer row, to the next.
     *
     * @return The number of bytes in one framebuffer row.
     */
    virtual uint16_t framebufferStride() const
    {
        return getFramebufferStride();
    }

    /**
     * @fn FORCE_INLINE_FUNCTION static uint16_t LCD8bpp_RGBA2222::getFramebufferStride()
     *
     * @brief Framebuffer stride in bytes
     *
     *        Framebuffer stride in bytes. The distance (in bytes) from the start of one
     *        framebuffer row, to the next.
     *
     * @return The number of bytes in one framebuffer row.
     */
    FORCE_INLINE_FUNCTION static uint16_t getFramebufferStride()
    {
        assert(HAL::FRAME_BUFFER_WIDTH > 0 && "HAL has not been initialized yet");
        return HAL::FRAME_BUFFER_WIDTH;
    }

    /**
     * @fn virtual colortype LCD8bpp_RGBA2222::getColorFrom24BitRGB(uint8_t red, uint8_t green, uint8_t blue) const
     *
     * @brief Generates a color representation to be used on the LCD, based on 24 bit RGB values.
     *
     *        Generates a color representation to be used on the LCD, based on 24 bit RGB values.
     *
     * @param red   Value of the red part (0-255).
     * @param green Value of the green part (0-255).
     * @param blue  Value of the blue part (0-255).
     *
     * @return The color representation depending on LCD color format.
     */
    virtual colortype getColorFrom24BitRGB(uint8_t red, uint8_t green, uint8_t blue) const
    {
        return getColorFromRGB(red, green, blue);
    }

    /**
     * @fn FORCE_INLINE_FUNCTION static colortype LCD8bpp_RGBA2222::getColorFromRGB(uint8_t red, uint8_t green, uint8_t blue)
     *
     * @brief Gets color from RGB
     *
     * @param red   The red.
     * @param green The green.
     * @param blue  The blue.
     *
     * @return The color from RGB.
     */
    FORCE_INLINE_FUNCTION static colortype getColorFromRGB(uint8_t red, uint8_t green, uint8_t blue)
    {
        return (red & 0xC0) | ((green & 0xC0) >> 2) | ((blue & 0xC0) >> 4);
    }

    /**
     * @fn virtual uint8_t LCD8bpp_RGBA2222::getRedColor(colortype color) const
     *
     * @brief Gets the red color part of a color.
     *
     *        Gets the red color part of a color. As this function must work for all color depths,
     *        it can be somewhat slow if used in speed critical sections. Consider finding the
     *        color in another way, if possible.
     *
     * @param color The color value.
     *
     * @return The red part of the color.
     */
    virtual uint8_t getRedColor(colortype color) const
    {
        return getRedFromColor(color);
    }

    /**
     * @fn FORCE_INLINE_FUNCTION static uint8_t LCD8bpp_RGBA2222::getRedFromColor(colortype color)
     *
     * @brief Gets red from color
     *
     * @param color The color.
     *
     * @return The red from color.
     */
    FORCE_INLINE_FUNCTION static uint8_t getRedFromColor(colortype color)
    {
        return ((color & 0xC0) >> 6) * 0x55;
    }

    /**
     * @fn virtual uint8_t LCD8bpp_RGBA2222::getGreenColor(colortype color) const
     *
     * @brief Gets the green color part of a color.
     *
     *        Gets the green color part of a color. As this function must work for all color depths,
     *        it can be somewhat slow if used in speed critical sections. Consider finding the
     *        color in another way, if possible.
     *
     * @param color The 16 bit color value.
     *
     * @return The green part of the color.
     */
    virtual uint8_t getGreenColor(colortype color) const
    {
        return getGreenFromColor(color);
    }

    /**
     * @fn FORCE_INLINE_FUNCTION static LCD8bpp_RGBA2222::getGreenFromColor(colortype color)
     *
     * @brief Gets green from color
     *
     * @param color The color.
     *
     * @return The green from color.
     */
    FORCE_INLINE_FUNCTION static uint8_t getGreenFromColor(colortype color)
    {
        return ((color & 0x30) >> 4) * 0x55;
    }

    /**
     * @fn virtual uint8_t LCD8bpp_RGBA2222::getBlueColor(colortype color) const
     *
     * @brief Gets the blue color part of a color.
     *
     *        Gets the blue color part of a color. As this function must work for all color depths,
     *        it can be somewhat slow if used in speed critical sections. Consider finding the
     *        color in another way, if possible.
     *
     * @param color The 16 bit color value.
     *
     * @return The blue part of the color.
     */
    virtual uint8_t getBlueColor(colortype color) const
    {
        return getBlueFromColor(color);
    }

    /**
     * @fn FORCE_INLINE_FUNCTION static uint8_t LCD8bpp_RGBA2222::getBlueFromColor(colortype color)
     *
     * @brief Gets blue from color
     *
     * @param color The color.
     *
     * @return The blue from color.
     */
    FORCE_INLINE_FUNCTION static uint8_t getBlueFromColor(colortype color)
    {
        return ((color & 0x0C) >> 2) * 0x55;
    }

    /**
     * @fn void LCD8bpp_RGBA2222::enableTextureMapperAll();
     *
     * @brief Enables the texture mappers for all image formats.
     *
     *        Enables the texture mappers for all image formats. This allows drawing any image
     *        using Bilinear Interpolation and Nearest Neighbor algorithms, but might use a
     *        lot of memory for the drawing algorithms.
     */
    void enableTextureMapperAll();

    /**
     * @fn void LCD8bpp_RGBA2222::enableTextureMapperRGBA2222();
     *
     * @brief Enables the texture mappers for RGBA2222 image format.
     *
     *        Enables the texture mappers for RGBA2222 image format. This allows drawing
     *        RGBA2222 images using Bilinear Interpolation and Nearest Neighbor algorithms.
     *
     * @see enableTextureMapperRGBA2222_BilinearInterpolation
     * @see enableTextureMapperRGBA2222_NearestNeighbor
     */
    void enableTextureMapperRGBA2222();

    /**
     * @fn void LCD8bpp_RGBA2222::enableTextureMapperRGBA2222_BilinearInterpolation();
     *
     * @brief Enables the texture mappers for RGBA2222 image format for Bilinear Interpolation algorithm.
     *
     *        Enables the texture mappers for RGBA2222 image format. This allows drawing
     *        RGBA2222 images using Bilinear Interpolation algorithm.
     *
     * @see enableTextureMapperRGBA2222
     * @see enableTextureMapperRGBA2222_NearestNeighbor
     */
    void enableTextureMapperRGBA2222_BilinearInterpolation();

    /**
     * @fn void LCD8bpp_RGBA2222::enableTextureMapperRGBA2222_NearestNeighbor();
     *
     * @brief Enables the texture mappers for RGBA2222 image format for Nearest Neighbor algorithm.
     *
     *        Enables the texture mappers for RGBA2222 image format. This allows drawing
     *        RGBA2222 images using Nearest Neighbor algorithm.
     *
     * @see enableTextureMapperRGBA2222
     * @see enableTextureMapperRGBA2222_BilinearInterpolation
     */
    void enableTextureMapperRGBA2222_NearestNeighbor();

    /**
     * @fn void LCD8bpp_RGBA2222::enableTextureMapperARGB8888();
     *
     * @brief Enables the texture mappers for ARGB8888 image format.
     *
     *        Enables the texture mappers for ARGB8888 image format. This allows drawing
     *        ARGB8888 images using Bilinear Interpolation and Nearest Neighbor algorithms.
     *
     * @see enableTextureMapperARGB8888_BilinearInterpolation
     * @see enableTextureMapperARGB8888_NearestNeighbor
     */
    void enableTextureMapperARGB8888();

    /**
     * @fn void LCD8bpp_RGBA2222::enableTextureMapperARGB8888_BilinearInterpolation();
     *
     * @brief Enables the texture mappers for ARGB8888 image format for Bilinear Interpolation algorithm.
     *
     *        Enables the texture mappers for ARGB8888 image format. This allows drawing
     *        ARGB8888 images using Bilinear Interpolation algorithm.
     *
     * @see enableTextureMapperARGB8888
     * @see enableTextureMapperARGB8888_NearestNeighbor
     */
    void enableTextureMapperARGB8888_BilinearInterpolation();

    /**
     * @fn void LCD8bpp_RGBA2222::enableTextureMapperARGB8888_NearestNeighbor();
     *
     * @brief Enables the texture mappers for ARGB8888 image format for Nearest Neighbor algorithm.
     *
     *        Enables the texture mappers for ARGB8888 image format. This allows drawing
     *        ARGB8888 images using Nearest Neighbor algorithm.
     *
     * @see enableTextureMapperARGB8888
     * @see enableTextureMapperARGB8888_BilinearInterpolation
     */
    void enableTextureMapperARGB8888_NearestNeighbor();

    /**
     * @fn void LCD8bpp_RGBA2222::enableTextureMapperA4();
     *
     * @brief Enables the texture mappers for A4 image format.
     *
     *        Enables the texture mappers for A4 image format. This allows drawing A4 images
     *        using Bilinear Interpolation and Nearest Neighbor algorithms.
     *
     * @see enableTextureMapperA4_BilinearInterpolation
     * @see enableTextureMapperA4_NearestNeighbor
     */
    void enableTextureMapperA4();

    /**
     * @fn void LCD8bpp_RGBA2222::enableTextureMapperA4_BilinearInterpolation();
     *
     * @brief Enables the texture mappers for A4 image format for Bilinear Interpolation algorithm.
     *
     *        Enables the texture mappers for A4 image format. This allows drawing A4 images
     *        using Bilinear Interpolation algorithm.
     *
     * @see enableTextureMapperA4
     * @see enableTextureMapperA4_NearestNeighbor
     */
    void enableTextureMapperA4_BilinearInterpolation();

    /**
     * @fn void LCD8bpp_RGBA2222::enableTextureMapperA4_NearestNeighbor();
     *
     * @brief Enables the texture mappers for A4 image format for Nearest Neighbor algorithm.
     *
     *        Enables the texture mappers for A4 image format. This allows drawing A4 images
     *        using Nearest Neighbor algorithm.
     *
     * @see enableTextureMapperA4
     * @see enableTextureMapperA4_BilinearInterpolation
     */
    void enableTextureMapperA4_NearestNeighbor();

protected:
    virtual DrawTextureMapScanLineBase* getTextureMapperDrawScanLine(const TextureSurface& texture, RenderingVariant renderVariant, uint8_t alpha);

    /**
     * @fn static int LCD8bpp_RGBA2222::nextPixel(bool rotatedDisplay, TextRotation textRotation);
     *
     * @brief Find out how much to advance in the display buffer to get to the next pixel.
     *
     *        Find out how much to advance in the display buffer to get to the next pixel.
     *
     * @param rotatedDisplay Is the display running in portrait mode?
     * @param textRotation   Rotation to perform.
     *
     * @return How much to advance to get to the next pixel.
     */
    static int nextPixel(bool rotatedDisplay, TextRotation textRotation);

    /**
     * @fn static int LCD8bpp_RGBA2222::nextLine(bool rotatedDisplay, TextRotation textRotation);
     *
     * @brief Find out how much to advance in the display buffer to get to the next line.
     *
     *        Find out how much to advance in the display buffer to get to the next line.
     *
     * @param rotatedDisplay Is the display running in portrait mode?
     * @param textRotation   Rotation to perform.
     *
     * @return How much to advance to get to the next line.
     */
    static int nextLine(bool rotatedDisplay, TextRotation textRotation);

    /**
     * @fn virtual void LCD8bpp_RGBA2222::drawGlyph(uint16_t* wbuf8, Rect widgetArea, int16_t x, int16_t y, uint16_t offsetX, uint16_t offsetY, const Rect& invalidatedArea, const GlyphNode* glyph, const uint8_t* glyphData, uint8_t dataFormatA4, colortype color, uint8_t bitsPerPixel, uint8_t alpha, TextRotation rotation);
     *
     * @brief Private version of draw-glyph with explicit destination buffer pointer argument.
     *
     *        Private version of draw-glyph with explicit destination buffer pointer argument.
     *        For all parameters (except the buffer pointer) see the public function drawString().
     *
     * @param [in] wbuf8      The destination (frame) buffer to draw to.
     * @param widgetArea      The canvas to draw the glyph inside.
     * @param x               Horizontal offset to start drawing the glyph.
     * @param y               Vertical offset to start drawing the glyph.
     * @param offsetX         Horizontal offset in the glyph to start drawing from.
     * @param offsetY         Vertical offset in the glyph to start drawing from.
     * @param invalidatedArea The area to draw within.
     * @param glyph           Specifications of the glyph to draw.
     * @param glyphData       Data containing the actual glyph (dense format)
     * @param dataFormatA4    The glyph is saved using ST A4 format.
     * @param color           The color of the glyph.
     * @param bitsPerPixel    Bit depth of the glyph.
     * @param alpha           The transparency of the glyph.
     * @param rotation        Rotation to do before drawing the glyph.
     */
    virtual void drawGlyph(uint16_t* wbuf8, Rect widgetArea, int16_t x, int16_t y, uint16_t offsetX, uint16_t offsetY, const Rect& invalidatedArea, const GlyphNode* glyph, const uint8_t* glyphData, uint8_t dataFormatA4, colortype color, uint8_t bitsPerPixel, uint8_t alpha, TextRotation rotation);

    /**
     * @fn static void LCD8bpp_RGBA2222::blitCopyARGB8888(const uint32_t* sourceData, const Rect& source, const Rect& blitRect, uint8_t alpha);
     *
     * @brief Blit a 2D source-array to the framebuffer.
     *
     *        Blit a 2D source-array to the framebuffer performing alpha-blending per pixel as
     *        specified if ARGB8888 is not supported by the DMA a software blend is performed.
     *
     * @param sourceData The source-array pointer (points to the beginning of the data). The
     *                   sourceData must be stored as 32- bits ARGB8888 values.
     * @param source     The location and dimension of the source.
     * @param blitRect   A rectangle describing what region is to be drawn.
     * @param alpha      The alpha value to use for blending applied to the whole image (255 =
     *                   solid, no blending)
     */
    static void blitCopyARGB8888(const uint32_t* sourceData, const Rect& source, const Rect& blitRect, uint8_t alpha);

    /**
     * @fn static void LCD8bpp_RGBA2222::blitCopyAlphaPerPixel(const uint16_t* sourceData16, const Rect& source, const Rect& blitRect, uint8_t alpha);
     *
     * @brief Blit a 2D source-array to the framebuffer.
     *
     *        Blit a 2D source-array to the framebuffer performing alpha-blending per pixel as
     *        specified Performs always a software blend.
     *
     * @param sourceData16 The source-array pointer (points to the beginning of the data). The
     *                     sourceData must be stored as 8-bit RGBA2222 values.
     * @param source       The location and dimension of the source.
     * @param blitRect     A rectangle describing what region is to be drawn.
     * @param alpha        The alpha value to use for blending applied to the whole image (255 =
     *                     solid, no blending)
     */
    static void blitCopyAlphaPerPixel(const uint16_t* sourceData16, const Rect& source, const Rect& blitRect, uint8_t alpha);

private:
    DrawTextureMapScanLineBase* textureMapper_RGBA2222_NonOpaque_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_RGBA2222_Opaque_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_RGBA2222_NonOpaque_BilinearInterpolation_GA;
    DrawTextureMapScanLineBase* textureMapper_RGBA2222_Opaque_BilinearInterpolation_GA;
    DrawTextureMapScanLineBase* textureMapper_ARGB8888_NonOpaque_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_ARGB8888_Opaque_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_ARGB8888_NonOpaque_BilinearInterpolation_GA;
    DrawTextureMapScanLineBase* textureMapper_ARGB8888_Opaque_BilinearInterpolation_GA;
    DrawTextureMapScanLineBase* textureMapper_A4_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_A4_BilinearInterpolation_GA;

    FORCE_INLINE_FUNCTION static uint8_t bilinearInterpolate8(uint8_t c00, uint8_t c10, uint8_t x)
    {
        assert(x < 16);
        const uint16_t xy10 = 16 * x;
        const uint16_t xy00 = 256 - xy10;

        return (c00 * xy00 + c10 * xy10) >> 8;
    }

    FORCE_INLINE_FUNCTION static uint8_t bilinearInterpolate8(uint8_t c00, uint8_t c10, uint8_t c01, uint8_t c11, uint8_t x, uint8_t y)
    {
        assert(x < 16 && y < 16);
        const uint16_t xy11 = x * y;
        const uint16_t xy10 = 16 * x - xy11;
        const uint16_t xy01 = 16 * y - xy11;
        const uint16_t xy00 = 256 - (xy11 + xy10 + xy01);

        return (c00 * xy00 + c10 * xy10 + c01 * xy01 + c11 * xy11) >> 8;
    }

    FORCE_INLINE_FUNCTION uint32_t convertRGBA2222toARGB8888(colortype col) const
    {
        return (((col & 0x03) << 24) | ((col & 0xC0) << 10) | ((col & 0x30) << 4) | ((col & 0x0C) >> 2)) * 0x55;
    }

    FORCE_INLINE_FUNCTION static uint32_t convertRGBA2222toRGB888(uint8_t val)
    {
        return (((val & 0xC0) << 10) | ((val & 0x30) << 4) | ((val & 0x0C) >> 2)) * 0x55;
    }

    FORCE_INLINE_FUNCTION static uint8_t convertRGB888toRGBX2222(uint32_t val)
    {
        val &= 0xC0C0C0;
        return (val >> 4) | (val >> 10) | (val >> 16);
    }

    FORCE_INLINE_FUNCTION static uint32_t bilinearInterpolate888(uint32_t c00, uint32_t c10, uint32_t c01, uint32_t c11, uint8_t x, uint8_t y)
    {
        assert(x < 16 && y < 16);
        const uint16_t xy11 = x * y;
        const uint16_t xy10 = 16 * x - xy11;
        const uint16_t xy01 = 16 * y - xy11;
        const uint16_t xy00 = 256 - (xy11 + xy10 + xy01);

        return ((((c00 & 0xFF00FF) * xy00 + (c10 & 0xFF00FF) * xy10 + (c01 & 0xFF00FF) * xy01 + (c11 & 0xFF00FF) * xy11) >> 8) & 0xFF00FF)
               | ((((c00 & 0x00FF00) * xy00 + (c10 & 0x00FF00) * xy10 + (c01 & 0x00FF00) * xy01 + (c11 & 0x00FF00) * xy11) >> 8) & 0x00FF00);
    }

    FORCE_INLINE_FUNCTION static uint32_t div255_888(uint32_t val, uint8_t factor)
    {
        return div255rb((val & 0xFF00FF) * factor) | div255g((val & 0x00FF00) * factor);
    }

    FORCE_INLINE_FUNCTION static uint32_t div255_888_FFcheck(uint32_t val, uint8_t factor)
    {
        return factor < 0xFF ? div255_888(val, factor) : val;
    }

    FORCE_INLINE_FUNCTION static uint8_t alphaBlend(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t alpha, const uint8_t fbr, const uint8_t fbg, const uint8_t fbb, const uint8_t ialpha)
    {
        return static_cast<uint8_t>(getColorFromRGB(div255(r * alpha + fbr * ialpha), div255(g * alpha + fbg * ialpha), div255(b * alpha + fbb * ialpha)));
    }

    class DrawTextureMapScanLineBase8 : public DrawTextureMapScanLineBase
    {
    protected:
        FORCE_INLINE_FUNCTION bool overrunCheckNearestNeighbor(uint8_t*& destBits, int& pixelsToDraw, fixed16_16& U, fixed16_16& V, fixed16_16 deltaU, fixed16_16 deltaV, const int16_t maxWidth, const int16_t maxHeight);
        FORCE_INLINE_FUNCTION bool overrunCheckBilinearInterpolation(uint8_t*& destBits, int& pixelsToDraw, fixed16_16& U, fixed16_16& V, fixed16_16 deltaU, fixed16_16 deltaV, const int16_t maxWidth, const int16_t maxHeight);
    };

    class TextureMapper_RGBA2222_NonOpaque_NearestNeighbor_GA : public DrawTextureMapScanLineBase8
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint8_t* const destBits, const uint8_t* const textureBits, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t alpha);
    };

    class TextureMapper_RGBA2222_Opaque_NearestNeighbor_GA : public DrawTextureMapScanLineBase8
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint8_t* const destBits, const uint8_t* const textureBits, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t alpha);
    };

    class TextureMapper_RGBA2222_NonOpaque_BilinearInterpolation_GA : public DrawTextureMapScanLineBase8
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint8_t* const destBits, const uint8_t* const textureBits, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint8_t* const destBits, const uint8_t* const textureBits, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };

    class TextureMapper_RGBA2222_Opaque_BilinearInterpolation_GA : public DrawTextureMapScanLineBase8
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint8_t* const destBits, const uint8_t* const textureBits, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint8_t* const destBits, const uint8_t* const textureBits, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };

    class TextureMapper_ARGB8888_NonOpaque_NearestNeighbor_GA : public DrawTextureMapScanLineBase8
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint8_t* const destBits, const uint32_t* const textureBits32, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t alpha);
    };

    class TextureMapper_ARGB8888_NonOpaque_BilinearInterpolation_GA : public DrawTextureMapScanLineBase8
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint8_t* const destBits, const uint32_t* const textureBits32, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint8_t* const destBits, const uint32_t* const textureBits32, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };

    class TextureMapper_A4_NearestNeighbor_GA : public DrawTextureMapScanLineBase8
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint8_t* const destBits, const uint8_t a4, const uint8_t alpha);
    };

    class TextureMapper_A4_BilinearInterpolation_GA : public DrawTextureMapScanLineBase8
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint8_t* const destBits, const uint16_t* const textureBits, const int16_t bitmapStride, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint8_t* const destBits, const uint16_t* const textureBits, const int16_t bitmapStride, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };
};

/**
 * @class LCD8RGBA2222DebugPrinter LCD8bpp_RGBA2222.hpp platform/driver/lcd/LCD8bpp_RGBA2222.hpp
 *
 * @brief The class LCD8RGBA2222DebugPrinter implements the DebugPrinter interface for printing debug messages on top of 8bit framebuffer.
 *
 *        The class LCD8RGBA2222DebugPrinter implements the DebugPrinter interface for printing debug messages on top of 8bit framebuffer.
 *
 * @see DebugPrinter
 */
class LCD8RGBA2222DebugPrinter : public DebugPrinter
{
public:
    virtual void draw(const Rect& rect) const;
};

} // namespace touchgfx
#endif // LCD8BPP_RGBA2222_HPP
