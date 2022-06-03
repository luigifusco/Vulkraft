#include "player.hpp"



Player::Player(Camera &_camera) : camera(_camera){}

Player::~Player(){}


void Player::onKeyEvent(GLFWwindow* window , float deltaT){
    
    if(glfwGetKey(window, GLFW_KEY_A)) {
        camera.updatePosition(CameraDirection::Left, speed, deltaT);
    }
    if(glfwGetKey(window, GLFW_KEY_D)) {
        camera.updatePosition(CameraDirection::Right, speed, deltaT);
    
    }        
    if(glfwGetKey(window, GLFW_KEY_S)) {
        camera.updatePosition(CameraDirection::Backward, speed, deltaT);
        
    }
    if(glfwGetKey(window, GLFW_KEY_W)) {
        camera.updatePosition(CameraDirection::Forward, speed, deltaT);
        
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
        camera.updatePosition(CameraDirection::Down, speed, deltaT);

    }
    if(glfwGetKey(window, GLFW_KEY_SPACE)) {
        camera.updatePosition(CameraDirection::Up, speed, deltaT);

    }


}

void Player::onCursorPositionEvent(GLFWwindow* window){
    static double old_xpos = 0, old_ypos = 0;

    double xpos, ypos;

    glfwGetCursorPos(window , &xpos, &ypos);

    double m_dx = old_xpos - xpos;
    double m_dy = old_ypos - ypos;
    old_xpos = xpos;
    old_ypos = ypos;

    camera.updateAngle(m_dx, m_dy);

}

Camera Player::getCamera(){
    return camera;
}

