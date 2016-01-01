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

BoxLayer* BoxLayer::create(Size size){
    BoxLayer* pRet = new BoxLayer();
    
    if(pRet && pRet->init(size)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete  pRet;
        pRet = NULL;
        return NULL;
    }
}

bool BoxLayer::init(Size size){
    if(!Node::init()){
        return false;
    }
    
    _size = size;
    Node::setContentSize(size);
    
    _dictionary_bg = ui::ScrollView::create();
    _dictionary_bg->setAnchorPoint(Vec2(0,1));
    _dictionary_bg->setPosition(Vec2(0,this->getContentSize().height));
    _dictionary_bg->setDirection(ui::ScrollView::Direction::VERTICAL);
    addChild(_dictionary_bg);
    
    _dictionary_bg->setName("scrollview");
    
    return true;
}

bool BoxLayer::initCats(){
    
    
    return true;
}

BoxLayerForSell* BoxLayerForSell::create(Size size,int max_select_cats){
    BoxLayerForSell* pRet = new BoxLayerForSell();
    
    if(pRet && pRet->init(size,max_select_cats)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete  pRet;
        pRet = NULL;
        return NULL;
    }
}

bool BoxLayerForSell::init(Size size,int max_select_cats){
    
    if(!BoxLayer::init(size)){
        return false;
    }
    
    _cat_list = UserData::getInstance()->getCats();
    
    initInnerContainer();
    initDictionary();
    
    _max_select_cats = max_select_cats;
    return true;
}

bool BoxLayerForSell::initDictionary(){
    Size visibleSize = Director::getInstance()->getVisibleSize();

    /* init dictionary bg */
    _dictionary_bg->setInnerContainerSize( innerContainer->getContentSize() );
    
    _dictionary_bg->setContentSize(_size);
    _dictionary_bg->setInnerContainerPosition(Vec2(0,_size.height));
    return true;
}

bool BoxLayerForSell::initInnerContainer(){
    /* init inner container */
    innerContainer = LayerColor::create(Color4B(128,128,128,128));
    innerContainer->setAnchorPoint(Vec2(0,1));
    
    initContents();
    
    _dictionary_bg->addChild(innerContainer,0,"container");
    
    initDictionary();
    return true;
}

bool BoxLayerForSell::initContents(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    const int CONTENTS_MARGIN = 20;
    
    innerContainer->removeAllChildrenWithCleanup(true);
  
    innerContainer->setContentSize(Size(visibleSize.width,
                                        (VISUAL_CONTENTS_SIZE + CONTENTS_MARGIN) * (_cat_list.size()/3+1)
                                        )
                                   );
    if(innerContainer->getContentSize().height < _size.height){
        innerContainer->setContentSize(_size);
    }
   
    Size visual_size = innerContainer->getContentSize();
    for(int i=0; i<_cat_list.size();){
        for(int j=0; j<3 && i<_cat_list.size() ; j++){
            auto file_path = Cat::neko_id_to_string(_cat_list[i].getId());
            CatIcon* visual_contents = CatIcon::create(_cat_list[i].getId());
            Size contents_size = visual_contents->getContentSize();
            innerContainer->addChild(visual_contents);
            visual_contents->setAnchorPoint(Vec2(0,1));
            visual_contents->setPosition(Vec2((visual_size.width/3) * j + CONTENTS_MARGIN,
                                              visual_size.height - (contents_size.height + CONTENTS_MARGIN) * (i/3)));
            
            /* event of selection a visual content  */
            visual_contents->addClickEventListener([=](Ref* ref){
                if(!visual_contents->getSelect() && _number_of_selected_cats == _max_select_cats){
                    //todo max select
                    return;
                }
                visual_contents->changeState();
                if(!visual_contents->getSelect()){
                    this->_selected_cats.erase( std::find(_selected_cats.begin(),_selected_cats.end(),i) );
                    if(_callback)_callback(eventType::DESELECT);
                    _number_of_selected_cats--;
                }
                else {
                    this->_selected_cats.push_back( i );
                    if(_callback)_callback(eventType::SELECT);
                    _number_of_selected_cats++;
                }
            });
            
            
            i++;
        }
    }
    _dictionary_bg->scrollToPercentVertical(0, 0.1, false);
    return true;
}

void BoxLayerForSell::removeSelectedCats(){
    
    UserData::getInstance()->removeCats(_selected_cats);
    _selected_cats.clear();
    _cat_list = UserData::getInstance()->getCats();
    initContents();
    initDictionary();
    
}

BoxLayerForVisual* BoxLayerForVisual::create(Size size){
    BoxLayerForVisual* pRet = new BoxLayerForVisual();
    
    if(pRet && pRet->init(size)){
        pRet->autorelease();
        return pRet;
    }
    else{
        delete  pRet;
        pRet = NULL;
        return NULL;
    }
}

bool BoxLayerForVisual::init(Size size){
    if(!BoxLayer::init(size)){
        return false;
    }
    
    innerContainer = LayerColor::create(Color4B(128,128,128,128));
    innerContainer->setAnchorPoint(Vec2(0,1));
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Size visual_size = innerContainer->getContentSize();
    const int CONTENTS_MARGIN = 20;
    
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
    _dictionary_bg->addChild(innerContainer,0,"container");
    
    _dictionary_bg->setInnerContainerSize( innerContainer->getContentSize() );
    
    _dictionary_bg->setContentSize(_size);
    _dictionary_bg->setInnerContainerPosition(Vec2(0,getContentSize().height));

    return true;
}

