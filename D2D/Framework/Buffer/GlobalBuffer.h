#pragma once

class  MatrixBuffer : public ConstBuffer
{
private:
	struct Data
	{
		Matrix matrix;
	};
public:
	MatrixBuffer() : ConstBuffer(&m_data, sizeof(Data))
	{
		m_data.matrix = XMMatrixIdentity();
	}
	void Set(Matrix value)
	{
		m_data.matrix = XMMatrixTranspose(value);
	}
private:
	Data m_data;
};

class  ViewBuffer : public ConstBuffer
{
private:
	struct Data
	{
		Matrix view;
		Matrix invView;
	};
public:
	ViewBuffer() : ConstBuffer(&m_data, sizeof(Data))
	{
		m_data.view    = XMMatrixIdentity();
		m_data.invView = XMMatrixIdentity();
	}
	void Set(Matrix view, Matrix invView)
	{
		m_data.view = XMMatrixTranspose(view);
		m_data.invView = XMMatrixTranspose(invView);
	}
private:
	Data m_data;
};

class LightBuffer : public ConstBuffer
{
private:
	struct Light
	{
		Float4 color     = { 1,1,1,1 };
		Float3 direction = { 1,-1,1 };  // ºûÀÇ ¹æÇâ
		float  shininess = 24.0f;        // Á¦°ö°ª
	};
	struct Data
	{
		Light lights[10];

		UINT lightCount = 1;
		Float3 ambientLight = { 0.1f, 0.1f, 0.1f };
		Float3 ambientCeil = { 0.1f, 0.1f, 0.1f };
		float padding = 0.0f;
	};
public:
	LightBuffer() : ConstBuffer(&m_data, sizeof(Data))
	{

	}
	Data& Get() { return m_data; }

private:
	Data  m_data;
};

class RayBuffer : public ConstBuffer
{
private:
	struct Data
	{
		Float3 pos;
		int    triangleSize;

		Float3 dir;
		float  padding;
	};
public:
	RayBuffer() : ConstBuffer(&m_data, sizeof(Data))
	{

	}
	Data& Get() { return m_data; }

private:
	Data  m_data;
};

class MaterialBuffer : public ConstBuffer
{
public:
	struct Data
	{
		Float4 diffuse   = { 1,1,1,1 };
		Float4 specular  = { 1,1,1,1 };
		Float4 ambient   = { 1,1,1,1 };
		Float4 emissive  = { 1,1,1,1 };

		float  shininess = 24.0f;
		int    hasNormalMap = 0;
		float  padding[2] = {};
	};
public:
	MaterialBuffer() : ConstBuffer(&m_data, sizeof(Data))
	{

	}
	Data& Get() { return m_data; }

private:
	Data  m_data;
};

class FloatValueBuffer : public ConstBuffer
{
public:
	FloatValueBuffer() : ConstBuffer(m_values, sizeof(float)*4)
	{

	}
	float* Get() { return m_values; }

private:
	float  m_values[4] = {};
};
