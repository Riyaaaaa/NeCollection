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

class ShopScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(ShopScene);
    
private:
    bool initUI();
    void replaceSceneWithName(std::string filename);
    
    cocos2d::Node* _shop_scene;
};

#endif /* ShopScene_hpp */
