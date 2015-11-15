//
//  Utility.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/01.
//
//

#ifndef Utility_h
#define Utility_h

#include<cmath>
#include<string>

template<typename T>
struct remove_ptr{
    using type = T;
};

template<typename T>
struct remove_ptr<T*>{
    using type = typename remove_ptr<T>::type;
};

template<typename T>
using remove_ptr_t = typename remove_ptr<T>::type;

template<int Digit=2>
std::string fill_zero(int id){
    std::string result;
    for(int i=Digit-1; i>=0; i--){
        if( 1 <= id / pow(10,i))break;
        else result.push_back('0');
    }
    result += std::to_string(id);
    return result;
}


#endif /* Utility_h */
