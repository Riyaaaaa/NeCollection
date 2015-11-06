//
//  params.h
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/29.
//
//

#ifndef params_h
#define params_h

enum params{
    NUMBER_OF_CATS=10,
    UTILITY_SIZE = 50,
    L_ARROW_X = 0,
    L_ARROW_Y = 0,
    R_ARROW_X = 50,
    R_ARROW_Y = 0,
    ALERT_X = 150,
    ALERT_Y = 0
};

enum class PRODUCTS{
    TOY=0,
    MEAL,
    FUTON,
    TRIMMER
};

class UserPramater{
    static UserPramater* getInstance(){static UserPramater obj; return &obj;};
};

#endif /* params_h */
