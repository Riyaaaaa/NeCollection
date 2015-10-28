//
//  ShopScene.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/27.
//
//

#ifndef ShopScene_hpp
#define ShopScene_hpp

class ShopScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(ShopScene);
};

#endif /* ShopScene_hpp */
