#ifndef SCREENCENTERVIEW_HPP
#define SCREENCENTERVIEW_HPP

#include <gui_generated/screencenter_screen/ScreenCenterViewBase.hpp>
#include <gui/screencenter_screen/ScreenCenterPresenter.hpp>

class ScreenCenterView : public ScreenCenterViewBase
{
public:
    ScreenCenterView();
    virtual ~ScreenCenterView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREENCENTERVIEW_HPP
