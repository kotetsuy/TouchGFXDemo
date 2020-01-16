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

#ifndef LCD32BPP_HPP
#define LCD32BPP_HPP

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
 * @class LCD32bpp LCD32bpp.hpp platform/driver/lcd/LCD32bpp.hpp
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
class LCD32bpp : public LCD
{
public:
    LCD32bpp();

    virtual ~LCD32bpp()
    {
    }

    /**
     * @fn virtual void LCD32bpp::init();
     *
     * @brief Performs initialization.
     *
     *        Performs initialization.
     */
    virtual void init();

    /**
     * @fn virtual void LCD32bpp::drawPartialBitmap(const Bitmap& bitmap, int16_t x, int16_t y, const Rect& rect, uint8_t alpha = 255, bool useOptimized = true);
     *
     * @brief Draws a portion of a bitmap.
     *
     *        Draws a portion of a bitmap.
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
     * @fn virtual void LCD32bpp::blitCopy(const uint16_t* sourceData, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels);
     *
     * @brief Blits a 2D source-array to the framebuffer.
     *
     *        Blits a 2D source-array to the framebuffer perfoming alpha-blending (and
     *        tranparency keying) as specified Performs a software blend if HAL does not
     *        support BLIT_COPY_WITH_ALPHA and alpha != 255.
     *
     * @param sourceData           The source-array pointer (points to the beginning of the
     *                             data).  The sourceData must be stored as 32-bits ARGB8888
     *                             values.
     * @param source               The location and dimension of the source.
     * @param blitRect             A rectangle describing what region is to be drawn.
     * @param alpha                The alpha value to use for blending (255 = solid, no blending)
     * @param hasTransparentPixels If true, this data copy contains transparent pixels and
     *                             require hardware support for that to be enabled.
     */
    virtual void blitCopy(const uint16_t* sourceData, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels);

    /**
     * @fn virtual void LCD32bpp::blitCopy(const uint8_t* sourceData, Bitmap::BitmapFormat sourceFormat, const Rect& source, const Rect& blitRect, uint8_t alpha, bool hasTransparentPixels);
     *
     * @brief Blits a 2D source-array to the framebuffer while converting the format.
     *
     *        Blits a 2D source-array to the framebuffer perfoming alpha-blending (and
     *        tranparency keying) as specified. Performs a software blend if HAL does not
     *        support BLIT_COPY_WITH_ALPHA and alpha != 255. LCD32 supports source data
     *        formats: RGB565, RGB888 and ARGB8888.
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
     * @fn virtual uint16_t* LCD32bpp::copyFrameBufferRegionToMemory(const Rect& visRegion, const Rect& absRegion, const BitmapId bitmapId);
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
     * @fn virtual void LCD32bpp::fillRect(const Rect& rect, colortype color, uint8_t alpha = 255);
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
     * @fn virtual uint8_t LCD32bpp::bitDepth() const
     *
     * @brief Number of bits per pixel used by the display.
     *
     *        Number of bits per pixel used by the display.
     *
     * @return The number of bits per pixel.
     */
    virtual uint8_t bitDepth() const
    {
        return 32;
    }

    /**
     * @fn virtual Bitmap::BitmapFormat LCD32bpp::framebufferFormat() const
     *
     * @brief Framebuffer format used by the display
     *
     *        Framebuffer format used by the display
     *
     * @return Bitmap::ARGB8888.
     */
    virtual Bitmap::BitmapFormat framebufferFormat() const
    {
        return Bitmap::ARGB8888;
    }

    /**
     * @fn virtual uint16_t LCD32bpp::framebufferStride() const
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
     * @fn FORCE_INLINE_FUNCTION static uint16_t LCD32bpp::getFramebufferStride()
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
        return HAL::FRAME_BUFFER_WIDTH * 4;
    }

    /**
     * @fn virtual colortype LCD32bpp::getColorFrom24BitRGB(uint8_t red, uint8_t green, uint8_t blue) const
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
     * @fn FORCE_INLINE_FUNCTION static colortype LCD32bpp::getColorFromRGB(uint8_t red, uint8_t green, uint8_t blue)
     *
     * @brief Generates a color representation to be used on the LCD, based on 24 bit RGB values.
     *
     *        Generates a color representation to be used on the LCD, based on 24 bit RGB values.
     *
     * @param red   Value of the red part (0-255).
     * @param green Value of the green part (0-255).
     * @param blue  Value of the blue part (0-255).
     *
     * @return The color from RGB.
     */
    FORCE_INLINE_FUNCTION static colortype getColorFromRGB(uint8_t red, uint8_t green, uint8_t blue)
    {
        return (0xff << 24) | (red << 16) | (green << 8) | (blue);
    }

    /**
     * @fn virtual uint8_t LCD32bpp::getRedColor(colortype color) const
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
     * @fn FORCE_INLINE_FUNCTION static uint8_t LCD32bpp::getRedFromColor(colortype color)
     *
     * @brief Gets red from color
     *
     * @param color The color.
     *
     * @return The red from color.
     */
    FORCE_INLINE_FUNCTION static uint8_t getRedFromColor(colortype color)
    {
        return (color.getColor32() >> 16) & 0xFF;
    }

