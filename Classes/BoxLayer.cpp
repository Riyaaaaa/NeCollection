//
//  BoxLayer.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/15.
//
//

#include "BoxLayer.hpp"
#include "UserData.hpp"
#include "Cat.hpp"

USING_NS_CC;

BoxLayer* BoxLayer::create(){
    BoxLayer* pRet = new BoxLayer();
    
    if(pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete  pRet;
        pRet = NULL;
        return NULL;
    }
}

bool BoxLayer::init(){
    if(!Layer::init()){
        return false;
    }
    
    _layer = CSLoader::getInstance()->createNode("box/BoxLayer.csb");
    addChild(_layer);

    Sprite* retButton = Sprite::create("utility/utility_ui.png",Rect(params::L_ARROW_X,params::L_ARROW_Y,params::UTILITY_SIZE,params::UTILITY_SIZE));
    _layer->addChild(retButton);
    retButton->setAnchorPoint(Vec2(0,0.5));
    retButton->setPosition(Vec2(0,_layer->getChildByName("title")->getPosition().y));
    
    auto* lisener = EventListenerTouchOneByOne::create();
    lisener->onTouchBegan = [=](Touch* touch,Event* event){ this->removeFromParent(); return true; };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(lisener,this);
    
    if(!initCats()){
        return false;
    }
    
    return true;
}

bool BoxLayer::initCats(){
    _cat_list = UserData::getInstance()->getCats();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _dictionary_bg = ui::ScrollView::create();
    _dictionary_bg->setAnchorPoint(Vec2(0,1));
    _dictionary_bg->setPosition(Vec2(0,visibleSize.height-_layer->getChildByName("title")->getContentSize().height));
    _dictionary_bg->setDirection(ui::ScrollView::Direction::VERTICAL);
    _layer->addChild(_dictionary_bg);
    
    const int CONTENTS_MARGIN = 20;
    
    auto* innerContainer = LayerColor::create(Color4B(128,128,128,128));
    innerContainer->setAnchorPoint(Vec2(0,1));
    innerContainer->setContentSize(Size(visibleSize.width,
                                        (VISUAL_CONTENTS_SIZE + CONTENTS_MARGIN) * (NUMBER_OF_CATS/3+1)
                                        )
                                   );
    _dictionary_bg->addChild(innerContainer);
    
    _dictionary_bg->setInnerContainerSize( Size(visibleSize.width,
                                               (VISUAL_CONTENTS_SIZE + CONTENTS_MARGIN) * (NUMBER_OF_CATS/3+1)
                                               )
                                         );
    _dictionary_bg->setContentSize(Size(visibleSize.width,visibleSize.height
                                       -_layer->getChildByName("title")->getContentSize().height));
    _dictionary_bg->setInnerContainerPosition(Vec2(0,visibleSize.height-_layer->getChildByName("title")->getContentSize().height));
    //_dictionary_bg->setInnerContainerPosition(Vec2(0,_dictionary_bg->getContentSize().height));
    
    Size visual_size = innerContainer->getContentSize();
    
    for(int i=0; i<params::NUMBER_OF_CATS;){
        for(int j=0; j<3 && i<params::NUMBER_OF_CATS ; j++){
            auto file_path = Cat::neko_id_to_string(i);
            CatIcon* visual_contents = CatIcon::create(i);
            Size contents_size = visual_contents->getContentSize();
            innerContainer->addChild(visual_contents);
            visual_contents->setAnchorPoint(Vec2(0,1));
            visual_contents->setPosition(Vec2((visual_size.width/3) * j + CONTENTS_MARGIN,
                                               visual_size.height - (contents_size.height + CONTENTS_MARGIN) * (i/3)));
            i++;
        }
    }
    
    return true;
}

BoxLayerForSell* BoxLayerForSell::create(int max_select_cats){
    BoxLayerForSell* pRet = new BoxLayerForSell();
    
    if(pRet && pRet->init(max_select_cats)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete  pRet;
        pRet = NULL;
        return NULL;
    }
}

bool BoxLayerForSell::init(int max_select_cats){
    
    if(!BoxLayer::init()){
        return false;
    }
    
    auto& contents = _dictionary_bg->getChildren();
    for(auto* content: contents){
        CatIcon* ico = dynamic_cast<CatIcon*>(content);
        ico->addClickEventListener([=](Ref* ref){
            if(!ico->getSelect() && _current_selected_cats == _max_select_cats)return;
            ico->changeState();
            if(ico->getSelect())_current_selected_cats--;
            else _current_selected_cats++;
        });
    }
    
    _max_select_cats = max_select_cats;
    return true;
}
