//
//  BoxLayer.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/15.
//
//

#ifndef BoxLayer_hpp
#define BoxLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "Cat.hpp"

class BoxLayer : public cocos2d::Layer{
public:
    static BoxLayer* create();
    virtual bool init();
    enum eventType{
        CLOSE=0
    };
    
    void setCallback(std::function<void(int)> callback){ _callback = callback;};
    
protected:
    bool initCats();
    int _max_select_cats;
    
    cocos2d::EventListenerTouchOneByOne* _listener;
    
    cocos2d::Node* _layer;
    cocos2d::ui::ScrollView* _dictionary_bg;
    cocos2d::Node* innerContainer;
    
    std::function<void(int)> _callback;
};

class BoxLayerForSell : public BoxLayer{
public:
    static BoxLayerForSell* create(int max_select_cats);
    virtual bool init(int max_select_cats);
    enum eventType{
        CLOSE=0,
        SELECT,
        DESELECT
    };
    
    CC_SYNTHESIZE_READONLY(std::vector<Cat>, _cat_list, CatList);
    CC_SYNTHESIZE_READONLY(std::vector<int>, _selected_cats, SelectedCats);
    
private:
    int _max_select_cats;
    int _number_of_selected_cats;
};

class BoxLayerForVisual : public BoxLayer{
public:
    virtual bool init();
    CREATE_FUNC(BoxLayerForVisual);
private:
};

#endif /* BoxLayer_hpp */
