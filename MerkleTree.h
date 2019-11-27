//
//  MerkleTree.h
//  Blockchain2
//
//  Created by Emilis Baliukonis on 2019-11-10.
//  Copyright © 2019 Emilis Baliukonis. All rights reserved.
//

#ifndef MerkleTree_h
#define MerkleTree_h

#include <vector>
#include <string>

class MerkleTree {
public:
    MerkleTree(std::vector<std::string> _nodes, std::function<std::string (std::string)> _hash) : nodes(_nodes), hash(_hash) { }
    
    std::string getRoot() {
        return hashLevel(nodes);
    }
private:
    std::vector<std::string> nodes;
    std::function<std::string (std::string)> hash;
    
    std::string hashLevel(std::vector<std::string> &levelNodes) {
        std::vector<std::string> hashes;
        
        for (int i = 0; i < levelNodes.size(); i += 2) {
            if (i + 1 < levelNodes.size()) {
                hashes.push_back(hash(levelNodes.at(i) + levelNodes.at(i+1)));
            } else {
                hashes.push_back(levelNodes[i]);
            }
        }
        
        if (hashes.empty()) {
            return "";
        }
        
        if (hashes.size() == 1) {
            return hashes.at(0);
        }
        
        return hashLevel(hashes);
    }
};

#endif /* MerkleTree_h */
