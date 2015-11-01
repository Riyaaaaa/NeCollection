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
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "CatObject.hpp"

class HomeScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HomeScene);
    
    bool onTouchBegin(cocos2d::Touch*,cocos2d::Event*);
    void onTouchMoved(cocos2d::Touch*,cocos2d::Event*);
    void onTouchEnded(cocos2d::Touch*,cocos2d::Event*);
    void onTouchCancelled(cocos2d::Touch*,cocos2d::Event*);
    
protected:
    enum class CAT_OBJECT{
        TOY=0,
        FUTON,
        MEAL,
        TRIMMER
    };
    
    cocos2d::Node* home_scene;
    cocos2d::Sprite* home_bg;
    
    //std::vector<std::unique_ptr<CatObject>> _cat_objects;
    std::vector<cocos2d::ui::Button*> _cat_objects;
    
    static void disenableCatObject(cocos2d::ui::Button*);
    
    bool initStatus();
    bool initUI();
    
    void comeCat();
    void getCat(int id);
    
    void replaceSceneWithName(std::string);
    
    void update(float dt);
    
    void saveScheduleTime();
    
    int _remain_event_time=600;
    cocos2d::Vec2 _old_pos;
    const int OCCURRE_EVENT_TIME = 500;
};

#endif /* HomeScene_hpp */
