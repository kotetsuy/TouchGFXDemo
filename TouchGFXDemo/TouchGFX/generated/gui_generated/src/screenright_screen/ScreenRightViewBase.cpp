/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screenright_screen/ScreenRightViewBase.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

ScreenRightViewBase::ScreenRightViewBase() :
    buttonCallback(this, &ScreenRightViewBase::buttonCallbackHandler)
{

    image1.setXY(0, 0);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_BG_RIGHT_ID));

    buttonLeft.setXY(7, 104);
    buttonLeft.setBitmaps(touchgfx::Bitmap(BITMAP_ARROW_LEFT_ID), touchgfx::Bitmap(BITMAP_ARROW_LEFT_GRAY_ID));
    buttonLeft.setAction(buttonCallback);

    imageProgress1.setXY(68, 110);
    imageProgress1.setProgressIndicatorPosition(2, 2, 180, 16);
    imageProgress1.setRange(0, 100);
    imageProgress1.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    imageProgress1.setBackground(touchgfx::Bitmap(BITMAP_BLUE_PROGRESSINDICATORS_BG_MEDIUM_PROGRESS_INDICATOR_BG_SQUARE_0_DEGREES_ID));
    imageProgress1.setBitmap(BITMAP_BLUE_PROGRESSINDICATORS_FILL_TILING_PROGRESS_INDICATOR_FILL_STRIPED_NORMAL_HORIZONTAL_ID);
    imageProgress1.setValue(60);
    imageProgress1.setAnchorAtZero(false);

    textArea1.setXY(90, 42);
    textArea1.setColor(touchgfx::Color::getColorFrom24BitRGB(255, 255, 0));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T_SINGLEUSEID2));

    add(image1);
    add(buttonLeft);
    add(imageProgress1);
    add(textArea1);
}

void ScreenRightViewBase::setupScreen()
{

}

void ScreenRightViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonLeft)
    {
        //Interaction1
        //When buttonLeft clicked change screen to ScreenCenter
        //Go to ScreenCenter with no screen transition
        application().gotoScreenCenterScreenNoTransition();
    }
}