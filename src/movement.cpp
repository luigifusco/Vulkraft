#include "movement.hpp"
#include <iostream>
#include <glm/gtx/hash.hpp>
#include <unordered_set>
#include <unordered_map>

#include "AABB.hpp"


bool Movement::canMove(const glm::vec3 & position ,const glm::vec3 & direction, const std::unordered_map<glm::ivec3, Chunk*> &chunkMap){
    PlayerAABB playerBox;    
    glm::vec3 endPosition = position + direction;
    std::vector<glm::ivec3> pointsToCheck;
    std::unordered_map<glm::vec3 , glm::ivec3> chunkToCheck;

    pointsToCheck = {
        glm::ivec3((int)endPosition.x , (int)endPosition.y ,     (int)endPosition.z),
        glm::ivec3((int)endPosition.x , (int)endPosition.y +1,   (int)endPosition.z),
        glm::ivec3((int)endPosition.x  +1 , (int)endPosition.y , (int)endPosition.z),
        glm::ivec3((int)endPosition.x - 1 , (int)endPosition.y,  (int)endPosition.z),
        glm::ivec3((int)endPosition.x , (int)endPosition.y -1,   (int)endPosition.z),
        glm::ivec3((int)endPosition.x -1, (int)endPosition.y +1, (int)endPosition.z),
        glm::ivec3((int)endPosition.x +1, (int)endPosition.y +1, (int)endPosition.z),
        glm::ivec3((int)endPosition.x +1, (int)endPosition.y -1, (int)endPosition.z),
        glm::ivec3((int)endPosition.x -1, (int)endPosition.y -1, (int)endPosition.z),
        
        glm::ivec3((int)endPosition.x , (int)endPosition.y ,     (int)endPosition.z+1),
        glm::ivec3((int)endPosition.x , (int)endPosition.y +1,   (int)endPosition.z+1),
        glm::ivec3((int)endPosition.x  +1 , (int)endPosition.y , (int)endPosition.z+1),
        glm::ivec3((int)endPosition.x - 1 , (int)endPosition.y,  (int)endPosition.z+1),
        glm::ivec3((int)endPosition.x , (int)endPosition.y -1,   (int)endPosition.z+1),
        glm::ivec3((int)endPosition.x -1, (int)endPosition.y +1, (int)endPosition.z+1),
        glm::ivec3((int)endPosition.x +1, (int)endPosition.y +1, (int)endPosition.z+1),
        glm::ivec3((int)endPosition.x +1, (int)endPosition.y -1, (int)endPosition.z+1),
        glm::ivec3((int)endPosition.x -1, (int)endPosition.y -1, (int)endPosition.z+1),

        glm::ivec3((int)endPosition.x , (int)endPosition.y ,     (int)endPosition.z-1),
        glm::ivec3((int)endPosition.x , (int)endPosition.y +1,   (int)endPosition.z-1),
        glm::ivec3((int)endPosition.x  +1 , (int)endPosition.y , (int)endPosition.z-1),
        glm::ivec3((int)endPosition.x - 1 , (int)endPosition.y,  (int)endPosition.z-1),
        glm::ivec3((int)endPosition.x , (int)endPosition.y -1,   (int)endPosition.z-1),
        glm::ivec3((int)endPosition.x -1, (int)endPosition.y +1, (int)endPosition.z-1),
        glm::ivec3((int)endPosition.x +1, (int)endPosition.y +1, (int)endPosition.z-1),
        glm::ivec3((int)endPosition.x +1, (int)endPosition.y -1, (int)endPosition.z-1),
        glm::ivec3((int)endPosition.x -1, (int)endPosition.y -1, (int)endPosition.z-1),

    };


    for(glm::vec3 & point: playerBox.points){
        point += endPosition;
    }

    for(auto & point : pointsToCheck){
        auto chunkIndex = Chunk::findChunkIndex(point , chunkMap);
        auto chunkPair = chunkMap.find(chunkIndex);
        if(chunkPair == chunkMap.end()){
            continue;
        }
        auto chunk = chunkPair->second;

        if(chunk->isBlockVisible(point)){
            BlockAABB block{point};

            if(playerBox.intersect(block)){
                return false;
            }
        }
    }
    
    
    // for(auto& pair : chunkToCheck){
    //     std::cout << "Blocks to Check: " << chunkToCheck.size() << std::endl;
    //     auto blockPosition = pair.first;
    //     auto chunkIndex = pair.second;

    //     const auto & chunkIterator = chunkMap.find(chunkIndex);
    //     if(chunkIterator  == chunkMap.end()) continue;

    //     const auto & chunk = chunkIterator->second;
    //     glm::ivec3 blockPositionInt = glm::ivec3((int)blockPosition.x , (int)blockPosition.y , (int)blockPosition.z);
    //     if(chunk->isBlockVisible(blockPositionInt)){
    //         std::cout<< "Visible" << std::endl;
    //         BlockAABB block{blockPositionInt};

    //         if(playerBox.intersect(block)){
    //             return false;
    //         }
    //     }
    // }

    // glm::ivec3 chunkIndex = Chunk::findChunkIndex(endPosition , chunkMap);

    // auto& chunk = chunkMap.find(chunkIndex)->second;
    // auto positions = chunk->getBlockPositions();

    // for(auto& position : positions){
    //     BlockAABB block{position};

    //     if(playerBox.intersect(block)){
    //         return false;
    //     }
    // }

    return true;
}


glm::vec3 Movement::resolveCollision(const glm::vec3& position , const glm::vec3& movement , const std::unordered_map<glm::ivec3, Chunk*> &chunkMap ){
    glm::vec3 finalMovement{0};
    glm::vec3 direction = glm::normalize(movement);
    glm::vec3 step;
    

    for(float i = 0.1 ; i <= 1.0f ; i+=0.1){
        step = movement * i;

        if(!Movement::canMove(position , step, chunkMap)){
            break;
        }
        finalMovement = step;

    }

    // if(Movement::canMove(position , movement , chunkMap)){
    //     finalMovement = movement;
    // }

    return finalMovement;
}