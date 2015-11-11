//
//  MainScene.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/02.
//
//

#include "MainScene.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Utility.hpp"
#include "HomeScene.hpp"
#include "ShopScene.hpp"
#include "VisualScene.hpp"

USING_NS_CC;

bool MainScene::initMainMenu(){
    auto initMenuButton = [&](auto* scene,std::string button){
        _scene->getChildByName("Menu")->
        getChildByName<ui::Button*>(button)->
        addClickEventListener([=](Ref* ref){
            auto* next_scene = remove_ptr_t<decltype(scene)>::createScene();
            Director::getInstance()->replaceScene(next_scene);
        });
    };
    
    initMenuButton( reinterpret_cast<HomeScene*>(0),"home");
    initMenuButton( reinterpret_cast<ShopScene*>(0),"shop");
    initMenuButton( reinterpret_cast<VisualScene*>(0),"dictionary");
    return true;
}

bool MainScene::init(std::string filename){
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    
    _scene = CSLoader::getInstance()->createNode(filename);
    _scene->setContentSize(size);
    cocos2d::ui::Helper::doLayout(_scene);
    addChild(_scene);
    
    initMainMenu();
    return true;
}
