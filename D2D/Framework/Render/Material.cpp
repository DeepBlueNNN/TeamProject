#include "framework.h"

Material::Material()
{
	buffer      =  new MaterialBuffer();
	// Model에서 처음에 png파일이 assin안되어 있는 경우를 고려
	diffuseMap  = Texture::Add(L"Textures/Color/White.png",L"DM");
	specularMap = Texture::Add(L"Textures/Color/White.png",L"SM");
	normalMap   = Texture::Add(L"Textures/Color/White.png",L"NM");
}

Material::Material(wstring shaderFile)
{
	SetShader(shaderFile);
	buffer = new MaterialBuffer();
    // Model에서 처음에 png파일이 assin안되어 있는 경우를 고려
    diffuseMap = Texture::Add(L"Textures/Color/White.png", L"DM");
    specularMap = Texture::Add(L"Textures/Color/White.png", L"SM");
    normalMap = Texture::Add(L"Textures/Color/White.png", L"NM");
}

Material::~Material()
{
	SAFE_DELETE(buffer);
}

void Material::Set()
{

    diffuseMap->PSSet(0);
    specularMap->PSSet(1);
    normalMap->PSSet(2);
    
    buffer->SetPS(1);
    vertexShader->Set();
    pixelShader->Set();
}

void Material::GUIRender()
{
    string title = name + "_Material";

    if (ImGui::TreeNode(title.c_str()))
    {
        ImTextureID textureID = diffuseMap->GetSRV();

        if (ImGui::ImageButton(textureID, ImVec2(50, 50)))
        {
			FileDialog dlg;
			wstring selectfile;
			if (dlg.Open(selectfile))
			{
				MessageBox(NULL, selectfile.c_str(), L"File", MB_OK);
				SetDiffuseMap(selectfile);
			}

        }

        ImGui::TreePop();
    }
}

void Material::SetShader(wstring shaderFile)
{
	vertexShader = Shader::AddVS(shaderFile);
	pixelShader = Shader::AddPS(shaderFile);

}
void Material::SetDiffuseMap(wstring textureFile)
{
	if (textureFile.length() > 0)
		diffuseMap = Texture::Add(textureFile);
	else
		diffuseMap = Texture::Add(L"Textures/Color/White.png");
}

void Material::SetSpecularMap(wstring textureFile)
{
	if (textureFile.length() > 0)
		specularMap = Texture::Add(textureFile);
	else
		specularMap = Texture::Add(L"Textures/Color/White.png");
}

void Material::SetNormalMap(wstring textureFile)
{
    if (textureFile.length() > 0)
    {
        normalMap = Texture::Add(textureFile);
        buffer->Get().hasNormalMap = 1;
    }
		
    else
    {
        normalMap = Texture::Add(L"Textures/Color/White.png");
        buffer->Get().hasNormalMap = 0;
    }
		
}

