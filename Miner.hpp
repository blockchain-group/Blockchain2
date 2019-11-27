//
//  Miner.hpp
//  Blockchain2
//
//  Created by Emilis Baliukonis on 2019-11-10.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#ifndef Miner_hpp
#define Miner_hpp

#include <string>
#include <iostream>
#include <vector>
#include "Block.hpp"
#include "Hash.h"
#include "Transaction.hpp"

class Miner {
public:
    Miner() {}
    Block mineBlock(std::string prevHash, unsigned int difficultyTarget, std::vector<Transaction> &transactions) {
        Block block(prevHash, time(0), difficultyTarget, transactions);
        for (unsigned int i = 0; i < 0xFFFFFFFF; i++) {
            block.setNonce(i);
            // std::cout << block.getHash() << '\n';
            if (block.isGoldenBlock()) {
                std::cout << "Block mined in attempt " << i << std::endl;
                return block;
            }
        }
        
        throw "Could not mine block";
    }
private:
    
};

#endif /* Miner_hpp */
