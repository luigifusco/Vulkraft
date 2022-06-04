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
        const float speed = 10.0f;
        std::unordered_set<glm::vec3> movements;
        bool collision =  true;
        
    private:
        void update(float deltaT, const std::unordered_map<glm::ivec3, Chunk*> &chunkMap );

    public:
        Player(Camera &_camera);
        ~Player();

        Camera getCamera();


        void onKeyEvent(GLFWwindow* window , float deltaT , const std::unordered_map<glm::ivec3, Chunk*> &chunkMap);
        void onCursorPositionEvent(GLFWwindow* window);


};