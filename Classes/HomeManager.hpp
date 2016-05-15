//
//  HomeManager.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2016/05/14.
//
//

#ifndef HomeManager_hpp
#define HomeManager_hpp

#include "GameManagerBase.hpp"
#include "HomeScene.hpp"

class HomeManager : public GameManagerBase<HomeManager, HomeScene> {
public:
    
    HomeManager();
    
    void runScene()override;
    
    void comeCat();
    void getCat(int id);
    
    void setEnableCatObject(bool,PRODUCTS);
    
    void replaceSceneWithName(std::string);
    void setRedecorateWindow();
    
    void saveScheduleTime();
    void saveObjectStatus();
    
    void update(float dt) override{}
    int lotteryCat();
    
private:
    int _remain_event_time=600;
    cocos2d::Vec2 _old_pos;
    const int OCCURRE_EVENT_TIME = 500;
    
    dbIO* _db;
};

#endif /* HomeManager_hpp */
