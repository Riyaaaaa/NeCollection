//
//  Products.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/02.
//
//

#ifndef Products_hpp
#define Products_hpp

#include "params.h"
#include "Utility.hpp"

struct Products{
    int id,price;
    bool isObtain;
    PRODUCTS type;
    std::string name;
    
    cocos2d::Sprite* getImage() { return cocos2d::Sprite::create("products/" + fill_zero(id) + ".png"); };
};

#endif /* Products_hpp */
