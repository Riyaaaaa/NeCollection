//
//  VisualScene.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/01.
//
//

#ifndef VisualScene_hpp
#define VisualScene_hpp

#include "MainScene.h"

class VisualScene : cocos2d::Layer,MainScene{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(VisualScene);
private:
    virtual bool init();
};

#endif /* VisualScene_hpp */
