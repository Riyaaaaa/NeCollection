//
//  HomeScene.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/27.
//
//

#include "HomeScene.hpp"
#include "ShopScene.hpp"
#include "VisualScene.hpp"
#include "params.h"
#include "Utility.hpp"
#include "UserData.hpp"
#include "Cat.hpp"
#include <ctime>

USING_NS_CC;

Scene* HomeScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    /*
     auto* titleScene = Sprite::create("title.png");
     CCLOG("%f %f",titleScene->getContentSize().width,titleScene->getContentSize().height);
     titleScene->setAnchorPoint(Vec2(0.5,0.5));
     titleScene->setPosition(size/2);
     */
    
    scene->addChild(HomeScene::create(),SCENE,"HomeScene");
    
    // return the scene
    return scene;
}


bool HomeScene::init()
{
    if ( !MainScene::init("home/HomeScene.csb") )
    {
        return false;
    }
    
    _home_bg = _scene->getChildByName<Sprite*>("home_bg");
    
    if(!initUI() || !initStatus()){
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HomeScene::onTouchBegin,this);
    listener->onTouchMoved = CC_CALLBACK_2(HomeScene::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(HomeScene::onTouchEnded,this);
    listener->onTouchCancelled = CC_CALLBACK_2(HomeScene::onTouchCancelled,this);
    
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    schedule(schedule_selector(HomeScene::update),1.0f);
    
    _db = dbIO::getInstance();
    
    refreshScene();
    
    return true;
}

bool HomeScene::initUI(){
    
    _scene->getChildByName("MoneyUI")->getChildByName("money_plate")->getChildByName<ui::Text*>("money")->setText(std::to_string(UserDefault::getInstance()->getIntegerForKey("money")));
    
    return true;
}

void HomeScene::replaceSceneWithName(std::string filename){
    CCLOG("filename = %s",filename.c_str());
    auto* next_scene = CSLoader::getInstance()->createNode(filename);
    auto* scene = Scene::create();
    
    scene->addChild(next_scene);
    
    Director::getInstance()->replaceScene(scene);
}

bool HomeScene::initStatus(){
    auto* tiny_data = UserDefault::getInstance();
    
    _cat_objects.resize(4);

    _cat_objects[static_cast<int>(CAT_OBJECT::TOY)]
        = _home_bg->getChildByName<ui::Button*>("toy");
    _cat_objects[static_cast<int>(CAT_OBJECT::TOY)]->addClickEventListener([&](Ref* ref){
        disenableCatObject(_cat_objects[static_cast<int>(CAT_OBJECT::TOY)]);
        getCat(lotteryCat());
        }
                                                                           );
    if(tiny_data->getBoolForKey("isCommingToy"))
        enableCatObject(_cat_objects[static_cast<int>(CAT_OBJECT::TOY)]);
    else
        disenableCatObject(_cat_objects[static_cast<int>(CAT_OBJECT::TOY)]);
    
    _cat_objects[static_cast<int>(CAT_OBJECT::MEAL)]
        = _home_bg->getChildByName<ui::Button*>("meal");
    _cat_objects[static_cast<int>(CAT_OBJECT::MEAL)]->addClickEventListener([&](Ref* ref){
        disenableCatObject(_cat_objects[static_cast<int>(CAT_OBJECT::MEAL)]);
        getCat(lotteryCat());
    }
                                                                            );
    if(tiny_data->getBoolForKey("isCommingMeal"))
        enableCatObject(_cat_objects[static_cast<int>(CAT_OBJECT::MEAL)]);
    else
        disenableCatObject(_cat_objects[static_cast<int>(CAT_OBJECT::MEAL)]);
    
    _cat_objects[static_cast<int>(CAT_OBJECT::FUTON)]
        = _home_bg->getChildByName<ui::Button*>("futon");
    _cat_objects[static_cast<int>(CAT_OBJECT::FUTON)]->addClickEventListener([&](Ref* ref){
        disenableCatObject(_cat_objects[static_cast<int>(CAT_OBJECT::FUTON)]);
        getCat(lotteryCat());
    }
                                                                             );
    if(tiny_data->getBoolForKey("isCommingFuton"))
        enableCatObject(_cat_objects[static_cast<int>(CAT_OBJECT::FUTON)]);
    else
        disenableCatObject(_cat_objects[static_cast<int>(CAT_OBJECT::FUTON)]);
    
    
    _cat_objects[static_cast<int>(CAT_OBJECT::TRIMMER)]
        = _home_bg->getChildByName<ui::Button*>("trimmer");
    _cat_objects[static_cast<int>(CAT_OBJECT::TRIMMER)]->addClickEventListener([&](Ref* ref){
        disenableCatObject(_cat_objects[static_cast<int>(CAT_OBJECT::TRIMMER)]);
        getCat(lotteryCat());
    }
                                                                               
                                                                               );
    if(tiny_data->getBoolForKey("isCommingTrimmer"))
        enableCatObject(_cat_objects[static_cast<int>(CAT_OBJECT::TRIMMER)]);
    else
        disenableCatObject(_cat_objects[static_cast<int>(CAT_OBJECT::TRIMMER)]);
    
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
        enableCatObject(target);
    }
}

