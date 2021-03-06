#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "InGameScene.h"
#include "LoginScene.h"
#include "SceneManager.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    srand((unsigned int)time(NULL));

    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(WINSIZE_X,WINSIZE_Y, kResolutionShowAll);
    
    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
//    pDirector->enableRetinaDisplay(true);

    // turn on display FPS
#ifndef GAME_DEBUGGER
    pDirector->setDisplayStats(false);
#else
    pDirector->setDisplayStats(true);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    
    SceneManager::create();
    
    //CCScene *pScene = InGameScene::scene();
    CCScene *pScene = LoginScene::scene();

    // run
    pDirector->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
