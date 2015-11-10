//
//  UserData.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/09.
//
//

#include"UserData.hpp"
#include"cocos2d.h"
#include<iostream>
#include<fstream>

using namespace cocos2d;

void UserData::saveFile(){
    std::string filepath = cocos2d::FileUtils::getInstance()->getWritablePath();
    std::ofstream ofs(filepath + "cat_box.csv",std::ios::trunc);
    if(!ofs.is_open())throw "can't open cat_box.csv";
    
    std::string line,cat_id;
    
    for(int id: _cat_box){
        ofs << id;
    }
    ofs << std::endl;
}

void UserData::loadFile(){
    std::string filepath = cocos2d::FileUtils::getInstance()->getWritablePath();
    std::ifstream ifs(filepath + "cat_box.csv");
    if(!ifs.is_open())throw "can't open cat_box.csv";
    
    std::string line,cat_id;
    
    _cat_box.clear();
    getline(ifs, line);
    
    std::istringstream stream(line);
    while( getline( stream, cat_id, ',' ) ) {
        if(cat_id.empty())continue;
        int id = std::atoi(cat_id.c_str());
        _cat_box.push_back(id);
        _is_obtain[id] = true;
    }
}

UserData::UserData(){
    try {
        loadFile();
    }
    catch(std::string str){
        std::cout << str << std::endl;
        exit(0);
    }
}

void UserData::addCats(int id){
    std::string filepath = cocos2d::FileUtils::getInstance()->getWritablePath();
    std::ofstream ofs(filepath + "cat_box.csv", std::ios_base::ate);
    if(!ofs.is_open())throw "can't open cat_box.csv";
    
    ofs << std::to_string(id) + ',';
    _is_obtain[id] = true;
}

void UserData::setMoney(int money){
    UserDefault::getInstance()->setIntegerForKey("money", money);
    _money = money;
}