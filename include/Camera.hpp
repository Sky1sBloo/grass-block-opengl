#pragma once
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	/**
	 * Constructor for camera
	 *
	 * @param pos Starting position of camera
	 * @param dir Modifies the pitch roll yaw
	 */
	Camera(const glm::vec3& pos = glm::vec3(0.f, 0.f, 0.f), 
			const glm::vec3& dir = glm::vec3(-90.f, 0.f, 0.f));

	/**
	 * Sets the projection to a perspective camera
	 *
	 * @param fovDef Field of view in degrees
	 * @param aspect Aspect ratio of the perspective
	 * @param near Min clipping distance
	 * @param far Max clipping distance
	 */
	void SetPerspective(float fovDeg, float aspect, float near, float far);

	/**
	 * Moves the position vector
	 *
	 * @param dir Direction where camera moves
	 */
	void Move(const glm::vec3& dir, float deltaTime);
	/**
	 * Gets the current camera view
	 *
	 * @return Product of projection and view
	 */
	glm::mat4 GetView() const { return  mProjection * mView; }

	/**
	 * Sets the camera direction
	 *
	 * @param dir Vec3 direction in degrees
	 * 	dir.x = yaw
	 * 	dir.y = pitch
	 * 	dir.z = roll
	 */
	void SetDirection(const glm::vec3& dirDeg);

	float GetSensitivity() const { return mCameraSens; }

	glm::vec3 GetPosition() const { return mPos; }
	glm::vec3 GetFront() const { return mFront; }
	glm::vec3 GetUp() const { return mUp; }
	glm::vec3 GetRight() const { return glm::cross(mFront, mUp); }
private:
	// Position
	glm::vec3 mPos;
	glm::vec3 mFront = glm::vec3(0.f, 0.f, 1.f);
	glm::vec3 mUp = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 mDir; 

	// Use these variables to change the camera face direction
	float mPitch;
	float mRoll;
	float mYaw = -90.f;

	// Camera settings
	glm::mat4 mProjection;
	glm::mat4 mView;

	const float mCameraSpeed = 3.0f;
	const float mCameraSens = 0.1f;
};
