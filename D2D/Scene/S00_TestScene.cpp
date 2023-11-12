#include "framework.h"
#include "S00_TestScene.h"

S00_TestScene::S00_TestScene()
{
	// Object
	m_cube = new Cube();
	m_cube->SetTag("Cube");

	m_sphere = new Sphere();
	m_sphere->SetTag("Sphere");

	m_cylinder = new Cylinder();
	m_cylinder->SetTag("Cylinder");

	// Collisions
	m_colliders.push_back(new BoxCollider());
	m_colliders.back()->SetTag("Box1");
	m_colliders.push_back(new BoxCollider());
	m_colliders.back()->SetTag("Box2");

	m_colliders.push_back(new SphereCollider());
	m_colliders.back()->SetTag("Sphere1");
	m_colliders.push_back(new SphereCollider());
	m_colliders.back()->SetTag("Sphere2");

	m_colliders.push_back(new CapsuleCollider());
	m_colliders.back()->SetTag("Capsule1");
	m_colliders.push_back(new CapsuleCollider());
	m_colliders.back()->SetTag("Capsule2");

	// model animation
	m_modelAnimator = new ModelAnimator("Jin");
	m_modelAnimator->SetTag("Jin");
	m_modelAnimator->ReadClip("Idle");
	m_modelAnimator->ReadClip("Walk");
	m_modelAnimator->ReadClip("Dancing");
	m_modelAnimator->Scale() = Vector3(0.05f, 0.05f, 0.05f);
}

S00_TestScene::~S00_TestScene()
{
	for (Collider* collider : m_colliders)
	{
		SAFE_DELETE(collider);
	}
	m_colliders.erase(m_colliders.begin(), m_colliders.end());

	SAFE_DELETE(m_cylinder);
	SAFE_DELETE(m_sphere);
	SAFE_DELETE(m_cube);
}

void S00_TestScene::Update()
{
	m_cube->UpdateWorld();
	m_sphere->UpdateWorld();
	m_cylinder->UpdateWorld();

	Ray ray = CAMERA->ScreenPointToRay(mousePos);
	Contact contact;

	// Box x Ray Contact

	if (m_colliders[0]->IsRayCollision(ray, &contact))
	{
		m_colliders[0]->SetColor(1.0f, 0.0f, 0.0f);
		//m_colliders[1]->Pos() = contact.hitPosition;
	}
	else
	{
		m_colliders[0]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Box x Box Collision

	if (m_colliders[0]->IsCollision(m_colliders[1]))
	{
		m_colliders[0]->SetColor(1.0f, 0.0f, 0.0f);
		m_colliders[1]->SetColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		m_colliders[0]->SetColor(0.0f, 1.0f, 0.0f);
		m_colliders[1]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Sphere x Ray Contact

	if (m_colliders[2]->IsRayCollision(ray, &contact))
	{
		m_colliders[2]->SetColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		m_colliders[2]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Sphere x Sphere Collision

	if (m_colliders[2]->IsCollision(m_colliders[3]))
	{
		m_colliders[2]->SetColor(1.0f, 0.0f, 0.0f);
		m_colliders[3]->SetColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		m_colliders[2]->SetColor(0.0f, 1.0f, 0.0f);
		m_colliders[3]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Box x Sphere Collision

	if (m_colliders[0]->IsCollision(m_colliders[2]))
	{
		m_colliders[0]->SetColor(1.0f, 0.0f, 0.0f);
		m_colliders[2]->SetColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		m_colliders[0]->SetColor(0.0f, 1.0f, 0.0f);
		m_colliders[2]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Capsule x Ray Collision

	if (m_colliders[4]->IsRayCollision(ray, &contact))
	{
		m_colliders[4]->SetColor(1.0f, 0.0f, 0.0f);
		//m_colliders[1]->Pos() = contact.hitPosition;
	}
	else
	{
		m_colliders[4]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Capsule x Box Collision

	if (m_colliders[0]->IsCollision(m_colliders[4]))
	{
		m_colliders[0]->SetColor(1.0f, 0.0f, 0.0f);
		m_colliders[4]->SetColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		m_colliders[0]->SetColor(0.0f, 1.0f, 0.0f);
		m_colliders[4]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Capsule x Sphere Collision

	if (m_colliders[4]->IsCollision(m_colliders[2]))
	{
		m_colliders[4]->SetColor(1.0f, 0.0f, 0.0f);
		m_colliders[2]->SetColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		m_colliders[4]->SetColor(0.0f, 1.0f, 0.0f);
		m_colliders[2]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Capsule x Capsule Collision

	if (m_colliders[4]->IsCollision(m_colliders[5]))
	{
		m_colliders[4]->SetColor(1.0f, 0.0f, 0.0f);
		m_colliders[5]->SetColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		m_colliders[4]->SetColor(0.0f, 1.0f, 0.0f);
		m_colliders[5]->SetColor(0.0f, 1.0f, 0.0f);
	}

	for (Collider* collider : m_colliders)
	{
		collider->UpdateWorld();
	}

	if (KEY_DOWN('1'))
		m_modelAnimator->PlayClip(0);
	if (KEY_DOWN('2'))
		m_modelAnimator->PlayClip(1);
	if (KEY_DOWN('3'))
		m_modelAnimator->PlayClip(2);

	m_modelAnimator->Update();
}

void S00_TestScene::Render()
{
	m_cube->Render();
	m_sphere->Render();
	m_cylinder->Render();

	for (Collider* collider : m_colliders)
	{
		collider->Render();
	}

	m_modelAnimator->Render();
}

void S00_TestScene::PreRender()
{
}

void S00_TestScene::PostRender()
{
}

void S00_TestScene::GUIRender()
{
	m_cube->GUIRender();
	m_sphere->GUIRender();
	m_cylinder->GUIRender();

	for (Collider* collider : m_colliders)
	{
		collider->GUIRender();
	}

	m_modelAnimator->GUIRender();
}
