#pragma once

#include <glm/glm.hpp>
#include <functional>

using TraceRayCallback = std::function<bool(glm::ivec3)>;

class TraceRay {
    public:
        static bool trace(TraceRayCallback callback, glm::ivec3 origin, glm::vec3 direction, int limit, glm::ivec3 &hitPos, glm::vec3 &hitNorm);
};