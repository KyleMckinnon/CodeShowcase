#pragma once

#include "core.h"

class cMesh;

class cScene
{
public:

	cScene() 
	{
		m_cameraId	= 0;
		m_lightId	= 0;
	}

	~cScene() {}
	void init(float w, float h);
	void render();
	void update();
	void openSDF();

	cShaderInfo		m_ShaderInfo;
	cCamera*		m_Camera;
	cLight*			m_Light;
	cMesh*			m_Mesh;
	cMesh*			m_Hud;
	cMesh*			m_Prim; // basic primitives used to represent light / camera objects etc

	sShaderDetails* ShaderTable;

	int m_shader_count;
	int m_camera_count;
	int m_light_count;
	int m_prim_count; // primitive count
	int m_mesh_count;
	int m_hud_count;
	int m_cameraId;
	int m_lightId;
	int width;
	int height;


private:

};