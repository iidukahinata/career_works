/**
* @file	   D3D11GrahicsDevice.cpp
* @brief
*
* @date	   2022/07/01 2022�N�x����
*/



#include "D3D11GrahicsDevice.h"
#include "RenderStates.h"

bool D3D11GraphicsDevice::Init(HWND hWnd, UINT screenWidth, UINT screenHeight, bool isFullscreen)
{
	HRESULT  hr;
	Microsoft::WRL::ComPtr<IDXGIFactory> factory;
	Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
	Microsoft::WRL::ComPtr<IDXGIOutput> adapterOutput;
	UINT numModes;
	UINT numerator = 60;		// ���q
	UINT denominator = 1;		// ����
	DXGI_MODE_DESC* displayModeList;
	D3D_FEATURE_LEVEL level;

	// �h���C�o�̎��
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,			// Windows Advanced Rasterizer
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_SOFTWARE,
	};

	UINT numDriverTypes = ARRAYSIZE(driverTypes);
	UINT createDeviceFlags = 0;

	// �@�\���x��
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,			// DirectX11.1�Ή�GPU���x��
		D3D_FEATURE_LEVEL_11_0,			// DirectX11�Ή�GPU���x��
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	// Create a DirectX graphics interface factory
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)factory.GetAddressOf());
	if (FAILED(hr)) {
		return false;
	}

	// use the factory to create an adpter for the primary graphics interface(video card)
	hr = factory->EnumAdapters(0, adapter.GetAddressOf());
	if (FAILED(hr)) {
		return false;
	}

	// enumerrate primary adapter output(monitor)
	hr = adapter->EnumOutputs(0, adapterOutput.GetAddressOf());
	if (FAILED(hr)) {
		return false;
	}

	// get the number of modes that fit the DXGI_FORMAT_R8G8B8_UNORM display format forthe adapter output(monitor)
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(hr)) {
		return false;
	}

	// create alist to hold all possible display modes for this monitor/video card combination
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList) {
		return false;
	}

	// now fill the display mode list structures
	hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(hr)) {
		return false;
	}

	// now go through all the display modes and find the one that matches the screen width and height
	// when a match is found store the numerator and denominator of the refresh rate for that monitor
	for (unsigned int i = 0; i < numModes; i++) {
		if (displayModeList[i].Width == screenWidth) {
			if (displayModeList[i].Height == screenHeight) {
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	delete[] displayModeList;
	displayModeList = nullptr;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		D3D11CreateDevice(nullptr, driverTypes[driverTypeIndex], nullptr, createDeviceFlags,
			featureLevels, numFeatureLevels, D3D11_SDK_VERSION,
			m_device.GetAddressOf(), &level, m_context.GetAddressOf());

		if (SUCCEEDED(hr)) {
			break;
		}
	}

	// MSAA
	bool isMSAA = true;
	UINT Quality = 0;
	m_device->CheckMultisampleQualityLevels(DXGI_FORMAT_D32_FLOAT, 4, &Quality);

	DXGI_SAMPLE_DESC sampleDesc;
	sampleDesc.Count = 4;				// �}���`�T���v���̐�
	sampleDesc.Quality = Quality - 1;	// �}���`�T���v���̃N�I���e�B

	// �X���b�v�`�F�C���̐ݒ�
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	sd.BufferDesc.Width = screenWidth;						// �o�b�N�o�b�t�@�̕�
	sd.BufferDesc.Height = screenHeight;					// �o�b�N�o�b�t�@�̍���
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		// �o�b�N�o�b�t�@�t�H�[�}�b�g(R,G,B �͈͂O�D�O����P�D�O)
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// �o�b�N�o�b�t�@�̎g�p���@
	sd.BufferDesc.RefreshRate.Numerator = numerator;		// ���t���b�V�����[�g�i����j
	sd.BufferDesc.RefreshRate.Denominator = denominator;	// ���t���b�V�����[�g�i���q�j
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	sd.OutputWindow = hWnd;			// �֘A�t����E�C���h�E
	if (isMSAA) {
		sd.SampleDesc = sampleDesc;
	}
	else {
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (isFullscreen) {
		sd.Windowed = FALSE;
	}
	else {
		sd.Windowed = TRUE;
	}

	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	hr = factory->CreateSwapChain(m_device.Get(), &sd, m_swapChain.GetAddressOf());
	if (FAILED(hr)) {
		return false;
	}

	//�[�x�X�e���V���o�b�t�@�쐬
	{
		// �o�b�N�o�b�t�@�֌W�̐ݒ菈��
		hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)m_backBuffer.GetAddressOf());
		if (FAILED(hr)) {
			return false;
		}

		hr = m_device->CreateRenderTargetView(m_backBuffer.Get(), NULL, m_renderTargetView.GetAddressOf());
		if (FAILED(hr)) {
			return false;
		}

		Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilTexture;
		D3D11_TEXTURE2D_DESC txDesc;
		ZeroMemory(&txDesc, sizeof(txDesc));
		txDesc.Width = screenWidth;
		txDesc.Height = screenHeight;
		txDesc.MipLevels = 1;
		txDesc.ArraySize = 1;
		txDesc.Format = DXGI_FORMAT_D32_FLOAT;
		if (isMSAA) {
			txDesc.SampleDesc = sampleDesc;
		}
		else {
			txDesc.SampleDesc.Count = 1;
			txDesc.SampleDesc.Quality = 0;
		}
		txDesc.Usage = D3D11_USAGE_DEFAULT;
		txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		txDesc.CPUAccessFlags = 0;
		txDesc.MiscFlags = 0;

		hr = m_device->CreateTexture2D(&txDesc, NULL, depthStencilTexture.GetAddressOf());
		if (FAILED(hr)) {
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
		ZeroMemory(&dsDesc, sizeof(dsDesc));
		dsDesc.Format = txDesc.Format;
		dsDesc.ViewDimension = isMSAA ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
		dsDesc.Texture2D.MipSlice = 0;
		hr = m_device->CreateDepthStencilView(depthStencilTexture.Get(), &dsDesc, m_depthStencilView.GetAddressOf());

		SetRenderTarget(m_renderTargetView.Get(), m_depthStencilView.Get());
	}

	//�r���[�|�[�g�ݒ�
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (FLOAT)screenWidth;
	viewport.Height = (FLOAT)screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_context->RSSetViewports(1, &viewport);

	D3D11RenderStates::Get().Init();

	return true;
}

void D3D11GraphicsDevice::Clear(const Math::Vector4& color)
{
	// ��ʃN���A�i�w��F�œh��Ԃ��j
	float clearColor[4] = { color.x, color.y, color.z, color.w };
	m_context->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);

	m_context->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void D3D11GraphicsDevice::Present()
{
	m_swapChain->Present(0, 0);
}

ID3D11Device* D3D11GraphicsDevice::GetDevice() noexcept
{
	return m_device.Get();
}

ID3D11DeviceContext* D3D11GraphicsDevice::GetContext() noexcept
{
	return m_context.Get();
}

IDXGISwapChain* D3D11GraphicsDevice::GetSwapChain() noexcept
{
	return m_swapChain.Get();
}

void D3D11GraphicsDevice::SetRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStencil)
{
	m_context->OMSetRenderTargets(1, &renderTarget, depthStencil);
}

void D3D11GraphicsDevice::SetRenderTargets(UINT numViews, ID3D11RenderTargetView** renderTargets, ID3D11DepthStencilView* depthStencil)
{
	m_context->OMSetRenderTargets(numViews, renderTargets, depthStencil);
}

ID3D11RenderTargetView* D3D11GraphicsDevice::GetRenderTarget() noexcept
{
	return m_renderTargetView.Get();
}

void D3D11GraphicsDevice::SetViewport(float width, float height)
{
	//�r���[�|�[�g�ݒ�
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	m_context->RSSetViewports(1, &viewport);
}

void D3D11GraphicsDevice::SetViewports(UINT numBffers, D3D11_VIEWPORT* viewports)
{
	m_context->RSSetViewports(numBffers, viewports);
}

ID3D11DepthStencilView* D3D11GraphicsDevice::GetDepthStencil() noexcept
{
	return m_depthStencilView.Get();
}