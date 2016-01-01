//
//  ModalWindow.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/12/15.
//
//

#include "ModalWindow.hpp"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "UserData.hpp"

USING_NS_CC;

Modal_Window* Modal_Window::create(std::string filename){
    Modal_Window* pRet = new Modal_Window();
    
    if(pRet && pRet->init(filename)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete  pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Modal_Window::init(std::string filename){
    
    if(!LayerColor::initWithColor(Color4B(0,0,0,128))){
        return false;
    }
    
    _modal_window = CSLoader::getInstance()->createNode(filename);
    addChild(_modal_window);
    
    _modal_window->setAnchorPoint(Vec2(0.5,0.5));
    _modal_window->setPosition(getContentSize()/2);
    
    auto listner = EventListenerTouchOneByOne::create();
    listner->setSwallowTouches(true);
    listner->onTouchBegan = [](Touch*,Event*){return true;};
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listner,this);
    
    return true;
    
}

Confirm_Window* Confirm_Window::create(std::string filename){
    
    Confirm_Window* pRet = new Confirm_Window();
    
    if(pRet && pRet->init(filename)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete  pRet;
        pRet = NULL;
        return NULL;
    }
    
}

bool Confirm_Window::init(std::string filename){
    
    if(!Modal_Window::init(filename)){
        return false;
    }
    
    return true;
    
}

void Confirm_Window::setText(std::string text){
    _modal_window->getChildByName<ui::Text*>("text")->setString(text);
}

void Confirm_Window::setCallBackYes(std::function<void(cocos2d::Ref*)> callback){
    _modal_window->getChildByName<ui::Button*>("yes")->addClickEventListener(callback);
}

void Confirm_Window::setCallBackNo(std::function<void(cocos2d::Ref*)> callback){
    _modal_window->getChildByName<ui::Button*>("no")->addClickEventListener(callback);
}

Sell_Confirm_Window* Sell_Confirm_Window::create(int selling_price){
    Sell_Confirm_Window* pRet = new Sell_Confirm_Window();
    
    if(pRet && pRet->init(selling_price)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete  pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Sell_Confirm_Window::init(int selling_price){
    if(!Confirm_Window::init("UI/Confirm_Window.csb")){
        return false;
    }
    
    _selling_price = selling_price;
    
    int money = UserData::getInstance()->getMoney();
    
    _modal_window->getChildByName<ui::Text*>("before_money")->setString(std::to_string(money));
    _modal_window->getChildByName<ui::Text*>("after_money")->setString(std::to_string(money + selling_price));
    
    setText("本当に売る？");
    setCallBackNo( [=](cocos2d::Ref*){ this->removeFromParent(); } );
    
    
    return true;
}

Buy_Confirm_Window* Buy_Confirm_Window::create(int buying_price){
    Buy_Confirm_Window* pRet = new Buy_Confirm_Window();
    
    if(pRet && pRet->init(buying_price)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete  pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Buy_Confirm_Window::init(int buying_price){
    if(!Confirm_Window::init("UI/Confirm_Window.csb")){
        return false;
    }
    
    _buying_price = buying_price;
    
    int money = UserData::getInstance()->getMoney();
    
    _modal_window->getChildByName<ui::Text*>("before_money")->setString(std::to_string(money));
    _modal_window->getChildByName<ui::Text*>("after_money")->setString(std::to_string(money - buying_price));
    
    if(money - buying_price < 0){
        _modal_window->getChildByName<ui::Button*>("yes")->setEnabled(false);
        _modal_window->getChildByName<ui::Text*>("after_money")->setColor(Color3B::RED);
    }
    
    setText("本当に買う？");
    setCallBackNo( [=](cocos2d::Ref*){ this->removeFromParent(); } );
    
    
    return true;
}