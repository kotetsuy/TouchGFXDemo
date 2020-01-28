#ifndef SCREENLEFTPRESENTER_HPP
#define SCREENLEFTPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ScreenLeftView;

class ScreenLeftPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ScreenLeftPresenter(ScreenLeftView& v);

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

    virtual ~ScreenLeftPresenter() {};

private:
    ScreenLeftPresenter();

    ScreenLeftView& view;
};

#endif // SCREENLEFTPRESENTER_HPP
