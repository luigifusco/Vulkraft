#pragma once

#include "../blocks/block.hpp"
#include "../structures/structure.hpp"
#include "../utils/perlin_noise.hpp"

#include <map>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <glm/glm.hpp>
#include <atomic>
#include <vector>

#include <vulkan/vulkan.h>

const int CHUNK_HEIGHT = 256;
const int CHUNK_WIDTH = 64;
const int CHUNK_DEPTH = 64;
const int WATER_LEVEL = 100;
const bool SHOW_CHUNK_BORDER = false;


struct BlockVertex {
    glm::vec3 pos;
	glm::vec3 norm;
    glm::vec2 tex;
	glm::vec3 mat;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions();
};

struct BlockFace {
	glm::ivec3 a, b, c, d;
	glm::vec3 norm;
};

class Block {
	public: 
    	BlockType *type;

		Block();

		BlockFace* getFace(Direction dir);
	
	private:
		static inline std::map<Direction, BlockFace> faces = {
			{Direction::Down, {glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, -1, 0)}},
			{Direction::Up, {glm::vec3(0, 1, 0), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 0), glm::vec3(0, +1, 0)}},
			{Direction::South, {glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, -1)}},
			{Direction::North, {glm::vec3(1, 0, 1), glm::vec3(1, 1, 1), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, +1)}},
			{Direction::East, {glm::vec3(1, 0, 0), glm::vec3(1, 1, 0), glm::vec3(1, 1, 1), glm::vec3(1, 0, 1), glm::vec3(+1, 0, 0)}},
			{Direction::West, {glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(0, 1, 0), glm::vec3(-1, 0, 0)}},
		};

		static inline std::map<Direction, BlockFace> diagonals = {
			{Direction::South, {glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 1), glm::vec3(1, 0, 1), glm::vec3(+1, 0, -1)}},
			{Direction::North, {glm::vec3(0, 0, 0), glm::vec3(1, 0, 1), glm::vec3(1, 1, 1), glm::vec3(0, 1, 0), glm::vec3(-1, 0, +1)}},
			{Direction::East, {glm::vec3(1, 0, 0), glm::vec3(1, 1, 0), glm::vec3(0, 1, 1), glm::vec3(0, 0, 1), glm::vec3(+1, 0, +1)}},
			{Direction::West, {glm::vec3(1, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 1), glm::vec3(1, 1, 0), glm::vec3(-1, 0, -1)}},
		};
};

class Chunk {
    private:
        Block blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEPTH];
        glm::ivec3 coordinates;
        std::vector<BlockVertex> vertices;
        std::vector<uint32_t> indices;
		std::vector<BlockVertex> waterVertices;
		std::vector<uint32_t> waterIndices;
		const std::unordered_map<glm::ivec3, Chunk*>& chunkMap;

		BlockType* selectedType = (BlockType *) WOOD_PLANK;

		std::vector<Direction> getVisibleFaces(int x, int y, int z, bool opaqueOnly);

		void buildBlockFace(int x, int y, int z, Direction dir, bool opaqueOnly);
	
		void buildBlock(int x, int y, int z, bool opaqueOnly);

		void buildStructure(StructureMeta* meta);

		int sampleHeight(int x, int z, float depth);

		void initTerrain();

		void initPlants();
		
		void initLogo();

    public:
        static siv::PerlinNoise::seed_type seed;
        static siv::PerlinNoise perlin;
        Chunk(int x, int y, int z, const std::unordered_map<glm::ivec3, Chunk*>& m);

		Chunk(glm::ivec3 pos, const std::unordered_map<glm::ivec3, Chunk*>& m);

		std::vector<BlockVertex> getVertices();

		std::vector<uint32_t> getIndices();

		std::vector<BlockVertex> getWaterVertices();

		std::vector<uint32_t> getWaterIndices();

        void build();

		std::vector<glm::ivec3> getBlockPositions();

		bool destroyLocal(glm::ivec3 position);
		bool destroyGlobal(glm::ivec3 position);

		bool placeLocal(glm::ivec3 position);
		bool placeGlobal(glm::ivec3 position);

		static glm::ivec3 findChunkIndex(glm::vec3 position);
		static glm::ivec3 findBlockIndex(glm::vec3 position);

		void clear();

		std::vector<std::pair<glm::ivec3, Chunk*>> getNeighbors();

		static void setSeed(unsigned int seedIn);
		
		bool isBlockSolidLocal(glm::ivec3 position);
		bool isBlockSolidGlobal(glm::ivec3 position);

		bool isBlockBreakableLocal(glm::ivec3 position);
		bool isBlockBreakableGlobal(glm::ivec3 position);

		bool isBlockWaterLocal(glm::ivec3 position);
		bool isBlockWaterGlobal(glm::ivec3 position);

		void spreadWater(glm::ivec3 position);

		bool selectBlockType(glm::ivec3 position);
};