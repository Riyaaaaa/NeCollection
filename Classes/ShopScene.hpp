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

class ShopScene : public cocos2d::Layer
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
    
private:
    bool initUI();
    void setProducts(PRODUCTS);
    void replaceSceneWithName(std::string filename);
    
    enum ZORDER{
        UI=2
    };
    
    const float LINEUP_HEIGHT = 300;
    
    cocos2d::Node* _shop_scene;
    
    std::vector<Node*> _lineup_products;
    int  _number_of_lineup_products;
};

#endif /* ShopScene_hpp */
