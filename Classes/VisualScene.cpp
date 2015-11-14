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
    const int CONTENTS_MARGIN = 10;
    dbIO* db = dbIO::getInstance();
    
    ui::ScrollView* dictionary_bg = _scene->getChildByName<ui::ScrollView*>("DictionaryView");
    
    auto* innerContainer = LayerColor::create(Color4B::RED);
    innerContainer->setAnchorPoint(Vec2(0,1));
    dictionary_bg->addChild(innerContainer);
    dictionary_bg->setInnerContainerPosition(Vec2(0,dictionary_bg->getContentSize().height));
    dictionary_bg->setInnerContainerSize( Size(dictionary_bg->getContentSize().width,
                                         (VISUAL_CONTENTS_SIZE + CONTENTS_MARGIN) * (NUMBER_OF_CATS/3)
                                         )
                                   );
    
    Size visual_size = innerContainer->getContentSize();
    
    for(int i=0; i<params::NUMBER_OF_CATS;){
        for(int j=0; j<3 && i<params::NUMBER_OF_CATS ; j++){
            auto file_path = Cat::neko_id_to_string(i);
            Sprite* visual_contents = Sprite::create(file_path);
            Size contents_size = visual_contents->getContentSize();
            innerContainer->addChild(visual_contents);
            visual_contents->setAnchorPoint(Vec2(0,1));
            visual_contents->setPosition((visual_size.width/3) * j + CONTENTS_MARGIN,
                                         visual_size.height - (contents_size.height + CONTENTS_MARGIN) * (i/3));
            i++;
        }
    }
    
    return true;
}