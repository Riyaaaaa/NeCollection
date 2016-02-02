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
#include "cocostudio/CocoStudio.h"
#include "HomeScene.hpp"
#include "Utility.hpp"
#include "params.h"
#include "Cat.hpp"

USING_NS_CC;

Scene* VisualScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    scene->addChild(VisualScene::create(),SCENE,"VisualScene");
    
    // return the scene
    return scene;
}

bool VisualScene::init(){
    
    if ( !MainScene::init("dictionary/VisualScene.csb") )
    {
        return false;
    }
    
    if(!initVisualDictionary()){
        return false;
    }
    return true;
}

bool VisualScene::initVisualDictionary(){
    Node* title = _scene->getChildByName("title");
    BoxLayerForVisual* box = BoxLayerForVisual::create(Size(Director::getInstance()->getVisibleSize()
                                                            - Size(0,title->getContentSize().height) - Size(0,_scene->getChildByName("Menu")->getContentSize().height))
                                          );
    box->setAnchorPoint(Vec2(0,1));
    this->addChild(box);
    box->setPosition(Vec2(0,Director::getInstance()->getVisibleSize().height
                                -title->getContentSize().height));

        return true;
}