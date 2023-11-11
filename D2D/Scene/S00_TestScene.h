#pragma once
class S00_TestScene : public Scene
{
public:
	S00_TestScene();
	~S00_TestScene();

public:
	void Update()      override;
	void Render()      override;
	void PreRender()   override;
	void PostRender()  override;
	void GUIRender()   override;

private:
	vector<Collider*> colliders;

};