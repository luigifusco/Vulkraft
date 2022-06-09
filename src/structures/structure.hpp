#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "../blocks/block.hpp"

struct StructureMeta {
    int size = 0;
    std::vector<glm::ivec3> coords;
    std::vector<BlockType*> types;
};

class Structure {
    protected:
        static void set(StructureMeta* meta, glm::ivec3 pos, BlockType* type) {
            meta->size++;
            meta->coords.push_back(pos);
            meta->types.push_back(type);
        };
    public:
        static void generate(StructureMeta* meta, glm::ivec3 base) {};
};

class Tree : public Structure {
    private:
        static const inline std::vector<std::vector<glm::ivec3>> leavesCoords = {
            {glm::ivec3(0,0,-1), glm::ivec3(-1,0,0), glm::ivec3(0,0,0), glm::ivec3(1,0,0), glm::ivec3(0,0,1)},
            {glm::ivec3(-1,0,-1), glm::ivec3(0,0,-1), glm::ivec3(1,0,-1), glm::ivec3(-1,0,0), glm::ivec3(1,0,0), glm::ivec3(-1,0,1), glm::ivec3(0,0,1), glm::ivec3(1,0,1)},
            {glm::ivec3(-1,0,-2), glm::ivec3(0,0,-2), glm::ivec3(1,0,-2), glm::ivec3(-2,0,-1), glm::ivec3(-1,0,-1), glm::ivec3(0,0,-1), glm::ivec3(1,0,-1), glm::ivec3(2,0,-1), glm::ivec3(-2,0,0), glm::ivec3(-1,0,0), glm::ivec3(1,0,0), glm::ivec3(2,0,0), glm::ivec3(-2,0,1), glm::ivec3(-1,0,1), glm::ivec3(0,0,1), glm::ivec3(1,0,1), glm::ivec3(2,0,1), glm::ivec3(-1,0,2), glm::ivec3(0,0,2), glm::ivec3(1,0,2)},
        };
        static void buildLeaves(StructureMeta* meta, int level, glm::ivec3 base);
    public:
        static void generate(StructureMeta* meta, glm::ivec3 base);
};