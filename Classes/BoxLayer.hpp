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
#include <functional>

class BoxLayer : public cocos2d::Node{
public:
    static BoxLayer* create(cocos2d::Size size);
    virtual bool init(cocos2d::Size size);
    enum eventType{
        CLOSE=0
    };
    
    void setCallback(std::function<void(int)> callback){ _callback = callback;};
    
protected:
    bool initCats();
    int _max_select_cats;
    
    cocos2d::EventListenerTouchOneByOne* _listener;
    
    cocos2d::ui::ScrollView* _dictionary_bg;
    cocos2d::Node* innerContainer;
    cocos2d::Size _size;
    
    std::function<void(int)> _callback;
};

class BoxLayerForSell : public BoxLayer{
public:
    static BoxLayerForSell* create(cocos2d::Size size,int max_select_cats);
    
    virtual bool init(cocos2d::Size size,int max_select_cats);
    bool initInnerContainer();
    bool initDictionary();
    bool initContents();
    
    enum eventType{
        CLOSE=0,
        SELECT,
        DESELECT
    };
    
    CC_SYNTHESIZE_READONLY(std::vector<Cat>, _cat_list, CatList);
    CC_SYNTHESIZE_READONLY(std::vector<int>, _selected_cats, SelectedCats);
    
    void removeSelectedCats();
    
private:
    int _max_select_cats;
    int _number_of_selected_cats;
    const int CONTENTS_MARGIN = 20;
};

class BoxLayerForVisual : public BoxLayer{
public:
    virtual bool init(cocos2d::Size size);
    static BoxLayerForVisual* create(cocos2d::Size size);
private:
};

#endif /* BoxLayer_hpp */
