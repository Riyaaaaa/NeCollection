//
//  ShopScene.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/27.
//
//

#ifndef ShopScene_hpp
#define ShopScene_hpp

#include "ShopScene.hpp"
#include "ui/CocosGUI.h"
#include "HomeScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "Utility.hpp"
#include "params.h"
#include "Products.hpp"
#include "MainScene.h"
#include "BoxLayer.hpp"

class SellContainer;

class ShopScene : public MainScene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(ShopScene);
    ~ShopScene();
    
    bool onTouchBegin(cocos2d::Touch*,cocos2d::Event*);
    //void onTouchMoved(cocos2d::Touch*,cocos2d::Event*);
    //void onTouchEnded(cocos2d::Touch*,cocos2d::Event*);
    //void onTouchCancelled(cocos2d::Touch*,cocos2d::Event*);
    
    void sellCallBack(int);
    
private:
    bool initUI();
    bool buyProducts(cocos2d::Touch*,cocos2d::Event*);
    void setProducts(PRODUCTS);
    void replaceSceneWithName(std::string filename);
    void setBuyEvent(Node* container, int id);
    void soldOut(cocos2d::Node* container);
    
    void refreshScreen();
    
    cocos2d::Node* createProducts(Products);
    
    enum ZORDER{
        SCENE=0,
        UI=2,
        MODAL_LAYER=3,
        MODAL_WINDOW=4,
        BOX=10,
        SELL_WINDOW=11
    };
    
    int _current_products;
    
    const float LINEUP_HEIGHT = 300;
    
    cocos2d::Sprite* _left_arrow=nullptr;
    cocos2d::Sprite* _right_arrow=nullptr;
    
    BoxLayerForSell* _sell_box;
    SellContainer* _sell_window;
    
    std::vector<Node*> _lineup_products;
    std::vector<Products> _products_list;
    int  _number_of_lineup_products;
};

class SellContainer : public cocos2d::Node{
public:
    virtual bool init();
    CREATE_FUNC(SellContainer);
    
    void setMoney(int);
    CC_SYNTHESIZE_READONLY(int, _money, Money);
    
    void select();
    void deselect();
private:
    int _current_select=0;
    cocos2d::Node* _window;

};

#endif /* ShopScene_hpp */
