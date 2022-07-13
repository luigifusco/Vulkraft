#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

#include "chunk/chunk.hpp"


namespace MovementDirection {
    const glm::vec3 Right = glm::vec3(1,0,0);
    const glm::vec3 Left = glm::vec3(-1,0,0);
    const glm::vec3 Backward = glm::vec3(0,0,1);
    const glm::vec3 Forward = glm::vec3(0,0,-1);
    const glm::vec3 Up = glm::vec3(0,1,0);
    const glm::vec3 Down = glm::vec3(0,-1,0);
 

}

namespace Movement {

    struct CollisionResponseT {
        bool collided = false;
        glm::vec3 position{0};
    };

    static const float numSteps = 3.0f;

    CollisionResponseT canMove(const glm::vec3 & endPosition, const std::unordered_map<glm::ivec3, Chunk*> &chunkMap );

    CollisionResponseT resolveCollision(const glm::vec3& position , const glm::vec3& movement, const std::unordered_map<glm::ivec3, Chunk*> &chunkMap);

    std::vector<glm::ivec3> getPositionsToCheck(glm::vec3 position);

}