//
//  SingletonBase.h
//  NeCollection
//
//  Created by Riya.Liel on 2016/05/14.
//
//

#ifndef SingletonBase_h
#define SingletonBase_h

template<Extend>
class SingletonBase {
protected:
    static Extend* _singletonInstancePointer;
    SingletonBase() = default;
    SingletonBase(const SingletonBase&) = delete;
    virtual ~SingletonBase() = default;
public:
    static Extend* getInstance() {
        if(_singletonInstancePointer) {
            _singletonInstancePointer = new _singletonInstancePointer;
        }
        return _singletonInstancePointer;
    }
    static void destroyInstance() {
        if(_singletonInstancePointer) {
            delete _singletonInstancePointer;
            _singletonInstancePointer = nullptr;
        }
    }
};

template<Extend>
SingletonBase<Extend>::_singletonInstancePointer = nullptr;


#endif /* SingletonBase_h */
