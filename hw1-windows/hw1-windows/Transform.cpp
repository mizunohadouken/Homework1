// Transform.cpp: implementation of the Transform class.

#include "Transform.h"


// TODO remove test matrix
void print3x3Matrix(mat3 mPrintMe)
{
	std::cout << mPrintMe[0][0] << " ";
	std::cout << mPrintMe[1][0] << " ";
	std::cout << mPrintMe[2][0] << "\n";
	std::cout << mPrintMe[0][1] << " ";
	std::cout << mPrintMe[1][1] << " ";
	std::cout << mPrintMe[2][1] << "\n";
	std::cout << mPrintMe[0][2] << " ";
	std::cout << mPrintMe[1][2] << " ";
	std::cout << mPrintMe[2][2] << " ";

	return;
}

// TODO remove test matrix
void print4x4Matrix(mat4 mPrintMe)
{
	std::cout << mPrintMe[0][0] << " ";
	std::cout << mPrintMe[1][0] << " ";
	std::cout << mPrintMe[2][0] << " ";
	std::cout << mPrintMe[3][0] << "\n";
	std::cout << mPrintMe[0][1] << " ";
	std::cout << mPrintMe[1][1] << " ";
	std::cout << mPrintMe[2][1] << " ";
	std::cout << mPrintMe[3][1] << "\n";
	std::cout << mPrintMe[0][2] << " ";
	std::cout << mPrintMe[1][2] << " ";
	std::cout << mPrintMe[2][2] << " ";
	std::cout << mPrintMe[3][2] << "\n";
	std::cout << mPrintMe[0][3] << " ";
	std::cout << mPrintMe[1][3] << " ";
	std::cout << mPrintMe[2][3] << " ";
	std::cout << mPrintMe[3][3] << "\n";
	return;
}

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
	float radians = degrees*pi / 180.0;

	glm::mat3 mRotation(0); // rotation matrix to return
	glm::mat3 mIdentity(1.0);
	glm::mat3 mAxisxAxisTranspose(axis.x * axis.x, axis.x * axis.y, axis.x * axis.z,
							axis.x * axis.y, axis.y * axis.y, axis.y * axis.z,
							axis.x * axis.z, axis.y * axis.z, axis.z * axis.z);
	glm::mat3 mAxisDualMatrix(0,	 axis.z, -axis.y,
							-axis.z,	  0, axis.x,
							axis.y,	 -axis.x, 0);

	// Calculate rotation matrix
	mRotation = (mIdentity * cos(radians))
				+ ((1 - cos(radians)) * mAxisxAxisTranspose)
				+ (sin(radians) * mAxisDualMatrix);

  // You will change this return call
  return mRotation;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up)
{
	vec3 vUpNorm = normalize(up);
	eye = (Transform::rotate(degrees, vUpNorm)) * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up)
{
	vec3 vEyeNorm = normalize(eye);
	vec3 vUpNorm = normalize(up);
	vec3 vUpRotAxis = cross(vEyeNorm, vUpNorm);
	
	eye = (Transform::rotate(degrees, vUpRotAxis)) * eye;
	up = (Transform::rotate(degrees, vUpRotAxis)) * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // TODO glm::lookat

	// Create coordinate frame for camera
	vec3 w = normalize(eye);
	vec3 u = normalize(cross(up, w));
	vec3 v = cross(w, u);

	// Define Rotation Matrix
	mat4 mCameraRotation(u.x, v.x, w.x, 0,
					u.y, v.y, w.y, 0,
					u.z, v.z, w.z, 0,
					0 , 0, 0, 1);

	// Define translation Matrix
	mat4 mCameraTranslation(1);
	mCameraTranslation[3][0] = -eye.x;
	mCameraTranslation[3][1] = -eye.y;
	mCameraTranslation[3][2] = -eye.z;

	// Apply translation for camera (eye) location
	mat4 mM = mCameraRotation * mCameraTranslation;

//	TODO Remove this: print4x4Matrix(mCameraTranslation);

  // You will change this return call
  return mM;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}