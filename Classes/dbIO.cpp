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
    
    auto insert_sql = "INSERT INTO cat(id,name, discription) VALUES(1,'neco1', 'first neco')";
    status = sqlite3_exec(useDataBase, insert_sql , NULL, NULL, &errorMessage);
    if( status != SQLITE_OK ){
        CCLOG("insert failed : %s", errorMessage);
        return false;
    }
    return true;
}

Cat dbIO::getCatById(int id){
    
    Cat cat;
    std::string sql = "select * from cat where id = '" + std::to_string(id)+ "'";
    sqlite3_stmt *stmt=nullptr;
    sqlite3_prepare(useDataBase, sql.c_str(), sql.size(), &stmt, NULL);
    
    sqlite3_reset(stmt);
    
    int r;
    if(SQLITE_ROW == (r=sqlite3_step(stmt))){
        cat.id = id;
        cat.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        cat.discription = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    }
    else{
        CCLOG("SELECT ERROR");
    }
    
    sqlite3_finalize(stmt);
    return cat;
}

std::vector<Cat> dbIO::getCatAll(){
    
    std::vector<Cat> cat;
    std::string sql = "select * from cat";
    sqlite3_stmt *stmt=nullptr;
    sqlite3_prepare(useDataBase, sql.c_str(), sql.size(), &stmt, NULL);
    
    sqlite3_reset(stmt);
    
    int r;
    while(SQLITE_ROW == (r=sqlite3_step(stmt))){
        cat.push_back(Cat());
        cat.back().id = sqlite3_column_int(stmt, 1);
        cat.back().name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        cat.back().discription = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    }
    if(r != SQLITE_DONE){
        CCLOG("SELECT ERROR");
    }
    
    sqlite3_finalize(stmt);
    return cat;
}


dbIO::~dbIO(){
    sqlite3_close(useDataBase);
}
