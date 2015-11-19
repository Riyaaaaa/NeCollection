//
//  BoxLayer.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/15.
//
//

#include "BoxLayer.hpp"
#include "UserData.hpp"

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
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(lisener,this);
    
    if(!initCats()){
        return false;
    }
    
    return true;
}

bool BoxLayer::initCats(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _dictionary_bg = ui::ScrollView::create();
    _dictionary_bg->setAnchorPoint(Vec2(0,1));
    _dictionary_bg->setPosition(Vec2(0,visibleSize.height-_layer->getChildByName("title")->getContentSize().height));
    _dictionary_bg->setDirection(ui::ScrollView::Direction::VERTICAL);
    _layer->addChild(_dictionary_bg);
    
    innerContainer = LayerColor::create(Color4B(128,128,128,128));
    innerContainer->setAnchorPoint(Vec2(0,1));
    
    _dictionary_bg->addChild(innerContainer,0,"container");
    
    _dictionary_bg->setContentSize(Size(visibleSize.width,visibleSize.height
                                       -_layer->getChildByName("title")->getContentSize().height));
    _dictionary_bg->setInnerContainerPosition(Vec2(0,visibleSize.height-_layer->getChildByName("title")->getContentSize().height));
    //_dictionary_bg->setInnerContainerPosition(Vec2(0,_dictionary_bg->getContentSize().height));
    
    _dictionary_bg->setName("scrollview");
    
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
    
    _cat_list = UserData::getInstance()->getCats();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size visual_size = innerContainer->getContentSize();
    const int CONTENTS_MARGIN = 20;
    
    innerContainer->setContentSize(Size(visibleSize.width,
                                        (VISUAL_CONTENTS_SIZE + CONTENTS_MARGIN) * (_cat_list.size()/3+1)
                                        )
                                   );
    _dictionary_bg->setInnerContainerSize( Size(visibleSize.width,
                                                (VISUAL_CONTENTS_SIZE + CONTENTS_MARGIN) * (_cat_list.size()/3+1)
                                                )
                                          );
    
    for(int i=0; i<_cat_list.size();){
        for(int j=0; j<3 && i<_cat_list.size() ; j++){
            auto file_path = Cat::neko_id_to_string(_cat_list[i].getId());
            CatIcon* visual_contents = CatIcon::create(_cat_list[i].getId());
            Size contents_size = visual_contents->getContentSize();
            innerContainer->addChild(visual_contents);
            visual_contents->setAnchorPoint(Vec2(0,1));
            visual_contents->setPosition(Vec2((visual_size.width/3) * j + CONTENTS_MARGIN,
                                              visual_size.height - (contents_size.height + CONTENTS_MARGIN) * (i/3)));
            
            visual_contents->addClickEventListener([=](Ref* ref){
                if(!visual_contents->getSelect() && _number_of_selected_cats == _max_select_cats){
                    //todo max select
                    return;
                }
                visual_contents->changeState();
                if(!visual_contents->getSelect()){
                    this->_selected_cats.erase( std::find(_selected_cats.begin(),_selected_cats.end(),i) );
                    _number_of_selected_cats--;
                }
                else {
                    this->_selected_cats.push_back( i );
                    _number_of_selected_cats++;
                }
            });

            
            i++;
        }
    }

    _max_select_cats = max_select_cats;
    return true;
}

bool BoxLayerForVisual::init(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size visual_size = innerContainer->getContentSize();
    const int CONTENTS_MARGIN = 20;
    
    innerContainer->setContentSize(Size(visibleSize.width,
                                        (VISUAL_CONTENTS_SIZE + CONTENTS_MARGIN) * (NUMBER_OF_CATS/3+1)
                                        )
                                   );
    _dictionary_bg->setInnerContainerSize( Size(visibleSize.width,
                                                (VISUAL_CONTENTS_SIZE + CONTENTS_MARGIN) * (NUMBER_OF_CATS/3+1)
                                                )
                                          );
    
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

