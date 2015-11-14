//
//  ShopScene.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/27.
//
//

#include "ShopScene.hpp"
#include "VisualScene.hpp"
#include "ui/CocosGUI.h"
#include "HomeScene.hpp"
#include "UserData.hpp"
#include "cocostudio/CocoStudio.h"
#include "Utility.hpp"

USING_NS_CC;

Scene* ShopScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    Size size = Director::getInstance()->getVisibleSize();
    
    scene->addChild(ShopScene::create(),SCENE,"ShopScene");
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ShopScene::init()
{
    
    if ( !MainScene::init("shop/ShopScene.csb") )
    {
        return false;
    }
    
    if( !initUI() ){
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(ShopScene::onTouchBegin,this);
    //listener->onTouchMoved = CC_CALLBACK_2(ShopScene::onTouchMoved,this);
    //listener->onTouchEnded = CC_CALLBACK_2(ShopScene::onTouchEnded,this);
    //listener->onTouchCancelled = CC_CALLBACK_2(ShopScene::onTouchCancelled,this);
    
    listener->setSwallowTouches(true);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool ShopScene::initUI(){
    auto initMenuButton = [&](auto* scene,std::string button){
        _scene->getChildByName("Menu")->
        getChildByName<ui::Button*>(button)->
        addClickEventListener([=](Ref* ref){
            auto* next_scene = remove_ptr_t<decltype(scene)>::createScene();
            Director::getInstance()->replaceScene(next_scene);
        });
    };
    
    initMenuButton( reinterpret_cast<HomeScene*>(0),"home");
    initMenuButton( reinterpret_cast<ShopScene*>(0),"shop");
    //initMenuButton("shop","shop/ShopScene.csb");
    initMenuButton( reinterpret_cast<VisualScene*>(0),"dictionary");
    //initMenuButton("battle","battle/BattleScene.csb");
    
    auto ui_layer = _scene->getChildByName("ProductsTopMenu");
    
    ui_layer->getChildByName<ui::Button*>("meal")->addClickEventListener([&](Ref* ref){this->setProducts(PRODUCTS::MEAL);});
    ui_layer->getChildByName<ui::Button*>("toy")->addClickEventListener([&](Ref* ref){this->setProducts(PRODUCTS::TOY);});
    ui_layer->getChildByName<ui::Button*>("futon")->addClickEventListener([&](Ref* ref){this->setProducts(PRODUCTS::FUTON);});
    ui_layer->getChildByName<ui::Button*>("trimmer")->addClickEventListener([&](Ref* ref){this->setProducts(PRODUCTS::TRIMMER);});
    
    refreshScreen();
    
    return true;
}

void ShopScene::replaceSceneWithName(std::string filename){
    auto* next_scene = CSLoader::getInstance()->createNode(filename);
    auto* scene = Scene::create();
    
    scene->addChild(next_scene);
    
    Director::getInstance()->replaceScene(scene);
}

void ShopScene::setProducts(PRODUCTS identify){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    dbIO* db = dbIO::getInstance();
    
    for(Node* product : _lineup_products){
        product->removeFromParent();
        product->release();
    }
    _lineup_products.clear();
    
    _products_list = db->getProductTypeAll(identify);
    
    _number_of_lineup_products = _products_list.size();
    _current_products = 0;
    
    for(long i=0; i<_products_list.size(); i++){
        _lineup_products.push_back(createProducts(_products_list[i]));
        _lineup_products[i]->setAnchorPoint(Vec2(0.5,0.5));
    }
    
    for(long i=0; i<_lineup_products.size() && i<3; i++){
        addChild(_lineup_products[i]);
        _lineup_products[i]->setPosition(Vec2((Director::getInstance()->getVisibleSize().width/2)*(i+1),LINEUP_HEIGHT));
    }
    
    setBuyEvent(_lineup_products[_current_products], _products_list[_current_products].id);
    
    if(!_right_arrow && !_left_arrow){
        _right_arrow = Sprite::create("utility/utility_ui.png",
                                      Rect(params::L_ARROW_X,params::L_ARROW_Y,params::UTILITY_SIZE,params::UTILITY_SIZE));
        _left_arrow = Sprite::create("utility/utility_ui.png",
                                     Rect(params::R_ARROW_X,params::R_ARROW_Y,params::UTILITY_SIZE,params::UTILITY_SIZE));
        
        addChild(_left_arrow,UI,"l_arrow");
        addChild(_right_arrow,UI,"r_arrow");
        
        _right_arrow->setPosition(Vec2(visibleSize.width / 2 - 150 , LINEUP_HEIGHT));
        _left_arrow->setPosition(Vec2(visibleSize.width / 2 + 150 , LINEUP_HEIGHT));
    }
    _left_arrow->setVisible(true);
    _right_arrow->setVisible(false);
}

Node* ShopScene::createProducts(Products products){
    Node* products_container = CSLoader::getInstance()->createNode("shop/ProductsUI.csb");
    auto image = products_container->getChildByName<ui::ImageView*>("ProductImg");
    image->loadTexture("products/" + products.name + ".png");
    products_container->getChildByName<ui::Text*>("price")->setText(std::to_string(products.price)+" yen");
    
    if(products.isObtain){
        Sprite* soldout = Sprite::create("UI/soldout.png");
        products_container->addChild(soldout);
        soldout->setPosition( products_container->getContentSize() / 2 );
    }
    
    products_container->retain();
    return products_container;
}

void ShopScene::setBuyEvent(cocos2d::Node *container, int id){
    bool isObtain = dbIO::getInstance()->getProductIsObtain(id);
    
    if(!isObtain){
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(ShopScene::buyProducts,this);
        listener->setSwallowTouches(true);
        container->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, container);
    }
}

bool ShopScene::buyProducts(cocos2d::Touch *touch, cocos2d::Event *event){
    int money = UserData::getInstance()->getMoney();
    
    if(_lineup_products[_current_products]->getBoundingBox().containsPoint(touch->getLocation())){
        Layer* modal_layer = LayerColor::create( Color4B(0,0,0,128) );
        addChild(modal_layer,MODAL_LAYER,"modal_layer");
        
        Node* modal_window = CSLoader::getInstance()->createNode("shop/Buy_Window.csb");
        modal_layer->addChild(modal_window);
        
        modal_window->setAnchorPoint(Vec2(0.5,0.5));
        modal_window->setPosition(modal_layer->getContentSize()/2);
        
        modal_window->getChildByName<ui::Text*>("before_money")->setString(std::to_string(money));
        modal_window->getChildByName<ui::Text*>("after_money")->setString(std::to_string(money - _products_list[_current_products].price));
        
        modal_window->getChildByName<ui::Button*>("no")->addClickEventListener([=](Ref* ref){modal_layer->removeFromParent();});
        
        if(UserData::getInstance()->getMoney() < _products_list[_current_products].price){
            modal_window->getChildByName<ui::Text*>("after_money")->setTextColor(Color4B::RED);
            modal_window->getChildByName<ui::Button*>("yes")->setEnabled(false);
        }
        else{
            modal_window->getChildByName<ui::Button*>("yes")->addClickEventListener([=](Ref* ref){
                modal_window->getChildByName<ui::Text*>("after_money")->setTextColor(Color4B::BLUE);
                this->soldOut(_lineup_products[_current_products]);
                dbIO::getInstance()->queryTable("update products set isObtain = 1 where id = " + std::to_string(_products_list[_current_products].id) + ";");
                UserData::getInstance()->setMoney(money -_products_list[_current_products].price);
                modal_layer->removeFromParent();
                this->refreshScreen();
            });
        }
        
        auto listner = EventListenerTouchOneByOne::create();
        listner->setSwallowTouches(true);
        listner->onTouchBegan = [](Touch*,Event*){return true;};
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listner,modal_layer);
        
        return true;
    }
    return false;
}

