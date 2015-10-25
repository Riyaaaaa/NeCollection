#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    auto titleScene = CSLoader::getInstance()->createNode("res/TitleScene.csb");
    auto textButton = titleScene->getChildByName<cocos2d::ui::Button*>("SButton");

    textButton->setTitleText("AAA");
    
    Size size = Director::getInstance()->getWinSize();
    titleScene->setContentSize(size);
    cocos2d::ui::Helper::doLayout(titleScene);
    
    // add layer as a child to scene
    scene->addChild(titleScene);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
