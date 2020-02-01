#include <gui/screenleft_screen/ScreenLeftView.hpp>
#include <touchgfx/widgets/AnimationTextureMapper.hpp>

ScreenLeftView::ScreenLeftView()
{

}

void ScreenLeftView::setupScreen()
{
    ScreenLeftViewBase::setupScreen();
    //AnimationTextureMapper::setTextureMapperAnimationStepAction(startAnimation);
}

void ScreenLeftView::tearDownScreen()
{
    ScreenLeftViewBase::tearDownScreen();
    //AnimationTextureMapper::setTextureMapperAnimationEndedAction(NULL);
}

#if 0
GenericCallback<const AnimationTextureMapper& > ScreenLeftView::startAnimation(void)
{

}
#endif
