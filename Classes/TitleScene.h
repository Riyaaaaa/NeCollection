#ifndef __TitleScene_SCENE_H__
#define __TitleScene_SCENE_H__

#include "cocos2d.h"

class TitleScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void beginAnimation();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TitleScene);
    
    static cocos2d::Node* _titlescene;
};

#endif // __TitleScene_SCENE_H__
