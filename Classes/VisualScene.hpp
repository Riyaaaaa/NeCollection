//
//  VisualScene.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/01.
//
//

#ifndef VisualScene_hpp
#define VisualScene_hpp

#include "MainScene.h"

class VisualScene : public MainScene{
public:
    CREATE_FUNC(VisualScene);
private:
    
    enum ZOrder{
        SCENE=0,
        DICTIONARY=10,
        MAINMENU=100,
    };
    
    virtual bool init();
    bool initVisualDictionary();
};

#endif /* VisualScene_hpp */
