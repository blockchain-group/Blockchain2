//
//  Transaction.hpp
//  Blockchain2
//
//  Created by Emilis Baliukonis on 2019-11-09.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#ifndef Transaction_hpp
#define Transaction_hpp

#include <stdio.h>
#include <string>
#include "Hash.h"

class Transaction {
public:
    Transaction(unsigned int _senderId, unsigned int _recipientId, double _amount) : senderId(_senderId), recipientId(_recipientId), amount(_amount) {
        id = getHash();
    }
    
    std::string getId() const {
        return id;
    }
    
    std::string getHash() {
        return Hash::getHash(toString());
    }
private:
    std::string id;
    unsigned int senderId;
    unsigned int recipientId;
    unsigned int timestamp;
    double amount;
    
    std::string toString() {
        return std::to_string(senderId) + "_" + std::to_string(recipientId) + "_" + std::to_string(timestamp) + "_" + std::to_string(amount);
    }
};

#endif /* Transaction_hpp */
