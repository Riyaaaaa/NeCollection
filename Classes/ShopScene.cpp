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
#include "cocostudio/CocoStudio.h"
#include "Utility.hpp"

USING_NS_CC;

Scene* ShopScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    Size size = Director::getInstance()->getVisibleSize();
    
    scene->addChild(ShopScene::create());
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ShopScene::init()
{
    //////////////////////////////
    // 1. super init first
    
    _shop_scene = CSLoader::getInstance()->createNode("shop/ShopScene.csb");
    Size size = Director::getInstance()->getVisibleSize();

    _shop_scene->setContentSize(size);
    cocos2d::ui::Helper::doLayout(_shop_scene);
    addChild(_shop_scene);
    
    if ( !Layer::init() )
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
        _shop_scene->getChildByName("Menu")->
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
    
    auto ui_layer = _shop_scene->getChildByName("ProductsTopMenu");
    
    ui_layer->getChildByName<ui::Button*>("meal")->addClickEventListener([&](Ref* ref){this->setProducts(PRODUCTS::MEAL);});
    ui_layer->getChildByName<ui::Button*>("toy")->addClickEventListener([&](Ref* ref){this->setProducts(PRODUCTS::TOY);});
    ui_layer->getChildByName<ui::Button*>("futon")->addClickEventListener([&](Ref* ref){this->setProducts(PRODUCTS::FUTON);});
    ui_layer->getChildByName<ui::Button*>("trimmer")->addClickEventListener([&](Ref* ref){this->setProducts(PRODUCTS::TRIMMER);});
    
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
    std::vector<Products> products_list;
    
    for(Node* product : _lineup_products){
        product->removeFromParent();
        product->release();
    }
    _lineup_products.clear();
    
    products_list = db->getProductTypeAll(identify);
    
    _number_of_lineup_products = products_list.size();
    
    for(long i=0; i<products_list.size(); i++){
        Node* products_container = CSLoader::getInstance()->createNode("shop/ProductsUI.csb");
        products_container->getChildByName<Sprite*>("ProductImg")->setTexture("products/" + products_list[i].name + ".png");
        products_container->getChildByName<ui::Text*>("price")->setText(std::to_string(products_list[i].price));
        products_container->retain();
        _lineup_products.push_back(products_container);
    }
    
    for(long i=0; i<_lineup_products.size() && i<3; i++){
        _lineup_products[0]->setPosition(Vec2((Director::getInstance()->getVisibleSize().width/2)*(i+1),LINEUP_HEIGHT));
    }
    
    Sprite* left_arrow = Sprite::create("utility/utility_ui.png",
                                        Rect(params::L_ARROW_X,params::L_ARROW_Y,params::UTILITY_SIZE,params::UTILITY_SIZE));
    Sprite* right_arrow = Sprite::create("utility/utility_ui.png",
                                         Rect(params::R_ARROW_X,params::R_ARROW_Y,params::UTILITY_SIZE,params::UTILITY_SIZE));
    
    addChild(left_arrow,UI,"l_arrow");
    addChild(right_arrow,UI,"r_arrow");
    
    left_arrow->setPosition(Vec2(visibleSize.width / 2 + 100 , LINEUP_HEIGHT + 150));
    right_arrow->setPosition(Vec2(visibleSize.width / 2 + 100 , LINEUP_HEIGHT + 150));

}

bool ShopScene::onTouchBegin(cocos2d::Touch* touch,cocos2d::Event* event){
    Vec2 pos = touch->getLocation();
    Size size = Director::getInstance()->getVisibleSize();
    
    if(pos.y < LINEUP_HEIGHT){
        if(pos.x < size.width/2){
            //lineup move right
        }
        else {
            //lineup move left
        }
        return true;
    }
    
    return false;
}

ShopScene::~ShopScene(){
    for(long i=0; i<_lineup_products.size(); i++){
        _lineup_products[i]->removeFromParent();
        _lineup_products[i]->release();
    }
}