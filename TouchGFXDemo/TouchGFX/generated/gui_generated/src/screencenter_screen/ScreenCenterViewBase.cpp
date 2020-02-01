/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screencenter_screen/ScreenCenterViewBase.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>

ScreenCenterViewBase::ScreenCenterViewBase() :
    buttonCallback(this, &ScreenCenterViewBase::buttonCallbackHandler)
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_BG_CENTER_ID));

    shape1.setPosition(47, 11, 229, 178);
    shape1.setOrigin(114.000f, 90.000f);
    shape1.setScale(1.000f, 1.000f);
    shape1.setAngle(0.000f);
    shape1Painter.setColor(touchgfx::Color::getColorFrom24BitRGB(226, 255, 8));
    shape1.setPainter(shape1Painter);
    const touchgfx::AbstractShape::ShapePoint<float> shape1Points[10] = { { 0.000f, -55.000f }, { 12.000f, -19.000f }, { 54.000f, -19.000f }, { 18.000f, -1.000f }, { 28.000f, 41.000f }, { 0.000f, 17.000f }, { -28.000f, 41.000f }, { -18.000f, -1.000f }, { -55.000f, -19.000f }, { -12.000f, -19.000f } };
    shape1.setShape(shape1Points);

    buttonDown.setXY(59, 197);
    buttonDown.setBitmaps(touchgfx::Bitmap(BITMAP_ARROW_DOWN_ID), touchgfx::Bitmap(BITMAP_ARROW_DOWN_GRAY_ID));
    buttonDown.setAction(buttonCallback);

    buttonUp.setXY(231, 197);
    buttonUp.setBitmaps(touchgfx::Bitmap(BITMAP_ARROW_UP_ID), touchgfx::Bitmap(BITMAP_ARROW_UP_GRAY_ID));
    buttonUp.setAction(buttonCallback);

    buttonLeft.setXY(7, 104);
    buttonLeft.setBitmaps(touchgfx::Bitmap(BITMAP_ARROW_LEFT_ID), touchgfx::Bitmap(BITMAP_ARROW_LEFT_GRAY_ID));
    buttonLeft.setAction(buttonCallback);

    buttonRight.setXY(282, 104);
    buttonRight.setBitmaps(touchgfx::Bitmap(BITMAP_ARROW_RIGHT_ID), touchgfx::Bitmap(BITMAP_ARROW_RIGHT_GRAY_ID));
    buttonRight.setAction(buttonCallback);

    add(image1);
    add(shape1);
    add(buttonDown);
    add(buttonUp);
    add(buttonLeft);
    add(buttonRight);
}

void ScreenCenterViewBase::setupScreen()
{

}

void ScreenCenterViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonDown)
    {
        //Interaction1
        //When buttonDown clicked scale shape1
        //Scale shape1
        float shape1XScale, shape1YScale;
        shape1.getScale(shape1XScale, shape1YScale);
        shape1.updateScale(shape1XScale * 0.900f, shape1YScale * 0.900f);

        //Interaction3
        //When buttonDown clicked rotate shape1
        //Rotate shape1
        shape1.updateAngle(shape1.getAngle() + 3.000f);
    }
    else if (&src == &buttonUp)
    {
        //Interaction2
        //When buttonUp clicked scale shape1
        //Scale shape1
        float shape1XScale, shape1YScale;
        shape1.getScale(shape1XScale, shape1YScale);
        shape1.updateScale(shape1XScale * 1.100f, shape1YScale * 1.100f);

        //Interaction4
        //When buttonUp clicked rotate shape1
        //Rotate shape1
        shape1.updateAngle(shape1.getAngle() + -3.000f);
    }
    else if (&src == &buttonLeft)
    {
        //Interaction5
        //When buttonLeft clicked change screen to ScreenLeft
        //Go to ScreenLeft with no screen transition
        application().gotoScreenLeftScreenNoTransition();
    }
    else if (&src == &buttonRight)
    {
        //Interaction6
        //When buttonRight clicked change screen to ScreenRight
        //Go to ScreenRight with no screen transition
        application().gotoScreenRightScreenNoTransition();
    }
}