void ShopScene::soldOut(Node* container){
    Sprite* soldout = Sprite::create("UI/soldout.png");
    container->addChild(soldout);
    soldout->setPosition( container->getContentSize() / 2 );
}

bool ShopScene::onTouchBegin(cocos2d::Touch* touch,cocos2d::Event* event){
    Vec2 pos = touch->getLocation();
    Size size = Director::getInstance()->getVisibleSize();
    
    Vector<FiniteTimeAction*> animations;
    
    if(_lineup_products.size() == 0)return false;
    
    _eventDispatcher->removeEventListenersForTarget(_lineup_products[_current_products]);
    
    if(pos.y < LINEUP_HEIGHT*1.5f){
        if(pos.x > size.width/2){
            //lineup move right
            if(_current_products < _lineup_products.size()-1){
                if(_current_products!=0)animations.pushBack(TargetedAction::create(_lineup_products[_current_products - 1],MoveTo::create(0.5f,Vec2(-size.width/2,LINEUP_HEIGHT))));
                animations.pushBack(TargetedAction::create(_lineup_products[_current_products],MoveTo::create(0.5f,Vec2(0,LINEUP_HEIGHT))));
                auto remove = RemoveSelf::create();
                remove->setTarget(_lineup_products[_current_products + 1]);
                animations.pushBack(Sequence::create(TargetedAction::create(_lineup_products[_current_products + 1],MoveTo::create(0.5f, Vec2(size.width/2,LINEUP_HEIGHT))),nullptr));
                
                if(_current_products < _lineup_products.size() - 2){
                    addChild(_lineup_products[_current_products + 2]);
                    _lineup_products[_current_products + 2],setPosition(Vec2(size.width*1.5f,LINEUP_HEIGHT));
                    animations.pushBack(TargetedAction::create(_lineup_products[_current_products + 2],MoveTo::create(0.5f,Vec2(size.width,LINEUP_HEIGHT))));
                }
                
                runAction(Spawn::create(animations));
                _current_products++;
                
            }
            
        }
        else {
            //lineup move left
            if(_current_products > 0){
                if(_current_products != _lineup_products.size()-1)animations.pushBack(TargetedAction::create(_lineup_products[_current_products + 1],MoveTo::create(0.5f,Vec2(size.width*1.5f,LINEUP_HEIGHT))));
                animations.pushBack(TargetedAction::create(_lineup_products[_current_products],MoveTo::create(0.5f,Vec2(size.width,LINEUP_HEIGHT))));
                animations.pushBack(Sequence::create(TargetedAction::create(_lineup_products[_current_products - 1],MoveTo::create(0.5f, Vec2(size.width/2,LINEUP_HEIGHT))),nullptr));
                
                if(_current_products > 1){
                    addChild(_lineup_products[_current_products - 2]);
                    _lineup_products[_current_products - 2],setPosition(Vec2(-size.width/2,LINEUP_HEIGHT));
                    animations.pushBack(TargetedAction::create(_lineup_products[_current_products - 2],MoveTo::create(0.5f,Vec2(0,LINEUP_HEIGHT))));
                }
                
                runAction(Spawn::create(animations));
                _current_products--;
            }
            
        }
        
        setBuyEvent(_lineup_products[_current_products], _products_list[_current_products].id);
        
        if(_current_products == 0)_right_arrow->setVisible(false);
        else _right_arrow->setVisible(true);
        
        if(_current_products == _lineup_products.size()-1)_left_arrow->setVisible(false);
        else _left_arrow->setVisible(true);
        
        return true;
    }
    
    return false;
}

void ShopScene::refreshScreen(){
    int money = UserData::getInstance()->getMoney();
    _scene->getChildByName("MoneyUI")->getChildByName("money_plate")
        ->getChildByName<ui::Text*>("money")->setString(std::to_string(money));
}

ShopScene::~ShopScene(){
    for(long i=0; i<_lineup_products.size(); i++){
        _lineup_products[i]->removeFromParent();
        _lineup_products[i]->release();
    }
}