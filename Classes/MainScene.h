//
//  MainScene.h
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/01.
//
//

#ifndef MainScene_h
#define MainScene_h

#include "cocos2d.h"

class MainScene: public cocos2d::Layer{
public:
    bool init();
protected:
    bool initUI();
    cocos2d::Node* _scene;
};

#endif /* MainScene_h */
