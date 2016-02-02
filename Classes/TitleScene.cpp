#include "TitleScene.h"
#include "ui/CocosGUI.h"
#include "HomeScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "AppDelegate.h"

USING_NS_CC;

cocos2d::Node* TitleScene::_titlescene;

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
    
    _titlescene = CSLoader::getInstance()->createNode("res/TitleScene.csb");
    
    auto* button = _titlescene->getChildByName<ui::Button*>("SButton");
    button->addClickEventListener([](Ref* ref){
        ((AppDelegate*)Application::getInstance())->launchGame();
    });
    
    CCLOG("%f %f",size.width,size.height);
     
    _titlescene->setContentSize(size);
    cocos2d::ui::Helper::doLayout(_titlescene);
    
    scene->addChild(_titlescene);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    
    beginAnimation();
    
    return true;
}

void TitleScene::beginAnimation(){
    
    
    cocos2d::Node* neko = _titlescene->getChildByName("neko");
    
    Animation *animation = Animation::create();
    for(int i=1; i<21; i++){
        animation->addSpriteFrameWithFileName("top_neco/neko" + fill_zero(i) + ".png");
    }
    for(int i=20; i>=1; i--){
        animation->addSpriteFrameWithFileName("top_neco/neko" + fill_zero(i) + ".png");
    }
    
    animation->setRestoreOriginalFrame(true);
    animation->setDelayPerUnit(0.5f / 4.0f);
    
    Animate *animate = Animate::create(animation);
    RepeatForever *animated = RepeatForever::create(animate);
    neko->runAction(animated);

}


void TitleScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
