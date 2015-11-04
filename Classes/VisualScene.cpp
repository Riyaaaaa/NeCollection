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
#include "params.h"

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
    
    if( !initUI() || !initVisualDictionary()){
        return false;
    }
    return true;
}

bool VisualScene::initVisualDictionary(){
    const int CONTENTS_MARGIN = 10;
    dbIO* db = dbIO::getInstance();
    
    cocos2d::Node* dictionary_bg = _scene->getChildByName("DictionaryView");
    Size visual_size = dictionary_bg->getContentSize();
    
    for(int i=0; i<params::NUMBER_OF_CATS;){
        for(int j=0; j<3 && i<params::NUMBER_OF_CATS ; j++){
            Sprite* visual_contents = Sprite::create("cat/" + db->getCatById(i).name + ".png");
            Size contents_size = visual_contents->getContentSize();
            dictionary_bg->addChild(visual_contents);
            visual_contents->setAnchorPoint(Vec2(0,1));
            visual_contents->setPosition((visual_size.width/3) * j + CONTENTS_MARGIN,
                                         visual_size.height - (contents_size.height + CONTENTS_MARGIN) * (i/3));
            i++;
        }
    }
    
    return true;
}