    /**
     * @fn virtual uint8_t LCD32bpp::getGreenColor(colortype color) const
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
     * @fn FORCE_INLINE_FUNCTION static uint8_t LCD32bpp::getGreenFromColor(colortype color)
     *
     * @brief Gets green from color
     *
     * @param color The color.
     *
     * @return The green from color.
     */
    FORCE_INLINE_FUNCTION static uint8_t getGreenFromColor(colortype color)
    {
        return (color.getColor32() >> 8) & 0xFF;
    }

    /**
     * @fn virtual uint8_t LCD32bpp::getBlueColor(colortype color) const
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
     * @fn FORCE_INLINE_FUNCTION static uint8_t LCD32bpp::getBlueFromColor(colortype color)
     *
     * @brief Gets blue from color
     *
     * @param color The color.
     *
     * @return The blue from color.
     */
    FORCE_INLINE_FUNCTION static uint8_t getBlueFromColor(colortype color)
    {
        return color.getColor32() & 0xFF;
    }

    /**
     * @fn void LCD32bpp::enableTextureMapperAll();
     *
     * @brief Enables the texture mappers for all image formats.
     *
     *        Enables the texture mappers for all image formats. This allows drawing any image
     *        using Bilinear Interpolation and Nearest Neighbor algorithms, but might use a
     *        lot of memory for the drawing algorithms.
     */
    void enableTextureMapperAll();

    /**
     * @fn void LCD32bpp::enableTextureMapperL8_RGB565();
     *
     * @brief Enables the texture mappers for L8_RGB565 image format.
     *
     *        Enables the texture mappers for L8_RGB565 image format. This allows drawing
     *        L8_RGB565 images using Bilinear Interpolation and Nearest Neighbor algorithms.
     *
     * @see enableTextureMapperL8_RGB565_BilinearInterpolation
     * @see enableTextureMapperL8_RGB565_NearestNeighbor
     */
    void enableTextureMapperL8_RGB565();

    /**
     * @fn void LCD32bpp::enableTextureMapperL8_RGB565_BilinearInterpolation();
     *
     * @brief Enables the texture mappers for L8_RGB565 image format for Bilinear Interpolation algorithm.
     *
     *        Enables the texture mappers for L8_RGB565 image format. This allows drawing
     *        L8_RGB565 images using Bilinear Interpolation algorithm.
     *
     * @see enableTextureMapperL8_RGB565
     * @see enableTextureMapperL8_RGB565_NearestNeighbor
     */
    void enableTextureMapperL8_RGB565_BilinearInterpolation();

    /**
     * @fn void LCD32bpp::enableTextureMapperL8_RGB565_NearestNeighbor();
     *
     * @brief Enables the texture mappers for L8_RGB565 image format for Nearest Neighbor algorithm.
     *
     *        Enables the texture mappers for L8_RGB565 image format. This allows drawing
     *        L8_RGB565 images using Nearest Neighbor algorithm.
     *
     * @see enableTextureMapperL8_RGB565
     * @see enableTextureMapperL8_RGB565_BilinearInterpolation
     */
    void enableTextureMapperL8_RGB565_NearestNeighbor();

    /**
     * @fn void LCD32bpp::enableTextureMapperL8_RGB888();
     *
     * @brief Enables the texture mappers for L8_RGB888 image format.
     *
     *        Enables the texture mappers for L8_RGB888 image format. This allows drawing
     *        L8_RGB888 images using Bilinear Interpolation and Nearest Neighbor algorithms.
     *
     * @see enableTextureMapperL8_RGB888_BilinearInterpolation
     * @see enableTextureMapperL8_RGB888_NearestNeighbor
     */
    void enableTextureMapperL8_RGB888();

    /**
     * @fn void LCD32bpp::enableTextureMapperL8_RGB888_BilinearInterpolation();
     *
     * @brief Enables the texture mappers for L8_RGB888 image format for Bilinear Interpolation algorithm.
     *
     *        Enables the texture mappers for L8_RGB888 image format. This allows drawing
     *        L8_RGB888 images using Bilinear Interpolation algorithm.
     *
     * @see enableTextureMapperL8_RGB888
     * @see enableTextureMapperL8_RGB888_NearestNeighbor
     */
    void enableTextureMapperL8_RGB888_BilinearInterpolation();

    /**
     * @fn void LCD32bpp::enableTextureMapperL8_RGB888_NearestNeighbor();
     *
     * @brief Enables the texture mappers for L8_RGB888 image format for Nearest Neighbor algorithm.
     *
     *        Enables the texture mappers for L8_RGB888 image format. This allows drawing
     *        L8_RGB888 images using Nearest Neighbor algorithm.
     *
     * @see enableTextureMapperL8_RGB888
     * @see enableTextureMapperL8_RGB888_BilinearInterpolation
     */
    void enableTextureMapperL8_RGB888_NearestNeighbor();

    /**
     * @fn void LCD32bpp::enableTextureMapperL8_ARGB8888();
     *
     * @brief Enables the texture mappers for L8_ARGB8888 image format.
     *
     *        Enables the texture mappers for L8_ARGB8888 image format. This allows drawing
     *        L8_ARGB8888 images using Bilinear Interpolation and Nearest Neighbor algorithms.
     *
     * @see enableTextureMapperL8_ARGB8888_BilinearInterpolation
     * @see enableTextureMapperL8_ARGB8888_NearestNeighbor
     */
    void enableTextureMapperL8_ARGB8888();

