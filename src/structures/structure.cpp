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

    int height = rand() % dHeight + minHeight;
    for(int i = 0; i < height; i++) {
        set(meta, base + glm::ivec3(0, i, 0), (BlockType*)WOOD_LOG);
    }

    buildLeaves(meta, 0, base + glm::ivec3(0, height, 0));
    buildLeaves(meta, 1, base + glm::ivec3(0, height - 1, 0));
    buildLeaves(meta, 2, base + glm::ivec3(0, height - 2, 0));
    buildLeaves(meta, 2, base + glm::ivec3(0, height - 3, 0));
}

void Letter::generateLetter(StructureMeta* meta, glm::ivec3 base, int description[HEIGHT][WIDTH]) {
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            glm::ivec3 localPos(x, y, 0);
            BlockType* type = (description[HEIGHT - y - 1][x] == 1) ? (BlockType*)BLACK_WOOL : (BlockType*) WHITE_WOOL;
            set(meta, base + localPos, type);
        }
    }
}

void Logo::generate(StructureMeta* meta, glm::ivec3 base) {
    LetterV::generate(meta, base + glm::ivec3( 0, -10, 0));
    LetterU::generate(meta, base + glm::ivec3( 7, -10, 0));
    LetterL::generate(meta, base + glm::ivec3(14, -10, 0));
    LetterK::generate(meta, base + glm::ivec3(21, -10, 0));
    LetterR::generate(meta, base + glm::ivec3(28, -10, 0));
    LetterA::generate(meta, base + glm::ivec3(35, -10, 0));
    LetterF::generate(meta, base + glm::ivec3(42, -10, 0));
    LetterT::generate(meta, base + glm::ivec3(49, -10, 0));
}