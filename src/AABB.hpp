#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <array>


struct AABB {
    public:
        std::array<glm::vec3, 8> points;


    public:
        AABB(std::array<glm::vec3, 8> points);
        AABB(glm::vec3 position, float offset);
        ~AABB() = default;
        
        bool intersect(AABB & aabb);

        float getMinAt(int index);
        float getMaxAt(int index);

        float getMinX() {return getMinAt(0);};
        float getMinY() {return getMinAt(1);};
        float getMinZ() {return getMinAt(2);};
        float getMaxX() {return getMaxAt(0);};
        float getMaxY() {return getMaxAt(1);};
        float getMaxZ() {return getMaxAt(2);};

};


struct PlayerAABB : public AABB {

    public:
        PlayerAABB();

};


struct BlockAABB : public AABB{

    public:
        BlockAABB(glm::vec3 blockPosition);

};