    /**
     * @fn void LCD32bpp::enableTextureMapperL8_ARGB8888_BilinearInterpolation();
     *
     * @brief Enables the texture mappers for L8_ARGB8888 image format for Bilinear Interpolation algorithm.
     *
     *        Enables the texture mappers for L8_ARGB8888 image format. This allows drawing
     *        L8_ARGB8888 images using Bilinear Interpolation algorithm.
     *
     * @see enableTextureMapperL8_ARGB8888
     * @see enableTextureMapperL8_ARGB8888_NearestNeighbor
     */
    void enableTextureMapperL8_ARGB8888_BilinearInterpolation();

    /**
     * @fn void LCD32bpp::enableTextureMapperL8_ARGB8888_NearestNeighbor();
     *
     * @brief Enables the texture mappers for L8_ARGB8888 image format for NearestNeighbor
     *        algorithm.
     *
     *        Enables the texture mappers for L8_ARGB8888 image format. This allows drawing
     *        L8_ARGB8888 images using Nearest Neighbor algorithm.
     *
     * @see enableTextureMapperL8_ARGB8888
     * @see enableTextureMapperL8_ARGB8888_BilinearInterpolation
     */
    void enableTextureMapperL8_ARGB8888_NearestNeighbor();

    /**
     * @fn void LCD32bpp::enableTextureMapperRGB565();
     *
     * @brief Enables the texture mappers for RGB565 image format.
     *
     *        Enables the texture mappers for RGB565 image format. This allows drawing RGB565
     *        images using Bilinear Interpolation and Nearest Neighbor algorithms.
     */
    void enableTextureMapperRGB565();

    /**
     * @fn void LCD32bpp::enableTextureMapperRGB565_Opaque_BilinearInterpolation();
     *
     * @brief Enables the texture mappers for Opaque RGB565 image format for Bilinear Interpolation
     *        algorithm.
     *
     *        Enables the texture mappers for Opaque RGB565 image format. This allows drawing
     *        RGB565 images using Bilinear Interpolation algorithm.
     *
     * @see enableTextureMapperRGB565
     * @see enableTextureMapperRGB565_NonOpaque_BilinearInterpolation
     */
    void enableTextureMapperRGB565_Opaque_BilinearInterpolation();

    /**
     * @fn void LCD32bpp::enableTextureMapperRGB565_NonOpaque_BilinearInterpolation();
     *
     * @brief Enables the texture mappers for NonOpaque RGB565 image format for Bilinear
     *        Interpolation algorithm.
     *
     *        Enables the texture mappers for NonOpaque RGB565 image format. This allows
     *        drawing RGB565 images using Bilinear Interpolation algorithm.
     *
     * @see enableTextureMapperRGB565
     * @see enableTextureMapperRGB565_Opaque_BilinearInterpolation
     */
    void enableTextureMapperRGB565_NonOpaque_BilinearInterpolation();

    /**
     * @fn void LCD32bpp::enableTextureMapperRGB565_Opaque_NearestNeighbor();
     *
     * @brief Enables the texture mappers for Opaque RGB565 image format for Nearest Neighbor
     *        algorithm.
     *
     *        Enables the texture mappers for Opaque RGB565 image format. This allows drawing
     *        RGB565 images using Nearest Neighbor algorithm.
     *
     * @see enableTextureMapperRGB565
     * @see enableTextureMapperRGB565_NonOpaque_NearestNeighbor
     */
    void enableTextureMapperRGB565_Opaque_NearestNeighbor();

    /**
     * @fn void LCD32bpp::enableTextureMapperRGB565_NonOpaque_NearestNeighbor();
     *
     * @brief Enables the texture mappers for NonOpaque RGB565 image format for Nearest Neighbor
     *        algorithm.
     *
     *        Enables the texture mappers for NonOpaque RGB565 image format. This allows
     *        drawing RGB565 images using Nearest Neighbor algorithm.
     *
     * @see enableTextureMapperRGB565
     * @see enableTextureMapperRGB565_Opaque_NearestNeighbor
     */
    void enableTextureMapperRGB565_NonOpaque_NearestNeighbor();

    /**
     * @fn void LCD32bpp::enableTextureMapperRGB888();
     *
     * @brief Enables the texture mappers for RGB888 image format.
     *
     *        Enables the texture mappers for RGB888 image format. This allows drawing RGB888
     *        images using Bilinear Interpolation and Nearest Neighbor algorithms.
     *
     * @see enableTextureMapperRGB888_BilinearInterpolation
     * @see enableTextureMapperRGB888_NearestNeighbor
     */
    void enableTextureMapperRGB888();

    /**
     * @fn void LCD32bpp::enableTextureMapperRGB888_BilinearInterpolation();
     *
     * @brief Enables the texture mappers for RGB888 image format for Bilinear Interpolation algorithm.
     *
     *        Enables the texture mappers for RGB888 image format. This allows drawing RGB888
     *        images using Bilinear Interpolation algorithm.
     *
     * @see enableTextureMapperRGB888
     * @see enableTextureMapperRGB888_NearestNeighbor
     */
    void enableTextureMapperRGB888_BilinearInterpolation();

