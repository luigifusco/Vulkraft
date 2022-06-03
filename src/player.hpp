#pragma once
#include<GLFW/glfw3.h>

#include "camera.hpp"

class Player{
    private:
        Camera& camera;
        const float speed = 10.0f;
        


    public:
        Player(Camera &_camera);
        ~Player();

        Camera getCamera();


        void onKeyEvent(GLFWwindow* window , float deltaT);
        void onCursorPositionEvent(GLFWwindow* window);

};