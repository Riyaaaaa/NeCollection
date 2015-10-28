//
//  ShopScene.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/27.
//
//

#include "ShopScene.hpp"
#include "ui/CocosGUI.h"
#include "ShopScene.hpp"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

Scene* ShopScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    Size size = Director::getInstance()->getVisibleSize();
    
    auto shopScene = CSLoader::getInstance()->createNode("res/ShopScene.csb");
    
    scene->addChild(shopScene);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ShopScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    return true;
}