    /**
     * @fn void LCD32bpp::enableTextureMapperRGB888_NearestNeighbor();
     *
     * @brief Enables the texture mappers for RGB888 image format for Nearest Neighbor algorithm.
     *
     *        Enables the texture mappers for RGB888 image format. This allows drawing RGB888
     *        images using Nearest Neighbor algorithm.
     *
     * @see enableTextureMapperRGB888
     * @see enableTextureMapperRGB888_BilinearInterpolation
     */
    void enableTextureMapperRGB888_NearestNeighbor();

    /**
     * @fn void LCD32bpp::enableTextureMapperARGB8888();
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
     * @fn void LCD32bpp::enableTextureMapperARGB8888_BilinearInterpolation();
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
     * @fn void LCD32bpp::enableTextureMapperARGB8888_NearestNeighbor();
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
     * @fn void LCD32bpp::enableTextureMapperA4();
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
     * @fn void LCD32bpp::enableTextureMapperA4_BilinearInterpolation();
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
     * @fn void LCD32bpp::enableTextureMapperA4_NearestNeighbor();
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
     * @fn static int LCD32bpp::nextPixel(bool rotatedDisplay, TextRotation textRotation);
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
     * @fn static int LCD32bpp::nextLine(bool rotatedDisplay, TextRotation textRotation);
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
     * @fn virtual void LCD32bpp::drawGlyph(uint16_t* wbuf, Rect widgetArea, int16_t x, int16_t y, uint16_t offsetX, uint16_t offsetY, const Rect& invalidatedArea, const GlyphNode* glyph, const uint8_t* glyphData, uint8_t dataFormatA4, colortype color, uint8_t bitsPerPixel, uint8_t alpha, TextRotation rotation);
     *
     * @brief Private version of draw-glyph with explicit destination buffer pointer argument.
     *
     *        Private version of draw-glyph with explicit destination buffer pointer argument.
     *        For all parameters (except the buffer pointer) see the public version of
     *        drawGlyph().
     *
     * @param [in] wbuf       The destination (frame) buffer to draw to.
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
    virtual void drawGlyph(uint16_t* wbuf, Rect widgetArea, int16_t x, int16_t y, uint16_t offsetX, uint16_t offsetY, const Rect& invalidatedArea, const GlyphNode* glyph, const uint8_t* glyphData, uint8_t dataFormatA4, colortype color, uint8_t bitsPerPixel, uint8_t alpha, TextRotation rotation);

    /**
     * @fn static void LCD32bpp::blitCopyRGB888(const uint16_t* sourceData16, const Rect& source, const Rect& blitRect, uint8_t alpha);
     *
     * @brief Blits a 2D source-array to the framebuffer.
     *
     *        Blits a 2D source-array to the framebuffer perfoming alpha-blending per pixel as
     *        specified. If RGB888 is not supported by the DMA a software blend is performed.
     *
     * @param sourceData16 The source-array pointer (points to the beginning of the data). The
     *                     sourceData must be stored as 24- bits RGB888 values.
     * @param source       The location and dimension of the source.
     * @param blitRect     A rectangle describing what region is to be drawn.
     * @param alpha        The alpha value to use for blending applied to the whole image (255 =
     *                     solid, no blending)
     */
    static void blitCopyRGB888(const uint16_t* sourceData16, const Rect& source, const Rect& blitRect, uint8_t alpha);

    /**
     * @fn static void LCD32bpp::blitCopyRGB565(const uint16_t* sourceData, const Rect& source, const Rect& blitRect, uint8_t alpha);
     *
     * @brief Blits a 2D source-array to the framebuffer.
     *
     *        Blits a 2D source-array to the framebuffer perfoming alpha-blending per pixel as
     *        specified. If! RGB565 is not supported by the DMA a software blend is performed.
     *
     * @param sourceData The source-array pointer (points to the beginning of the data). The
     *                   sourceData must be stored as 16- bits RGB565 values.
     * @param source     The location and dimension of the source.
     * @param blitRect   A rectangle describing what region is to be drawn.
     * @param alpha      The alpha value to use for blending applied to the whole image (255 =
     *                   solid, no blending)
     */
    static void blitCopyRGB565(const uint16_t* sourceData16, const Rect& source, const Rect& blitRect, uint8_t alpha);

    /**
     * @fn static void LCD32bpp::blitCopyL8(const uint8_t* sourceData, const uint8_t* clutData, const Rect& source, const Rect& blitRect, uint8_t alpha);
     *
     * @brief Blits a 2D indexed 8-bit source to the framebuffer.
     *
     *        Blits a 2D indexed 8-bit source to the framebuffer perfoming alpha-blending per pixel as
     *        specified if indexed format is not supported by the DMA a software blend is performed.
     *
     * @param sourceData The source-indexes pointer (points to the beginning of the data). The
     *                   sourceData must be stored as 8- bits indexes.
     * @param clutData   The source-clut pointer (points to the beginning of the CLUT color format and
     *                   size data followed by colors entries.
     * @param source     The location and dimension of the source.
     * @param blitRect   A rectangle describing what region is to be drawn.
     * @param alpha      The alpha value to use for blending applied to the whole image (255 =
     *                   solid, no blending)
     */
    static void blitCopyL8(const uint8_t* sourceData, const uint8_t* clutData, const Rect& source, const Rect& blitRect, uint8_t alpha);

