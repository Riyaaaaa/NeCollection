//
//  dbIO.hpp
//  NeCollection
//
//  Created by Riya.Liel on 2015/10/31.
//
//

#ifndef dbIO_hpp
#define dbIO_hpp

#include "SQLite/sqlite3.h"
#include "Cat.hpp"
#include "Products.hpp"

class dbIO{
public:
    static dbIO* getInstance(){static dbIO shared_instance; return &shared_instance;}
    
    bool createTable(std::string);
    bool insertTable(std::string);
    
    bool queryTableWritable(std::string);
    
    /* query to cat table */
    bool insertCat(int id,std::string name,std::string discription);
    Cat getCatById(int id);
    std::string getCatNameById(int id);
    std::vector<Cat> getCatAll();
    
    /* query to product table*/
    std::vector<Products> getProductAll();
    std::vector<Products> getProductTypeAll(PRODUCTS);
    bool getProductIsObtain(int);
    
    std::vector<int> getPrimaryKeys(std::string table);
    
    std::vector<int> getColumnsInt(std::string table,std::string column);
    std::vector<std::string> getColumnsText(std::string table,std::string column);
    
    ~dbIO();
    
private:
    dbIO();
    dbIO(const dbIO& rhs)=default;
    
    sqlite3* useDataBase = nullptr;
    sqlite3* writableDataBase = nullptr;
    char* errorMessage = nullptr;
};

#endif /* dbIO_hpp */
