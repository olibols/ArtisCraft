#include "Frustrum.h"

enum RelativePlanes {
	Near,
	Far,
	Left,
	Right,
	Top,
	Bottom,
};

float Plane::distanceToPoint(glm::vec3 & point)
{
	return glm::dot(point, normal) + distanceToOrigin;
}

void Frustrum::update(glm::mat4 & projViewMatrix)
{
	// left
	_planes[RelativePlanes::Left].normal.x = projViewMatrix[0][3] + projViewMatrix[0][0];
	_planes[RelativePlanes::Left].normal.y = projViewMatrix[1][3] + projViewMatrix[1][0];
	_planes[RelativePlanes::Left].normal.z = projViewMatrix[2][3] + projViewMatrix[2][0];
	_planes[RelativePlanes::Left].distanceToOrigin = projViewMatrix[3][3] + projViewMatrix[3][0];

	// right
	_planes[RelativePlanes::Right].normal.x = projViewMatrix[0][3] - projViewMatrix[0][0];
	_planes[RelativePlanes::Right].normal.y = projViewMatrix[1][3] - projViewMatrix[1][0];
	_planes[RelativePlanes::Right].normal.z = projViewMatrix[2][3] - projViewMatrix[2][0];
	_planes[RelativePlanes::Right].distanceToOrigin = projViewMatrix[3][3] - projViewMatrix[3][0];

	// bottom
	_planes[RelativePlanes::Bottom].normal.x = projViewMatrix[0][3] + projViewMatrix[0][1];
	_planes[RelativePlanes::Bottom].normal.y = projViewMatrix[1][3] + projViewMatrix[1][1];
	_planes[RelativePlanes::Bottom].normal.z = projViewMatrix[2][3] + projViewMatrix[2][1];
	_planes[RelativePlanes::Bottom].distanceToOrigin = projViewMatrix[3][3] + projViewMatrix[3][1];

	// top
	_planes[RelativePlanes::Top].normal.x = projViewMatrix[0][3] - projViewMatrix[0][1];
	_planes[RelativePlanes::Top].normal.y = projViewMatrix[1][3] - projViewMatrix[1][1];
	_planes[RelativePlanes::Top].normal.z = projViewMatrix[2][3] - projViewMatrix[2][1];
	_planes[RelativePlanes::Top].distanceToOrigin = projViewMatrix[3][3] - projViewMatrix[3][1];

	// near
	_planes[RelativePlanes::Near].normal.x = projViewMatrix[0][3] + projViewMatrix[0][2];
	_planes[RelativePlanes::Near].normal.y = projViewMatrix[1][3] + projViewMatrix[1][2];
	_planes[RelativePlanes::Near].normal.z = projViewMatrix[2][3] + projViewMatrix[2][2];
	_planes[RelativePlanes::Near].distanceToOrigin = projViewMatrix[3][3] + projViewMatrix[3][2];

	// far
	_planes[RelativePlanes::Far].normal.x = projViewMatrix[0][3] - projViewMatrix[0][2];
	_planes[RelativePlanes::Far].normal.y = projViewMatrix[1][3] - projViewMatrix[1][2];
	_planes[RelativePlanes::Far].normal.z = projViewMatrix[2][3] - projViewMatrix[2][2];
	_planes[RelativePlanes::Far].distanceToOrigin = projViewMatrix[3][3] - projViewMatrix[3][2];

	for (auto& plane : _planes) {
		float length = glm::length(plane.normal);
		plane.normal /= length;
		plane.distanceToOrigin /= length;
	}

}

bool Frustrum::isInFrustrum(AABB & box)
{
	bool result = true;
	for (auto& plane : _planes)
	{
		if (plane.distanceToPoint(box.getVP(plane.normal)) < 0)
		{
			return false;
		}
		else if (plane.distanceToPoint(box.getVN(plane.normal)) < 0)
		{
			result = true;
		}
	}
	return result;
}
