#include "player.hpp"

#include "movement.hpp"

#include <iostream>

Player::Player(Camera &_camera) : camera(_camera){}

Player::~Player(){}


void Player::update(float deltaT, const std::unordered_map<glm::ivec3, Chunk*> &chunkMap ){
    glm::vec3 currentPosition = camera.getPosition();
    glm::vec3 currentAngle = camera.getAngle();
    glm::vec3 movement(0);
    glm::vec3 newDirection(0);
    
    
    if(movements.empty() && (gravity == false)) return;
    
    if(gravity){
        gravityVector += glm::vec3(0,-1,0) * gravityFactor * deltaT;

        if(Movement::canMove(currentPosition, gravityVector, chunkMap)){
            newDirection += gravityVector;
        }
        else{
            gravityVector = glm::vec3(0);
            canJump = true;
        }
    }

    for(const auto & mov : movements){
        movement += mov;
    }


    if(movement != glm::vec3(0)){
        movement = glm::normalize(movement) * speed * deltaT;
    }


    if(collision){
        std::vector<glm::vec3> axes = {glm::vec3(1,0,0),glm::vec3(0,1,0),glm::vec3(0,0,1)};

        for(const auto & axis : axes){
            glm::vec3 movementInAxis = movement * axis;
            //correct direction relative to cam angle
            glm::vec3 direction = glm::vec3(glm::rotate(glm::mat4(1.0f), currentAngle.y, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(movementInAxis.x, movementInAxis.y, movementInAxis.z, 1));
            if(Movement::canMove(camera.getPosition(), direction, chunkMap)){
                newDirection += movementInAxis;
            }
        }

    } else {
        newDirection = glm::vec3(glm::rotate(glm::mat4(1.0f), currentAngle.y, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(movement.x, movement.y, movement.z, 1));;
    }



    camera.updatePosition(newDirection);

}



void Player::keyEventListener(GLFWwindow* window , float deltaT , const std::unordered_map<glm::ivec3, Chunk*> &chunkMap ){
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
        if(canJump && gravity){
            gravityVector = MovementDirection::Up * jumpFactor * gravityFactor/4.5f;
            canJump = false;
        }else{
            movements.insert(MovementDirection::Up);
        }
    }

    update(deltaT , chunkMap);


}

void Player::cursorPositionEventListener(GLFWwindow* window){
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

