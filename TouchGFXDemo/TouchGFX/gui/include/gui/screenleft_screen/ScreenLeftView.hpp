#ifndef SCREENLEFTVIEW_HPP
#define SCREENLEFTVIEW_HPP

#include <gui_generated/screenleft_screen/ScreenLeftViewBase.hpp>
#include <gui/screenleft_screen/ScreenLeftPresenter.hpp>

class ScreenLeftView : public ScreenLeftViewBase
{
public:
    ScreenLeftView();
    virtual ~ScreenLeftView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
    //GenericCallback<const AnimationTextureMapper& > startAnimation(void);
};

#endif // SCREENLEFTVIEW_HPP
