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

class VisualScene : public MainScene{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(VisualScene);
private:
    virtual bool init();
    bool initVisualDictionary();
};

#endif /* VisualScene_hpp */
