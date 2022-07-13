#pragma once

#include<GLFW/glfw3.h>
#include <glm/gtx/hash.hpp>

#include <unordered_map>

#include "camera/camera.hpp"
#include "chunk/chunk.hpp"
#include <unordered_set>

class Player {
    private:
        Camera& camera;
        std::unordered_map<glm::ivec3, Chunk*>& chunkMap;
        float speed = 5.0f;
        bool flying = false;
        bool swimming = false;
        const float NORMAL_SPEED = 5.0f;
        const float FLYING_SPEED = 50.f;
        const float SWIMMING_SPEED = 4.0f;
        bool collision =  true;
        bool gravity = true;
        bool canJump = false;
        const float gravityFactor = 50.f;
        const float jumpFactor = 11.f;
        glm::vec3 gravityVector{0};
        std::unordered_set<glm::vec3> movements;

        void update(float deltaT);
        void updateSpeed();

    public:
        Player(Camera &_camera , std::unordered_map<glm::ivec3, Chunk*>& chunkMap);
        ~Player();

        Camera getCamera();

        void keyEventListener(GLFWwindow* window , float deltaT);
        void cursorPositionEventListener(GLFWwindow* window);
        void updatePhysics();

        bool isSwimming() { 
            return swimming; 
        }
};