#include "structure.hpp"

void Tree::buildLeaves(StructureMeta* meta, int level, glm::ivec3 base) {
    for(auto& pos : leavesCoords[level]) {
        set(meta, base + pos, (BlockType*)LEAVES);
    }
}

void Tree::generate(StructureMeta* meta, glm::ivec3 base) {
    const int minHeight = 5;
    const int dHeight = 4;

    meta->coords.clear();
    meta->types.clear();

    int height = random() % dHeight + minHeight;
    for(int i = 0; i < height; i++) {
        set(meta, base + glm::ivec3(0, i, 0), (BlockType*)WOOD_LOG);
    }

    buildLeaves(meta, 0, base + glm::ivec3(0, height, 0));
    buildLeaves(meta, 1, base + glm::ivec3(0, height - 1, 0));
    buildLeaves(meta, 2, base + glm::ivec3(0, height - 2, 0));
    buildLeaves(meta, 2, base + glm::ivec3(0, height - 3, 0));
}