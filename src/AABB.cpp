#include "AABB.hpp"


AABB::AABB(std::array<glm::vec3, 8> _points) : points(_points){}
AABB::AABB(std::array<glm::vec3, 8> _points , float _width , float _height , float _depth) : points(_points) , width(_width) , height(_height), depth(_depth){}


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

    width =  offset;
    height =  offset;
    depth =  offset;
}

AABB::AABB(glm::vec3 position , float width , float height , float depth) {
    points = {
       position,
       position + glm::vec3{width, height, depth},
       position + glm::vec3{width, height, 0},
       position + glm::vec3{width, 0, depth},
       position + glm::vec3{width, 0, 0},
       position + glm::vec3{0, height, depth},
       position + glm::vec3{0, height, 0},
       position + glm::vec3{0, 0, depth},
    };
}

PlayerAABB::PlayerAABB(): AABB({
     glm::vec3(0.4, 0.3, 0.4),
     glm::vec3(0.4, 0.3, -0.4),
     glm::vec3(-0.4, 0.3, 0.4),
     glm::vec3(-0.4, 0.3, -0.4),
     glm::vec3(0.4, -1.5, 0.4),
     glm::vec3(0.4, -1.5, -0.4),
     glm::vec3(-0.4, -1.5, 0.4),
     glm::vec3(-0.4, -1.5, -0.4),
  } , 0.8 , 1.8, 0.8){}

BlockAABB::BlockAABB(glm::vec3 blockPosition) : AABB(blockPosition , 1.0) {}

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
  return (getMinX() < aabb.getMaxX() && getMaxX() > aabb.getMinX()) &&
         (getMinY() < aabb.getMaxY() && getMaxY() > aabb.getMinY()) &&
         (getMinZ() < aabb.getMaxZ() && getMaxZ() > aabb.getMinZ());
}

glm::vec3 AABB::getPopOut(AABB& aabb) {
    const float OFF = 0.0001f;
    glm::vec3 mv(aabb.getMinX() - getMaxX() - OFF, 0, 0);
    if (abs(getMinX() - aabb.getMaxX()) < glm::length(mv)) {
        mv = glm::vec3(aabb.getMaxX() - getMinX() + OFF, 0, 0);
    }
    if (abs(aabb.getMinY() - getMaxY()) < glm::length(mv)) {
        mv = glm::vec3(0, aabb.getMinY() - getMaxY() - OFF, 0);
    }
    if (abs(getMinY() - aabb.getMaxY()) < glm::length(mv)) {
        mv = glm::vec3(0, aabb.getMaxY() - getMinY() + OFF, 0);
    }
    if (abs(aabb.getMinZ() - getMaxZ()) < glm::length(mv)) {
        mv = glm::vec3(0, 0, aabb.getMinZ() - getMaxZ() - OFF);
    }
    if (abs(getMinZ() - aabb.getMaxZ()) < glm::length(mv)) {
        mv = glm::vec3(0, 0, aabb.getMaxZ() - getMinZ() + OFF);
    }

    return mv;
}


