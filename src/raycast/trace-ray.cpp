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

    // std::cout << "STARTING FROM: " << std::endl;
    // std::cout << origin.x << ", " << origin.y << ", " << origin.z << std::endl;
    // std::cout << direction.x << ", " << direction.y << ", " << direction.z << std::endl << std::endl;

    // std::cout << "TRACING PARAMS:" << std::endl;
    // std::cout << stepX << ", " << stepY << ", " << stepZ << std::endl;
    // std::cout << txDelta << ", " << tyDelta << ", " << tzDelta << std::endl;
    // std::cout << txMax << ", " << tyMax << ", " << tzMax << std::endl << std::endl;

    glm::vec3 current = glm::ivec3(origin);

    while(t <= limit) {
        // std::cout << "INTERSECTION:" << std::endl;
        // std::cout << current.x << ", " << current.y << ", " << current.z << std::endl;
        // std::cout << "t = " << t << std::endl;
        // std::cout << txMax << ", " << tyMax << ", " << tzMax << std::endl;

        bool stop = callback(current);
        if(stop) {
            hitPos.x = current.x;
            hitPos.y = current.y;
            hitPos.z = current.z;
            hitNorm.x = steppedIndex == 0 ? -stepX : 0;
            hitNorm.y = steppedIndex == 1 ? -stepY : 0;
            hitNorm.z = steppedIndex == 2 ? -stepZ : 0;
            // std::cout << "HIT: " << std::endl;
            // std::cout << hitPos.x << ", " << hitPos.y << ", " << hitPos.z << std::endl;
            // std::cout << hitNorm.x << ", " << hitNorm.y << ", " << hitNorm.z << std::endl << std::endl;
            return true;
        }

        if(txMax < tyMax) {
            if(txMax < tzMax) {
                current.x += stepX;
                t = txMax;
                txMax += txDelta;
                steppedIndex = 0;
                // std::cout << "FOLLOW X" << std::endl << std::endl;
            } else {
                current.z += stepZ;
                t = tzMax;
                tzMax += tzDelta;
                steppedIndex = 2;
                // std::cout << "FOLLOW Z" << std::endl << std::endl;
            }
        } else {
            if(tyMax < tzMax) {
                current.y += stepY;
                t = tyMax;
                tyMax += tyDelta;
                steppedIndex = 1;
                // std::cout << "FOLLOW Y" << std::endl << std::endl;
            } else {
                current.z += stepZ;
                t = tzMax;
                tzMax += tzDelta;
                steppedIndex = 2;
                // std::cout << "FOLLOW Z" << std::endl << std::endl;
            }
        }
    }

    hitPos.x = current.x;
    hitPos.y = current.y;
    hitPos.z = current.z;
    hitNorm.x = 0;
    hitNorm.y = 0;
    hitNorm.z = 0;
    // std::cout << "NO HIT: " << std::endl;
    // std::cout << hitPos.x << ", " << hitPos.y << ", " << hitPos.z << std::endl;
    // std::cout << hitNorm.x << ", " << hitNorm.y << ", " << hitNorm.z << std::endl << std::endl;
    return false;
}