//
//  User.hpp
//  Blockchain2
//
//  Created by Emilis Baliukonis on 2019-11-09.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#ifndef User_hpp
#define User_hpp

#include <stdio.h>
#include <string>

class User {
public:
    User(unsigned int _id, std::string _name, std::string _publicKey, double _balance) : id(_id), name(_name), publicKey(_publicKey), balance(_balance) { }
    
    unsigned int getId() const {
        return id;
    }
private:
    unsigned int id;
    std::string name;
    std::string publicKey;
    double balance;
};

#endif /* User_hpp */
