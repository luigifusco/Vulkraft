#include "glm.hpp"
#include <vector>

const int CHUNK_HEIGHT = 256;
const int CHUNK_WIDTH = 256;
const int CHUNK_DEPTH = 256;


void makeRectangle(int* arr, int o, int a, int b, int c, int d) {
	arr[o+0] = a;
	arr[o+1] = b;
	arr[o+2] = c;
	arr[o+3] = a;
	arr[o+4] = c;
	arr[o+5] = d;
}

enum BlockType {
    Air = 0,
    Grass,
    Glass
};

struct Block {
    BlockType type;

    Block() {
        type = BlockType::Air;
    }

    bool isOpaque() {
        return !(type == BlockType::Air || type == BlockType::Glass);
    }
};

struct BlockData {
    unsigned char x, y, z, type;
};

struct BlockVertex {
    glm::vec3 pos;
    glm::vec2 tex;
};

class Chunk {
    private:
        Block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];
        glm::ivec3 coordinates;
        std::vector<BlockData> chunk_data;
        std::vector<BlockVertex> chunk_graphics_vert;
        std::vector<int> chunk_graphics_idx;


    public:
        Chunk(int x, int y, int z) {
            coordinates = glm::vec3(x, y, z);
        }

        void build() {
            chunk_data.clear();
            for (int x = 0; x < CHUNK_WIDTH; ++x) {
                for (int y = 0; y < CHUNK_HEIGHT; ++y) {
                    for (int z = 0; z < CHUNK_DEPTH; ++z) {
                        Block b = blocks[x][y][z];
                        if (b.type != BlockType::Air) {
                            BlockData d = {x, y, z, b.type};
                            chunk_data.push_back(d);
                        }
                    }
                }
            }
        }

        void buildGraphics() {
            build();
            chunk_graphics_vert.clear();
            chunk_graphics_idx.clear();
            idx_offset = 0;
            for (BlockData &b : chunk_data) {
                glm::vec3 blockPos(coordinates.x+b.x, coordinates.y+b.y, coordinates.z+b.z);
                makeRectangle(M1_indices.data(), 0, 0, 1, 2, 3);
                makeRectangle(M1_indices.data(), 6, 4, 5, 6, 7);
                makeRectangle(M1_indices.data(), 12, 0, 1, 5, 4);
                makeRectangle(M1_indices.data(), 18, 2, 3, 7, 6);
                makeRectangle(M1_indices.data(), 24, 1, 2, 6, 5);
                makeRectangle(M1_indices.data(), 30, 0, 3, 7, 4);               
            }
        }
};