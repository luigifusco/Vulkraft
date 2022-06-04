#pragma once

#include "blocks/block.hpp"
#include "utils/perlin_noise.hpp"

#include <unordered_map>
#include <glm/glm.hpp>

const int CHUNK_HEIGHT = 32;
const int CHUNK_WIDTH = 32;
const int CHUNK_DEPTH = 32;
const bool SHOW_CHUNK_BORDER = false;


struct BlockVertex {
    glm::vec3 pos;
	glm::vec3 norm;
    glm::vec2 tex;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();
};

struct BlockFace {
	glm::ivec3 a, b, c, d;
	glm::vec3 norm;
};

struct Block {
    BlockType *type;

	static inline std::map<Direction, BlockFace> faces = {
		{Direction::Down, {glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, -1, 0)}},
		{Direction::Up, {glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 0), glm::vec3(0, +1, 0)}},
		{Direction::South, {glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1)}},
		{Direction::North, {glm::vec3(1, 0, 1), glm::vec3(1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, +1)}},
		{Direction::East, {glm::vec3(1, 0, 0), glm::vec3(1, 1, 0), glm::vec3(1, 1, 1), glm::vec3(1, 0, 1), glm::vec3(+1, 0, 0)}},
		{Direction::West, {glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0)}},
	};

	Block();
};

class Chunk {
    private:
        Block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];
        glm::ivec3 coordinates;
        std::vector<BlockVertex> vertices;
        std::vector<uint32_t> indices;
        const siv::PerlinNoise::seed_type seed = 123456u;
        const siv::PerlinNoise perlin{ seed };

		std::vector<Direction> getVisibleFaces(int x, int y, int z);

		void buildBlockFace(int x, int y, int z, Direction dir);
	
		void buildBlock(int x, int y, int z);

		int sampleHeight(int x, int z);

		void initTerrain();

    public:
        Chunk(int x, int y, int z);

		Chunk(glm::ivec3 pos);

		std::vector<BlockVertex>& getVertices();

		std::vector<uint32_t>& getIndices();

        void build();

		void clear();
};