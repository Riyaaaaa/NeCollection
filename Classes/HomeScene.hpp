//
//  HomeScene.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/27.
//
//

#ifndef HomeScene_hpp
#define HomeScene_hpp

#include <array>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "CatObject.hpp"
#include "MainScene.h"
#include "dbIO.hpp"

class HomeScene : public MainScene
{
public:
    static cocos2d::Scene* createScene();
    void refreshScene();
    
    virtual bool init();
    
    ~HomeScene();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HomeScene);
    
    bool onTouchBegin(cocos2d::Touch*,cocos2d::Event*);
    void onTouchMoved(cocos2d::Touch*,cocos2d::Event*);
    void onTouchEnded(cocos2d::Touch*,cocos2d::Event*);
    void onTouchCancelled(cocos2d::Touch*,cocos2d::Event*);
    
    void saveScheduleTime();
    void saveObjectStatus();
    
protected:
    enum ZOrder{
        SCENE=0
    };

    cocos2d::Sprite* _home_bg;
    
    dbIO* _db;
    
    //std::vector<std::unique_ptr<CatObject>> _cat_objects;
    std::vector<cocos2d::ui::Button*> _cat_objects;
    std::array< CatObjectStatus, params::NUMBER_OF_PRODUCT_TYPES > _cat_object_status;
    
    void setEnableCatObject(bool,PRODUCTS);
    
    
    bool initStatus();
    bool initUI();
    
    void comeCat();
    void getCat(int id);
    
    void replaceSceneWithName(std::string);
    void setCatObject(PRODUCTS product,int id);
    
    void update(float dt);
    int lotteryCat();
    
    int _remain_event_time=600;
    cocos2d::Vec2 _old_pos;
    const int OCCURRE_EVENT_TIME = 500;
};

#endif /* HomeScene_hpp */
