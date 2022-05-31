#pragma once

#include <glm/glm.hpp>
#include "../utils/enums.hpp"

class BlockType {
    public:
        static constexpr float textureSize = 1.0 / 16.0;
        const bool isSolid;
        const bool isOpaque;

        BlockType(bool _isSolid, bool _isOpaque) : isSolid(_isSolid), isOpaque(_isOpaque) {}

        virtual bool isVisible() {
            return true;
        }

        virtual glm::ivec2 getTextureOffset(Direction dir, glm::ivec3 corner) = 0;

        glm::ivec2 purge(Direction dir, glm::ivec3 coords);
};

class Air : public BlockType {
    public:
        Air() : BlockType(false, false) {};

        glm::ivec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        bool isVisible() {
            return false;
        }
};

class Dirt : public BlockType {
    public:
        Dirt() : BlockType(true, true) {};

        glm::ivec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;
};

class Grass : public BlockType {
    public:
        Grass() : BlockType(true, true) {};

        glm::ivec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;
};

class Log : public BlockType {
    public:
        Log() : BlockType(true, true) {};

        glm::ivec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;
};