#pragma once

#include<GLFW/glfw3.h>
#include <glm/gtx/hash.hpp>

#include <unordered_map>

#include "camera.hpp"
#include "chunk.hpp"
#include <unordered_set>

class Player{
    private:
        Camera& camera;
        const float speed = 5.0f;
        bool collision =  true;
        bool gravity = true;
        bool canJump = false;
        const float gravityFactor = 0.98f;
        const float jumpFactor = gravityFactor;
        glm::vec3 gravityVector{0};
        std::unordered_set<glm::vec3> movements;
        
    private:
        void update(float deltaT, const std::unordered_map<glm::ivec3, Chunk*> &chunkMap );

    public:
        Player(Camera &_camera);
        ~Player();

        Camera getCamera();


        void keyEventListener(GLFWwindow* window , float deltaT , const std::unordered_map<glm::ivec3, Chunk*> &chunkMap);
        void cursorPositionEventListener(GLFWwindow* window);


};