    /**
     * @fn static void LCD32bpp::blitCopyL8_ARGB8888(const uint8_t* sourceData, const uint8_t* clutData, const Rect& source, const Rect& blitRect, uint8_t alpha);
     *
     * @brief Blits a 2D indexed 8-bit source to the framebuffer.
     *
     *        Blits a 2D indexed 8-bit source to the framebuffer perfoming alpha-blending per pixel as
     *        specified if L8_ARGB8888 is not supported by the DMA a software blend is performed.
     *
     * @param sourceData The source-indexes pointer (points to the beginning of the data). The
     *                   sourceData must be stored as 8- bits indexes.
     * @param clutData   The source-clut pointer (points to the beginning of the CLUT color format and
     *                   size data followed by colors entries stored as 32- bits (ARGB8888) format.
     * @param source     The location and dimension of the source.
     * @param blitRect   A rectangle describing what region is to be drawn.
     * @param alpha      The alpha value to use for blending applied to the whole image (255 =
     *                   solid, no blending)
     */
    static void blitCopyL8_ARGB8888(const uint8_t* sourceData, const uint8_t* clutData, const Rect& source, const Rect& blitRect, uint8_t alpha);

    /**
     * @fn static void LCD32bpp::blitCopyL8_RGB888(const uint8_t* sourceData, const uint8_t* clutData, const Rect& source, const Rect& blitRect, uint8_t alpha);
     *
     * @brief Blits a 2D indexed 8-bit source to the framebuffer.
     *
     *        Blits a 2D indexed 8-bit source to the framebuffer perfoming alpha-blending per pixel as
     *        specified if L8_RGB888 is not supported by the DMA a software blend is performed.
     *
     * @param sourceData The source-indexes pointer (points to the beginning of the data). The
     *                   sourceData must be stored as 8- bits indexes.
     * @param clutData   The source-clut pointer (points to the beginning of the CLUT color format and
     *                   size data followed by colors entries stored as 32- bits (RGB888) format.
     * @param source     The location and dimension of the source.
     * @param blitRect   A rectangle describing what region is to be drawn.
     * @param alpha      The alpha value to use for blending applied to the whole image (255 =
     *                   solid, no blending)
     */
    static void blitCopyL8_RGB888(const uint8_t* sourceData, const uint8_t* clutData, const Rect& source, const Rect& blitRect, uint8_t alpha);

    /**
     * @fn static void LCD32bpp::blitCopyL8_RGB565(const uint8_t* sourceData, const uint8_t* clutData, const Rect& source, const Rect& blitRect, uint8_t alpha);
     *
     * @brief Blits a 2D indexed 8-bit source to the framebuffer.
     *
     *        Blits a 2D indexed 8-bit source to the framebuffer perfoming alpha-blending per pixel as
     *        specified if L8_RGB565 is not supported by the DMA a software blend is performed.
     *
     * @param sourceData The source-indexes pointer (points to the beginning of the data). The
     *                   sourceData must be stored as 8- bits indexes.
     * @param clutData   The source-clut pointer (points to the beginning of the CLUT color format and
     *                   size data followed by colors entries stored as 16- bits (RGB565) format.
     * @param source     The location and dimension of the source.
     * @param blitRect   A rectangle describing what region is to be drawn.
     * @param alpha      The alpha value to use for blending applied to the whole image (255 =
     *                   solid, no blending)
     */
    static void blitCopyL8_RGB565(const uint8_t* sourceData, const uint8_t* clutData, const Rect& source, const Rect& blitRect, uint8_t alpha);

private:
    DrawTextureMapScanLineBase* textureMapper_L8_RGB565_Opaque_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_L8_RGB565_Opaque_NearestNeighbor_NoGA;
    DrawTextureMapScanLineBase* textureMapper_L8_RGB565_Opaque_BilinearInterpolation_GA;
    DrawTextureMapScanLineBase* textureMapper_L8_RGB565_Opaque_BilinearInterpolation_NoGA;
    DrawTextureMapScanLineBase* textureMapper_L8_RGB888_Opaque_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_L8_RGB888_Opaque_NearestNeighbor_NoGA;
    DrawTextureMapScanLineBase* textureMapper_L8_RGB888_Opaque_BilinearInterpolation_GA;
    DrawTextureMapScanLineBase* textureMapper_L8_RGB888_Opaque_BilinearInterpolation_NoGA;
    DrawTextureMapScanLineBase* textureMapper_L8_ARGB8888_NonOpaque_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_L8_ARGB8888_NonOpaque_BilinearInterpolation_GA;
    DrawTextureMapScanLineBase* textureMapper_RGB565_NonOpaque_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_RGB565_NonOpaque_NearestNeighbor_NoGA;
    DrawTextureMapScanLineBase* textureMapper_RGB565_Opaque_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_RGB565_Opaque_NearestNeighbor_NoGA;
    DrawTextureMapScanLineBase* textureMapper_RGB565_NonOpaque_BilinearInterpolation_GA;
    DrawTextureMapScanLineBase* textureMapper_RGB565_NonOpaque_BilinearInterpolation_NoGA;
    DrawTextureMapScanLineBase* textureMapper_RGB565_Opaque_BilinearInterpolation_GA;
    DrawTextureMapScanLineBase* textureMapper_RGB565_Opaque_BilinearInterpolation_NoGA;
    DrawTextureMapScanLineBase* textureMapper_RGB888_Opaque_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_RGB888_Opaque_NearestNeighbor_NoGA;
    DrawTextureMapScanLineBase* textureMapper_RGB888_Opaque_BilinearInterpolation_GA;
    DrawTextureMapScanLineBase* textureMapper_RGB888_Opaque_BilinearInterpolation_NoGA;
    DrawTextureMapScanLineBase* textureMapper_ARGB8888_NonOpaque_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_ARGB8888_NonOpaque_BilinearInterpolation_GA;
    DrawTextureMapScanLineBase* textureMapper_A4_NearestNeighbor_GA;
    DrawTextureMapScanLineBase* textureMapper_A4_NearestNeighbor_NoGA;
    DrawTextureMapScanLineBase* textureMapper_A4_BilinearInterpolation_GA;
    DrawTextureMapScanLineBase* textureMapper_A4_BilinearInterpolation_NoGA;

