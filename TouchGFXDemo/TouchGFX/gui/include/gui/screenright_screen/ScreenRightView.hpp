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
protected:
};

#endif // SCREENRIGHTVIEW_HPP
