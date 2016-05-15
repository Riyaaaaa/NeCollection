//
//  HomeScene.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/27.
//
//

#include "HomeScene.hpp"
#include "ShopScene.hpp"
#include "ModalWindow.hpp"
#include "VisualScene.hpp"
#include "params.h"
#include "Utility.hpp"
#include "UserData.hpp"
#include "Cat.hpp"
#include <ctime>

USING_NS_CC;

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
    return true;
}

bool HomeScene::initUI(){
    
    _scene->getChildByName("MoneyUI")->getChildByName("money_plate")->getChildByName<ui::Text*>("money")->setString(std::to_string(UserDefault::getInstance()->getIntegerForKey("money")));
    
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
    cocos2d::Data data = tiny_data->getDataForKey("CatObjectStatuses");
    memcpy(&_cat_object_status[0], data.getBytes(), data.getSize());
    
    _cat_objects.resize(params::NUMBER_OF_PRODUCT_TYPES);
    
    for(int i=0; i<params::NUMBER_OF_PRODUCT_TYPES; i++){
        setCatObject(static_cast<PRODUCTS>(i), _cat_object_status[i].id);
    }
    
    auto* redecorate = _scene->getChildByName<ui::Button*>("redecorate");
    
    redecorate->addClickEventListener([=](Ref* ref){
        this->setRedecorateWindow();
            });

    return true;
}

void HomeScene::setRedecorateWindow(){
    if(!_redecorate_window){
        
        /* crate node from binary files */
        _redecorate_window = CSLoader::createNode("home/Redecorate_Window.csb");
        /* set node propaty*/
        _redecorate_window->ignoreAnchorPointForPosition(false);
        _redecorate_window->setAnchorPoint(Vec2(0.5,0.5));
        
        /* set redecorate window layout */
        for(int i=0; i<params::NUMBER_OF_PRODUCT_TYPES; i++){
            Sprite* right_arrow = Sprite::create("utility/utility_ui.png",
                                                 Rect(params::R_ARROW_X,params::R_ARROW_Y,params::UTILITY_SIZE,params::UTILITY_SIZE));
            Sprite* left_arrow= Sprite::create("utility/utility_ui.png",
                                               Rect(params::L_ARROW_X,params::L_ARROW_Y,params::UTILITY_SIZE,params::UTILITY_SIZE));
            
            MenuItemSprite* r_button = MenuItemSprite::create(right_arrow,   right_arrow, [=](Ref*){ CCLOG( "%d th rbutton",i ); }  );
            MenuItemSprite* l_button = MenuItemSprite::create(left_arrow ,   left_arrow , [=](Ref*){ CCLOG( "%d th lbutton",i ); }  );
            
            Node* cat_object = _redecorate_window->getChildByName("Plate")->getChildByTag(100 + i);
            Vec2 pos = cat_object->getPosition();
            Size size = cat_object->getContentSize();
            
            _redecorate_window->addChild( r_button   );
            _redecorate_window->addChild( l_button   );
            
            r_button->setPosition(   pos - Size( size.width/2, 0 ) - Size(0, size.height/2) );
            l_button->setPosition(   pos + Size( size.width/2, 0 ) - Size(0, size.height/2) );
        }
        
        addChild(_redecorate_window);
        _redecorate_window->setPosition( Director::getInstance()->getVisibleSize()/2.0f );
    }
    else {
        _redecorate_window->removeFromParent();
        _redecorate_window=nullptr;
    }

}

void HomeScene::setCatObject(PRODUCTS product,int id){
    /* rerender cat object graphics and set event listener*/
    _cat_objects[static_cast<int>(product)] = dynamic_cast<ui::Button*>(_home_bg->getChildByTag( 100 + static_cast<int>(product) ));
    
    _cat_objects[static_cast<int>(product)]->loadTextures("products/"+ fill_zero(id) + ".png",
                                                          "products/"+ fill_zero(id) + ".png" );
    
}

void HomeScene::setCatObjectCallback(std::function<void(Ref*)> callback, PRODUCTS product) {
    _cat_objects[static_cast<int>(product)]->addClickEventListener(callback);
}

void HomeScene::update(float dt){
    _remain_event_time += dt;
    
    while(true){
        if(_remain_event_time > OCCURRE_EVENT_TIME){
            if(_callback) _callback(EventType::OCCURED_EVENT_TIME);
            _remain_event_time -= OCCURRE_EVENT_TIME;
            if(_remain_event_time < 0) _remain_event_time = 0;
        }
        else break;
    }
}

bool HomeScene::onTouchBegin(cocos2d::Touch* touch,cocos2d::Event* event){
    _old_pos = touch->getLocation();
    return true;
}

void HomeScene::onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event){
    /* move background image */
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

void HomeScene::onEnter(){
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

void HomeScene::onExit() {
    auto* tiny_data = UserDefault::getInstance();
    tiny_data->setIntegerForKey("time",_remain_event_time);
}
