#include "movement.hpp"
#include <iostream>
#include <glm/gtx/hash.hpp>
#include <unordered_set>
#include <unordered_map>
#include <cmath>

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


Movement::CollisionResponseT Movement::canMove(const glm::vec3 & endPosition, const std::unordered_map<glm::ivec3, Chunk*> &chunkMap){
    PlayerAABB playerBox;    
    std::vector<glm::ivec3> positionsToCheck = Movement::getPositionsToCheck(endPosition);
    std::unordered_map<glm::vec3 , glm::ivec3> chunkToCheck;
    Movement::CollisionResponseT response;



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

            if(playerBox.intersect(block)){;

                response.position = playerBox.getPopOut(block);
                response.collided = true;
                return response;          

            }
        }
    }

    response.collided = false;
    response.position = endPosition;

    return response;
;
}


Movement::CollisionResponseT Movement::resolveCollision(const glm::vec3& position , const glm::vec3& movement, const std::unordered_map<glm::ivec3, Chunk*> &chunkMap){
    Movement::CollisionResponseT response;

    const float MAX_LEN = 0.01f;
    float len = glm::length(movement);
    int nSteps = ceil(len / MAX_LEN);
    glm::vec3 step = movement / (float)nSteps;
    glm::vec3 finalPos(position);
    bool collided = false;
    
    for (int i = 0; i < nSteps; ++i) {
        finalPos += step;
        auto collisionResponse = Movement::canMove(finalPos, chunkMap);
        while (collisionResponse.collided) {
            collided = true;
            finalPos += collisionResponse.position;
            collisionResponse = Movement::canMove(finalPos, chunkMap);
        }
    }

    response.collided = collided;
    response.position = finalPos;
    return response;
}