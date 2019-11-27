//
//  main.cpp
//  Blockchain2
//
//  Created by Emilis Baliukonis on 2019-11-09.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "Block.hpp"
#include "Hash.h"
#include "MerkleTree.h"
#include "TransactionBuilder.hpp"
#include "UserBuilder.hpp"
#include "User.hpp"
#include "Transaction.hpp"
#include "Random.hpp"
#include "Block.hpp"
#include "Miner.hpp"

#define TRANSACTIONS_PER_BLOCK 100

std::string testHash(std::string input) {
    return "Hash(" + input + ")";
}

int main(int argc, const char * argv[]) {
    UserBuilder userBuilder(1000);
    std::vector<User> users = userBuilder.getUsers();
    
    TransactionBuilder transactionBuilder(10000, users);
    std::vector<Transaction> transactions = transactionBuilder.getTransactions();
    
    std::vector<Transaction> genesisTransactions;
    Block genesisBlock("0", 0, 0, genesisTransactions);
    
    std::stack<Block> blockchain;
    blockchain.push(genesisBlock);
    
    unsigned int difficultyTarget = 5;
    
    Miner miner1;
    
    for (int i = 0; i < 10000; i += TRANSACTIONS_PER_BLOCK) {
        std::vector<Transaction> blockTransactions(transactions.begin() + i, transactions.begin() + i + TRANSACTIONS_PER_BLOCK);
        Block block1 = miner1.mineBlock(blockchain.top().getHash(), difficultyTarget, blockTransactions);
        blockchain.push(block1);
        std::cout << "Block " << i / TRANSACTIONS_PER_BLOCK << ": " << block1.getHash() << std::endl;
    }
    
    return 0;
}
