#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "BevTestScene.h"

#include "BehaviorTreeEditor.h"

#include "Utils.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

	if (Utils::init())
	{
		log("Utils init error!!!");
	}

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	// set design resolution
	float design_resolution_width = Utils::getGlobalSettingFloat("design_resolution_width", 960);
	float design_resolution_height = Utils::getGlobalSettingFloat("design_resolution_height", 640);
	glview->setDesignResolutionSize(design_resolution_width, design_resolution_height, ResolutionPolicy::NO_BORDER);

    // create a scene. it's an autorelease object
    //auto scene = BevTestScene::createScene();

	auto scene = BehaviorTreeEditor::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
