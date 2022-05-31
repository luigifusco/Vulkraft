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

glm::vec2 Air::getTextureOffset(Direction dir, glm::ivec3 corner) {
	glm::vec2 fileOffset(11, 1);
	glm::vec2 blockOffset = BlockType::purge(dir, corner);
    return (fileOffset + blockOffset) * BlockType::textureSize;
}

glm::vec2 Dirt::getTextureOffset(Direction dir, glm::ivec3 corner) {
	glm::vec2 fileOffset(2, 0);
	glm::vec2 blockOffset = BlockType::purge(dir, corner);
    return (fileOffset + blockOffset) * BlockType::textureSize;
}

glm::vec2 Grass::getTextureOffset(Direction dir, glm::ivec3 corner) {
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

glm::vec2 WoodLog::getTextureOffset(Direction dir, glm::ivec3 corner) {
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

glm::vec2 WoodPlank::getTextureOffset(Direction dir, glm::ivec3 corner) {
	glm::vec2 fileOffset(5, 0);
	glm::vec2 blockOffset = BlockType::purge(dir, corner);
    return (fileOffset + blockOffset) * BlockType::textureSize;
}

glm::vec2 Stone::getTextureOffset(Direction dir, glm::ivec3 corner) {
	glm::vec2 fileOffset(1, 0);
	glm::vec2 blockOffset = BlockType::purge(dir, corner);
    return (fileOffset + blockOffset) * BlockType::textureSize;
}

glm::vec2 Cobblestone::getTextureOffset(Direction dir, glm::ivec3 corner) {
	glm::vec2 fileOffset(0, 1);
	glm::vec2 blockOffset = BlockType::purge(dir, corner);
    return (fileOffset + blockOffset) * BlockType::textureSize;
}

glm::vec2 Sand::getTextureOffset(Direction dir, glm::ivec3 corner) {
	glm::vec2 fileOffset(2, 1);
	glm::vec2 blockOffset = BlockType::purge(dir, corner);
    return (fileOffset + blockOffset) * BlockType::textureSize;
}

glm::vec2 Gravel::getTextureOffset(Direction dir, glm::ivec3 corner) {
	glm::vec2 fileOffset(3, 1);
	glm::vec2 blockOffset = BlockType::purge(dir, corner);
    return (fileOffset + blockOffset) * BlockType::textureSize;
}

glm::vec2 Bedrock::getTextureOffset(Direction dir, glm::ivec3 corner) {
	glm::vec2 fileOffset(1, 1);
	glm::vec2 blockOffset = BlockType::purge(dir, corner);
    return (fileOffset + blockOffset) * BlockType::textureSize;
}