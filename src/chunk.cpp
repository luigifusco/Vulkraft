#include <glm/glm.hpp>
#include <vector>
#include <map>

#include "blocks/block.hpp"
#include "utils/enums.hpp"
#include "utils/perlin_noise.hpp"

const int CHUNK_HEIGHT = 127;
const int CHUNK_WIDTH = 256;
const int CHUNK_DEPTH = 256;

const bool SHOW_CHUNK_BORDER = false;

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
        type = new Air();
    }
};

class Chunk {
    private:
        Block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];
        glm::ivec3 coordinates;
        std::vector<BlockVertex> vertices;
        std::vector<int> indices;
        const siv::PerlinNoise::seed_type seed = 123456u;
        const siv::PerlinNoise perlin{ seed };

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

		int sampleHeight(int x, int z) {
            static const int octaves = 20;
			static const int minHeight = 16;
			static const float varY = 20.0;

            float dx = (float)(x + coordinates.x) / CHUNK_WIDTH;
            float dz = (float)(z + coordinates.z) / CHUNK_DEPTH;
            
            const float noise = varY * perlin.normalizedOctave2D(dx, dz, octaves);
            return std::clamp(minHeight + (int)noise, 0, CHUNK_HEIGHT - 1);
		}

		void initTerrain() {
            for (int x = 0; x < CHUNK_WIDTH; ++x) {
				for (int z = 0; z < CHUNK_DEPTH; ++z) {
					int maxY = sampleHeight(x, z);
					blocks[x][0][z].type = new Bedrock();
					for (int y = 1; y < maxY; ++y) {
						blocks[x][y][z].type = new Dirt();
                    }
                    if(SHOW_CHUNK_BORDER && (x == 0 || z == 0)) {
                        blocks[x][maxY][z].type = new Dirt();
                    } else {
                        blocks[x][maxY][z].type = new Grass();
                    }
                }
            }
		}

    public:
        Chunk(int x, int y, int z) {
            coordinates = glm::ivec3(x, y, z);
			initTerrain();
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