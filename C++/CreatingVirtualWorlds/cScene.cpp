#include "core.h"
#include "cMesh.h"

/////////////////////////////////////////////////////////////////////////////////////
// update() - 
/////////////////////////////////////////////////////////////////////////////////////
void cScene::update()
{
	m_Camera[m_cameraId].update();

	for (int i = 0; i < m_mesh_count; i++)
	{
		m_Mesh[i].m_transform.update();
	}

	for (int i = 0; i < m_hud_count; i++)
	{
		m_Hud[i].m_transform.update();
	}

#ifdef DEBUG_MODE
	{
		for (int i = 0; i < m_light_count; i++)
		{
			m_Light[i].pPrimitive->m_transform.update(m_Light[i].m_info.m_pos);
		}
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////
// init() - 
/////////////////////////////////////////////////////////////////////////////////////
void cScene::init(float w, float h)
{
	
	width = w;
	height = h;

	openSDF();

#ifdef DEBUG_MODE
	// load in the primitives here
	for (int i = 0; i < m_prim_count; i++)
	{
		m_Prim[i].init();
	}

	for (int i = 0; i < m_light_count; i++)
	{
		// //////////////////////////////////////////////////////////////////
		// // TO DO: change the pointer to the primitive mesh objects
		// // as only the first two primitives are getting rendered
		// //////////////////////////////////////////////////////////////////
		// 
		// set up pointers to the mesh we wish to use to represent this light
		m_Light[i].pPrimitive = &m_Prim[m_Light[i].m_prim];
	}
#endif

	for (int i = 0; i < m_mesh_count; i++)
	{
		m_Mesh[i].init();
	}

	for (int i = 0; i < m_hud_count; i++)
	{
		m_Hud[i].init();
	}

	for (int i = 0; i < m_camera_count; i++)
	{
		m_Camera[i].init(w,h);
	}

	glBindVertexArray(0);

	m_ShaderInfo.create();
}

/////////////////////////////////////////////////////////////////////////////////////
// render() - 
/////////////////////////////////////////////////////////////////////////////////////
void cScene::render()
{
	
	update();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	
	// render all mesh objects
	for (int i = 0; i < m_mesh_count; i++)
	{
		m_Mesh[i].render(this, &m_ShaderInfo);
		glReadBuffer(GL_BACK);
		glBindTexture(GL_TEXTURE_2D, m_Mesh[2].m_tex[0]);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, width, height, 0);

		glBindTexture(GL_TEXTURE_2D, m_Mesh[2].m_tex[0]);
		glDrawBuffer(GL_BACK);
	}

	

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glActiveTexture(GL_TEXTURE0 + m_Mesh[2].m_tex[0]);
#ifdef DEBUG_MODE
	for (int i = 0; i < m_light_count; i++)
	{
		// //////////////////////////////////////////////////////////////////
		// // TO DO: change the pointer to the primitive mesh objects
		// // as only the first two primitives are getting rendered
		// //////////////////////////////////////////////////////////////////
		// render a primitive mesh object to represent this light source
		m_Light[i].pPrimitive->render(this, &m_ShaderInfo);
	}
#endif

	if (m_hud_count)
	{
		// Finally render the HUD.... if we have one
		// HUD elements are rendered as a sprite overlays
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (int i = 0; i < m_hud_count; i++)
		{
			m_Hud[i].renderHUD(this, &m_ShaderInfo);
		}
	}


}

/////////////////////////////////////////////////////////////////////////////////////
// openSDF() - Opens up a scene descriptor file
/////////////////////////////////////////////////////////////////////////////////////
void cScene::openSDF()
{
	// load the scene file here

	FILE* fp = NULL;
	
	fopen_s(&fp, "scene.sdf", "r");

	if (!fp)
		assert(0);

	char buffer[256] = { "\0"};
	float value;
	
	////////////////////////////////////////////////////////////
	// CAMERA
	////////////////////////////////////////////////////////////
	fscanf_s(fp, "%s%d", buffer, 256, &m_camera_count);		// LIGHT_COUNT: 2

	m_Camera = new cCamera[m_camera_count];

	for (int i = 0; i < m_camera_count; i++)
	{
		fscanf_s(fp, "%s%s", buffer, 256, buffer, 256); // CAMERA {
		fscanf_s(fp, "%s%f", buffer, 256, &m_Camera[i].m_fov);		// FOV:	45.0
		fscanf_s(fp, "%s%f", buffer, 256, &m_Camera[i].m_near);		// NEAR:	0.5
		fscanf_s(fp, "%s%f", buffer, 256, &m_Camera[i].m_far);		// FAR:	100.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Camera[i].m_pos.x, &m_Camera[i].m_pos.y, &m_Camera[i].m_pos.z);		// POS:		0.0 0.0 -5.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Camera[i].m_rot.x, &m_Camera[i].m_rot.y, &m_Camera[i].m_rot.z);		// ROT:	0.0 0.0 0.0
		fscanf_s(fp, "%s", buffer, 256);				// }
	}


	////////////////////////////////////////////////////////////
	// LIGHTS
	////////////////////////////////////////////////////////////
	
	fscanf_s(fp, "%s%d", buffer, 256, &m_light_count);		// LIGHT_COUNT: 2

	// allocate block of memory to store the lights..
	m_Light = new cLight[m_light_count];

	for (int i = 0; i < m_light_count; i++)
	{
		fscanf_s(fp, "%s%s", buffer, 256, buffer, 256);	// LIGHT: }
		fscanf_s(fp, "%s%d", buffer, 256, &m_Light[i].m_type); // TYPE:	0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Light[i].m_info.m_pos.x, &m_Light[i].m_info.m_pos.y, &m_Light[i].m_info.m_pos.z); // POS:	-25.0 0.0 20.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Light[i].m_info.m_col.x, &m_Light[i].m_info.m_col.y, &m_Light[i].m_info.m_col.z); // COL:	1.0 1.0 1.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Light[i].m_info.m_att.x, &m_Light[i].m_info.m_att.y, &m_Light[i].m_info.m_att.z); // ATT:	1.0 0.5 0.2
		fscanf_s(fp, "%s%d", buffer, 256, &m_Light[i].m_prim); // PRIM: ePrimitiveTypes
		fscanf_s(fp, "%s", buffer, 256);				// }
	}

	////////////////////////////////////////////////////////////
	// PRIMITIVES
	////////////////////////////////////////////////////////////
	fscanf_s(fp, "%s%d", buffer, 256, &m_prim_count);		// PRIM_COUNT: 1

	// allocate memory to store the basic primitive types needed to display cameras/lights etc
	m_Prim = new cMesh[m_prim_count];

	for (int i = 0; i < m_prim_count; i++)
	{
		fscanf_s(fp, "%s%s", buffer, 256, m_Prim[i].m_filename, 256);	//PRIM: cube.obj
		fscanf_s(fp, "%s", buffer, 256);					// }
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Prim[i].m_transform.m_scale.x, &m_Prim[i].m_transform.m_scale.y, &m_Prim[i].m_transform.m_scale.z);			// SCALE : 1.25 1.25 1.25
		fscanf_s(fp, "%s%d", buffer, 256, &m_Prim[i].m_shaderID); // SHADER_ID	0

		fscanf_s(fp, "%s", buffer, 256);					// }
	}


	////////////////////////////////////////////////////////////
	// MESHES
	////////////////////////////////////////////////////////////
	fscanf_s(fp, "%s%d", buffer, 256, &m_mesh_count);		// MESH_COUNT: 4

	// allocate block of memory to store the mesh objects..
	m_Mesh = new cMesh[m_mesh_count];

	for (int i = 0; i < m_mesh_count; i++)
	{
		fscanf_s(fp, "%s%s", buffer, 256, m_Mesh[i].m_filename, 256);	//MESH: torus.obj
		fscanf_s(fp, "%s", buffer, 256);					// }
		fscanf_s(fp, "%s%s", buffer, 256, m_Mesh[i].m_name, 256);		//MESH: torus.obj
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_pos.x, &m_Mesh[i].m_transform.m_pos.y, &m_Mesh[i].m_transform.m_pos.z);					// POS:	0.0 0.0 0.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_rot.x, &m_Mesh[i].m_transform.m_rot.y, &m_Mesh[i].m_transform.m_rot.z);					// ROT : 2.0 2.0 0.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_rot_incr.x, &m_Mesh[i].m_transform.m_rot_incr.y, &m_Mesh[i].m_transform.m_rot_incr.z);	// ROT_INCR:	1.0 1.0 0.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_scale.x, &m_Mesh[i].m_transform.m_scale.y, &m_Mesh[i].m_transform.m_scale.z);			// SCALE : 1.25 1.25 1.25
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Mesh[i].m_transform.m_vel.x, &m_Mesh[i].m_transform.m_vel.y, &m_Mesh[i].m_transform.m_vel.z);					// VEL : 0.2 0.1 0.0
		fscanf_s(fp, "%s%d", buffer, 256, &m_Mesh[i].m_shaderID); // SHADER_ID	0

		fscanf_s(fp, "%s", buffer, 256);					// }
	}	

	////////////////////////////////////////////////////////////
	// HUD
	////////////////////////////////////////////////////////////
	fscanf_s(fp, "%s%d", buffer, 256, &m_hud_count);		// HUD_COUNT: 4

	// allocate block of memory to store the mesh objects..
	m_Hud = new cMesh[m_hud_count];

	for (int i = 0; i < m_hud_count; i++)
	{
		fscanf_s(fp, "%s%s", buffer, 256, m_Hud[i].m_filename, 256);	//MESH: torus.obj
		fscanf_s(fp, "%s", buffer, 256);					// }
		fscanf_s(fp, "%s%s", buffer, 256, m_Hud[i].m_name, 256);		//MESH: doughnut
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Hud[i].m_transform.m_pos.x, &m_Hud[i].m_transform.m_pos.y, &m_Hud[i].m_transform.m_pos.z);					// POS:	0.0 0.0 0.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Hud[i].m_transform.m_rot.x, &m_Hud[i].m_transform.m_rot.y, &m_Hud[i].m_transform.m_rot.z);					// ROT : 2.0 2.0 0.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Hud[i].m_transform.m_rot_incr.x, &m_Hud[i].m_transform.m_rot_incr.y, &m_Hud[i].m_transform.m_rot_incr.z);	// ROT_INCR:	1.0 1.0 0.0
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Hud[i].m_transform.m_scale.x, &m_Hud[i].m_transform.m_scale.y, &m_Hud[i].m_transform.m_scale.z);			// SCALE : 1.25 1.25 1.25
		fscanf_s(fp, "%s%f%f%f", buffer, 256, &m_Hud[i].m_transform.m_vel.x, &m_Hud[i].m_transform.m_vel.y, &m_Hud[i].m_transform.m_vel.z);					// VEL : 0.2 0.1 0.0
		fscanf_s(fp, "%s%d", buffer, 256, &m_Hud[i].m_shaderID);		// SHADER_ID	0

		fscanf_s(fp, "%s", buffer, 256);					// }
	}


	////////////////////////////////////////////////////////////
	// SHADERS
	////////////////////////////////////////////////////////////
	fscanf_s(fp, "%s%d", buffer, 256, &m_shader_count);		// SHADER_COUNT: 2

	ShaderTable = new sShaderDetails[m_shader_count];
	
	fscanf_s(fp, "%s", buffer, 256); // SHADER:

	for (int i = 0; i < m_shader_count; i++)
	{
		// init shader types..
		for( int j=0; j<6; j++ )
			ShaderTable[i].types[j] = 0;


		fscanf_s(fp, "%s", buffer, 256);		
		strcpy_s(ShaderTable[i].filename, buffer);
		
		int loop_count = 0;
		
		while (strcmp(buffer, "SHADER:") != 0)
		{
			loop_count++;

			fscanf_s(fp, "%s", buffer, 256);
			if (strcmp(buffer, "SHADER:") == 0)
				break;

			// sort the shader by type and add to list..
			if (strcmp(buffer, "VERT_SHDR") == 0)
				ShaderTable[i].types[0] = GL_VERTEX_SHADER;
			else
			if (strcmp(buffer, "CTRL_SHDR") == 0)
				ShaderTable[i].types[1] = GL_TESS_CONTROL_SHADER;
			else
			if (strcmp(buffer, "EVAL_SHDR") == 0)
				ShaderTable[i].types[2] = GL_TESS_EVALUATION_SHADER;
			else
			if (strcmp(buffer, "GEOM_SHDR") == 0)
				ShaderTable[i].types[3] = GL_GEOMETRY_SHADER;
			else
			if (strcmp(buffer, "FRAG_SHDR") == 0)
				ShaderTable[i].types[4] = GL_FRAGMENT_SHADER;
			else
				ShaderTable[i].types[5] = GL_COMPUTE_SHADER;

			if (loop_count == 6)
				break;
		};
	}

	fclose(fp);

}