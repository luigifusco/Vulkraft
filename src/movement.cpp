#include "movement.hpp"
#include <iostream>


#include "AABB.hpp"


bool Movement::canMove(const glm::vec3 & position ,const glm::vec3 & direction, const std::unordered_map<glm::ivec3, Chunk*> &chunkMap){

    PlayerAABB playerBox;
    
    glm::vec3 endPosition = position + direction;

    glm::vec3 chunkIndex = Chunk::findChunkIndex(endPosition , chunkMap);

    const auto & chunkIterator = chunkMap.find(chunkIndex);
    if(chunkIterator  == chunkMap.end()) return true;

    const auto & chunk = chunkIterator->second;
    const auto & positions = chunk->getBlockPositions();

    for(auto & point: playerBox.points){
        point += endPosition;
    }

    for(const auto & position : positions){

        BlockAABB block(position);

        if(block.intersect(playerBox)){
            return false;
        }

    }





    return true;
}