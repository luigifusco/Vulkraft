#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#include <limits>
#include <cmath>

const float voxelExtent = 1;
const float voxelHalfExtent = 0.5;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template <typename T> int sgnNeg(T val) {
    return -(val < T(0));
}


void raycast(glm::vec3 start, glm::vec3 dir) {
    glm::vec3 voxelIndex(floor(start.x), floor(start.y), floor(start.z));

    int stepX = (int) sgn(dir.x);
    int stepY = (int) sgn(dir.y);
    int stepZ = (int) sgn(dir.z);

    // Distance along the ray to the next voxel border from the current position (tMaxX, tMaxY, tMaxZ).
    float nextVoxelBoundaryX = voxelIndex.x + (sgnNeg(stepX) + 1);
    float nextVoxelBoundaryY = voxelIndex.y + (sgnNeg(stepY) + 1);
    float nextVoxelBoundaryZ = voxelIndex.z + (sgnNeg(stepZ) + 1);

    // tMaxX, tMaxY, tMaxZ -- distance until next intersection with voxel-border
    // the value of t at which the ray crosses the first vertical voxel boundary
    float tMaxX = (dir.x != 0) ? (nextVoxelBoundaryX - start.x) / dir.x : numeric_limits<float>::max();
    float tMaxY = (dir.y != 0) ? (nextVoxelBoundaryY - start.y) / dir.y : numeric_limits<float>::max();
    float tMaxZ = (dir.z != 0) ? (nextVoxelBoundaryZ - start.z) / dir.z : numeric_limits<float>::max();

    // tDeltaX, tDeltaY, tDeltaZ --
    // how far along the ray we must move for the horizontal component to equal the width of a voxel
    // the direction in which we traverse the grid
    // can only be FLT_MAX if we never go in that direction
    float tDeltaX = (dir.x != 0) ? stepX / dir.x : numeric_limits<float>::max();
    float tDeltaY = (dir.y != 0) ? stepY / dir.y : numeric_limits<float>::max();
    float tDeltaZ = (dir.z != 0) ? stepZ / dir.z : numeric_limits<float>::max();
}