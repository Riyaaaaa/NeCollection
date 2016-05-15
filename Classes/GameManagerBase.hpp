//
//  GameManagerBase.h
//  NeCollection
//
//  Created by Riya.Liel on 2016/05/14.
//
//

#ifndef GameManagerBase_h
#define GameManagerBase_h

#include "SingletonBase.hpp"
#include "cocos2d.h"

template<class Extend, class Scene_t>
class GameManagerBase : public SingletonBase<Extend> {
public:
    virtual void update(float dt){}
    virtual void runScene() {
        _scene = Scene_t::create();
        cocos2d::Director::getInstance()->replaceScene(_scene);
    }
protected:
    GameManagerBase() : _scene(nullptr) {
        auto scheduler = cocos2d::Director::getInstance()->getScheduler();
        scheduler->scheduleUpdateForTarget(this, 0, false);
    }
    virtual ~GameManagerBase() {
        
    }
    Scene_t* _scene;
};



#endif /* GameManagerBase_h */
