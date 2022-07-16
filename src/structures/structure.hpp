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

class Letter : public Structure {
    protected:
        static const int HEIGHT = 11;
        static const int WIDTH = 8;

        static void generateLetter(StructureMeta* meta, glm::ivec3 base, int description[HEIGHT][WIDTH]);

    public:
        static void generate(StructureMeta* meta, glm::ivec3 base);
};

class LetterV : public Letter {
    private:
        static inline int description[HEIGHT][WIDTH] = {
            { 1, 1, 1, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 1, 0, 0, 0, 0, 1, 1, },
            { 1, 1, 1, 0, 0, 1, 1, 1, },
            { 1, 1, 1, 1, 1, 1, 1, 1, },
        };

    public:
        static void generate(StructureMeta* meta, glm::ivec3 base) {
            generateLetter(meta, base, description);
        }
};

class LetterU : public Letter {
    private:
        static inline int description[HEIGHT][WIDTH] = {
            { 1, 1, 1, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 1, 1, 1, 1, 1, 1, 1, },
        };

    public:
        static void generate(StructureMeta* meta, glm::ivec3 base) {
            generateLetter(meta, base, description);
        }
};

class LetterL : public Letter {
    private:
        static inline int description[HEIGHT][WIDTH] = {
            { 1, 1, 1, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 1, 1, 1, 1, 1, 1, 1, },
        };

    public:
        static void generate(StructureMeta* meta, glm::ivec3 base) {
            generateLetter(meta, base, description);
        }
};

class LetterK : public Letter {
    private:
        static inline int description[HEIGHT][WIDTH] = {
            { 1, 1, 1, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 0, 0, 0, 1, },
            { 1, 0, 0, 0, 0, 0, 1, 1, },
            { 1, 0, 0, 0, 0, 1, 1, 1, },
            { 1, 0, 0, 0, 1, 1, 1, 1, },
            { 1, 0, 0, 0, 0, 1, 1, 1, },
            { 1, 0, 0, 0, 0, 0, 1, 1, },
            { 1, 0, 0, 1, 0, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 1, 1, 1, 1, 1, 1, 1, },
        };

    public:
        static void generate(StructureMeta* meta, glm::ivec3 base) {
            generateLetter(meta, base, description);
        }
};

class LetterR : public Letter {
    private:
        static inline int description[HEIGHT][WIDTH] = {
            { 1, 1, 1, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 0, 0, 0, 0, 0, 1, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 1, 1, 1, 1, 1, 1, 1, },
        };

    public:
        static void generate(StructureMeta* meta, glm::ivec3 base) {
            generateLetter(meta, base, description);
        }
};

class LetterA : public Letter {
    private:
        static inline int description[HEIGHT][WIDTH] = {
            { 1, 1, 1, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 0, 0, 1, },
            { 1, 1, 1, 1, 1, 1, 1, 1, },
        };

    public:
        static void generate(StructureMeta* meta, glm::ivec3 base) {
            generateLetter(meta, base, description);
        }
};

class LetterF : public Letter {
    private:
        static inline int description[HEIGHT][WIDTH] = {
            { 1, 1, 1, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 0, 0, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 1, 1, 1, 1, 1, },
            { 1, 1, 1, 1, 1, 1, 1, 1, },
        };

    public:
        static void generate(StructureMeta* meta, glm::ivec3 base) {
            generateLetter(meta, base, description);
        }
};

class LetterT : public Letter {
    private:
        static inline int description[HEIGHT][WIDTH] = {
            { 1, 1, 1, 1, 1, 1, 1, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 0, 0, 0, 0, 0, 0, 1, },
            { 1, 1, 1, 0, 0, 1, 1, 1, },
            { 1, 1, 1, 0, 0, 1, 1, 1, },
            { 1, 1, 1, 0, 0, 1, 1, 1, },
            { 1, 1, 1, 0, 0, 1, 1, 1, },
            { 1, 1, 1, 0, 0, 1, 1, 1, },
            { 1, 1, 1, 0, 0, 1, 1, 1, },
            { 1, 1, 1, 0, 0, 1, 1, 1, },
            { 1, 1, 1, 1, 1, 1, 1, 1, },
        };

    public:
        static void generate(StructureMeta* meta, glm::ivec3 base) {
            generateLetter(meta, base, description);
        }
};

class Logo : public Structure {
    public:
        static void generate(StructureMeta* meta, glm::ivec3 base);
};