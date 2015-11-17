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
