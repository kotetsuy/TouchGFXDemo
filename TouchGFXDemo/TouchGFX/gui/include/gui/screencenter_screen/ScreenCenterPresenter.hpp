#ifndef SCREENCENTERPRESENTER_HPP
#define SCREENCENTERPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScreenCenterView;

class ScreenCenterPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScreenCenterPresenter(ScreenCenterView& v);

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

    virtual ~ScreenCenterPresenter() {};

private:
    ScreenCenterPresenter();

    ScreenCenterView& view;
};

#endif // SCREENCENTERPRESENTER_HPP
