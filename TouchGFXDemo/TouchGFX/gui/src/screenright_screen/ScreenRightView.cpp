#include <gui/screenright_screen/ScreenRightView.hpp>

ScreenRightView::ScreenRightView()
{

}

void ScreenRightView::setupScreen()
{
    ScreenRightViewBase::setupScreen();
    tickCounter = 0;
    imageProgress1.getRange(imageProgress1Min, imageProgress1Max);
    circleProgress1.getRange(circleProgressMin, circleProgressMax);

}

void ScreenRightView::tearDownScreen()
{
    ScreenRightViewBase::tearDownScreen();
}

void ScreenRightView::updateProgress(uint16_t tick)
{
    imageProgress1.setValue(tick % (imageProgress1Max + 1));
    circleProgress1.setValue(tick % (circleProgressMax + 1));
}

void ScreenRightView::handleTickEvent()
{
    tickCounter++;
    updateProgress(tickCounter);
}

