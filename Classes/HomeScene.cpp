//
//  HomeScene.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/27.
//
//

#include "HomeScene.hpp"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

Scene* HomeScene::createScene()
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
    
    auto homeScene = CSLoader::getInstance()->createNode("res/HomeScene.csb");
    
    homeScene->setContentSize(size);
    cocos2d::ui::Helper::doLayout(homeScene);
    
    scene->addChild(homeScene);
    
    // return the scene
    return scene;
}


bool HomeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    if( !initLayout() || !initStatus()){
        return false;
    }
    
    scheduleUpdate();
    
    return true;
}

bool HomeScene::initLayout(){return true;}
bool HomeScene::initStatus(){return true;}

void HomeScene::update(float dt){
    _remain_event_time -= dt;
    
    while(true){
        if(_remain_event_time < OCCURRE_EVENT_TIME){
            comeCat();
            _remain_event_time - OCCURRE_EVENT_TIME;
            if(_remain_event_time < 0) _remain_event_time = 0;
        }
        else break;
    }
}

void HomeScene::comeCat(){}

void HomeScene::saveScheduleTime(){
    auto* tiny_data = UserDefault::getInstance();
    
    tiny_data->setIntegerForKey("time",_remain_event_time);
}