void HomeScene::disenableCatObject(cocos2d::ui::Button* btn){
    btn->setEnabled(false);
    auto* alert = btn->getChildByName<Sprite*>("alert");
    if(alert)alert->removeFromParent();
}

void HomeScene::enableCatObject(ui::Button* btn){
    auto* alert = Sprite::create("res/utility/utility_ui.png",Rect(params::ALERT_X,params::ALERT_Y,params::UTILITY_SIZE,params::UTILITY_SIZE));
    btn->setEnabled(true);
    btn->addChild(alert,1,"alert");
    
    alert->setPosition(Vec2(btn->getContentSize().width,btn->getContentSize().height));
}

void HomeScene::getCat(int id){
    Cat cat = _db->getCatById(id);
    Scene* newScene = Scene::create();
    
    Node* resultScene = (CSLoader::getInstance()->createNode("result/GetResultScene.csb"));
    ui::Text* message = resultScene->getChildByName("Window")->getChildByName<ui::Text*>("Message");
    
    message->setString(cat.discription);
    
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

void HomeScene::saveScheduleTime(){
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

void HomeScene::saveObjectStatus(){
    auto* tiny_data = UserDefault::getInstance();
    
    tiny_data->setBoolForKey("isCommingToy", _cat_objects[static_cast<int>(CAT_OBJECT::TOY)]->isEnabled());
    tiny_data->setBoolForKey("isCommingMeal", _cat_objects[static_cast<int>(CAT_OBJECT::MEAL)]->isEnabled());
    tiny_data->setBoolForKey("isCommingTrimmer", _cat_objects[static_cast<int>(CAT_OBJECT::TRIMMER)]->isEnabled());
    tiny_data->setBoolForKey("isCommingFuton", _cat_objects[static_cast<int>(CAT_OBJECT::FUTON)]->isEnabled());
}

bool HomeScene::onTouchBegin(cocos2d::Touch* touch,cocos2d::Event* event){
    _old_pos = touch->getLocation();
    return true;
}

void HomeScene::onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event){
    Vec2 new_pos = touch->getLocation();
    Vec2 delta_pos = new_pos - _old_pos;
    _old_pos = new_pos;
    
    new_pos = _home_bg->getPosition() +  Vec2(delta_pos.x,0);
    if(new_pos.x > 520)new_pos.x = 520;
    else if(new_pos.x < 120)new_pos.x = 120;
    _home_bg->setPosition(Vec2(new_pos));
    
}
void HomeScene::onTouchEnded(cocos2d::Touch*,cocos2d::Event*){
}

void HomeScene::onTouchCancelled(cocos2d::Touch* touch,cocos2d::Event* unused_event){
    onTouchEnded(touch,unused_event);
}

int HomeScene::lotteryCat(){
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> dist(0,params::NUMBER_OF_CATS);
    
    return dist(mt);
}

void HomeScene::refreshScene(){
    auto* tiny_data = UserDefault::getInstance();
    std::time_t timer;
    struct std::tm *t_st;
    
    std::time(&timer);
    t_st = localtime(&timer);
    int current_time = t_st->tm_sec + t_st->tm_min * 60 + t_st->tm_hour * 3600;
    int elapsed_time = current_time - tiny_data->getIntegerForKey("previous_time");
    CCLOG("elapsed time = %d",elapsed_time);
    
    tiny_data->setIntegerForKey("previous_time", current_time);
    _remain_event_time = tiny_data->getIntegerForKey("time") + elapsed_time;
}

HomeScene::~HomeScene(){
    saveScheduleTime();
    saveObjectStatus();
}
