//
//  UserData.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/11/09.
//
//

#include"UserData.hpp"
#include"cocos2d.h"
#include"dbIO.hpp"
#include<iostream>
#include<fstream>

using namespace cocos2d;

void UserData::saveFile(){
    /*
    std::string filepath = cocos2d::FileUtils::getInstance()->getWritablePath();
    std::ofstream ofs(filepath + "cat_box.csv",std::ios::trunc);
    if(!ofs.is_open())throw "can't open cat_box.csv";
    
    std::string line,cat_id;
    
    for(int id: _cat_box){
        ofs << id;
    }
    ofs << std::endl;
     */
}

void UserData::loadFile(){
    auto* db = dbIO::getInstance();
    std::vector<int> keys = db->getColumnsInt("catbox","cat_id");
    
    _cat_box.clear();
    _cat_box.resize(keys.size());
    
    for(std::size_t i=0; i<_cat_box.size(); i++){
        _cat_box[i] = keys[i];
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
    auto* db = dbIO::getInstance();
    db->queryTableWritable("insert into catbox (date,cat_id) values(datetime('now')," + std::to_string(id) + ")");
    db->queryTableWritable("update cat_isobtain set isObtain = 1 where id = " + std::to_string(id) + ";");
    _cat_box.push_back(id);
}

void UserData::setMoney(int money){
    UserDefault::getInstance()->setIntegerForKey("money", money);
    _money = money;
}