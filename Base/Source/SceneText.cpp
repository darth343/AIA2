#include "SceneText.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include "KeyboardController.h"
#include "MouseController.h"
#include "SceneManager.h"
#include "GraphicsManager.h"
#include "ShaderProgram.h"
#include "EntityManager.h"

#include "GenericEntity.h"
#include "GroundEntity.h"
#include "TextEntity.h"
#include "SpriteEntity.h"
#include "Light.h"
#include "SkyBox/SkyBoxEntity.h"
#include <iostream>
#include "AI\Melee.h"
#include "AI\Scout.h"
#include "AI\Healer.h"
#include "AI\Commander.h"
#include "AI\Ranged.h"
#include "RenderHelper.h"

using namespace std;

SceneText* SceneText::sInstance = new SceneText(SceneManager::GetInstance());

SceneText::SceneText()
{
}

SceneText::SceneText(SceneManager* _sceneMgr)
{
	_sceneMgr->AddScene("Start", this);
}

SceneText::~SceneText()
{
}

void SceneText::Init()
{
	glClearColor(0.2, 0.2, 0.2, 1);
	Math::InitRNG();
	currProg = GraphicsManager::GetInstance()->LoadShader("default", "Shader//Texture.vertexshader", "Shader//Texture.fragmentshader");
	
	// Tell the shader program to store these uniform locations
	currProg->AddUniform("MVP");
	currProg->AddUniform("MV");
	currProg->AddUniform("MV_inverse_transpose");
	currProg->AddUniform("material.kAmbient");
	currProg->AddUniform("material.kDiffuse");
	currProg->AddUniform("material.kSpecular");
	currProg->AddUniform("material.kShininess");
	currProg->AddUniform("lightEnabled");
	currProg->AddUniform("numLights");
	currProg->AddUniform("lights[0].type");
	currProg->AddUniform("lights[0].position_cameraspace");
	currProg->AddUniform("lights[0].color");
	currProg->AddUniform("lights[0].power");
	currProg->AddUniform("lights[0].kC");
	currProg->AddUniform("lights[0].kL");
	currProg->AddUniform("lights[0].kQ");
	currProg->AddUniform("lights[0].spotDirection");
	currProg->AddUniform("lights[0].cosCutoff");
	currProg->AddUniform("lights[0].cosInner");
	currProg->AddUniform("lights[0].exponent");
	currProg->AddUniform("lights[1].type");
	currProg->AddUniform("lights[1].position_cameraspace");
	currProg->AddUniform("lights[1].color");
	currProg->AddUniform("lights[1].power");
	currProg->AddUniform("lights[1].kC");
	currProg->AddUniform("lights[1].kL");
	currProg->AddUniform("lights[1].kQ");
	currProg->AddUniform("lights[1].spotDirection");
	currProg->AddUniform("lights[1].cosCutoff");
	currProg->AddUniform("lights[1].cosInner");
	currProg->AddUniform("lights[1].exponent");
	currProg->AddUniform("colorTextureEnabled");
	currProg->AddUniform("colorTexture");
	currProg->AddUniform("textEnabled");
	currProg->AddUniform("textColor");
	
	// Tell the graphics manager to use the shader we just loaded
	GraphicsManager::GetInstance()->SetActiveShader("default");

	lights[0] = new Light();
	GraphicsManager::GetInstance()->AddLight("lights[0]", lights[0]);
	lights[0]->type = Light::LIGHT_DIRECTIONAL;
	lights[0]->position.Set(0, 20, 0);
	lights[0]->color.Set(1, 1, 1);
	lights[0]->power = 1;
	lights[0]->kC = 1.f;
	lights[0]->kL = 0.01f;
	lights[0]->kQ = 0.001f;
	lights[0]->cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0]->cosInner = cos(Math::DegreeToRadian(30));
	lights[0]->exponent = 3.f;
	lights[0]->spotDirection.Set(0.f, 1.f, 0.f);
	lights[0]->name = "lights[0]";

	lights[1] = new Light();
	GraphicsManager::GetInstance()->AddLight("lights[1]", lights[1]);
	lights[1]->type = Light::LIGHT_DIRECTIONAL;
	lights[1]->position.Set(1, 1, 0);
	lights[1]->color.Set(1, 1, 0.5f);
	lights[1]->power = 0.4f;
	lights[1]->name = "lights[1]";

	currProg->UpdateInt("numLights", 1);
	currProg->UpdateInt("textEnabled", 0);
	

	// Create and attach the camera to the scene
	//camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	camera.Init(Vector3(-800, 865, -6.5), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateAxes("reference");
	MeshBuilder::GetInstance()->GenerateCrossHair("crosshair");
	MeshBuilder::GetInstance()->GenerateQuad("quad", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("Legend", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("Legend")->textureID = LoadTGA("Image//Legend.tga");;
	MeshBuilder::GetInstance()->GenerateQuad("MeleeBlue", Color(0.7, 0.7, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("MeleeBlue")->textureID = LoadTGA("Image//MeleeBlue.tga");
	MeshBuilder::GetInstance()->GenerateQuad("MeleeRed", Color(0.7, 0.7, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("MeleeRed")->textureID = LoadTGA("Image//MeleeRed.tga");
	MeshBuilder::GetInstance()->GenerateQuad("HealerBlue", Color(0, 1, 0), 1.f);
	MeshBuilder::GetInstance()->GetMesh("HealerBlue")->textureID = LoadTGA("Image//HealerBlue.tga");
	MeshBuilder::GetInstance()->GenerateQuad("HealerRed", Color(0, 1, 0), 1.f);
	MeshBuilder::GetInstance()->GetMesh("HealerRed")->textureID = LoadTGA("Image//HealerRed.tga");
	MeshBuilder::GetInstance()->GenerateQuad("RangedBlue", Color(0, 1, 0), 1.f);
	MeshBuilder::GetInstance()->GetMesh("RangedBlue")->textureID = LoadTGA("Image//RangedBlue.tga");
	MeshBuilder::GetInstance()->GenerateQuad("RangedRed", Color(0, 1, 0), 1.f);
	MeshBuilder::GetInstance()->GetMesh("RangedRed")->textureID = LoadTGA("Image//RangedRed.tga");
	MeshBuilder::GetInstance()->GenerateQuad("ScoutBlue", Color(0, 1, 0), 1.f);
	MeshBuilder::GetInstance()->GetMesh("ScoutBlue")->textureID = LoadTGA("Image//ScoutBlue.tga");
	MeshBuilder::GetInstance()->GenerateQuad("ScoutRed", Color(0, 1, 0), 1.f);
	MeshBuilder::GetInstance()->GetMesh("ScoutRed")->textureID = LoadTGA("Image//ScoutRed.tga");
	MeshBuilder::GetInstance()->GenerateQuad("darkbluequad", Color(0.1, 0.1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("CommanderRed", Color(1, 0.3, 0.3), 1.f);
	MeshBuilder::GetInstance()->GetMesh("CommanderRed")->textureID = LoadTGA("Image//CommanderRed.tga");
	MeshBuilder::GetInstance()->GenerateQuad("CommanderBlue", Color(1, 0.3, 0.3), 1.f);
	MeshBuilder::GetInstance()->GetMesh("CommanderBlue")->textureID = LoadTGA("Image//CommanderBlue.tga");
	MeshBuilder::GetInstance()->GenerateQuad("yellowquad", Color(1, 1, 0), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("quad", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("BlackQuad", Color(0, 0, 0), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("HPQuad", Color(0, 0.6, 0.2), 1.f);
	//MeshBuilder::GetInstance()->GetMesh("quad")->textureID = LoadTGA("Image//calibri.tga");
	MeshBuilder::GetInstance()->GenerateText("text", 16, 16);
	MeshBuilder::GetInstance()->GetMesh("text")->textureID = LoadTGA("Image//calibri.tga");
	MeshBuilder::GetInstance()->GetMesh("text")->material.kAmbient.Set(1, 0, 0);
	MeshBuilder::GetInstance()->GenerateText("text_noalpha", 16, 16);
	MeshBuilder::GetInstance()->GetMesh("text_noalpha")->textureID = LoadTGA("Image//calibri_noalpha.tga");
	MeshBuilder::GetInstance()->GetMesh("text_noalpha")->material.kAmbient.Set(1, 0, 0);
	MeshBuilder::GetInstance()->GenerateRing("ring", Color(1, 0, 1), 36, 1, 0.5f);
	MeshBuilder::GetInstance()->GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1.f);
	MeshBuilder::GetInstance()->GenerateSphere("sphere", Color(1, 0, 0), 18, 36, 0.5f);
	MeshBuilder::GetInstance()->GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);
	MeshBuilder::GetInstance()->GenerateCube("cube", Color(1.0f, 1.0f, 0.0f), 1.0f);
	MeshBuilder::GetInstance()->GetMesh("cone")->material.kDiffuse.Set(0.99f, 0.99f, 0.99f);
	MeshBuilder::GetInstance()->GetMesh("cone")->material.kSpecular.Set(0.f, 0.f, 0.f);

	// Create entities into the scene
	Create::Asset("reference", Vector3(0.0f, 10.0f, 0.0f)); // Reference
	Create::Asset("lightball", Vector3(lights[0]->position.x, lights[0]->position.y, lights[0]->position.z)); // Lightball

	//Create::Text3DObject("text", Vector3(0.0f, 0.0f, 0.0f), "DM2210", Vector3(10.0f, 10.0f, 10.0f), Color(0, 1, 1));
	Create::Sprite2DObject("crosshair", Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 10.0f, 10.0f));

	SkyBoxEntity* theSkyBox = Create::SkyBox("SKYBOX_FRONT", "SKYBOX_BACK",
											 "SKYBOX_LEFT", "SKYBOX_RIGHT",
											 "SKYBOX_TOP", "SKYBOX_BOTTOM");

	// Setup the 2D entities
	//float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	//float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;
	float halfWindowWidth = 400;
	float halfWindowHeight = 300;
	float fontSize = 25.0f;
	float halfFontSize = fontSize / 2.0f;

	for (int i = 0; i < 3; ++i)
	{
		textObj[i] = Create::Text2DObject("text", Vector3(-halfWindowWidth, -halfWindowHeight + fontSize*i + halfFontSize, 0.0f), "", Vector3(fontSize, fontSize, fontSize), Color(0.0f,1.0f,0.0f));
	}

	// Team 1
	/*Create::MeleeCharacter("MeleeBlue", 1, Vector3(350, 250, 0), Vector3(50, 50, 0));
	Create::MeleeCharacter("MeleeBlue", 1, Vector3(350, 265, 0), Vector3(50, 50, 0));
	Create::MeleeCharacter("MeleeBlue", 1, Vector3(350, 280, 0), Vector3(50, 50, 0));
	Create::MeleeCharacter("MeleeBlue", 1, Vector3(350, 295, 0), Vector3(50, 50, 0));
	Create::MeleeCharacter("MeleeBlue", 1, Vector3(350, 295, 0), Vector3(50, 50, 0));
	Create::MeleeCharacter("MeleeBlue", 1, Vector3(350, 295, 0), Vector3(50, 50, 0));
	Create::MeleeCharacter("MeleeBlue", 1, Vector3(350, 295, 0), Vector3(50, 50, 0));
	Create::MeleeCharacter("MeleeBlue", 1, Vector3(350, 295, 0), Vector3(50, 50, 0));
	Create::MeleeCharacter("MeleeBlue", 1, Vector3(350, 295, 0), Vector3(50, 50, 0));
	*/
	//Create::MeleeCharacter("MeleeBlue", 1, Vector3(350, 295, 0), Vector3(50, 50, 0));

	

	team1.TeamInit(1, 1, 1, 1, 1, 0);
	team2.TeamInit(2, 1, 1, 1, 1, 0);

	//CMelee* Melee1 = Create::MeleeCharacter("MeleeBlue", 1, Vector3(350, 295, 0), Vector3(50, 50, 0));
	//Melee1->SetHealth(30);

	//Create::CommanderCharacter("CommanderRed", 1, Vector3(350, 295, 0), Vector3(50, 50, 0));

	//CScout* Scout1 = Create::ScoutCharacter("darkbluequad", 1, Vector3(350, 220, 0), Vector3(20, 20, 0));
	////Scout1->GoTo(Vector3(-100, 100, 0));

	//CMelee* Melee2 = Create::MeleeCharacter("MeleeRed", 2, Vector3(-350, -250, 0), Vector3(20, 20, 0));
	//Melee2->GoTo(Vector3(-100, 100, 0));

	//Create::HealerCharacter("HealerBlue", 1, Vector3(300, 200, 0), Vector3(20, 20, 0));

	//Create::RangedCharacter("yellowquad", 1, Vector3(400, 200, 0), Vector3(20, 20, 0));

	//textObj[0]->SetText("HELLO WORLD");

	Messageboard = MessageBoard::GetInstance();
	Messageboard->SetFontSize(25);
	Messageboard->Add(NULL, "", "Message Board Started!");

}

void SceneText::Update(double dt)
{
	EntityManager::GetInstance()->Update(dt);

	// THIS WHOLE CHUNK TILL <THERE> CAN REMOVE INTO ENTITIES LOGIC! Or maybe into a scene function to keep the update clean
	if(KeyboardController::GetInstance()->IsKeyDown('1'))
		glEnable(GL_CULL_FACE);
	if(KeyboardController::GetInstance()->IsKeyDown('2'))
		glDisable(GL_CULL_FACE);
	if(KeyboardController::GetInstance()->IsKeyDown('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(KeyboardController::GetInstance()->IsKeyDown('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// if the left mouse button was released
	if (MouseController::GetInstance()->IsButtonReleased(MouseController::LMB))
	{
		cout << "Left Mouse Button was released!" << endl;
	}
	if (MouseController::GetInstance()->IsButtonReleased(MouseController::RMB))
	{
		cout << "Right Mouse Button was released!" << endl;
	}
	if (MouseController::GetInstance()->IsButtonReleased(MouseController::MMB))
	{
		cout << "Middle Mouse Button was released!" << endl;
	}
	//if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_XOFFSET) != 0.0)
	//{
	//	cout << "Mouse Wheel has offset in X-axis of " << MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_XOFFSET) << endl;
	//}
	//if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) != 0.0)
	//{
	//	cout << "Mouse Wheel has offset in Y-axis of " << MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) << endl;
	//}
	// <THERE>

	//camera.Update(dt); // Can put the camera into an entity rather than here (Then we don't have to write this)

	GraphicsManager::GetInstance()->UpdateLights(dt);
	Messageboard->Update();
	// Update the 2 text object values. NOTE: Can do this in their own class but i'm lazy to do it now :P
	// Eg. FPSRenderEntity or inside RenderUI for LightEntity


	std::ostringstream ss;
	ss.precision(5);
	float fps = (float)(1.f / dt);
	ss << "FPS: " << fps;
	textObj[0]->SetText(ss.str());

	//static int count = 0;
	//static float timer = 0;
	//timer += dt;
	//if (timer > 1)
	//{
	//	ss.str("");
	//	ss << count++;
	//	Messageboard->Add(NULL, "", ss.str());
	//	timer -= 1;
	//}
}

void SceneText::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GraphicsManager::GetInstance()->UpdateLightUniforms();
	//GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Setup 2D pipeline then render 2D
	int halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2;
	int halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2;
	GraphicsManager::GetInstance()->SetOrthographicProjection(-halfWindowWidth, halfWindowWidth, -halfWindowHeight, halfWindowHeight, -10, 10);
	GraphicsManager::GetInstance()->DetachCamera();

	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();

	modelStack.PushMatrix();
	modelStack.Translate(400, 150, 0);
	modelStack.Scale(400, 600, 0);
	RenderHelper::RenderMesh(MeshBuilder::GetInstance()->GetMesh("Legend"));
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(-200, 150, 0);
	EntityManager::GetInstance()->Render();
	EntityManager::GetInstance()->RenderUI();
	modelStack.PopMatrix();

	Messageboard->Render();
	// Message Board Rendering

}

void SceneText::Exit()
{
	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();

	// Delete the lights
	delete lights[0];
	delete lights[1];
}
