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

	//create right vector from look Direction
	Vector3 right;
	m_forward.Cross(Vector3::UnitY, right);
	right.Normalize();

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
		m_camPosition += right * m_moveSpeed;
	}
	if (m_InputCommands.left)
	{
		m_camPosition -= right * m_moveSpeed;
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

DirectX::SimpleMath::Vector3 Camera::GetPosition() const
{
	return m_camPosition;
}

DirectX::SimpleMath::Matrix Camera::GetViewMatrix() const
{
	return Matrix::CreateLookAt(m_camPosition, m_lookAt, Vector3::UnitY);
}
