#include "ResourceManager.h"
#include "DX11DeviceBuilder.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Mesh.h"
#include "GeometryGenerator.h"

namespace MZGraphics
{
	ResourceManager::ResourceManager()
		: _builder(nullptr)
	{
	}

	void ResourceManager::Initialize(DX11DeviceBuilder* builder)
	{
		_builder = std::unique_ptr<DX11DeviceBuilder>(builder);
		LoadShaders();
		LoadFonts();
		CreateRasterizerStates();
		CreatePrimitives();
	}

	void ResourceManager::LoadShaders()
	{
		LoadVertexShader("VertexShader.cso");
		LoadPixelShader("PixelShader.cso");
	}

	void ResourceManager::LoadVertexShader(const std::string& filename)
	{
		std::string fullPath = "Resources/Shaders/" + filename;
		std::wstring wstr(fullPath.begin(), fullPath.end());
		VertexShader* vertexShader = new VertexShader(GetDevice(), GetDeviceContext());
		if (vertexShader->LoadShaderFile(wstr.c_str()))
			_vertexShaders.insert(std::make_pair(filename, vertexShader));
	}

	void ResourceManager::LoadPixelShader(const std::string& filename)
	{
		std::string fullPath = "Resources/Shaders/" + filename;
		std::wstring wstr(fullPath.begin(), fullPath.end());
		PixelShader* pixelShader = new PixelShader(GetDevice(), GetDeviceContext());
		if (pixelShader->LoadShaderFile(wstr.c_str()))
			_pixelShaders.insert(std::make_pair(filename, pixelShader));
	}

