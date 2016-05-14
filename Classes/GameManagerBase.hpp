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
class GameManagerBase : public SingletonBase<GameManagerBase> {
    GameManagerBase() : _scene(nullptr) {}
    void runScene() {
        _scene =　Scene_t::create();
        Director::getInstnce()->replaceScene(_scene);
    }
protected:
    Scene_t* _scene;
};



#endif /* GameManagerBase_h */
