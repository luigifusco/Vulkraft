#include "player.hpp"

#include "movement.hpp"

#include <iostream>

Player::Player(Camera &_camera , std::unordered_map<glm::ivec3, Chunk*>& _chunkMap) : camera(_camera) , chunkMap(_chunkMap){}

Player::~Player(){}

void Player::update(float deltaT){
    glm::vec3 currentPosition = camera.getPosition();
    glm::vec3 currentAngle = camera.getAngle();
    glm::vec3 movement(0);
    glm::vec3 finalMovement(0);

    glm::ivec3 baseChunkIndex = Chunk::findChunkIndex(currentPosition);
    Chunk* chunk = chunkMap.find(baseChunkIndex)->second;
    bool wasSwimming = swimming;
    swimming = chunk->isBlockWaterGlobal(currentPosition);
    updateSpeed();

    if(!wasSwimming && swimming) {
        // Allows bouncing on the surface
        canJump = true;
    }
    
    if(movements.empty() && !gravity) return;

    if(gravity && (!swimming)){
        glm::vec3 acc = glm::vec3(0, -1, 0) * gravityFactor;
        glm::vec3 dY = gravityVector * deltaT + (0.5f * acc * deltaT * deltaT);
        if(swimming) gravityVector *= 0.8f;

        auto collisionResponse = Movement::resolveCollision(currentPosition, dY, chunkMap);

        if(collisionResponse.collided){
            gravityVector = glm::vec3(0);
            if (currentPosition.y + dY.y - collisionResponse.position.y > 0)
                canJump = true;
        }
        currentPosition = collisionResponse.position;
        gravityVector += acc * deltaT;

    }

    for(const auto & mov : movements){
        movement += mov;
    }

    if(movement != glm::vec3(0)){
        movement = glm::normalize(movement) * speed * deltaT;
    }

    if(collision){
        static const std::vector<glm::vec3> axes = {glm::vec3(1,0,0),glm::vec3(0,0,1)};

        movement = glm::vec3(glm::rotate(glm::mat4(1.0f), currentAngle.y, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(movement.x, movement.y, movement.z, 1));

        auto collisionResponse = Movement::resolveCollision(currentPosition, movement, chunkMap);
        currentPosition = collisionResponse.position;
        camera.setPosition(currentPosition);
    } else {
        finalMovement = glm::vec3(glm::rotate(glm::mat4(1.0f), currentAngle.y, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(movement.x, movement.y, movement.z, 1));;
        camera.updatePosition(finalMovement);
    }
}

void Player::updateSpeed() {
    if(flying) {
        speed = FLYING_SPEED;
    } else if(swimming) {
        speed = SWIMMING_SPEED;
    } else {
        speed = NORMAL_SPEED;
    }
}

void Player::updatePhysics(){
    collision = !collision;
    gravity = !gravity;
    flying = !flying;
    updateSpeed();
}

void Player::keyEventListener(GLFWwindow* window , float deltaT){
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
        if(canJump && gravity && !swimming){
            gravityVector = MovementDirection::Up * jumpFactor;
            canJump = false;
        }
        if (!gravity || swimming) {
            movements.insert(MovementDirection::Up);
        }
    }
    
    update(deltaT);
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

