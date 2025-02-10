#pragma once
#include "Singleton.h"
#include <memory>
#include <d3d11.h>
#include <DirectXMath.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <DXTK/SpriteFont.h>
#include <DXTK/CommonStates.h>

/// <summary>
/// 스테이트, 버퍼, 쉐이더, 파일 등의 리소스를 관리하는 클래스
/// </summary>

namespace MZGraphics
{
	class DX11DeviceBuilder;
	class VertexShader;
	class PixelShader;
	class Mesh;

	struct FileData
	{
		std::vector<Mesh*> loadedMeshes;
	};

	enum class eRasterizerState
	{
		SOLID,
		CULLFRONTSOLID,
		CULLNONESOLID,
		WIREFRAME,
		SHADOWMAP,
		CUBEMAP,
	};

	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		friend Singleton<ResourceManager>;
		~ResourceManager();
		void Initialize(DX11DeviceBuilder* builder);

	public:
		ID3D11Device* GetDevice() const;
		ID3D11DeviceContext* GetDeviceContext() const;
		IDXGISwapChain* GetSwapChain() const;
		ID3D11RenderTargetView* GetRTV() const;
		ID3D11RasterizerState* GetRasterizerState(eRasterizerState eState) const;

	public:
		VertexShader* GetVertexShader(const std::string& filename) const;
		PixelShader* GetPixelShader(const std::string& filename) const;
		FileData* GetFileData(const std::string& filename) const;

	public:
		// 폰트 관련
		DirectX::SpriteFont* GetFont(const std::string& fontname) const;
		DirectX::SpriteBatch* GetSpriteBatch() const;
		DirectX::CommonStates* GetCommonStates() const;

	public:
		void AddFileData(const std::string& filename, FileData* data);

	private:
		ResourceManager();
		void LoadShaders();
		void LoadVertexShader(const std::string& filename);
		void LoadPixelShader(const std::string& filename);
		void LoadFonts();
		void CreateRasterizerStates();
		void CreatePrimitives();

	private:
		std::unique_ptr<DX11DeviceBuilder> _builder;
		std::unordered_map<std::string, VertexShader*> _vertexShaders;
		std::unordered_map<std::string, PixelShader*> _pixelShaders;
		std::unordered_map<std::string, FileData*> _fileDatas;
		std::unordered_map<std::string, DirectX::SpriteFont*> _spriteFonts;

	private:
		std::vector<ID3D11RasterizerState*> _rasterizerStates;

	private:
		// Text 관련
		DirectX::SpriteBatch* _spriteBatch;
		DirectX::CommonStates* _commonStates;
	};
}

