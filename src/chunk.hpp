#pragma once

#include "blocks/block.hpp"
#include "structures/structure.hpp"
#include "utils/perlin_noise.hpp"

#include <map>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <glm/glm.hpp>
#include <atomic>
#include <vector>

#include <vulkan/vulkan.h>

const int CHUNK_HEIGHT = 48;
const int CHUNK_WIDTH = 32;
const int CHUNK_DEPTH = 32;
const bool SHOW_CHUNK_BORDER = false;


struct BlockVertex {
    glm::vec3 pos;
	glm::vec3 norm;
    glm::vec2 tex;
	int blend;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions();
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
		const std::unordered_map<glm::ivec3, Chunk*>& chunkMap;

		std::vector<Direction> getVisibleFaces(int x, int y, int z);

		void buildBlockFace(int x, int y, int z, Direction dir);
	
		void buildBlock(int x, int y, int z);

		void buildStructure(StructureMeta* meta);

		int sampleHeight(int x, int z, float depth);

		void initTerrain();

		void initTrees();

    public:
        static siv::PerlinNoise::seed_type seed;
        static siv::PerlinNoise perlin;
        Chunk(int x, int y, int z, const std::unordered_map<glm::ivec3, Chunk*>& m);

		Chunk(glm::ivec3 pos, const std::unordered_map<glm::ivec3, Chunk*>& m);

		std::vector<BlockVertex> getVertices();

		std::vector<uint32_t> getIndices();

        void build();

		std::vector<glm::ivec3> getBlockPositions();

		static glm::ivec3 findChunkIndex(glm::vec3 position, const std::unordered_map<glm::ivec3, Chunk*> & chunkMap );

		void clear();

		std::vector<std::pair<glm::ivec3, Chunk*>> getNeighbors();

		static void setSeed(unsigned int seedIn);
		
		bool isBlockVisible(glm::ivec3 position);
};

void chunkGeneratorFunction(
	std::unordered_map<glm::ivec3, Chunk*>& chunkMap,
	std::mutex& mapM,
	std::queue<glm::ivec3>& inQ,
	std::mutex& inM,
	std::condition_variable& inC,
	std::queue<glm::ivec3>& outQ,
	std::mutex& outM,
	std::atomic_bool& isThreadStopped,
	std::atomic_bool& threadProcessing);