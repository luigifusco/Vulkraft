#include "player.hpp"

#include "movement.hpp"

#include <iostream>

Player::Player(Camera &_camera) : camera(_camera){}

Player::~Player(){}


void Player::update(float deltaT, const std::unordered_map<glm::ivec3, Chunk*> &chunkMap ){
    
    if(movements.empty()) return;
    
    glm::vec3 movement(0);
    


    for(const auto & mov : movements){
        movement += mov;

    }

    if(movement == glm::vec3(0)) return;

    movement = glm::normalize(movement) * speed * deltaT;



    glm::vec3 newPosition(0);

    if(collision){
        std::vector<glm::vec3> axes = {glm::vec3(1,0,0),glm::vec3(0,1,0),glm::vec3(0,0,1)};

        for(const auto & axis : axes){
            glm::vec3 movementInAxis = movement * axis;
            if(Movement::canMove(camera.getPosition(), movementInAxis, chunkMap)){
                newPosition += movementInAxis;
            }
        }

    }



    camera.updatePosition(newPosition);

}



void Player::onKeyEvent(GLFWwindow* window , float deltaT , const std::unordered_map<glm::ivec3, Chunk*> &chunkMap ){
    movements.clear();
    if(glfwGetKey(window, GLFW_KEY_A)) {
        movements.insert(MovementDirection::Left);
    }
    if(glfwGetKey(window, GLFW_KEY_D)) {
        movements.insert(MovementDirection::Right);
    
    }        
    if(glfwGetKey(window, GLFW_KEY_S)) {
        movements.insert(MovementDirection::Backward);
        
    }
    if(glfwGetKey(window, GLFW_KEY_W)) {
        movements.insert(MovementDirection::Forward);
        
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
        movements.insert(MovementDirection::Down);
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE)) {
        movements.insert(MovementDirection::Up);

    }

    update(deltaT , chunkMap);


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

