//
//  Cat.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/01.
//
//

#include "Cat.hpp"
#include "dbIO.hpp"

USING_NS_CC;

Cat::Cat(int id):_id(id){
    *this = dbIO::getInstance()->getCatById( id );
}

CatIcon* CatIcon::create(int id){
    CatIcon* pRet = new CatIcon(id);
    
    if(pRet && pRet->init(id)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete  pRet;
        pRet = NULL;
        return NULL;
    }
}

bool CatIcon::init(int id){
    if(!ui::Button::init()){
        return false;
    }
    ui::Button::loadTextureNormal(Cat::neko_id_to_string(id));
    ui::Button::loadTexturePressed(Cat::neko_id_to_string(id));
    
    _touchListener->setSwallowTouches(false);
    _touchListener->onTouchBegan = [=](Touch* touch,Event* event){
        Node* scrollview=nullptr;
        for(Node* parent=getParent(); parent!=nullptr && scrollview==nullptr; parent=parent->getParent()){
            scrollview = dynamic_cast<ui::ScrollView*>(parent);
        }
        if(scrollview && scrollview->getBoundingBox().containsPoint(touch->getLocation())){
            return ui::Widget::onTouchBegan(touch, event);
        }
        else return true;
    };
    _touchListener->onTouchEnded = [=](Touch* touch,Event* event){
        constexpr int leave_length = 10;
        if((touch->getLocation() - touch->getStartLocation()).length() < leave_length){
            ui::Widget::onTouchEnded(touch, event);
        }
    };
    
    return true;
}

void CatIcon::setSelect(bool isSelected){
    _isSelected = isSelected;
    
    if(_isSelected){
        auto* sprite = Sprite::create("utility/selected.png");
        addChild(sprite,0,"selected");
        sprite->setPosition(this->getContentSize()/2);
    }
    else{
        removeChildByName("selected");
    }
}

void CatIcon::setTouchEnabled(bool enable)
{
    if (enable == _touchEnabled)
    {
        return;
    }
    _touchEnabled = enable;
    if (_touchEnabled)
    {
        _touchListener = EventListenerTouchOneByOne::create();
        CC_SAFE_RETAIN(_touchListener);
        _touchListener->setSwallowTouches(false);
        _touchListener->onTouchBegan = CC_CALLBACK_2(Widget::onTouchBegan, this);
        _touchListener->onTouchMoved = CC_CALLBACK_2(Widget::onTouchMoved, this);
        _touchListener->onTouchEnded = CC_CALLBACK_2(Widget::onTouchEnded, this);
        _touchListener->onTouchCancelled = CC_CALLBACK_2(Widget::onTouchCancelled, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    }
    else
    {
        _eventDispatcher->removeEventListener(_touchListener);
        CC_SAFE_RELEASE_NULL(_touchListener);
    }
}
