#ifndef SCREENRIGHTVIEW_HPP
#define SCREENRIGHTVIEW_HPP

#include <gui_generated/screenright_screen/ScreenRightViewBase.hpp>
#include <gui/screenright_screen/ScreenRightPresenter.hpp>

class ScreenRightView : public ScreenRightViewBase
{
public:
    ScreenRightView();
    virtual ~ScreenRightView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    void updateProgress(uint16_t tick);
protected:
    uint16_t tickCounter;
    int16_t imageProgress1Max;
    int16_t imageProgress1Min;
    int16_t circleProgressMax;
    int16_t circleProgressMin;
};

#endif // SCREENRIGHTVIEW_HPP
