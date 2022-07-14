#include "camera.hpp"
#include <algorithm>

Camera::Camera(){
    CamMat = getMatrix();
    CamDir = glm::mat3(1.0f);
    CamPos = glm::vec3(16.0f , 300.0f , 16.0f);
    CamAng = glm::vec3(0.0f);
}

Camera::~Camera(){

}

glm::vec3 Camera::getPosition(){
    return CamPos;
}

void Camera::setPosition(glm::vec3 position){
    CamPos = position;
}

void Camera::updatePosition(glm::vec3 direction){
    CamPos += direction;
}

glm::vec3 Camera::getAngle(){
    return CamAng;
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


void Camera::updateDirection(){
    CamDir =    glm::mat3(glm::rotate(glm::mat4(1.0f), CamAng.y, glm::vec3(0.0f, 1.0f, 0.0f))) *
                glm::mat3(glm::rotate(glm::mat4(1.0f), CamAng.x, glm::vec3(1.0f, 0.0f, 0.0f))) *
                glm::mat3(glm::rotate(glm::mat4(1.0f), CamAng.z, glm::vec3(0.0f, 0.0f, 1.0f)));
}

glm::vec3 Camera::getDirection() {
    return glm::vec3(
        glm::rotate(glm::mat4(1), CamAng.y, glm::vec3(0.f, 1.f, 0.f)) *
        glm::rotate(glm::mat4(1), CamAng.x, glm::vec3(1.f, 0.f, 0.f)) *
        glm::vec4(0.f, 0.f, 1.f, 1.f));
}