//
//  ModalWindow.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/12/15.
//
//

#ifndef ModalWindow_hpp
#define ModalWindow_hpp

#include "cocos2d.h"

class Modal_Window : public cocos2d::LayerColor{
public:
    static Modal_Window* create(std::string);
    virtual bool init(std::string);
    
    cocos2d::Node* getModalWindow() { return _modal_window; };
    
protected:
    cocos2d::Node* _modal_window;
};

class Confirm_Window : public Modal_Window{
public:
    static Confirm_Window* create(std::string);
    virtual bool init(std::string);
    
    void setText(std::string);
    
    void setCallBackYes(std::function<void(cocos2d::Ref*)>);
    void setCallBackNo(std::function<void(cocos2d::Ref*)>);
};

class Sell_Confirm_Window : public Confirm_Window{
public:
    static Sell_Confirm_Window* create(int selling_price);
    virtual bool init(int selling_price);
    
    template<class CONTENT>
    void setContents(std::vector<CONTENT> contents){
        for(int i=0; i<2; i++){
            for(int j=0; j<5 && i*5+j < contents.size(); j++){
                cocos2d::Sprite* sprite = contents[i+j*5].getImage();
                sprite->setScale( CONTENT_SIZE / sprite->getContentSize().width );
                addChild(sprite);
                sprite->setPosition( cocos2d::Vec2( (CONTENT_SIZE+CONTENT_MARGIN)*j ,
                                                     CONTENT_HEIGHT - (CONTENT_SIZE+CONTENT_MARGIN)*i
                                                   )
                                    );
            }
        }
    }
private:
    int _selling_price;
    const int CONTENT_SIZE = 25;
    const int CONTENT_MARGIN = 5;
    const int CONTENT_HEIGHT = 300;
};

class Buy_Confirm_Window : public Confirm_Window{
public:
    static Buy_Confirm_Window* create(int buying_price);
    virtual bool init(int buying_price);
    template<class CONTENT>
    void setContent(CONTENT content){
        cocos2d::Sprite* sprite = content.getImage();
        sprite->setScale( CONTENT_SIZE / sprite->getContentSize().width );
        addChild(sprite);
        sprite->setPosition( this->getContentSize() / 2 );
    }
    
private:
    int _buying_price;
    const int CONTENT_SIZE = 100;
    const int CONTENT_MARGIN = 5;
    const int CONTENT_HEIGHT = 300;

};

#endif /* ModalWindow_hpp */
