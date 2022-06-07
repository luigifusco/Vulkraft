#include "movement.hpp"
#include <iostream>
#include <glm/gtx/hash.hpp>
#include <unordered_set>
#include <unordered_map>

#include "AABB.hpp"


bool Movement::canMove(const glm::vec3 & position ,const glm::vec3 & direction, const std::unordered_map<glm::ivec3, Chunk*> &chunkMap){
    PlayerAABB playerBox;    
    glm::vec3 endPosition = position + direction;
    std::unordered_map<glm::vec3 , glm::ivec3> chunkToCheck;

    // for(glm::vec3 & point: playerBox.points){
    //     point += endPosition;
    //     glm::ivec3 chunkIndex = Chunk::findChunkIndex(point , chunkMap);
    //     chunkToCheck.insert(std::pair(point , chunkIndex));
    // }
    
    
    // for(auto& pair : chunkToCheck){
    //     std::cout << "Blocks to Check: " << chunkToCheck.size() << std::endl;
    //     auto blockPosition = pair.first;
    //     auto chunkIndex = pair.second;

    //     const auto & chunkIterator = chunkMap.find(chunkIndex);
    //     if(chunkIterator  == chunkMap.end()) continue;

    //     const auto & chunk = chunkIterator->second;
    //     glm::ivec3 blockPositionInt = glm::ivec3((int)blockPosition.x , (int)blockPosition.y , (int)blockPosition.z);
    //     if(chunk->isBlockVisible(blockPositionInt)){
    //         // std::cout<< "Visible" << std::endl;
    //         BlockAABB block{blockPositionInt};

    //         if(playerBox.intersect(block)){
    //             return false;
    //         }
    //     }
    // }

    return true;
}


glm::vec3 Movement::resolveCollision(const glm::vec3& position , const glm::vec3& movement , const std::unordered_map<glm::ivec3, Chunk*> &chunkMap ){
    glm::vec3 finalMovement{0};
    glm::vec3 direction = glm::normalize(movement);
    glm::vec3 stepFactor = movement / Movement::numSteps;
    

    // while(finalMovement != movement){
    //     std::cout << "Start : " << finalMovement.x << "   " << finalMovement.y << "   " << finalMovement.z  << "\n" ;
    //     std::cout << "Start : " << movement.x << "   " << movement.y << "   " << movement.z  << "\n" ;
    //     std::cout << "AAAA" <<  std::endl;
    //     glm::vec3 stepMovement = finalMovement + stepFactor;

    //     if(!Movement::canMove(position , stepFactor, chunkMap)){
    //         break;
    //     }
    //     finalMovement = stepMovement;

    // }

    if(Movement::canMove(position , movement , chunkMap)){
        finalMovement = movement;
    }

    return finalMovement;
}