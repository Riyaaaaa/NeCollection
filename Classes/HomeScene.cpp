//
//  HomeScene.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/27.
//
//

#include "HomeScene.hpp"
#include "params.h"

USING_NS_CC;

Scene* HomeScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    FileUtils::getInstance()->addSearchPath("res/");
    
    /*
     auto* titleScene = Sprite::create("title.png");
     CCLOG("%f %f",titleScene->getContentSize().width,titleScene->getContentSize().height);
     titleScene->setAnchorPoint(Vec2(0.5,0.5));
     titleScene->setPosition(size/2);
     */
    
    scene->addChild(HomeScene::create());
    
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
    
    Size size = Director::getInstance()->getVisibleSize();
    
    home_scene = CSLoader::getInstance()->createNode("home/HomeScene.csb");
    home_scene->setContentSize(size);
    cocos2d::ui::Helper::doLayout(home_scene);
    addChild(home_scene);
    
    if( !initLayout() || !initStatus()){
        return false;
    }
    
    home_bg = home_scene->getChildByName<Sprite*>("home_bg");
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HomeScene::onTouchBegin,this);
    listener->onTouchMoved = CC_CALLBACK_2(HomeScene::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(HomeScene::onTouchEnded,this);
    listener->onTouchCancelled = CC_CALLBACK_2(HomeScene::onTouchCancelled,this);
    
    listener->setSwallowTouches(true);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    schedule(schedule_selector(HomeScene::update),1.0f);
    
    return true;
}

bool HomeScene::initLayout(){return true;}
bool HomeScene::initStatus(){
    
    _cat_objects.resize(4);
    
    _cat_objects[static_cast<int>(CAT_OBJECT::TOY)]
        = home_scene->getChildByName<ui::Button*>("toy");
    _cat_objects[static_cast<int>(CAT_OBJECT::MEAL)]
        = home_scene->getChildByName<ui::Button*>("meal");
    _cat_objects[static_cast<int>(CAT_OBJECT::FUTON)]
        = home_scene->getChildByName<ui::Button*>("futon");
    _cat_objects[static_cast<int>(CAT_OBJECT::TRIMMER)]
        = home_scene->getChildByName<ui::Button*>("trimmer");
    
    return true;
}

void HomeScene::update(float dt){
    _remain_event_time += dt;
    
    while(true){
        if(_remain_event_time > OCCURRE_EVENT_TIME){
            comeCat();
            _remain_event_time -= OCCURRE_EVENT_TIME;
            if(_remain_event_time < 0) _remain_event_time = 0;
        }
        else break;
    }
}

void HomeScene::comeCat(){
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<int> dist(0,3);
    
    CAT_OBJECT index = static_cast<CAT_OBJECT>(dist(mt));
    auto* target = _cat_objects[static_cast<int>(index)];
    
    if(!target->isEnabled()){
        auto* alert = Sprite::create("res/utility/utility_ui.png",Rect(params::ALERT_X,params::ALERT_Y,params::UTILITY_SIZE,params::UTILITY_SIZE));
        target->setEnabled(true);
        
        target->addChild(alert);
        alert->setPosition(Vec2(target->getContentSize().width,0));
    }
}

void HomeScene::getCat(int id){
    
    Scene* resultScene = dynamic_cast<Scene*>(CSLoader::getInstance()->createNode("result/ResultScene.csb"));
    Director::getInstance()->pushScene(resultScene);
    
}

void HomeScene::saveScheduleTime(){
    auto* tiny_data = UserDefault::getInstance();
    
    tiny_data->setIntegerForKey("time",_remain_event_time);
}

bool HomeScene::onTouchBegin(cocos2d::Touch* touch,cocos2d::Event* event){
    _old_pos = touch->getLocation();
    return true;
}

void HomeScene::onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event){
    Vec2 new_pos = touch->getLocation();
    Vec2 delta_pos = new_pos - _old_pos;
    _old_pos = new_pos;
    
    new_pos = home_bg->getPosition() +  Vec2(delta_pos.x,0);
    if(new_pos.x > 520)new_pos.x = 520;
    else if(new_pos.x < 120)new_pos.x = 120;
    home_bg->setPosition(Vec2(new_pos));
    
}
void HomeScene::onTouchEnded(cocos2d::Touch*,cocos2d::Event*){
}

void HomeScene::onTouchCancelled(cocos2d::Touch* touch,cocos2d::Event* unused_event){
    onTouchEnded(touch,unused_event);
}

