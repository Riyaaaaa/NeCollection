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

class BoxLayer : public cocos2d::Layer{
public:
    static BoxLayer* create();
    virtual bool init();
    
protected:
    bool initCats();
    int _max_select_cats;
    cocos2d::Node* _layer;
    cocos2d::ui::ScrollView* _dictionary_bg;
    
    std::vector<int> _cat_list;
};

class BoxLayerForSell : public BoxLayer{
public:
    static BoxLayerForSell* create(int max_select_cats);
    virtual bool init(int max_select_cats);
    
private:
    int _max_select_cats;
    int _current_selected_cats;
};

#endif /* BoxLayer_hpp */
