//
//  dbIO.cpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/31.
//
//

#include "dbIO.hpp"
#include "cocos2d.h"

USING_NS_CC;

dbIO::dbIO(){
    //DBファイルの保存先のパス
    auto filePath = FileUtils::getInstance()->getWritablePath();
    filePath.append("Neco.db");
    CCLOG("%s",filePath.c_str());
    
    //OPEN
    auto status = sqlite3_open(filePath.c_str(), &useDataBase);
    
    //ステータスが0以外の場合はエラーを表示
    if (status != SQLITE_OK){
        CCLOG("opne failed : %s", errorMessage);
        exit(1);
    }else{
        CCLOG("open sucessed");
    }
    
}

bool dbIO::createTable(std::string str){
    int status;
    
    status = sqlite3_exec(useDataBase, str.c_str(), NULL, NULL, &errorMessage );
    if( status != SQLITE_OK ){
        CCLOG("create table failed : %s", errorMessage);
        return false;
    }
    
    return true;
}

bool dbIO::insertTable(std::string){
    int status;
    
    auto insert_sql = "INSERT INTO neco(id,name, discription) VALUES(1,'neco1', 'first neco')";
    status = sqlite3_exec(useDataBase, insert_sql , NULL, NULL, &errorMessage);
    if( status != SQLITE_OK ){
        CCLOG("insert failed : %s", errorMessage);
        return false;
    }
    return true;
}

dbIO::~dbIO(){
    sqlite3_close(useDataBase);
}
