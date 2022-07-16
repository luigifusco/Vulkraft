#pragma once

#include <glm/glm.hpp>
#include <string>
#include "../utils/enums.hpp"

class BlockType {
    public:
        static constexpr float textureSize = 1.0 / 16.0;
        const bool isSolid;
        const bool isOpaque;
        const bool isBreakable;

        BlockType(bool _isSolid, bool _isBreakable, bool _isOpaque) : isSolid(_isSolid), isBreakable(_isBreakable), isOpaque(_isOpaque) {}

        virtual bool isDiagonal() {
            return false;
        }

        virtual bool isVisible() {
            return true;
        }

        virtual bool shouldBlend() {
            return false;
        }

        virtual glm::vec3 getMaterialSettings() {
            return glm::vec3(
                1.0f,       // Minimum opacity (boolean)
                2.0f,       // Roughness
                -1.0f       // Specularity
            );
        }

        virtual glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) = 0;        

        glm::vec2 purge(Direction dir, glm::ivec3 coords);

        virtual std::string toString() = 0;
};

class Air : public BlockType {
    public:
        Air() : BlockType(false, false, false) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        bool isVisible() override {
            return false;
        }

        std::string toString() override {
            return "Air";
        }
};

class Dirt : public BlockType {
    public:
        Dirt() : BlockType(true, true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        std::string toString() override {
            return "Dirt";
        }
};

class Grass : public BlockType {
    public:
        Grass() : BlockType(true, true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        std::string toString() override {
            return "Grass";
        }
};

class WoodLog : public BlockType {
    public:
        WoodLog() : BlockType(true, true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        std::string toString() override {
            return "WoodLog";
        }
};

class WoodPlank : public BlockType {
    public:
        WoodPlank() : BlockType(true, true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        std::string toString() override {
            return "WoodPlank";
        }
};

class Stone : public BlockType {
    public:
        Stone() : BlockType(true, true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        std::string toString() override {
            return "Stone";
        }
};

class Cobblestone : public BlockType {
    public:
        Cobblestone() : BlockType(true, true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        std::string toString() override {
            return "Cobblestone";
        }
};

class Sand : public BlockType {
    public:
        Sand() : BlockType(true, true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        std::string toString() override {
            return "Sand";
        }
};

class Gravel : public BlockType {
    public:
        Gravel() : BlockType(true, true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        std::string toString() override {
            return "Gravel";
        }
};

class Bedrock : public BlockType {
    public:
        Bedrock() : BlockType(true, false, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        std::string toString() override {
            return "Bedrock";
        }
};

class Leaves : public BlockType {
    public:
        Leaves() : BlockType(true, true, false) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        std::string toString() override {
            return "Leaves";
        }
};

class Water : public BlockType {
    public:
        Water() : BlockType(false, false, false) {};

        bool shouldBlend() override {
            return true;
        }

        glm::vec3 getMaterialSettings() override {
            return glm::vec3(
                0.0f,       // Minimum opacity (boolean)
                0.3f,       // Roughness
                200.0f      // Specularity
            );
        }

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        std::string toString() override {
            return "Water";
        }
};

class Bush : public BlockType {
    public:
        Bush() : BlockType(false, true, false) {};

        bool isDiagonal() override {
            return true;
        }

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        std::string toString() override {
            return "Bush";
        }
};

class BlackWool : public BlockType {
    public:
        BlackWool() : BlockType(true, true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        std::string toString() override {
            return "BlackWool";
        }
};

class WhiteWool : public BlockType {
    public:
        WhiteWool() : BlockType(true, true, true) {};

        glm::vec2 getTextureOffset(Direction dir, glm::ivec3 corner) override;

        std::string toString() override {
            return "WhiteWool";
        }
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
extern const Bush* BUSH;
extern const BlackWool* BLACK_WOOL;
extern const WhiteWool* WHITE_WOOL;
/* -------------------------  */