    FORCE_INLINE_FUNCTION static uint32_t expandRgb565(uint16_t c)
    {
        return ((c & 0x07E0) << 16) | (c & ~0x07E0);
    }

    FORCE_INLINE_FUNCTION static uint16_t compactRgb565(uint32_t c)
    {
        return ((c >> 16) & 0x07E0) | (c & ~0x07E0);
    }

    FORCE_INLINE_FUNCTION static uint32_t convertRgb565toArgb8888(uint16_t rgb565)
    {
        uint8_t r = (rgb565 & 0xF800) >> 8;
        r |= r >> 5;
        uint8_t g = (rgb565 & 0x07E0) >> 3;
        g |= g >> 6;
        uint8_t b = rgb565 << 3;
        b |= b >> 5;
        return (r << 16) | (g << 8) | b;
    }

    FORCE_INLINE_FUNCTION static void copy888(const uint8_t* const rgb888, uint8_t* const destBits)
    {
        destBits[0] = rgb888[0];
        destBits[1] = rgb888[1];
        destBits[2] = rgb888[2];
    }

    FORCE_INLINE_FUNCTION static void alphaBlend888(const uint8_t r, const uint8_t g, const uint8_t b, uint8_t* const destBits, const uint8_t alpha, const uint8_t ialpha)
    {
        destBits[0] = div255(b * alpha + destBits[0] * ialpha);
        destBits[1] = div255(g * alpha + destBits[1] * ialpha);
        destBits[2] = div255(r * alpha + destBits[2] * ialpha);
    }

    FORCE_INLINE_FUNCTION static void alphaBlend888(const uint8_t* const rgb888, uint8_t* const destBits, const uint8_t alpha, const uint8_t ialpha)
    {
        alphaBlend888(rgb888[2], rgb888[1], rgb888[0], destBits, alpha, ialpha);
    }

    FORCE_INLINE_FUNCTION static void alphaBlend565(const uint16_t rgb565, uint8_t* const destBits, const uint8_t alpha, const uint8_t ialpha)
    {
        const uint8_t r = (rgb565 & 0xF800) >> 8;
        const uint8_t g = (rgb565 & 0x07E0) >> 3;
        const uint8_t b = rgb565 << 3;
        alphaBlend888(r, g, b, destBits, alpha, ialpha);
    }

    FORCE_INLINE_FUNCTION static uint16_t bilinearInterpolate565(uint16_t c00, uint16_t c10, uint16_t c01, uint16_t c11, uint8_t x, uint8_t y)
    {
        assert(x < 16 && y < 16);
        uint32_t a00 = expandRgb565(c00);
        uint32_t a10 = expandRgb565(c10);
        uint32_t a01 = expandRgb565(c01);
        uint32_t a11 = expandRgb565(c11);

        uint8_t xy = (x * y) >> 3;
        return compactRgb565((a00 * (32 - 2 * y - 2 * x + xy) + a10 * (2 * x - xy) + a01 * (2 * y - xy) + a11 * xy) >> 5);
    }

    FORCE_INLINE_FUNCTION static uint16_t bilinearInterpolate565(uint16_t c00, uint16_t c10, uint8_t x)
    {
        assert(x < 16);
        uint32_t a00 = expandRgb565(c00);
        uint32_t a10 = expandRgb565(c10);

        return compactRgb565((a00 * (32 - 2 * x) + a10 * (2 * x)) >> 5);
    }

    FORCE_INLINE_FUNCTION static uint8_t bilinearInterpolate8(uint8_t c00, uint8_t c10, uint8_t x)
    {
        assert(x < 16);
        uint16_t xy10 = 16 * x;
        uint16_t xy00 = 256 - xy10;

        return (c00 * xy00 + c10 * xy10) >> 8;
    }

