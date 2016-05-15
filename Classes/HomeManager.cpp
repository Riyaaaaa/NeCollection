//
//  HomeManager.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2016/05/14.
//
//

#include "HomeManager.hpp"
#include "UserData.hpp"
#include "params.h"

USING_NS_CC;

HomeManager::HomeManager() {
    for(int i = 0; i < params::NUMBER_OF_PRODUCT_TYPES; i++) {
        _scene->setCatObjectCallback([=](Ref* ref){
            setEnableCatObject(false,static_cast<PRODUCTS>(i));
            getCat(lotteryCat());
        },static_cast<PRODUCTS>(i));
    }
}

void HomeManager::runScene() {
    GameManagerBase<HomeManager, HomeScene>::runScene();
    for(int i = 0; i < params::NUMBER_OF_PRODUCT_TYPES; i++) {
        setEnableCatObject( _scene->getCatObjectStatuses()[i].isComing, static_cast<PRODUCTS>(i) );
    }
}

void HomeManager::comeCat(){
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<int> dist(0,3);
    
    PRODUCTS index = static_cast<PRODUCTS>(dist(mt));
    
    if(!_scene->getCatObjectStatuses()[static_cast<int>(index)].isComing){
        setEnableCatObject(true,index);
    }
}

void HomeManager::getCat(int id){
    /* get cat event */
    Cat cat = _db->getCatById(id);
    Scene* newScene = Scene::create();
    
    /* todo: add some effects */
    Node* resultScene = (CSLoader::getInstance()->createNode("result/GetResultScene.csb"));
    ui::Text* message = resultScene->getChildByName("Window")->getChildByName<ui::Text*>("Message");
    
    message->setString(cat.getDiscription());
    
    Sprite* sprite = Sprite::create(Cat::neko_id_to_string(id));
    resultScene->addChild(sprite);
    sprite->setPosition(Director::getInstance()->getVisibleSize()/2);
    
    newScene->addChild(resultScene);
    Director::getInstance()->pushScene(newScene);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](Touch* touch,Event* event){Director::getInstance()->popScene(); return true;};
    listener->setSwallowTouches(true);
    
    resultScene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, message);
    
    UserData::getInstance()->addCats(id);
}

void HomeManager::setEnableCatObject(bool is_enabled,PRODUCTS identify){
    /* set enable comming cat event on cat object  */
    auto& btn = _scene->getCatObjectButtons()[static_cast<int>(identify)];
    auto& status = _scene->getCatObjectStatuses()[static_cast<int>(identify)];
    if(is_enabled){
        auto* alert = Sprite::create("res/utility/utility_ui.png",Rect(params::ALERT_X,params::ALERT_Y,params::UTILITY_SIZE,params::UTILITY_SIZE));
        btn->setEnabled(true);
        status.isComing = true;
        btn->addChild(alert,1,"alert");
        alert->setPosition(Vec2(btn->getContentSize().width, btn->getContentSize().height));
    }
    else{
        btn->setEnabled(false);
        status.isComing = false;
        auto* alert = btn->getChildByName<Sprite*>("alert");
        if(alert) alert->removeFromParent();
    }
    
    
}

void HomeManager::saveScheduleTime(){
    /* write scheduling time to plist file */
    auto* tiny_data = UserDefault::getInstance();
    std::time_t timer;
    struct std::tm *t_st;
    
    std::time(&timer);
    t_st = localtime(&timer);
    int previous_time = t_st->tm_sec + t_st->tm_min * 60 + t_st->tm_hour * 3600;
    CCLOG("previous time = %d",previous_time);
    
    tiny_data->setIntegerForKey("previous_time", previous_time);
    tiny_data->setIntegerForKey("time",_remain_event_time);
}

void HomeManager::saveObjectStatus(){
    /* write status of cat object to binary file */
    auto* tiny_data = UserDefault::getInstance();
    
    cocos2d::Data data;
    data.copy(reinterpret_cast<unsigned char*>(&_scene->getCatObjectStatuses()[0]), sizeof(CatObjectStatus)*4);
    
    tiny_data->setDataForKey("CatObjectStatuses",data);
}

int HomeManager::lotteryCat(){
    /* todo: add lottery modules */
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> dist(0,params::NUMBER_OF_CATS);
    
    return dist(mt);
}
