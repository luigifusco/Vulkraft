#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <array>
#include <unordered_map>

#include <vulkan/vulkan.h>
#include <glm/gtx/hash.hpp>

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>


#include "blocks/block.hpp"
#include "utils/enums.hpp"
#include "utils/perlin_noise.hpp"
#include "chunk.hpp"


/* singleton block definition */
const Air* AIR = new Air();
const Dirt* DIRT = new Dirt();
const Grass* GRASS = new Grass();
const WoodLog* WOOD_LOG = new WoodLog();
const WoodPlank* WOOD_PLANK = new WoodPlank();
const Stone* STONE = new Stone();
const Cobblestone* COBBLESTONE = new Cobblestone();
const Sand* SAND = new Sand();
const Bedrock* BEDROCK = new Bedrock();
/* -------------------------  */

Block::Block() {
    type = (BlockType*) AIR;
}

VkVertexInputBindingDescription BlockVertex::getBindingDescription()  {
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(BlockVertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
}

std::array<VkVertexInputAttributeDescription, 3> BlockVertex::getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(BlockVertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(BlockVertex, norm);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(BlockVertex, tex);

        return attributeDescriptions;
    }


std::vector<Direction> Chunk::getVisibleFaces(int x, int y, int z) {
    Block block = blocks[x][y][z];
    if(!block.type->isVisible()) return {};
    std::vector<Direction> faces;
    if (x == 0) {
        glm::ivec3 wIndex(coordinates.x - CHUNK_WIDTH, coordinates.y, coordinates.z);
        auto iter = chunkMap.find(wIndex);
        if (iter == chunkMap.end() || !iter->second->blocks[CHUNK_WIDTH - 1][y][z].type->isOpaque) faces.push_back(Direction::West);
    } else if (!blocks[x - 1][y][z].type->isOpaque) faces.push_back(Direction::West);

    if(y == 0 || !blocks[x][y - 1][z].type->isOpaque) faces.push_back(Direction::Down);

    if (z == 0) {
        glm::ivec3 sIndex(coordinates.x, coordinates.y, coordinates.z - CHUNK_DEPTH);
        auto iter = chunkMap.find(sIndex);
        if (iter == chunkMap.end() || !iter->second->blocks[x][y][CHUNK_DEPTH - 1].type->isOpaque) faces.push_back(Direction::South);
    } else if (!blocks[x][y][z - 1].type->isOpaque) faces.push_back(Direction::South);

    if (x == CHUNK_WIDTH - 1) {
        glm::ivec3 eIndex(coordinates.x + CHUNK_WIDTH, coordinates.y, coordinates.z);
        auto iter = chunkMap.find(eIndex);
        if (iter == chunkMap.end() || !iter->second->blocks[0][y][z].type->isOpaque) faces.push_back(Direction::East);
    } else if (!blocks[x + 1][y][z].type->isOpaque) faces.push_back(Direction::East);

    if(y == CHUNK_HEIGHT - 1 || !blocks[x][y + 1][z].type->isOpaque) faces.push_back(Direction::Up);

    if (z == CHUNK_DEPTH - 1) {
        glm::ivec3 nIndex(coordinates.x, coordinates.y, coordinates.z + CHUNK_DEPTH);
        auto iter = chunkMap.find(nIndex);
        if (iter == chunkMap.end() || !iter->second->blocks[x][y][0].type->isOpaque) faces.push_back(Direction::North);
    } else if (!blocks[x][y][z + 1].type->isOpaque) faces.push_back(Direction::North);

    return faces;
}

void Chunk::buildBlockFace(int x, int y, int z, Direction dir) {
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

void Chunk::buildBlock(int x, int y, int z) {
    std::vector<Direction> visibleFaces = getVisibleFaces(x, y, z);
    for(const Direction &dir : visibleFaces) {
        buildBlockFace(x, y, z, dir);
    }
}

int Chunk::sampleHeight(int x, int z) {
    static const int octaves = 20;
    static const int minHeight = 16;
    static const float varY = 20.0;

    float dx = (float)(x + coordinates.x) / CHUNK_WIDTH;
    float dz = (float)(z + coordinates.z) / CHUNK_DEPTH;
    
    const float noise = varY * perlin.normalizedOctave2D(dx, dz, octaves);
    return std::clamp(minHeight + (int)noise, 0, CHUNK_HEIGHT - 1);
}

void Chunk::initTerrain() {
    for (int x = 0; x < CHUNK_WIDTH; ++x) {
        for (int z = 0; z < CHUNK_DEPTH; ++z) {
            int maxY = sampleHeight(x, z);
            blocks[x][0][z].type = (BlockType*) BEDROCK;
            for (int y = 1; y < maxY; ++y) {
                blocks[x][y][z].type = (BlockType*) DIRT;
            }
            if(SHOW_CHUNK_BORDER && (x == 0 || z == 0)) {
                blocks[x][maxY][z].type = (BlockType*) DIRT;
            } else {
                blocks[x][maxY][z].type = (BlockType*) GRASS;
            }
        }
    }
}


Chunk::Chunk(glm::ivec3 pos, const std::unordered_map<glm::ivec3, Chunk*>& m) : coordinates(pos), chunkMap(m) {
    initTerrain();
}

Chunk::Chunk(int x, int y, int z, const std::unordered_map<glm::ivec3, Chunk*>& m) : Chunk(glm::ivec3(x, y, z), m) {}

std::vector<BlockVertex>& Chunk::getVertices() {
    return vertices;
}

std::vector<uint32_t>& Chunk::getIndices() {
    return indices;
}

void Chunk::build() {
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

void Chunk::clear() {
    vertices.clear();
    indices.clear();
}

void chunkGeneratorFunction(
    std::unordered_map<glm::ivec3, Chunk*>& chunkMap,
    std::queue<glm::ivec3>& inQ,
    std::mutex& inM,
    std::condition_variable& inC,
    std::queue <std::pair<glm::ivec3, Chunk*>>& outQ,
    std::mutex& outM,
    std::atomic_bool& isThreadStopped) {
    while (!isThreadStopped) {
        glm::ivec3 curPos;
        {
            std::unique_lock l(inM);
            while (inQ.empty())
                inC.wait(l);
            curPos = inQ.front();
            inQ.pop();
        }
        Chunk* newChunk = new Chunk(curPos, chunkMap);
        newChunk->build();
        chunkMap.insert(std::pair(curPos, newChunk));
        {
            std::unique_lock l(outM);
            outQ.push(std::pair(curPos, newChunk));
        }
    }
}

std::vector<glm::ivec3> Chunk::getBlockPositions(){
    std::vector<glm::ivec3> positions;

    for (int x = 0 ; x < CHUNK_WIDTH ; x++){
        for(int y = 0 ; y< CHUNK_HEIGHT ; y++){
            for(int z = 0; z < CHUNK_WIDTH ; z++){
                if(blocks[x][y][z].type->isVisible()){
                    positions.push_back(coordinates + glm::ivec3(x,y,z));
                }
            }
        }
    }

    return positions;

}


glm::ivec3 Chunk::findChunkIndex(glm::vec3 position, const std::unordered_map<glm::ivec3, Chunk*> & chunkMap ) {
        return glm::vec3((int) floor(position.x / (float)CHUNK_WIDTH) * CHUNK_WIDTH, 0, (int) floor(position.z / (float)CHUNK_DEPTH) * CHUNK_DEPTH);
}
 