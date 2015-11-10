//
//  Utility.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/01.
//
//

#ifndef Utility_h
#define Utility_h

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


#endif /* Utility_h */
