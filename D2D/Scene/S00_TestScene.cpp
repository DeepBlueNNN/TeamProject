#include "framework.h"
#include "S00_TestScene.h"

S00_TestScene::S00_TestScene()
{
	// Box Collision
	colliders.push_back(new BoxCollider());
	colliders.back()->SetTag("Box1");
	colliders.push_back(new BoxCollider());
	colliders.back()->SetTag("Box2");

	// Sphere Collision
	colliders.push_back(new SphereCollider());
	colliders.back()->SetTag("Sphere1");
	colliders.push_back(new SphereCollider());
	colliders.back()->SetTag("Sphere2");


	// Capsule Collision
	colliders.push_back(new CapsuleCollider());
	colliders.back()->SetTag("Capsule1");
	colliders.push_back(new CapsuleCollider());
	colliders.back()->SetTag("Capsule2");
}

S00_TestScene::~S00_TestScene()
{
	for (Collider* collider : colliders)
	{
		delete collider;
	}
	colliders.erase(colliders.begin(), colliders.end());
}

void S00_TestScene::Update()
{
	Ray ray = CAMERA->ScreenPointToRay(mousePos);
	Contact contact;

	// Box x Ray Contact

	if (colliders[0]->IsRayCollision(ray, &contact))
	{
		colliders[0]->SetColor(1.0f, 0.0f, 0.0f);
		//colliders[1]->Pos() = contact.hitPosition;
	}
	else
	{
		colliders[0]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Box x Box Collision

	if (colliders[0]->IsCollision(colliders[1]))
	{
		colliders[0]->SetColor(1.0f, 0.0f, 0.0f);
		colliders[1]->SetColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		colliders[0]->SetColor(0.0f, 1.0f, 0.0f);
		colliders[1]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Sphere x Ray Contact

	if (colliders[2]->IsRayCollision(ray, &contact))
	{
		colliders[2]->SetColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		colliders[2]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Sphere x Sphere Collision

	if (colliders[2]->IsCollision(colliders[3]))
	{
		colliders[2]->SetColor(1.0f, 0.0f, 0.0f);
		colliders[3]->SetColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		colliders[2]->SetColor(0.0f, 1.0f, 0.0f);
		colliders[3]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Box x Sphere Collision

	if (colliders[0]->IsCollision(colliders[2]))
	{
		colliders[0]->SetColor(1.0f, 0.0f, 0.0f);
		colliders[2]->SetColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		colliders[0]->SetColor(0.0f, 1.0f, 0.0f);
		colliders[2]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Capsule x Ray Collision

	if (colliders[4]->IsRayCollision(ray, &contact))
	{
		colliders[4]->SetColor(1.0f, 0.0f, 0.0f);
		//colliders[1]->Pos() = contact.hitPosition;
	}
	else
	{
		colliders[4]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Capsule x Box Collision

	if (colliders[0]->IsCollision(colliders[4]))
	{
		colliders[0]->SetColor(1.0f, 0.0f, 0.0f);
		colliders[4]->SetColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		colliders[0]->SetColor(0.0f, 1.0f, 0.0f);
		colliders[4]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Capsule x Sphere Collision

	if (colliders[4]->IsCollision(colliders[2]))
	{
		colliders[4]->SetColor(1.0f, 0.0f, 0.0f);
		colliders[2]->SetColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		colliders[4]->SetColor(0.0f, 1.0f, 0.0f);
		colliders[2]->SetColor(0.0f, 1.0f, 0.0f);
	}

	// Capsule x Capsule Collision

	if (colliders[4]->IsCollision(colliders[5]))
	{
		colliders[4]->SetColor(1.0f, 0.0f, 0.0f);
		colliders[5]->SetColor(1.0f, 0.0f, 0.0f);
	}
	else
	{
		colliders[4]->SetColor(0.0f, 1.0f, 0.0f);
		colliders[5]->SetColor(0.0f, 1.0f, 0.0f);
	}

	for (Collider* collider : colliders)
	{
		collider->UpdateWorld();
	}
}

void S00_TestScene::Render()
{
	for (Collider* collider : colliders)
	{
		collider->Render();
	}
}

void S00_TestScene::PreRender()
{
}

void S00_TestScene::PostRender()
{
}

void S00_TestScene::GUIRender()
{
	for (Collider* collider : colliders)
	{
		collider->GUIRender();
	}
}
