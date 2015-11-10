//
//  UserData.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/09.
//
//

#ifndef UserData_hpp
#define UserData_hpp

#include<vector>
#include<array>
#include"params.h"

class UserData{
public:
    static UserData* getInstance(){ static UserData obj; return &obj;}
    void addCats(int id);
    void setMoney(int money);
    int getMoney(){ return _money; };
private:
    void saveFile();
    void loadFile();
    
    UserData();
    UserData(const UserData& rhs)=default;
    
    int _money;
    std::vector<int> _cat_box;
    std::array<bool,NUMBER_OF_CATS> _is_obtain;
};

#endif /* UserData_hpp */
