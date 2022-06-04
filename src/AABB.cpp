#include "AABB.hpp"


AABB::AABB(std::array<glm::vec3, 8> _points) : points(_points){}

AABB::AABB(glm::vec3 position , float offset) {
    points = {
       position,
       position + glm::vec3{offset, offset, offset},
       position + glm::vec3{offset, offset, 0},
       position + glm::vec3{offset, 0, offset},
       position + glm::vec3{offset, 0, 0},
       position + glm::vec3{0, offset, offset},
       position + glm::vec3{0, offset, 0},
       position + glm::vec3{0, 0, offset},
    };
}

float AABB::getMinAt(int index){
  float min = (&points[0].x)[index];

  for (int32_t i = 1; i < points.size(); i++) {
    float val = (&points[i].x)[index];
    if (val < min) {
      min = val;
    }
  }

  return min;
}

float AABB::getMaxAt(int index){
  float max = (&points[0].x)[index];

  for (int32_t i = 1; i < points.size(); i++) {
    float val = (&points[i].x)[index];
    if (val > max) {
      max = val;
    }
  }

  return max;
}



bool AABB::intersect(AABB &aabb){
  return (getMinX() <= aabb.getMaxX() && getMaxX() >= aabb.getMinX()) &&
         (getMinY() <= aabb.getMaxY() && getMaxY() >= aabb.getMinY()) &&
         (getMinZ() <= aabb.getMaxZ() && getMaxZ() >= aabb.getMinZ());
}


PlayerAABB::PlayerAABB(): AABB({
     glm::vec3(0.3, 0.3, 0.3),
     glm::vec3(0.3, 0.3, -0.3),
     glm::vec3(-0.3, 0.3, 0.3),
     glm::vec3(-0.3, 0.3, -0.3),
     glm::vec3(0.3, -1.5, 0.3),
     glm::vec3(0.3, -1.5, -0.3),
     glm::vec3(-0.3, -1.5, 0.3),
     glm::vec3(-0.3, -1.5, -0.3),
  }){}



BlockAABB::BlockAABB(glm::vec3 blockPosition) : AABB(blockPosition , 1.0) {}