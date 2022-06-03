#include "camera.hpp"
#include <algorithm>

Camera::Camera(){
    CamMat = getMatrix();
    CamDir = glm::mat3(1.0f);
    CamPos = glm::vec3(0.0f);
    CamAng = glm::vec3(0.0f);
}


void Camera::updateDirection(){
    CamDir =    glm::mat3(glm::rotate(glm::mat4(1.0f), CamAng.y, glm::vec3(0.0f, 1.0f, 0.0f))) *
                glm::mat3(glm::rotate(glm::mat4(1.0f), CamAng.x, glm::vec3(1.0f, 0.0f, 0.0f))) *
                glm::mat3(glm::rotate(glm::mat4(1.0f), CamAng.z, glm::vec3(0.0f, 0.0f, 1.0f)));
}

void Camera::updatePosition(glm::vec4 direction, float speed, float deltaT){
    CamPos += speed * glm::vec3(glm::rotate(glm::mat4(1.0f), CamAng.y, glm::vec3(0.0f, 1.0f, 0.0f)) * direction) * deltaT;
}

glm::vec3 Camera::getPosition(){
    return CamPos;
}

void Camera::updateAngle(double x , double y){
    
    CamAng.y += x * rotSpeed / mouseRes;
    CamAng.x += y * rotSpeed / mouseRes;
    CamAng.x = std::clamp(CamAng.x, glm::radians(-90.0f) , glm::radians(90.0f));


    updateDirection();
}

glm::mat4 Camera::getMatrix(){
    CamMat = glm::translate(glm::transpose(glm::mat4(CamDir)), -CamPos) ;
    return CamMat;
}

Camera::~Camera(){

}