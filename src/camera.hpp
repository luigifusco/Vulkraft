#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace CameraDirection {
    const glm::vec4 Right = glm::vec4(1,0,0,1);
    const glm::vec4 Left = glm::vec4(-1,0,0,1);
    const glm::vec4 Backward = glm::vec4(0,0,1,1);
    const glm::vec4 Forward = glm::vec4(0,0,-1,1);
    const glm::vec4 Up = glm::vec4(0,1,0,1);
    const glm::vec4 Down = glm::vec4(0,-1,0,1);
 

}

class Camera {
    private:
        const float rotSpeed =  glm::radians(60.f);
        const float mouseRes = 500.0f;
        glm::mat4 CamMat;
        glm::mat3 CamDir;
        glm::vec3 CamPos;
        glm::vec3 CamAng;
        

    private:
        void updateDirection();
    
    public:

        Camera();
        ~Camera();


        glm::mat4 getCamera();
        glm::vec3 getPosition();
        void setPOsition(glm::vec3 position);
        void updatePosition(glm::vec4 direction , float speed, float deltaT);
        glm::mat3 getDirection();
        glm::vec3 getAngle();
        void updateAngle(double x , double y);
        glm::mat4 getMatrix();

};