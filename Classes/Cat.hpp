//
//  Cat.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/01.
//
//

#ifndef Cat_hpp
#define Cat_hpp

#include<string>
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

struct Cat{
    explicit Cat(int id);
    Cat()=default;
    
    static std::string neko_id_to_string(int id){
        return "cat/neko" + ((id < 10) ? "0" + std::to_string(0) : std::to_string(0)) + ".png";
    }
    
    CC_SYNTHESIZE(int, _id, Id);
    CC_SYNTHESIZE(std::string, _name, Name);
    CC_SYNTHESIZE(std::string, _discription, Discription);

private:
};

struct CatIcon : public cocos2d::ui::Button{
    virtual bool init(int id);
    static CatIcon* create(int id);
    
    explicit CatIcon(int id):_cat(Cat(id)){}
    virtual ~CatIcon()=default;
    
    void setSelect(bool isSelected);
    bool getSelect(){return _isSelected;}
    
    void changeState(){setSelect(!_isSelected);}
    
private:
    Cat _cat;
    bool _isSelected=false;
};

#endif /* Cat_hpp */