    FORCE_INLINE_FUNCTION static uint8_t bilinearInterpolate8(uint8_t c00, uint8_t c10, uint8_t c01, uint8_t c11, uint8_t x, uint8_t y)
    {
        assert(x < 16 && y < 16);
        uint16_t xy11 = x * y;
        uint16_t xy10 = 16 * x - xy11;
        uint16_t xy01 = 16 * y - xy11;
        uint16_t xy00 = 256 - (xy11 + xy10 + xy01);

        return (c00 * xy00 + c10 * xy10 + c01 * xy01 + c11 * xy11) >> 8;
    }

    FORCE_INLINE_FUNCTION static uint32_t bilinearInterpolate888(uint32_t c00, uint32_t c10, uint8_t x)
    {
        assert(x < 16);
        uint16_t xy10 = 16 * x;
        uint16_t xy00 = 256 - xy10;

        return ((((c00 & 0xFF00FF) * xy00 + (c10 & 0xFF00FF) * xy10) >> 8) & 0xFF00FF)
               | ((((c00 & 0x00FF00) * xy00 + (c10 & 0x00FF00) * xy10) >> 8) & 0x00FF00);
    }

    FORCE_INLINE_FUNCTION static uint32_t bilinearInterpolate888(uint32_t c00, uint32_t c10, uint32_t c01, uint32_t c11, uint8_t x, uint8_t y)
    {
        assert(x < 16 && y < 16);
        uint16_t xy11 = x * y;
        uint16_t xy10 = 16 * x - xy11;
        uint16_t xy01 = 16 * y - xy11;
        uint16_t xy00 = 256 - (xy11 + xy10 + xy01);

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

    FORCE_INLINE_FUNCTION static uint32_t div31rb(uint16_t val, uint8_t factor)
    {
        uint32_t val32 = (val & 0xF81F) * (factor >> 3);
        return ((val32 + 0x0801 + ((val32 >> 5) & 0xF81F)) >> 5) & 0xF81F;
    }

    FORCE_INLINE_FUNCTION static uint32_t div31g(uint16_t val, uint8_t factor)
    {
        uint32_t val32 = (val & 0x07E0) * factor;
        return ((val32 + 0x0020 + (val32 >> 8)) >> 8) & 0x07E0;
    }

    FORCE_INLINE_FUNCTION static uint32_t div255_565(uint16_t val, uint8_t factor)
    {
        return div31rb(val, factor) | div31g(val, factor);
    }

    FORCE_INLINE_FUNCTION static uint32_t div255_565_FFcheck(uint16_t val, uint8_t factor)
    {
        return factor < 0xFF ? div31rb(val, factor) | div31g(val, factor) : val;
    }

    class DrawTextureMapScanLineBase32 : public DrawTextureMapScanLineBase
    {
    protected:
        FORCE_INLINE_FUNCTION bool overrunCheckNearestNeighbor(uint32_t*& destBits, int& pixelsToDraw, fixed16_16& U, fixed16_16& V, fixed16_16 deltaU, fixed16_16 deltaV, const int16_t maxWidth, const int16_t maxHeight);
        FORCE_INLINE_FUNCTION bool overrunCheckBilinearInterpolation(uint32_t*& destBits, int& pixelsToDraw, fixed16_16& U, fixed16_16& V, fixed16_16 deltaU, fixed16_16 deltaV, const int16_t maxWidth, const int16_t maxHeight);
    };

    class TextureMapper_L8_RGB565_Opaque_NearestNeighbor_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t* const textureBits8, const uint16_t* const palette16, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t alpha);
    };

    class TextureMapper_L8_RGB565_Opaque_NearestNeighbor_NoGA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t* const textureBits8, const uint16_t* const palette16, const int16_t bitmapWidth, const int UInt, const int VInt);
    };

    class TextureMapper_L8_RGB565_Opaque_BilinearInterpolation_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t* const textureBits8, const uint16_t* const palette16, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint32_t* const destBits, const uint8_t* const textureBits8, const uint16_t* const palette16, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };

    class TextureMapper_L8_RGB565_Opaque_BilinearInterpolation_NoGA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t* const textureBits8, const uint16_t* const palette16, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac);
        void writePixelOnEdge(uint32_t* const destBits, const uint8_t* const textureBits8, const uint16_t* const palette16, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac);
    };

    class TextureMapper_L8_RGB888_Opaque_NearestNeighbor_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t* const textureBits8, const uint8_t* const palette8, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t alpha);
    };

    class TextureMapper_L8_RGB888_Opaque_NearestNeighbor_NoGA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t* const textureBits8, const uint8_t* const palette8, const int16_t bitmapWidth, const int UInt, const int VInt);
    };

    class TextureMapper_L8_RGB888_Opaque_BilinearInterpolation_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t* const textureBits8, const uint8_t* const palette8, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint32_t* const destBits, const uint8_t* const textureBits8, const uint8_t* const palette8, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };

    class TextureMapper_L8_RGB888_Opaque_BilinearInterpolation_NoGA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t* const textureBits8, const uint8_t* const palette8, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac);
        void writePixelOnEdge(uint32_t* const destBits, const uint8_t* const textureBits8, const uint8_t* const palette8, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac);
    };

    class TextureMapper_L8_ARGB8888_NonOpaque_NearestNeighbor_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t* const textureBits8, const uint32_t* const palette32, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t alpha);
    };

    class TextureMapper_L8_ARGB8888_NonOpaque_BilinearInterpolation_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t* const textureBits8, const uint32_t* const palette32, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint32_t* const destBits, const uint8_t* const textureBits8, const uint32_t* const palette32, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };

    class TextureMapper_RGB565_NonOpaque_NearestNeighbor_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint16_t* const textureBits, const uint8_t* alphaBits, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t alpha);
    };

    class TextureMapper_RGB565_NonOpaque_NearestNeighbor_NoGA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint16_t* const textureBits, const uint8_t* alphaBits, const int16_t bitmapWidth, const int UInt, const int VInt);
    };

    class TextureMapper_RGB565_NonOpaque_BilinearInterpolation_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint16_t* const textureBits, const uint8_t* alphaBits, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint32_t* const destBits, const uint16_t* const textureBits, const uint8_t* alphaBits, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };

    class TextureMapper_RGB565_NonOpaque_BilinearInterpolation_NoGA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint16_t* const textureBits, const uint8_t* alphaBits, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac);
        void writePixelOnEdge(uint32_t* const destBits, const uint16_t* const textureBits, const uint8_t* alphaBits, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac);
    };

    class TextureMapper_RGB565_Opaque_NearestNeighbor_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint16_t* const textureBits, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t alpha);
    };

    class TextureMapper_RGB565_Opaque_NearestNeighbor_NoGA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint16_t* const textureBits, const int16_t bitmapWidth, const int UInt, const int VInt);
    };

    class TextureMapper_RGB565_Opaque_BilinearInterpolation_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint16_t* const textureBits, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint32_t* const destBits, const uint16_t* const textureBits, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };

    class TextureMapper_RGB565_Opaque_BilinearInterpolation_NoGA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint16_t* const textureBits, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac);
        void writePixelOnEdge(uint32_t* const destBits, const uint16_t* const textureBits, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac);
    };

    class TextureMapper_RGB888_Opaque_NearestNeighbor_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t* const textureBits8, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t alpha);
    };

    class TextureMapper_RGB888_Opaque_NearestNeighbor_NoGA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t* const textureBits8, const int16_t bitmapWidth, const int UInt, const int VInt);
    };

    class TextureMapper_RGB888_Opaque_BilinearInterpolation_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t* const textureBits8, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint32_t* const destBits, const uint8_t* const textureBits8, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };

    class TextureMapper_RGB888_Opaque_BilinearInterpolation_NoGA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t* const textureBits8, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac);
        void writePixelOnEdge(uint32_t* const destBits, const uint8_t* const textureBits8, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac);
    };

    class TextureMapper_ARGB8888_NonOpaque_NearestNeighbor_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint32_t* const textureBits32, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t alpha);
    };

    class TextureMapper_ARGB8888_NonOpaque_BilinearInterpolation_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint32_t* const textureBits32, const int16_t bitmapWidth, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint32_t* const destBits, const uint32_t* const textureBits32, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };

    class TextureMapper_A4_NearestNeighbor_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t a4, const uint8_t alpha);
    };

    class TextureMapper_A4_NearestNeighbor_NoGA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint8_t a4);
    };

    class TextureMapper_A4_BilinearInterpolation_GA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint16_t* const textureBits, const int16_t bitmapStride, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
        void writePixelOnEdge(uint32_t* const destBits, const uint16_t* const textureBits, const int16_t bitmapStride, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac, const uint8_t alpha);
    };

    class TextureMapper_A4_BilinearInterpolation_NoGA : public DrawTextureMapScanLineBase32
    {
    public:
        virtual void drawTextureMapScanLineSubdivisions(int subdivisions, const int widthModLength, int pixelsToDraw, const int affineLength, float oneOverZRight, float UOverZRight, float VOverZRight, fixed16_16 U, fixed16_16 V, fixed16_16 deltaU, fixed16_16 deltaV, float ULeft, float VLeft, float URight, float VRight, float ZRight, const DrawingSurface& dest, const int destX, const int destY, const int16_t bitmapWidth, const int16_t bitmapHeight, const TextureSurface& texture, uint8_t alpha, const float dOneOverZdXAff, const float dUOverZdXAff, const float dVOverZdXAff);

    private:
        FORCE_INLINE_FUNCTION void writePixel(uint32_t* const destBits, const uint16_t* const textureBits, const int16_t bitmapStride, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac);
        void writePixelOnEdge(uint32_t* const destBits, const uint16_t* const textureBits, const int16_t bitmapStride, const int16_t bitmapWidth, const int16_t bitmapHeight, const int UInt, const int VInt, const uint8_t UFrac, const uint8_t VFrac);
    };
};

/**
 * @class LCD32DebugPrinter LCD32bpp.hpp platform/driver/lcd/LCD32bpp.hpp
 *
 * @brief The class LCD32DebugPrinter implements the DebugPrinter interface for printing debug messages on top of 32bit framebuffer.
 *
 *        The class LCD32DebugPrinter implements the DebugPrinter interface for printing debug messages on top of 32bit framebuffer.
 *
 * @see DebugPrinter
 */
class LCD32DebugPrinter : public DebugPrinter
{
public:
    virtual void draw(const Rect& rect) const;
};
} // namespace touchgfx
#endif // LCD32BPP_HPP
