#include "Camera.hpp"

Camera::Camera(const glm::vec3& pos, const glm::vec3& dir) :
	mPos(pos), mPitch(dir.y), mRoll(dir.z), mYaw(dir.x)
{
}

void Camera::SetPerspective(float fovDeg, float aspect, float near, float far)
{
	mProjection = glm::perspective(glm::radians(fovDeg), aspect,  near, far);
}

void Camera::Move(const glm::vec3& dir, float deltaTime)
{
	mPos += glm::normalize(dir) * mCameraSpeed * deltaTime;
}

void Camera::SetDirection(const glm::vec3& dirDeg)
{
	mPitch += dirDeg.y;
	mRoll += dirDeg.z;
	mYaw += dirDeg.x;
	
	if (mPitch > 89.f)
		mPitch = 89.f;
	else if (mPitch < -89.f)
		mPitch = -89.f;

	mDir.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	mDir.y = sin(glm::radians(mPitch));
	mDir.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));

	mFront = glm::normalize(mDir);
	mView = glm::lookAt(mPos, mPos + mFront, mUp);
}
