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
#include "ModalWindow.hpp"

USING_NS_CC;

Scene* ShopScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
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
    
    _scene->getChildByName<ui::Button*>("sell")->addClickEventListener([=](Ref* ref){
        Size visibleSize = Director::getInstance()->getVisibleSize();
        
        _title = CSLoader::getInstance()->createNode("UI/Title.csb");
        _title->getChildByName<ui::Text*>("label")->setString("ねこボックス");
        _title->setAnchorPoint(Vec2(0.5,1));
        _title->setPosition(Vec2( visibleSize.width/2 , visibleSize.height ));
        this->addChild(_title);
        
        _sell_box = BoxLayerForSell::create(Size(visibleSize - Size(0,_title->getContentSize().height))
                                            ,10);

        _sell_box->setCallback(CC_CALLBACK_1(ShopScene::sellCallBack, this));
        this->addChild(_sell_box,ZORDER::BOX);
        _sell_box->setAnchorPoint(Vec2(0,1));
        _sell_box->setPosition(Vec2(0,visibleSize.height-_title->getContentSize().height));
        
        _sell_window = SellContainer::create();
        _sell_window->getWindow()->getChildByName<ui::Button*>("sell")->addClickEventListener([=](Ref* ref){
            this->sellCats();
        });
        
        _sell_window->getWindow()->getChildByName<ui::Button*>("cancell")->addClickEventListener([=](Ref* ref){ this->_sell_box->removeFromParent();
            this->_sell_window->removeFromParent();
            this->_title->removeFromParent();
        });
        this->addChild(_sell_window,ZORDER::SELL_WINDOW);
    });
    
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
    
    for(long i=0; i<_lineup_products.size() && i<2; i++){
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
    image->loadTexture("products/" + fill_zero(products.id) + ".png");
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
        Buy_Confirm_Window* buy_window = Buy_Confirm_Window::create(_products_list[_current_products].price);
        addChild(buy_window,MODAL_LAYER,"modal_layer");
        
        buy_window->setPosition(Point::ZERO);
        
        buy_window->setContent(_products_list[_current_products]);

        buy_window->setCallBackYes( [=](Ref* ref){
                this->soldOut(_lineup_products[_current_products]);
                dbIO::getInstance()->queryTableWritable("update productbox set isObtain = 1 where id = " + std::to_string(_products_list[_current_products].id) + ";");
                UserData::getInstance()->setMoney(money -_products_list[_current_products].price);
                buy_window->removeFromParent();
                this->refreshScreen();
            });
        
        auto listner = EventListenerTouchOneByOne::create();
        listner->setSwallowTouches(true);
        listner->onTouchBegan = [](Touch*,Event*){return true;};
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listner,buy_window);
        
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
                auto* right_slider = MoveBy::create(0.5f,Vec2(-size.width/2,0));
                
                if(_current_products!=0){
                    auto remove = RemoveSelf::create();
                    animations.pushBack(TargetedAction::create(_lineup_products[_current_products - 1],
                                                               Sequence::create(
                                                                                right_slider->clone(),
                                                                                remove,
                                                                                nullptr
                                                                                )
                                                               )
                                        );
                }
                
                animations.pushBack(TargetedAction::create(_lineup_products[_current_products],right_slider->clone()));
                
                
                animations.pushBack(TargetedAction::create(_lineup_products[_current_products + 1],right_slider->clone()));
                
                if(_current_products < static_cast<int>(_lineup_products.size()) - 2){
                    addChild(_lineup_products[_current_products + 2]);
                    _lineup_products[_current_products + 2]->setPosition(Vec2(size.width*1.5f,LINEUP_HEIGHT));
                    animations.pushBack(TargetedAction::create(_lineup_products[_current_products + 2],
                                                               right_slider->clone())
                                        );
                }
                
                runAction(Spawn::create(animations));
                _current_products++;
                
            }
            
        }
        else {
            auto* left_slide = MoveBy::create(0.5f,Vec2(size.width/2,0));
            //lineup move left
            if(_current_products > 0){
                if(_current_products != _lineup_products.size()-1){
                    auto remove = RemoveSelf::create();
                    animations.pushBack(TargetedAction::create(_lineup_products[_current_products + 1],
                                                               Sequence::create(
                                                                                left_slide->clone(),
                                                                                remove,
                                                                                nullptr
                                                                                )
                                                               )
                                        );
                }
                
                animations.pushBack(TargetedAction::create(_lineup_products[_current_products],left_slide->clone()));
                animations.pushBack(TargetedAction::create(_lineup_products[_current_products - 1],left_slide->clone()));
                
                if(_current_products > 1){
                    addChild(_lineup_products[_current_products - 2]);
                    _lineup_products[_current_products - 2]->setPosition(Vec2(-size.width/2,LINEUP_HEIGHT));
                    animations.pushBack(TargetedAction::create(_lineup_products[_current_products - 2],left_slide->clone()));
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

void ShopScene::sellCallBack(int type){
    switch (type) {
        case BoxLayerForSell::eventType::CLOSE:
            _sell_window->removeFromParent();
            return;
            break;
        case BoxLayerForSell::eventType::SELECT:
            _sell_window->select();
            break;
            
        case BoxLayerForSell::eventType::DESELECT:
            _sell_window->deselect();
            break;
    }
    
    std::vector<int> selected_cats = _sell_box->getSelectedCats();
    const std::vector<Cat>& cats = _sell_box->getCatList();
    int sum=0;
    
    for(int index:  selected_cats){
        sum += cats[index].getSellingPrice();
    }
    
    _sell_window->setMoney(sum);
}

void ShopScene::sellCats(){
    const auto& cat_list = _sell_box->getCatList();
    const auto& selected_list = _sell_box->getSelectedCats();
    int sum=0;
    
    for(int index: selected_list){
        sum += (dbIO::getInstance()->getCatById(cat_list[index].getId()).getSellingPrice());
    }
    
    UserData::getInstance()->addMoney(sum);
    refreshScreen();
    _sell_box->removeSelectedCats();
    _sell_window->clear();
}

ShopScene::~ShopScene(){
    for(long i=0; i<_lineup_products.size(); i++){
        _lineup_products[i]->removeFromParent();
        _lineup_products[i]->release();
    }
}

bool SellContainer::init(){
    
    if(!Node::init())return false;
    
    _window = CSLoader::createNode("UI/sell_window.csb");
    if(!_window)return false;
    addChild(_window);
    
    return true;
}

void SellContainer::select(){
    _window->getChildByName<Sprite*>( "select" + std::to_string(_current_select))->setTexture("UI/sold_active.png");
    _current_select++;
}

void SellContainer::deselect(){
    _current_select--;
    _window->getChildByName<Sprite*>( "select" + std::to_string(_current_select))->setTexture("UI/sold_gray.png");
}

void SellContainer::clear(){
    _current_select=0;
    for(int i=0; i<10; i++){
        _window->getChildByName<Sprite*>( "select" + std::to_string(i))->setTexture("UI/sold_gray.png");
    }
}

void SellContainer::setMoney(int money){
    _money = money;
    _window->getChildByName<ui::Text*>("money")->setString(std::to_string(money));
    
}