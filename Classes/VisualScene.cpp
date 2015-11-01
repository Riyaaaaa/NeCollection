//
//  VisualScene.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/01.
//
//

#include "VisualScene.hpp"
#include "ShopScene.hpp"
#include "ui/CocosGUI.h"
#include "HomeScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "Utility.hpp"

USING_NS_CC;

Scene* VisualScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    Size size = Director::getInstance()->getVisibleSize();
    
    scene->addChild(VisualScene::create());
    
    // return the scene
    return scene;
}

bool VisualScene::init(){
    _scene = CSLoader::getInstance()->createNode("dictionary/VisualScene.csb");
    Size size = Director::getInstance()->getVisibleSize();
    
    _scene->setContentSize(size);
    cocos2d::ui::Helper::doLayout(_scene);
    addChild(_scene);
    
    if ( !Layer::init() )
    {
        return false;
    }
    
    if( !initUI() ){
        return false;
    }
    return true;
}