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

struct Cat{
    static std::string neko_id_to_string(int id){
        return "cat/neko" + ((id < 10) ? "0" + std::to_string(id) : std::to_string(id)) + ".jpg";
    }
    int id;
    std::string name,discription;
};

#endif /* Cat_hpp */
