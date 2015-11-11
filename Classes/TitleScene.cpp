#include "TitleScene.h"
#include "ui/CocosGUI.h"
#include "HomeScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "AppDelegate.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    Size size = Director::getInstance()->getVisibleSize();
    
    FileUtils::getInstance()->addSearchPath("res/");
    
    /*
    auto* titleScene = Sprite::create("title.png");
    CCLOG("%f %f",titleScene->getContentSize().width,titleScene->getContentSize().height);
    titleScene->setAnchorPoint(Vec2(0.5,0.5));
    titleScene->setPosition(size/2);
     */
    
    auto titleScene = CSLoader::getInstance()->createNode("res/TitleScene.csb");
    
    auto* button = titleScene->getChildByName<ui::Button*>("SButton");
    button->addClickEventListener([](Ref* ref){
        ((AppDelegate*)Application::getInstance())->launchGame();
    });
    
    CCLOG("%f %f",size.width,size.height);
     
    titleScene->setContentSize(size);
    cocos2d::ui::Helper::doLayout(titleScene);
    
    scene->addChild(titleScene);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    return true;
}


void TitleScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
