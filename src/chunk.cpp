#include <glm/glm.hpp>
#include <vector>
#include <map>

#include "blocks/block.hpp"
#include "utils/enums.cpp"

const int CHUNK_HEIGHT = 16;
const int CHUNK_WIDTH = 16;
const int CHUNK_DEPTH = 16;

struct BlockVertex {
    glm::vec3 pos;
	glm::vec3 norm;
    glm::vec2 tex;
};

struct BlockFace {
	glm::ivec3 a, b, c, d;
	glm::vec3 norm;
};

struct Block {
    BlockType *type;

	static inline std::map<Direction, BlockFace> faces = {
		{Direction::Down, {glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, -1, 0)}},
		{Direction::Up, {glm::vec3(0, 1, 0), glm::vec3(1, 1, 0), glm::vec3(1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, +1, 0)}},
		{Direction::South, {glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1)}},
		{Direction::North, {glm::vec3(1, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1), glm::vec3(0, 0, +1)}},
		{Direction::East, {glm::vec3(1, 0, 0), glm::vec3(1, 0, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 0), glm::vec3(+1, 0, 0)}},
		{Direction::West, {glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0)}},
	};

    Block() {
        switch(rand() % 4) {
            case 0:
                type = new Air();
            case 1:
                type = new Dirt();
            case 2:
                type = new Grass();
            case 3:
                type = new Log();
        }
    }
};

class Chunk {
    private:
        Block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];
        glm::ivec3 coordinates;
        std::vector<BlockVertex> vertices;
        std::vector<int> indices;

		std::vector<Direction> getVisibleFaces(int x, int y, int z) {
			Block block = blocks[x][y][z];
			if(!block.type->isVisible()) return {};
			std::vector<Direction> faces;
			if(x == 0 || !blocks[x - 1][y][z].type->isOpaque) faces.push_back(Direction::West);
			if(y == 0 || !blocks[x][y - 1][z].type->isOpaque) faces.push_back(Direction::Down);
			if(z == 0 || !blocks[x][y][z - 1].type->isOpaque) faces.push_back(Direction::South);
			if(x == CHUNK_WIDTH - 1 || !blocks[x + 1][y][z].type->isOpaque) faces.push_back(Direction::East);
			if(y == CHUNK_HEIGHT - 1 || !blocks[x][y + 1][z].type->isOpaque) faces.push_back(Direction::Up);
			if(z == CHUNK_DEPTH - 1 || !blocks[x][y][z + 1].type->isOpaque) faces.push_back(Direction::North);
			return faces;
		}

		void buildBlockFace(int x, int y, int z, Direction dir) {
			Block block = blocks[x][y][z];
			BlockFace face = block.faces[dir];
			glm::ivec3 pos = coordinates + glm::ivec3(x, y, z);
			int index = vertices.size();

			vertices.push_back({pos + face.a, face.norm, block.type->getTextureOffset(dir, face.a)});
			vertices.push_back({pos + face.b, face.norm, block.type->getTextureOffset(dir, face.b)});
			vertices.push_back({pos + face.c, face.norm, block.type->getTextureOffset(dir, face.c)});
			vertices.push_back({pos + face.d, face.norm, block.type->getTextureOffset(dir, face.d)});

			indices.push_back(index + 0);
			indices.push_back(index + 1);
			indices.push_back(index + 2);
			indices.push_back(index + 0);
			indices.push_back(index + 2);
			indices.push_back(index + 3);
		}
	
		void buildBlock(int x, int y, int z) {
			std::vector<Direction> visibleFaces = getVisibleFaces(x, y, z);
			for(const Direction &dir : visibleFaces) {
				buildBlockFace(x, y, z, dir);
			}
		}

    public:
        Chunk(int x, int y, int z) {
            coordinates = glm::ivec3(x, y, z);
        }

		std::vector<BlockVertex> getVertices() {
			return vertices;
		}

		std::vector<int> getIndices() {
			return indices;
		}

        void build() {
            vertices.clear();
            indices.clear();
            for (int x = 0; x < CHUNK_WIDTH; ++x) {
                for (int y = 0; y < CHUNK_HEIGHT; ++y) {
                    for (int z = 0; z < CHUNK_DEPTH; ++z) {
						buildBlock(x, y, z);
                    }
                }
            }
        }
};