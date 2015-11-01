//
//  ShopScene.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/27.
//
//

#include "ShopScene.hpp"
#include "VisualScene.hpp"
#include "ui/CocosGUI.h"
#include "HomeScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "Utility.hpp"

USING_NS_CC;

Scene* ShopScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    Size size = Director::getInstance()->getVisibleSize();
    
    scene->addChild(ShopScene::create());
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ShopScene::init()
{
    //////////////////////////////
    // 1. super init first
    
    _shop_scene = CSLoader::getInstance()->createNode("shop/ShopScene.csb");
    Size size = Director::getInstance()->getVisibleSize();

    _shop_scene->setContentSize(size);
    cocos2d::ui::Helper::doLayout(_shop_scene);
    addChild(_shop_scene);
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    if( !initUI() ){
        return false;
    }
    
    return true;
}

bool ShopScene::initUI(){
    auto initMenuButton = [&](auto* scene,std::string button){
        _shop_scene->getChildByName("Menu")->
        getChildByName<ui::Button*>(button)->
        addClickEventListener([=](Ref* ref){
            auto* next_scene = remove_ptr_t<decltype(scene)>::createScene();
            Director::getInstance()->replaceScene(next_scene);
        });
    };
    
    initMenuButton( reinterpret_cast<HomeScene*>(0),"home");
    initMenuButton( reinterpret_cast<ShopScene*>(0),"shop");
    //initMenuButton("shop","shop/ShopScene.csb");
    initMenuButton( reinterpret_cast<VisualScene*>(0),"dictionary");
    //initMenuButton("battle","battle/BattleScene.csb");
    
    return true;
}

void ShopScene::replaceSceneWithName(std::string filename){
    auto* next_scene = CSLoader::getInstance()->createNode(filename);
    auto* scene = Scene::create();
    
    scene->addChild(next_scene);
    
    Director::getInstance()->replaceScene(scene);
}
