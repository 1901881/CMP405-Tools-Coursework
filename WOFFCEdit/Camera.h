#pragma once
#include "pch.h"

struct InputCommands;

class Camera
{
	using Vector3 = DirectX::SimpleMath::Vector3;
	using Matrix = DirectX::SimpleMath::Matrix;

public:

	void Update(const InputCommands& inputCommands);
	void Arcball(const InputCommands& m_InputCommands, float viewportWidth, float viewportHeight);
	void ObjectFocus(Vector3 m_selectedObjectPos);

	
	Matrix GetViewMatrix() const;
	
	Vector3 GetPosition() const;
	Vector3 GetLookAt() const;
	Vector3 GetUpVector() const;
	Vector3 GetRightVector() const;

	void SetSelectedObjectPosition(Vector3 m_selectedObjectPos) { this->m_selectedObjectPos = m_selectedObjectPos; }

private:
	Vector3 m_scale;
	Vector3 m_camOrientation;
	Vector3 m_camPosition{ 0.f, 3.7f, -3.5f };

	Vector3 m_forward;
	Vector3 m_upVector;
	Vector3 m_lookAt;

	Vector3 m_rightVector;

	float m_moveSpeed = 0.3f;
	float m_camRotRate = 3.f;

	//Object Focus
	Vector3 m_selectedObjectPos;
};

