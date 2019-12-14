//
//  main.cpp
//  Blockchain2
//
//  Created by Emilis Baliukonis on 2019-11-09.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#include <iostream>
#include <algorithm>
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

std::vector<Transaction> getRandomVerifiedTransactions(std::vector<Transaction> &allTransactions, int numTransactions, const std::vector<User> &users) {
    std::random_shuffle(allTransactions.begin(), allTransactions.end());
    
    std::vector<Transaction> randomTransactions(allTransactions.begin(), allTransactions.begin() + std::min(numTransactions, (int)allTransactions.size()));
    
    for (int i = 0; i < randomTransactions.size(); i++) {
        Transaction originalTransaction = randomTransactions.at(i);
        Transaction newTransaction = Transaction(originalTransaction.getSenderId(), originalTransaction.getRecipientId(), originalTransaction.getAmount(), originalTransaction.getTimestamp());
        
        User sender = users.at(originalTransaction.getSenderId());
        
        if (originalTransaction.getId() != newTransaction.getHash() || sender.getBalance() < originalTransaction.getAmount()) {
            randomTransactions.erase(randomTransactions.begin() + i);
            std::cout << "Fake transaction detected!" << std::endl;
            
            if (i > 0) {
                i--;
            }
        }
    }
    
    return randomTransactions;
}

void removeMinedTransactions(std::vector<Transaction> &allTransactions, int transactionsPerBlock) {
    allTransactions.erase(allTransactions.begin(), allTransactions.begin() + std::min(transactionsPerBlock, (int)allTransactions.size()));
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
    
    unsigned int difficultyTarget = 4;
    
    Miner miner1;
    
    for (int i = 0; i < 10000; i += TRANSACTIONS_PER_BLOCK) {
        std::vector<Transaction> blockTransactions = getRandomVerifiedTransactions(transactions, TRANSACTIONS_PER_BLOCK, users);
        Block block1 = miner1.mineBlock(blockchain.top().getHash(), difficultyTarget, blockTransactions);
        blockchain.push(block1);
        
        removeMinedTransactions(transactions, TRANSACTIONS_PER_BLOCK);
        std::cout << "Block " << i / TRANSACTIONS_PER_BLOCK << ": " << block1.getHash() << std::endl;
        std::cout << "Transactions left in pool: " << transactions.size() << std::endl;
    }
    
    return 0;
}
