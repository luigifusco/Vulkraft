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

        virtual bool shouldBlend() {
            return false;
        }

        virtual glm::vec3 getMaterialSettings() {
            return glm::vec3(
                0.0f,       // Blend (boolean)
                2.0f,       // Roughness
                200.0f      // Specularity
            );
        }

        virtual glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) = 0;        

        glm::vec2 purge(Direction dir, glm::ivec3 coords);
};

class Air : public BlockType {
    public:
        Air() : BlockType(false, false) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        bool isVisible() override {
            return false;
        }
};

class Dirt : public BlockType {
    public:
        Dirt() : BlockType(true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;
};

class Grass : public BlockType {
    public:
        Grass() : BlockType(true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;
};

class WoodLog : public BlockType {
    public:
        WoodLog() : BlockType(true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;
};

class WoodPlank : public BlockType {
    public:
        WoodPlank() : BlockType(true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;
};

class Stone : public BlockType {
    public:
        Stone() : BlockType(true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;
};

class Cobblestone : public BlockType {
    public:
        Cobblestone() : BlockType(true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;
};

class Sand : public BlockType {
    public:
        Sand() : BlockType(true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;
};

class Gravel : public BlockType {
    public:
        Gravel() : BlockType(true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;
};

class Bedrock : public BlockType {
    public:
        Bedrock() : BlockType(true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;
};

class Leaves : public BlockType {
    public:
        Leaves() : BlockType(true, false) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;
};

class Water : public BlockType {
    public:
        Water() : BlockType(false, false) {};

        bool shouldBlend() override {
            return true;
        }

        glm::vec3 getMaterialSettings() override {
            return glm::vec3(
                0.0f,       // Blend (boolean)
                0.3f,       // Roughness
                20.0f       // Specularity
            );
        }

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;
};

/* singleton block definition */
extern const Air* AIR;
extern const Dirt* DIRT;
extern const Grass* GRASS;
extern const WoodLog* WOOD_LOG;
extern const WoodPlank* WOOD_PLANK;
extern const Stone* STONE;
extern const Cobblestone* COBBLESTONE;
extern const Sand* SAND;
extern const Bedrock* BEDROCK;
extern const Leaves* LEAVES;
extern const Water* WATER;
/* -------------------------  */