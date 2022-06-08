#include "movement.hpp"
#include <iostream>
#include <glm/gtx/hash.hpp>
#include <unordered_set>
#include <unordered_map>

#include "AABB.hpp"

std::vector<glm::ivec3> Movement::getPositionsToCheck(glm::vec3 position){
    std::vector<glm::ivec3> positions;
    for(int x = -1 ; x<2 ; x++){
        for(int y = -2 ; y<2 ; y++){
            for(int z = -1 ; z<2 ; z++){
                positions.push_back(glm::ivec3((int)position.x +x, (int)position.y +y, (int)position.z +z));
            }
        }
    }

    return positions;
}


bool Movement::canMove(const glm::vec3 & position ,const glm::vec3 & direction, const std::unordered_map<glm::ivec3, Chunk*> &chunkMap){
    PlayerAABB playerBox;    
    glm::vec3 endPosition = position + direction;
    std::vector<glm::ivec3> positionsToCheck = Movement::getPositionsToCheck(endPosition);
    std::unordered_map<glm::vec3 , glm::ivec3> chunkToCheck;



    for(glm::vec3 & point: playerBox.points){
        point += endPosition;
    }

    for(auto & pos : positionsToCheck){
        auto chunkIndex = Chunk::findChunkIndex(pos , chunkMap);
        auto chunkPair = chunkMap.find(chunkIndex);
        if(chunkPair == chunkMap.end()){
            continue;
        }
        auto chunk = chunkPair->second;

        if(chunk->isBlockVisible(pos)){
            BlockAABB block{pos};

            if(playerBox.intersect(block)){
                return false;
            }
        }
    }

    return true;
}


glm::vec3 Movement::resolveCollision(const glm::vec3& position , const glm::vec3& movement , const std::unordered_map<glm::ivec3, Chunk*> &chunkMap ){
    glm::vec3 finalMovement{0};
    glm::vec3 step;
    

    for(float i = 0.1 ; i <= 1.0f ; i+=0.1){
        step = movement * i;

        if(!Movement::canMove(position , step, chunkMap)){
            break;
        }
        finalMovement = step;

    }

    return finalMovement;
}