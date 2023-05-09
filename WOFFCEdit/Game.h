//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "SceneObject.h"
#include "DisplayObject.h"
#include "DisplayChunk.h"
#include "ChunkObject.h"
#include "InputCommands.h"
#include <vector>

#include "Camera.h"

#include <iostream>
#include <algorithm>

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

	Game();
	~Game();

	// Initialization and management
	void Initialize(HWND window, int width, int height);
	void SetGridState(bool state);

	// Basic game loop
	void Tick(InputCommands * Input);
	void Render();

	// Rendering helpers
	void Clear();

	// IDeviceNotify
	virtual void OnDeviceLost() override;
	virtual void OnDeviceRestored() override;

	// Messages
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowSizeChanged(int width, int height);

	//tool specific
	void BuildDisplayList(std::vector<SceneObject> * SceneGraph); //note vector passed by reference 
	void BuildDisplayChunk(ChunkObject *SceneChunk);
	void SaveDisplayChunk(ChunkObject *SceneChunk);	//saves geometry et al
	void ClearDisplayList();

	//lab 6
	std::vector<int> MousePicking();
	RECT m_ScreenDimensions;
	std::vector<int> multiSelect;
	

	/**
	 * @brief Paste copied objects - Iterate through copied objects creating a new object with the copied objects values and add to the display list
	 * @param copiedIDs  - contains the the IDs of the copied objects
	 */
	void PasteObject(std::vector<int> copiedIDs);

	/**
	 * @brief Iterates through selected objects and increases or descreases their scale
	 * @param scaleUporDown  - True - scale up, False - scale down
	 * @param scaleDirection  - controls the axis in which the object is scaled
	 * @param selectedIDs  - contains the the IDs of the selected objects
	 */
	void ObjectScaling(bool scaleUpOrDown, InputCommands::ScaleDirection scaleDirection, std::vector<int> selectedIDs);
	
	void MoveObject(std::vector<int> copiedIDs, InputCommands::MoveDirection moveDirection);
	
	void RotateObject(std::vector<int> copiedIDs, InputCommands::MoveDirection moveDirection);
	
	
	void ObjectHighlightUpdate(std::vector<int> selectedIDs);

	

	 /**
	 * @brief Iterates through selected objects and turns on or off their wireframe mode
	 * @param selectedIDs  - contains the the IDs of the selected objects
	 */
	void ObjectWireframe(std::vector<int> selectedIDs);

	std::vector<DisplayObject> GetDisplayList() { return m_displayList; }

	//Bool Setters
	void setM_bIsTerrainWireframe(bool m_bIsTerrainWireframe) { this->m_bIsTerrainWireframe = m_bIsTerrainWireframe; }
	void setM_bAltDown(bool m_bAltDown) { this->m_bAltDown = m_bAltDown; }
	void setM_bObjectMovementMode(bool m_bObjectMovementMode) { this->m_bObjectMovementMode = m_bObjectMovementMode; }
	void setM_bObjectRotationMode(bool m_bObjectRotationMode) { this->m_bObjectRotationMode = m_bObjectRotationMode; }
	void setM_bObjectScalingMode(bool m_bObjectScalingMode) { this->m_bObjectScalingMode = m_bObjectScalingMode; }
	void setM_bMultiSelectActive(bool m_bMultiSelectActive) { this->m_bMultiSelectActive = m_bMultiSelectActive; }

	//Bool Getters
	bool getM_bIsTerrainWireframe() { return m_bIsTerrainWireframe; }
	bool getM_bObjectMovementMode() { return m_bObjectMovementMode; }
	bool getM_bObjectRotationMode() { return m_bObjectRotationMode; }
	bool getM_bObjectScalingMode() { return m_bObjectScalingMode; }


#ifdef DXTK_AUDIO
	void NewAudioDevice();
#endif

private:

	void Update(DX::StepTimer const& timer);

	void CreateDeviceDependentResources();
	void CreateWindowSizeDependentResources();

	void XM_CALLCONV DrawGrid(DirectX::FXMVECTOR xAxis, DirectX::FXMVECTOR yAxis, DirectX::FXMVECTOR origin, size_t xdivs, size_t ydivs, DirectX::GXMVECTOR color);

	//tool specific
	std::vector<DisplayObject>			m_displayList;
	DisplayChunk						m_displayChunk;
	InputCommands						m_InputCommands;

	//functionality
	float								m_movespeed;

	//camera
	DirectX::SimpleMath::Vector3		m_camPosition;
	DirectX::SimpleMath::Vector3		m_camOrientation;
	DirectX::SimpleMath::Vector3		m_camLookAt;
	DirectX::SimpleMath::Vector3		m_camLookDirection;
	DirectX::SimpleMath::Vector3		m_camRight;
	float m_camRotRate;

	//control variables
	bool m_grid;							//grid rendering on / off
	// Device resources.
    std::shared_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

    // Input devices.
    std::unique_ptr<DirectX::GamePad>       m_gamePad;
    std::unique_ptr<DirectX::Keyboard>      m_keyboard;
    std::unique_ptr<DirectX::Mouse>         m_mouse;

    // DirectXTK objects.
    std::unique_ptr<DirectX::CommonStates>                                  m_states;
    std::unique_ptr<DirectX::BasicEffect>                                   m_batchEffect;
    std::unique_ptr<DirectX::EffectFactory>                                 m_fxFactory;
    std::unique_ptr<DirectX::GeometricPrimitive>                            m_shape;
    std::unique_ptr<DirectX::Model>                                         m_model;
    std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>  m_batch;
    std::unique_ptr<DirectX::SpriteBatch>                                   m_sprites;
    std::unique_ptr<DirectX::SpriteFont>                                    m_font;

#ifdef DXTK_AUDIO
    std::unique_ptr<DirectX::AudioEngine>                                   m_audEngine;
    std::unique_ptr<DirectX::WaveBank>                                      m_waveBank;
    std::unique_ptr<DirectX::SoundEffect>                                   m_soundEffect;
    std::unique_ptr<DirectX::SoundEffectInstance>                           m_effect1;
    std::unique_ptr<DirectX::SoundEffectInstance>                           m_effect2;
#endif

    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texture1;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>                        m_texture2;
    Microsoft::WRL::ComPtr<ID3D11InputLayout>                               m_batchInputLayout;

#ifdef DXTK_AUDIO
    uint32_t                                                                m_audioEvent;
    float                                                                   m_audioTimerAcc;

    bool                                                                    m_retryDefault;
#endif

    DirectX::SimpleMath::Matrix                                             m_world;
    DirectX::SimpleMath::Matrix                                             m_view;
    DirectX::SimpleMath::Matrix                                             m_projection;

	Camera m_camera;

	int selectCounter = 0;
	int previousSelectedID = 0;
	

	bool m_bIsTerrainWireframe = false;//Controls the terrain wireframe mode
	bool m_bAltDown = false;//Retrieves key data from tool main
	bool m_bObjectMovementMode = false;//If true object can be moved
	bool m_bObjectRotationMode = false;//If true object can be rotated
	bool m_bObjectScalingMode = false;//If true object can be scaled
	bool m_bMultiSelectActive = false;//True when Ctrl is down
};

std::wstring StringToWCHART(std::string s);