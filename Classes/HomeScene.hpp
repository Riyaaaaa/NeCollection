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
    void onEnter() override;
    void onExit() override;
    
    enum class EventType {
        OCCURED_EVENT_TIME
    };
    
    virtual bool init() override;
    
    ~HomeScene() = default;
    
    // implement the "static create()" method manually
    CREATE_FUNC(HomeScene);
    
    bool onTouchBegin(cocos2d::Touch*,cocos2d::Event*);
    void onTouchMoved(cocos2d::Touch*,cocos2d::Event*);
    void onTouchEnded(cocos2d::Touch*,cocos2d::Event*);
    void onTouchCancelled(cocos2d::Touch*,cocos2d::Event*);
    
    std::array< CatObjectStatus, params::NUMBER_OF_PRODUCT_TYPES >& getCatObjectStatuses() { return _cat_object_status; }
    std::vector<cocos2d::ui::Button*>& getCatObjectButtons() { return _cat_objects; };
    
    void setCatObjectCallback(std::function<void(Ref*)> callback, PRODUCTS product);
    
    CC_SYNTHESIZE(std::function<void(EventType)>, _callback, EventCallBack);
    
protected:
    enum ZOrder{
        SCENE=0
    };

    cocos2d::Sprite* _home_bg;
    cocos2d::Node* _redecorate_window;
    
    dbIO* _db;
    
    //std::vector<std::unique_ptr<CatObject>> _cat_objects;
    std::vector<cocos2d::ui::Button*> _cat_objects;
    std::array< CatObjectStatus, params::NUMBER_OF_PRODUCT_TYPES > _cat_object_status;
    
    void setCatObject(PRODUCTS product,int id);
    
    bool initStatus();
    bool initUI();
    
    void replaceSceneWithName(std::string);
    void setRedecorateWindow();
    
    void update(float dt) override;
    
    int _remain_event_time=600;
    cocos2d::Vec2 _old_pos;
    const int OCCURRE_EVENT_TIME = 500;
};

#endif /* HomeScene_hpp */
