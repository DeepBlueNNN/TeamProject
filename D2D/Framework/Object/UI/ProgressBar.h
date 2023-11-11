#pragma once
class ProgressBar : public Quad
{
public:
	ProgressBar(wstring frontImageFile, wstring backImageFile);
	~ProgressBar();

public:
	void  Render();
	void  SetAmount(float value);

private:
	Texture*			m_backImage = nullptr;
	float				m_fillAmount = 1.0f;
	FloatValueBuffer	m_valueBuffer;
};