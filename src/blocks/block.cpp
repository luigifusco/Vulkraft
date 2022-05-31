#include "block.hpp"

glm::ivec2 BlockType::purge(Direction dir, glm::ivec3 coords) {
    switch(dir) {
        case Direction::Up: 
            return glm::ivec2(coords.x, coords.z);
        case Direction::Down: 
            return glm::ivec2((coords.x + 1) % 2, coords.z);
        case Direction::North: 
            return glm::ivec2(coords.x, (coords.y + 1) % 2);
        case Direction::South:
            return glm::ivec2((coords.x + 1) % 2, (coords.y + 1) % 2);
        case Direction::East: 
            return glm::ivec2((coords.z + 1) % 2, (coords.y + 1) % 2);
        case Direction::West:
            return glm::ivec2(coords.z, (coords.y + 1) % 2);
    }
}

glm::ivec2 Air::getTextureOffset(Direction dir, glm::ivec3 corner) {
    return glm::ivec2(11, 1);
}

glm::ivec2 Dirt::getTextureOffset(Direction dir, glm::ivec3 corner) {
	glm::vec2 fileOffset = glm::vec2(2, 0);
	glm::vec2 blockOffset = BlockType::purge(dir, corner);
    return (fileOffset + blockOffset) * BlockType::textureSize;
}

glm::ivec2 Grass::getTextureOffset(Direction dir, glm::ivec3 corner) {
	glm::vec2 fileOffset;
	glm::vec2 blockOffset = BlockType::purge(dir, corner);
    switch(dir) {
        case Direction::Up:
            fileOffset = glm::vec2(0, 0);	// TODO: wtf
            break;
        case Direction::Down:
            fileOffset = glm::vec2(2, 0);
            break;
        default:
            fileOffset = glm::vec2(3, 0);
            break;
    }
    return (fileOffset + blockOffset) * BlockType::textureSize;
}

glm::ivec2 Log::getTextureOffset(Direction dir, glm::ivec3 corner) {
	glm::vec2 fileOffset;
	glm::vec2 blockOffset = BlockType::purge(dir, corner);
    switch(dir) {
        case Direction::Up:
        case Direction::Down:
            fileOffset = glm::vec2(5, 1);
            break;
        default:
            fileOffset = glm::vec2(4, 1);
            break;
    }
    return (fileOffset + blockOffset) * BlockType::textureSize;
}