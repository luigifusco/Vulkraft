#include "trace-ray.hpp"
#include <iostream>

bool TraceRay::trace(TraceRayCallback callback, glm::ivec3 origin, glm::vec3 direction, int limit, glm::ivec3 &hitPos, glm::vec3 &hitNorm) {
    direction = glm::normalize(direction);

    double t = 0.0;

    int stepX = direction.x > 0 ? 1 : -1;
    int stepY = direction.y > 0 ? 1 : -1;
    int stepZ = direction.z > 0 ? 1 : -1;

    double txDelta = direction.x != 0 ? abs(1.0 / direction.x) : std::numeric_limits<double>::infinity();
    double tyDelta = direction.y != 0 ? abs(1.0 / direction.y) : std::numeric_limits<double>::infinity();
    double tzDelta = direction.z != 0 ? abs(1.0 / direction.z) : std::numeric_limits<double>::infinity();

    double txMax = txDelta * abs(stepX);
    double tyMax = tyDelta * abs(stepY);
    double tzMax = tzDelta * abs(stepZ);

    int steppedIndex = -1;

    glm::vec3 current = glm::ivec3(origin);

    while(t <= limit) {
        bool stop = callback(current);
        if(stop) {
            hitPos.x = origin.x + t * direction.x;
            hitPos.y = origin.y + t * direction.y;
            hitPos.z = origin.z + t * direction.z;
            hitNorm.x = steppedIndex == 0 ? -stepX : 0;
            hitNorm.y = steppedIndex == 1 ? -stepY : 0;
            hitNorm.z = steppedIndex == 2 ? -stepZ : 0;
            return true;
        }

        if(txMax < tyMax) {
            if(txMax < tzMax) {
                current.x += stepX;
                t = txMax;
                txMax += txDelta;
                steppedIndex = 0;
            } else {
                current.z += stepZ;
                t = txMax;
                tzMax += tzDelta;
                steppedIndex = 2;
            }
        } else {
            if(tyMax < tzMax) {
                current.y += stepY;
                t = tyMax;
                tyMax += tyDelta;
                steppedIndex = 1;
            } else {
                current.z += stepZ;
                t = txMax;
                tzMax += tzDelta;
                steppedIndex = 2;
            }
        }
    }

    hitPos.x = origin.x + t * direction.x;
    hitPos.y = origin.y + t * direction.y;
    hitPos.z = origin.z + t * direction.z;
    hitNorm.x = 0;
    hitNorm.y = 0;
    hitNorm.z = 0;
    return false;
}