void Material::Save(string file)
{
    tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
    tinyxml2::XMLElement* material = document->NewElement("Material");
    material->SetAttribute("Name", name.c_str());
    document->InsertFirstChild(material);

    tinyxml2::XMLElement* shader = document->NewElement("Shader");
    string shaderFile;
    if (vertexShader)
        StringPath::ToString(vertexShader->GetFile());
    shader->SetAttribute("Vertex", shaderFile.c_str());
    if (pixelShader)
        shaderFile = StringPath::ToString(pixelShader->GetFile());
    shader->SetAttribute("Pixel", shaderFile.c_str());
    material->InsertFirstChild(shader);

    tinyxml2::XMLElement* texture = document->NewElement("Texture");
    string textureFile = StringPath::ToString(diffuseMap->GetFile());
    texture->SetAttribute("Diffuse", textureFile.c_str());
    textureFile = StringPath::ToString(specularMap->GetFile());
    texture->SetAttribute("Specular", textureFile.c_str());
    textureFile = StringPath::ToString(normalMap->GetFile());
    texture->SetAttribute("Normal", textureFile.c_str());
    material->InsertEndChild(texture);

    tinyxml2::XMLElement* property = document->NewElement("Property");
    tinyxml2::XMLElement* diffuse = document->NewElement("Diffuse");
    diffuse->SetAttribute("R", buffer->Get().diffuse.x);
    diffuse->SetAttribute("G", buffer->Get().diffuse.y);
    diffuse->SetAttribute("B", buffer->Get().diffuse.z);
    diffuse->SetAttribute("A", buffer->Get().diffuse.w);
    property->InsertEndChild(diffuse);

    tinyxml2::XMLElement* specular = document->NewElement("Specular");
    specular->SetAttribute("R", buffer->Get().specular.x);
    specular->SetAttribute("G", buffer->Get().specular.y);
    specular->SetAttribute("B", buffer->Get().specular.z);
    specular->SetAttribute("A", buffer->Get().specular.w);
    property->InsertEndChild(specular);

    tinyxml2::XMLElement* ambient = document->NewElement("Ambient");
    ambient->SetAttribute("R", buffer->Get().ambient.x);
    ambient->SetAttribute("G", buffer->Get().ambient.y);
    ambient->SetAttribute("B", buffer->Get().ambient.z);
    ambient->SetAttribute("A", buffer->Get().ambient.w);
    property->InsertEndChild(ambient);

    tinyxml2::XMLElement* emissive = document->NewElement("Emissive");
    emissive->SetAttribute("R", buffer->Get().emissive.x);
    emissive->SetAttribute("G", buffer->Get().emissive.y);
    emissive->SetAttribute("B", buffer->Get().emissive.z);
    emissive->SetAttribute("A", buffer->Get().emissive.w);
    property->InsertEndChild(emissive);

    property->SetAttribute("Shininess", buffer->Get().shininess);
    property->SetAttribute("HasNormalMap", buffer->Get().hasNormalMap);

    material->InsertEndChild(property);

    document->SaveFile(file.c_str());

    delete document;

}

void Material::Load(string file)
{
    this->file = file;

    tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
    document->LoadFile(file.c_str());
    tinyxml2::XMLElement* material = document->FirstChildElement();
    name = material->Attribute("Name");

    tinyxml2::XMLElement* shader = material->FirstChildElement();
    wstring shaderFile = StringPath::ToWString(shader->Attribute("Vertex"));
    shaderFile = shaderFile.substr(shaderFile.find_first_of('/') + 1, shaderFile.length());
    vertexShader = Shader::AddVS(shaderFile);
    shaderFile = StringPath::ToWString(shader->Attribute("Pixel"));
    shaderFile = shaderFile.substr(shaderFile.find_first_of('/') + 1, shaderFile.length());
    pixelShader = Shader::AddPS(shaderFile);

    tinyxml2::XMLElement* texture = shader->NextSiblingElement();
    wstring textureFile = StringPath::ToWString(texture->Attribute("Diffuse"));
    SetDiffuseMap(textureFile);
    textureFile = StringPath::ToWString(texture->Attribute("Specular"));
    SetSpecularMap(textureFile);
    textureFile = StringPath::ToWString(texture->Attribute("Normal"));
    SetNormalMap(textureFile);

    tinyxml2::XMLElement* property = texture->NextSiblingElement();
    tinyxml2::XMLElement* diffuse = property->FirstChildElement();
    buffer->Get().diffuse.x = diffuse->FloatAttribute("R");
    buffer->Get().diffuse.y = diffuse->FloatAttribute("G");
    buffer->Get().diffuse.z = diffuse->FloatAttribute("B");
    buffer->Get().diffuse.w = diffuse->FloatAttribute("A");

    tinyxml2::XMLElement* specular = diffuse->NextSiblingElement();
    buffer->Get().specular.x = specular->FloatAttribute("R");
    buffer->Get().specular.y = specular->FloatAttribute("G");
    buffer->Get().specular.z = specular->FloatAttribute("B");
    buffer->Get().specular.w = specular->FloatAttribute("A");

    tinyxml2::XMLElement* ambient = specular->NextSiblingElement();
    buffer->Get().ambient.x = ambient->FloatAttribute("R");
    buffer->Get().ambient.y = ambient->FloatAttribute("G");
    buffer->Get().ambient.z = ambient->FloatAttribute("B");
    buffer->Get().ambient.w = ambient->FloatAttribute("A");

    tinyxml2::XMLElement* emissive = ambient->NextSiblingElement();
    buffer->Get().emissive.x = emissive->FloatAttribute("R");
    buffer->Get().emissive.y = emissive->FloatAttribute("G");
    buffer->Get().emissive.z = emissive->FloatAttribute("B");
    buffer->Get().emissive.w = emissive->FloatAttribute("A");

    buffer->Get().shininess = property->FloatAttribute("Shininess");
    buffer->Get().hasNormalMap = property->IntAttribute("HasNormalMap");

    SAFE_DELETE(document);
}