	void ResourceManager::LoadFonts()
	{
		_spriteBatch = new DirectX::SpriteBatch(GetDeviceContext());
		_commonStates = new DirectX::CommonStates(GetDevice());

		std::string searchPath = "Resources/font/*.*";
		WIN32_FIND_DATAA fileData;
		HANDLE hFind = FindFirstFileA(searchPath.c_str(), &fileData);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					std::string filename = std::string(fileData.cFileName);
					std::wstring wfilename(filename.begin(), filename.end());
					std::string fontname = filename.substr(0, filename.find_last_of("."));
					std::string fileExtension = filename.substr(filename.find_last_of(".") + 1, filename.length() - filename.find_last_of("."));
					if (fileExtension == "spriteFont")
					{
						DirectX::SpriteFont* spriteFont = new DirectX::SpriteFont(GetDevice(), wfilename.c_str());
						_spriteFonts.insert({ fontname, spriteFont });
					}
				}
			} while (FindNextFileA(hFind, &fileData));
			FindClose(hFind);
		}
	}

	void ResourceManager::CreateRasterizerStates()
	{
		D3D11_RASTERIZER_DESC solidDesc;
		ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
		solidDesc.FillMode = D3D11_FILL_SOLID;
		solidDesc.CullMode = D3D11_CULL_BACK;
		solidDesc.FrontCounterClockwise = false;
		solidDesc.DepthClipEnable = true;
		ID3D11RasterizerState* solid;
		GetDevice()->CreateRasterizerState(&solidDesc, &solid);
		_rasterizerStates.push_back(solid);

		D3D11_RASTERIZER_DESC cullFrontSolidDesc;
		ZeroMemory(&cullFrontSolidDesc, sizeof(D3D11_RASTERIZER_DESC));
		cullFrontSolidDesc.FillMode = D3D11_FILL_SOLID;
		cullFrontSolidDesc.CullMode = D3D11_CULL_FRONT;
		cullFrontSolidDesc.FrontCounterClockwise = false;
		cullFrontSolidDesc.DepthClipEnable = true;
		ID3D11RasterizerState* cullFrontSolid;
		GetDevice()->CreateRasterizerState(&cullFrontSolidDesc, &cullFrontSolid);
		_rasterizerStates.push_back(cullFrontSolid);

		D3D11_RASTERIZER_DESC cullNoneSolidDesc;
		ZeroMemory(&cullNoneSolidDesc, sizeof(D3D11_RASTERIZER_DESC));
		cullNoneSolidDesc.FillMode = D3D11_FILL_SOLID;
		cullNoneSolidDesc.CullMode = D3D11_CULL_NONE;
		cullNoneSolidDesc.FrontCounterClockwise = false;
		cullNoneSolidDesc.DepthClipEnable = true;
		ID3D11RasterizerState* cullNoneSolid;
		GetDevice()->CreateRasterizerState(&cullNoneSolidDesc, &cullNoneSolid);
		_rasterizerStates.push_back(cullNoneSolid);

		D3D11_RASTERIZER_DESC wireframeDesc;
		ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
		wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
		wireframeDesc.CullMode = D3D11_CULL_BACK;
		wireframeDesc.FrontCounterClockwise = false;
		wireframeDesc.DepthClipEnable = true;
		ID3D11RasterizerState* wireframe;
		GetDevice()->CreateRasterizerState(&wireframeDesc, &wireframe);
		_rasterizerStates.push_back(wireframe);

		D3D11_RASTERIZER_DESC shadowMapDesc;
		ZeroMemory(&shadowMapDesc, sizeof(D3D11_RASTERIZER_DESC));
		shadowMapDesc.FillMode = D3D11_FILL_SOLID;
		shadowMapDesc.CullMode = D3D11_CULL_FRONT;
		shadowMapDesc.FrontCounterClockwise = false;
		shadowMapDesc.DepthClipEnable = true;
		ID3D11RasterizerState* shadowMapRS;
		GetDevice()->CreateRasterizerState(&shadowMapDesc, &shadowMapRS);
		_rasterizerStates.push_back(shadowMapRS);

		D3D11_RASTERIZER_DESC cubeMapDesc;
		ZeroMemory(&cubeMapDesc, sizeof(D3D11_RASTERIZER_DESC));
		cubeMapDesc.FillMode = D3D11_FILL_SOLID;
		cubeMapDesc.CullMode = D3D11_CULL_NONE;
		cubeMapDesc.FrontCounterClockwise = false;
		cubeMapDesc.DepthClipEnable = true;
		ID3D11RasterizerState* cubemapRS;
		GetDevice()->CreateRasterizerState(&cubeMapDesc, &cubemapRS);
		_rasterizerStates.push_back(cubemapRS);
	}

	void ResourceManager::CreatePrimitives()
	{
		GeometryGenerator generator;
		generator.CreateGrid();
	}

	ResourceManager::~ResourceManager()
	{
	}

	ID3D11Device* ResourceManager::GetDevice() const
	{
		return _builder->GetDevice();
	}

	ID3D11DeviceContext* ResourceManager::GetDeviceContext() const
	{
		return _builder->GetDeviceContext();
	}

	IDXGISwapChain* ResourceManager::GetSwapChain() const
	{
		return _builder->GetSwapChain();
	}

	ID3D11RenderTargetView* ResourceManager::GetRTV() const
	{
		return _builder->GetRTV();
	}

	ID3D11RasterizerState* ResourceManager::GetRasterizerState(eRasterizerState eState) const
	{
		return _rasterizerStates[static_cast<int>(eState)];
	}

	MZGraphics::VertexShader* ResourceManager::GetVertexShader(const std::string& filename) const
	{
		if (_vertexShaders.find(filename) != _vertexShaders.end())
			return _vertexShaders.at(filename);
		return nullptr;
	}

	MZGraphics::PixelShader* ResourceManager::GetPixelShader(const std::string& filename) const
	{
		if (_pixelShaders.find(filename) != _pixelShaders.end())
			return _pixelShaders.at(filename);
		return nullptr;
	}

	MZGraphics::FileData* ResourceManager::GetFileData(const std::string& filename) const
	{
		if (_fileDatas.find(filename) != _fileDatas.end())		
			return _fileDatas.at(filename);		
		return nullptr;
	}

	DirectX::SpriteFont* ResourceManager::GetFont(const std::string& fontname) const
	{
		if (_spriteFonts.find(fontname) != _spriteFonts.end())
			return _spriteFonts.at(fontname);
		return nullptr;
	}

	DirectX::SpriteBatch* ResourceManager::GetSpriteBatch() const
	{
		return _spriteBatch;
	}

	DirectX::CommonStates* ResourceManager::GetCommonStates() const
	{
		return _commonStates;
	}

	void ResourceManager::AddFileData(const std::string& filename, FileData* data)
	{
		_fileDatas[filename] = data;
	}

}