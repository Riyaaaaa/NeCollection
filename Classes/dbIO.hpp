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

class dbIO{
public:
    static dbIO* getInstance(){static dbIO shared_instance; return &shared_instance;}
    
    bool createTable(std::string);
    bool insertTable(std::string);
    
    bool insertCat(int id,std::string name,std::string discription);
    Cat getCatById(int id);
    std::vector<Cat> getCatAll();
    
    ~dbIO();
    
private:
    dbIO();
    dbIO(const dbIO& rhs)=default;
    
    sqlite3* useDataBase = nullptr;
    char* errorMessage = nullptr;
};

#endif /* dbIO_hpp */
