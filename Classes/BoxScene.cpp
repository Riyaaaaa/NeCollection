//
//  BoxScene.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/12.
//
//

#include "BoxScene.hpp"

USING_NS_CC;

Scene* BoxScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    scene->addChild(BoxScene::create(),SCENE,"VisualScene");
    
    // return the scene
    return scene;
}

bool BoxScene::init(){
    
    if ( !MainScene::init("dictionary/VisualScene.csb") )
    {
        return false;
    }
    
    if(!initBox()){
        return false;
    }
    return true;
}

bool BoxScene::initBox(){
    
    
    return true;
}
