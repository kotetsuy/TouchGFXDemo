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
    int animationStep;

    Callback<ScreenLeftView, const AnimationTextureMapper&> animationEndedCallback;
    void animationEndedHandler(const AnimationTextureMapper& src);

    void setupAndStartAnimation();
};

#endif // SCREENLEFTVIEW_HPP
