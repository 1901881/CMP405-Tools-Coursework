#include "Camera.h"
#include "InputCommands.h"

using namespace DirectX;

void Camera::Update(const InputCommands& m_InputCommands)
{
	if (m_InputCommands.rotRight)
	{
		m_camOrientation.y -= m_camRotRate;
	}
	if (m_InputCommands.rotLeft)
	{
		m_camOrientation.y += m_camRotRate;
	}
	if (m_InputCommands.rotUp)
	{
		m_camOrientation.x += m_camRotRate;
	}
	if (m_InputCommands.rotDown)
	{
		m_camOrientation.x -= m_camRotRate;
	}

	m_camOrientation.y += m_InputCommands.mouseDX;
	m_camOrientation.x += m_InputCommands.mouseDY;

	// Avoid gimbal lock
	m_camOrientation.x = std::min(m_camOrientation.x, +89.f);
	m_camOrientation.x = std::max(m_camOrientation.x, -89.f);

	//create look direction from Euler angles in m_camOrientation	
	float cosY = cosf(XMConvertToRadians(m_camOrientation.y));
	float cosP = cosf(XMConvertToRadians(m_camOrientation.x));

	float sinY = sinf(XMConvertToRadians(m_camOrientation.y));
	float sinP = sinf(XMConvertToRadians(m_camOrientation.x));

	m_forward.x = sinY * cosP;
	m_forward.y = sinP;
	m_forward.z = cosP * cosY;
	m_forward.Normalize();

	//create right vector from look Directio
	m_forward.Cross(Vector3::UnitY, m_rightVector);
	m_rightVector.Normalize();

	//process input and update stuff
	if (m_InputCommands.forward)
	{
		m_camPosition += m_forward * m_moveSpeed;
	}
	if (m_InputCommands.back)
	{
		m_camPosition -= m_forward * m_moveSpeed;
	}
	if (m_InputCommands.right)
	{
		m_camPosition += m_rightVector * m_moveSpeed;
	}
	if (m_InputCommands.left)
	{
		m_camPosition -= m_rightVector * m_moveSpeed;
	}
	if (m_InputCommands.up)
	{
		m_camPosition.y += m_moveSpeed;
	}
	if (m_InputCommands.down)
	{
		m_camPosition.y -= m_moveSpeed;
	}

	//update lookat point
	m_lookAt = m_camPosition + m_forward;
}

void Camera::Arcball(const InputCommands& m_InputCommands, float viewportWidth, float viewportHeight)
{
	//Vector3 camPosition;
	//Vector3 camPosition;

	float lastMousePosX;
	float lastMousePosY;

	Vector3 pivot;//object selected position

	float PI = 3.142f;

	// step 1 : Calculate the amount of rotation given the mouse movement.
	float deltaAngleX = (2 * PI / viewportWidth); // a movement from left to right = 2*PI = 360 deg
	float deltaAngleY = (PI / viewportHeight);  // a movement from top to bottom = PI = 180 deg
	float xAngle = (lastMousePosX - m_InputCommands.mouse_X) * deltaAngleX;
	float yAngle = (lastMousePosY - m_InputCommands.mouse_Y) * deltaAngleY;

	// Extra step to handle the problem when the camera direction is the same as the up vector
	float cosAngle = m_forward.Dot(m_upVector);
	if (cosAngle * sinf(deltaAngleY) > 0.99f)
		deltaAngleY = 0;

	// step 2: Rotate the camera around the pivot point on the first axis.
	//Matrix rotationMatrixX;
	//rotationMatrixX = Matrix::CreateRotationX(xAngle, m_upVector);
	//
	//
	//m_camPosition = (rotationMatrixX * (m_camPosition - pivot)) + pivot;
}

//Move camera to selected object
void Camera::ObjectFocus(Vector3 m_selectedObjectPos)
{
	m_lookAt = m_selectedObjectPos;
	m_camOrientation = m_selectedObjectPos;
	Vector3 focusPosition = Vector3(m_selectedObjectPos.x, m_selectedObjectPos.y + 0.5, m_selectedObjectPos.z - 3);
	m_camPosition = focusPosition;
}

DirectX::SimpleMath::Matrix Camera::GetViewMatrix() const
{
	return Matrix::CreateLookAt(m_camPosition, m_lookAt, Vector3::UnitY);
}

DirectX::SimpleMath::Vector3 Camera::GetPosition() const
{
	return m_camPosition;
}

DirectX::SimpleMath::Vector3 Camera::GetLookAt() const
{
	return m_lookAt;
}

DirectX::SimpleMath::Vector3 Camera::GetUpVector() const
{
	return m_upVector;
}

DirectX::SimpleMath::Vector3 Camera::GetRightVector() const
{
	return m_rightVector;
}