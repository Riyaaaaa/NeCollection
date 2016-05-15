//
//  GlobalGameManager.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2016/05/15.
//
//

#ifndef GlobalGameManager_hpp
#define GlobalGameManager_hpp

#include "GameManagerBase.hpp"
#include "HomeScene.hpp"

class GlobalGameManager : GameManagerBase<GlobalGameManager, HomeScene>{
    
    ~GlobalGameManager();
    
    void update(float) override;
};

#endif /* GlobalGameManager_hpp */
