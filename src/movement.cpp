#include "movement.hpp"
#include <iostream>


bool Movement::canMove(const glm::vec3 & position ,const glm::vec3 & direction, const std::unordered_map<glm::ivec3, Chunk*> &chunkMap){

    glm::ivec3 currChunkIndex = Chunk::findChunkIndex(position, chunkMap);
    // glm::ivec3 nextChunkIndex = Chunk::findChunkIndex(position + direction , chunkMap);


//    const auto& chunk = chunkMap.find(currChunkIndex);

//    if(chunk->)



    return true;
}