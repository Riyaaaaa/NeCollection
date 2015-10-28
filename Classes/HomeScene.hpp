//
//  HomeScene.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/27.
//
//

#ifndef HomeScene_hpp
#define HomeScene_hpp

#include "cocos2d.h"

class HomeScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HomeScene);
    
protected:
    bool initLayout();
    bool initStatus();
    
    void comeCat();
    
    void update(float dt);
    
    void saveScheduleTime();
    
    int _remain_event_time;
    
    const int OCCURRE_EVENT_TIME = 500;
};

#endif /* HomeScene_hpp */
