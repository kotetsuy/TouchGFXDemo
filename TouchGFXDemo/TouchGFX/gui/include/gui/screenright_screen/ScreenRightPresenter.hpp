#ifndef SCREENRIGHTPRESENTER_HPP
#define SCREENRIGHTPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScreenRightView;

class ScreenRightPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScreenRightPresenter(ScreenRightView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~ScreenRightPresenter() {};

private:
    ScreenRightPresenter();

    ScreenRightView& view;
};

#endif // SCREENRIGHTPRESENTER_HPP
