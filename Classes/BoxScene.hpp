//
//  BoxScene.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/12.
//
//

#ifndef BoxScene_hpp
#define BoxScene_hpp

#include "MainScene.h"
#include "cocos2d.h"

class BoxScene : public MainScene{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(BoxScene);
    
private:
    enum ZOrder{
        SCENE=0
    };
    
    virtual bool init();
    bool initBox();
};

#endif /* BoxScene_hpp */