void Material::ParsingShader(tinyxml2::XMLNode* Parent)
{
    tinyxml2::XMLNode* child = NULL;
    tinyxml2::XMLElement* element = NULL;

    for (child = Parent->FirstChild(); child; child = child->NextSibling())
    {
        string value = child->Value();
        if (value == "Vertex")
        {
            element = child->ToElement();
            wstring shaderFile = StringPath::ToWString(element->GetText());
            shaderFile = shaderFile.substr(shaderFile.find_first_of('/') + 1, shaderFile.length());
            vertexShader = Shader::AddVS(shaderFile);
        }
        if (value == "Pixel")
        {
            element = child->ToElement();
            wstring shaderFile = StringPath::ToWString(element->GetText());
            shaderFile = shaderFile.substr(shaderFile.find_first_of('/') + 1, shaderFile.length());
            pixelShader = Shader::AddPS(shaderFile);
        }
    }
}

void Material::ParsingTexture(tinyxml2::XMLNode* Parent)
{
    tinyxml2::XMLNode* child = NULL;
    tinyxml2::XMLElement* element = NULL;

    for (child = Parent->FirstChild(); child; child = child->NextSibling())
    {
        string value = child->Value();
        if (value == "Diffuse")
        {
            element = child->ToElement();
            wstring textureFile = StringPath::ToWString(element->GetText());
            SetDiffuseMap(textureFile);
        }
        if (value == "Specular")
        {
            element = child->ToElement();
            wstring textureFile = StringPath::ToWString(element->GetText());
            SetSpecularMap(textureFile);
        }
        if (value == "Normal")
        {
            element = child->ToElement();
            wstring textureFile = StringPath::ToWString(element->GetText());
            SetNormalMap(textureFile);
        }
    }
}

void Material::ParsingProperty(tinyxml2::XMLNode* Parent)
{
    tinyxml2::XMLNode* child = NULL;
    tinyxml2::XMLElement* element = NULL;

    for (child = Parent->FirstChild(); child; child = child->NextSibling())
    {
        string value = child->Value();

        if (value == "Shininess")
        {
            element = child->ToElement();
            int temp = stoi(element->GetText());
            buffer->Get().shininess = temp;
        }
        if (value == "HasNormalMap")
        {
            element = child->ToElement();
            int temp = stoi(element->GetText());
            buffer->Get().hasNormalMap = temp;
        }
        Float4 Color;
        if (value == "Diffuse")
        {
            Color = ParsingColor(child);
            buffer->Get().diffuse = Color;
        }
      
        if (value == "Specular")
        {
            Color = ParsingColor(child);
            buffer->Get().specular = Color;
        }
        if (value == "Ambient")
        {
            Color = ParsingColor(child);
            buffer->Get().ambient = Color;
        }
        if (value == "Emissive")
        {
            Color = ParsingColor(child);
            buffer->Get().emissive = Color;
        }
    }
}

Float4 Material::ParsingColor(tinyxml2::XMLNode* Parent)
{
    Float4 color = Float4(1.0f, 1.0f, 1.0f, 1.0f);

    tinyxml2::XMLNode* child = NULL;
    tinyxml2::XMLElement* element = NULL;

    for (child = Parent->FirstChild(); child; child = child->NextSibling())
    {
        string value = child->Value();
        if (value == "R")
        {
            element = child->ToElement();
            float temp = stof(element->GetText());
            color.x = temp;
        }
        if (value == "G")
        {
            element = child->ToElement();
            float temp = stof(element->GetText());
            color.y = temp;
        }
        if (value == "B")
        {
            element = child->ToElement();
            float temp = stof(element->GetText());
            color.z = temp;
        }
        if (value == "A")
        {
            element = child->ToElement();
            float temp = stof(element->GetText());
            color.w = temp;
        }
    }

    return color;
}
