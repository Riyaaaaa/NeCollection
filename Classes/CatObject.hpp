//
//  cat_object.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/29.
//
//

#ifndef cat_object_hpp
#define cat_object_hpp

#include "cocos2d.h"

class CatObject{
public:
    explicit CatObject(cocos2d::Sprite* sprite):_isCome(false),_sprite(sprite){}
    virtual ~CatObject()=default;
    
    CC_SYNTHESIZE(bool, _isCome, Enable);
    CC_SYNTHESIZE_READONLY(cocos2d::Sprite*, _sprite, Image);
    
private:
};

class Toy : public CatObject{
    
};

class Futon : public CatObject{
    
};

class Meal : public CatObject{
    
};

class Trimmer : public CatObject{
    
};

#endif /* cat_object_hpp */
