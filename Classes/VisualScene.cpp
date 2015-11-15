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
    Size visibleSize = Director::getInstance()->getVisibleSize();

    ui::ScrollView* dictionary_bg = ui::ScrollView::create();
    dictionary_bg->setAnchorPoint(Vec2(0,1));
    dictionary_bg->setPosition(Vec2(0,visibleSize.height-_scene->getChildByName("title")->getContentSize().height));
    dictionary_bg->setDirection(ui::ScrollView::Direction::VERTICAL);
    _scene->addChild(dictionary_bg);
    
    auto* innerContainer = LayerColor::create(Color4B(128,128,128,128));
    innerContainer->setAnchorPoint(Vec2(0,1));
    innerContainer->setContentSize(Size(visibleSize.width,
                                        (VISUAL_CONTENTS_SIZE + CONTENTS_MARGIN) * (NUMBER_OF_CATS/3+1)
                                        )
                                   );
    dictionary_bg->addChild(innerContainer);
    
    dictionary_bg->setInnerContainerSize( Size(visibleSize.width,
                                               (VISUAL_CONTENTS_SIZE + CONTENTS_MARGIN) * (NUMBER_OF_CATS/3+1)
                                               )
                                         );
    dictionary_bg->setContentSize(Size(visibleSize.width,visibleSize.height
                                       -_scene->getChildByName("title")->getContentSize().height
                                       -_scene->getChildByName("Menu")->getContentSize().height));
    dictionary_bg->setInnerContainerPosition(Vec2(0,visibleSize.height-_scene->getChildByName("title")->getContentSize().height));
    //dictionary_bg->setInnerContainerPosition(Vec2(0,dictionary_bg->getContentSize().height));
    
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
    
    CCLOG("Dictionary Size=(%f,%f)",dictionary_bg->getContentSize().width,dictionary_bg->getContentSize().height);
    CCLOG("Visual Size=(%f,%f)",innerContainer->getContentSize().width,innerContainer->getContentSize().height);
    return true;
}