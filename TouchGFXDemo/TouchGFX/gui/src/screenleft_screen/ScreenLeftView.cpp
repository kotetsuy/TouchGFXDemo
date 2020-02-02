#include <gui/screenleft_screen/ScreenLeftView.hpp>
#include <touchgfx/widgets/AnimationTextureMapper.hpp>

ScreenLeftView::ScreenLeftView() :
	animationStep(0),
	animationEndedCallback(this, &ScreenLeftView::animationEndedHandler)
{
#if 0
    // Support of larger displays for this example
    // is handled by showing a black box in the
    // unused part of the display.
    if (HAL::DISPLAY_WIDTH > image1.getWidth() ||
            HAL::DISPLAY_HEIGHT > image1.getHeight())
    {
        backgroundBox.setVisible(true);
    }
#endif
}

void ScreenLeftView::setupScreen()
{
    ScreenLeftViewBase::setupScreen();
    textureMapper1.setTextureMapperAnimationEndedAction(animationEndedCallback);
    // Start the first animation. When it is done the animationEndedHandler is called.
    setupAndStartAnimation();
}

void ScreenLeftView::tearDownScreen()
{
    ScreenLeftViewBase::tearDownScreen();
}

void ScreenLeftView::animationEndedHandler(const AnimationTextureMapper& src)
{
    animationStep++;
    setupAndStartAnimation();
}

void ScreenLeftView::setupAndStartAnimation()
{
    if (animationStep % 2 == 0)
    {
        // Setup an animation that rotates around the X and Y axis
    	textureMapper1.setupAnimation(AnimationTextureMapper::X_ROTATION, textureMapper1.getXAngle() + 0.7f, 130, 0, EasingEquations::cubicEaseInOut);
    	textureMapper1.setupAnimation(AnimationTextureMapper::Y_ROTATION, textureMapper1.getYAngle() + 2.7f, 200, 0, EasingEquations::quadEaseIn);
    	textureMapper1.setupAnimation(AnimationTextureMapper::SCALE, 1.f, 200, 0);
    }
    else
    {
        // Setup an animation that rotates around the Z axis
    	textureMapper1.setupAnimation(AnimationTextureMapper::Z_ROTATION, textureMapper1.getZAngle() + 1.7f, 130, 0, EasingEquations::cubicEaseInOut);
    	textureMapper1.setupAnimation(AnimationTextureMapper::SCALE, 1.5f, 130, 0);
    }
    textureMapper1.startAnimation();
}
