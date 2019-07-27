#include "DX12Base.h"
#include "../../Screen/Screen.h"
#include <tchar.h> // Debug文字列用

namespace MSLib {
	DX12Base::DX12Base(ApplicationBase* app) :
		IDXBase(app)
	{

	}

	DX12Base::~DX12Base() {
		this->Release();
	}

	HRESULT DX12Base::Initialize() {
		HRESULT hr;

		UINT flagsDXGI = DebugCheck();

		ComPtr<IDXGIFactory4> pFactory;
		hr = CreateFactory(&pFactory, flagsDXGI);
		if (FAILED(hr)) {
			OutputDebugString(_T("Failed : CreateDXGIFactory2"));
			return E_FAIL;
		}

		ComPtr<IDXGIAdapter1> useAdapter;
		hr = CreateDevice(pFactory.Get(), &useAdapter);
		if (FAILED(hr)) {
			OutputDebugString(_T("Failed : Not Found DX12 supports adapter"));
			return E_FAIL;
		}

		D3D12_COMMAND_QUEUE_DESC commandQueueDesc;
		ZeroMemory(&commandQueueDesc, sizeof(commandQueueDesc));
		SettingCommandQueue(&commandQueueDesc);
		hr = m_pDevice->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(pCmdQueue.GetAddressOf()));
		if (FAILED(hr)) {
			OutputDebugString(_T("Failed : CreateCommandQueue"));
			return E_FAIL;
		}

		DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		SettingSwapChain(&swapChainDesc);
		hr = CreateSwapChain(pFactory.Get(), &swapChainDesc);
		if (FAILED(hr)) {
			OutputDebugString(_T("Failed : CreateSwapChain"));
			return E_FAIL;
		}

		// RenderTargetView
		D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc;
		ZeroMemory(&descriptorHeapDesc, sizeof(descriptorHeapDesc));
		SettingRenderTargetViewHeapDesc(&descriptorHeapDesc);
		hr = CreateDescriptorHeap(&descriptorHeapDesc, m_pRtvHeap.GetAddressOf(), &m_RtvDescriptorSize);
		if (FAILED(hr)) {
			OutputDebugString(_T("Failed : CreateDescriptorHeap RenderTargetView"));
			return E_FAIL;
		}

		hr = CreateRenderTargetView();
		if (FAILED(hr)) {
			OutputDebugString(_T("Failed : CreateRenderTargetView"));
			return E_FAIL;
		}

		// DepthStencilView
		SettingDepthStencilViewHeapDesc(&descriptorHeapDesc);
		hr = CreateDescriptorHeap(&descriptorHeapDesc, m_pDsvHeap.GetAddressOf(), &m_DsvDescriptorSize);
		if (FAILED(hr)) {
			OutputDebugString(_T("Failed : CreateDescriptorHeap DepthStencilView"));
			return E_FAIL;
		}

		hr = CreateDepthStencilView();
		if (FAILED(hr)) {
			OutputDebugString(_T("Failed : CreateDepthStencilView"));
			return E_FAIL;
		}

		for (int i = 0; i < SwapChainBufferCount; ++i)
		{
			hr = m_pDevice->CreateCommandAllocator(
				D3D12_COMMAND_LIST_TYPE_DIRECT,
				IID_PPV_ARGS(m_pCmdAllocator[i].GetAddressOf()));
			if (FAILED(hr)) {
				OutputDebugString(_T("Failed : CreateCommandAllocator"));
				return E_FAIL;
			}
		}

		hr = m_pDevice->CreateCommandList(
			0,
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			m_pCmdAllocator[0].Get(),
			nullptr,
			IID_PPV_ARGS(m_pCmdList.GetAddressOf()));
		if (FAILED(hr)) {
			return E_FAIL;
		}

		hr = m_pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(m_pFence.GetAddressOf()));
		if (FAILED(hr)) {
			return E_FAIL;
		}

		m_FenceValue = 1;
		m_FenceEvent = CreateEventEx(nullptr, FALSE, FALSE, EVENT_ALL_ACCESS);
		if (m_FenceEvent == nullptr) {
			return E_FAIL;
		}

		SettingViewport(&m_Viewport);

		return S_OK;
	}

	UINT DX12Base::DebugCheck() {
		UINT flags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		ComPtr<ID3D12Debug> pDebug;
		HRESULT hr = D3D12GetDebugInterface(IID_PPV_ARGS(&pDebug));
		if (SUCCEEDED(hr)) {
			pDebug->EnableDebugLayer();
			pDebug->Release();
			pDebug = nullptr;
		}
		flags |= DXGI_CREATE_FACTORY_DEBUG;
#endif
		return flags;
	}

	HRESULT DX12Base::CreateFactory(ComPtr<IDXGIFactory4>* pFactory, UINT debugFlag) {
		return CreateDXGIFactory2(debugFlag, IID_PPV_ARGS(pFactory->GetAddressOf()));
	}

	HRESULT DX12Base::CreateDevice(IDXGIFactory4* pFactory, ComPtr<IDXGIAdapter1>* adapter) {
		HRESULT hr;
		UINT adapterIndex = 0;
		while (DXGI_ERROR_NOT_FOUND != pFactory->EnumAdapters1(adapterIndex, adapter->GetAddressOf())) {
			DXGI_ADAPTER_DESC1 desc;
			adapter->Get()->GetDesc1(&desc);
			++adapterIndex;
			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
				continue;

			// デバイス生成
			// TODO : ここで対応シェーダバージョンを確認する感じに
			hr = D3D12CreateDevice(adapter->Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(m_pDevice.GetAddressOf()));
			if (SUCCEEDED(hr)) {
				return S_OK;
			}
		}

		return E_FAIL;
	}

	void DX12Base::SettingCommandQueue(D3D12_COMMAND_QUEUE_DESC* desc) {
		desc->Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		desc->Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		desc->Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		desc->NodeMask = 0;
	}

	void DX12Base::SettingSwapChain(DXGI_SWAP_CHAIN_DESC1* desc) {
		desc->Width = Screen::GetWidth();
		desc->Height = Screen::GetHeight();
		desc->Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc->Stereo = FALSE;
		desc->SampleDesc.Count = 1;
		desc->SampleDesc.Quality = 0;
		desc->BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc->BufferCount = SwapChainBufferCount;
		desc->Scaling = DXGI_SCALING_STRETCH;
		desc->SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		desc->AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		desc->Flags = 0;
	}

	HRESULT DX12Base::CreateSwapChain(IDXGIFactory4* pFactory, DXGI_SWAP_CHAIN_DESC1* desc) {
		ComPtr<IDXGISwapChain1> pSwapChain;
		HRESULT hr = pFactory->CreateSwapChainForHwnd(
			this->pCmdQueue.Get(),
			GetApplication()->GetHWND(),
			desc,
			nullptr,
			nullptr,
			pSwapChain.GetAddressOf());
		if (FAILED(hr)) {
			return E_FAIL;
		}

		pSwapChain.As(&m_pSwapChain);

		return hr;
	}

	void DX12Base::SettingRenderTargetViewHeapDesc(D3D12_DESCRIPTOR_HEAP_DESC* desc) {
		desc->NumDescriptors = SwapChainBufferCount;
		desc->Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		desc->Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		desc->NodeMask = 0;
	}

	void DX12Base::SettingDepthStencilViewHeapDesc(D3D12_DESCRIPTOR_HEAP_DESC* desc) {
		desc->NumDescriptors = 1;
		desc->Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		desc->Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		desc->NodeMask = 0;
	}

	HRESULT DX12Base::CreateDescriptorHeap(
		D3D12_DESCRIPTOR_HEAP_DESC* desc,
		ID3D12DescriptorHeap** heap,
		UINT* descSize)
	{
		HRESULT hr = m_pDevice->CreateDescriptorHeap(desc, IID_PPV_ARGS(heap));
		if (FAILED(hr)) {
			return E_FAIL;
		}
		*descSize = m_pDevice->GetDescriptorHandleIncrementSize(desc->Type);
		return hr;
	}

	void DX12Base::SettingRenderTargetViewDesc(D3D12_RENDER_TARGET_VIEW_DESC* desc) {
		desc->Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		desc->ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		desc->Texture2D.MipSlice = 0;
		desc->Texture2D.PlaneSlice = 0;
	}

	HRESULT DX12Base::CreateRenderTargetView() {
		HRESULT hr;
		D3D12_CPU_DESCRIPTOR_HANDLE handle = m_pRtvHeap->GetCPUDescriptorHandleForHeapStart();
		D3D12_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		SettingRenderTargetViewDesc(&renderTargetViewDesc);

		for (UINT i = 0; i < SwapChainBufferCount; ++i) {
			hr = m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(m_pRenderTarget[i].GetAddressOf()));
			if (FAILED(hr)) {
				return E_FAIL;
			}

			m_pDevice->CreateRenderTargetView(m_pRenderTarget[i].Get(), &renderTargetViewDesc, handle);

			handle.ptr += m_RtvDescriptorSize;
		}

		return S_OK;
	}

	HRESULT DX12Base::CreateDepthStencilView() {
		D3D12_HEAP_PROPERTIES prop;
		SettingDepthHeapProperties(&prop);

		D3D12_RESOURCE_DESC desc;
		SettingDepthResourceDesc(&desc);

		D3D12_CLEAR_VALUE clearValue;
		SettingDepthClearValue(&clearValue);

		HRESULT hr = m_pDevice->CreateCommittedResource(
			&prop,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			D3D12_RESOURCE_STATE_DEPTH_WRITE,
			&clearValue,
			IID_PPV_ARGS(m_pDepthStencil.GetAddressOf()));
		if (FAILED(hr)) {
			return E_FAIL;
		}

		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
		SettingDepthStencilViewDesc(&dsvDesc);

		m_pDevice->CreateDepthStencilView(
			m_pDepthStencil.Get(),
			&dsvDesc,
			m_pDsvHeap->GetCPUDescriptorHandleForHeapStart());

		return hr;
	}

	void DX12Base::SettingDepthHeapProperties(D3D12_HEAP_PROPERTIES* desc) {
		desc->Type = D3D12_HEAP_TYPE_DEFAULT;
		desc->CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
		desc->MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
		// 下記2つはマルチアダプタ用
		desc->CreationNodeMask = 1;
		desc->VisibleNodeMask = 1;
	}

	void DX12Base::SettingDepthResourceDesc(D3D12_RESOURCE_DESC* desc) {
		desc->Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		desc->Alignment = 0;
		desc->Width = Screen::GetWidth();
		desc->Height = Screen::GetHeight();
		desc->DepthOrArraySize = 1;
		desc->MipLevels = 0;
		desc->Format = DXGI_FORMAT_D32_FLOAT;
		desc->SampleDesc.Count = 1;
		desc->SampleDesc.Quality = 0;
		desc->Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		desc->Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	}

	void DX12Base::SettingDepthClearValue(D3D12_CLEAR_VALUE* clearValue) {
		clearValue->Format = DXGI_FORMAT_D32_FLOAT;
		clearValue->DepthStencil.Depth = 1.0f;
		clearValue->DepthStencil.Stencil = 0;
	}

	void DX12Base::SettingDepthStencilViewDesc(D3D12_DEPTH_STENCIL_VIEW_DESC* desc) {
		desc->Format = DXGI_FORMAT_D32_FLOAT;
		desc->ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
		desc->Flags = D3D12_DSV_FLAG_NONE;
	}

	void DX12Base::SettingViewport(D3D12_VIEWPORT* viewport) {
		viewport->TopLeftX = 0;
		viewport->TopLeftY = 0;
		viewport->Width = static_cast<FLOAT>(Screen::GetWidth());
		viewport->Height = static_cast<FLOAT>(Screen::GetHeight());
		viewport->MinDepth = 0.0f;
		viewport->MaxDepth = 1.0f;
	}

	void DX12Base::BeginResourceBarrier() {
		D3D12_RESOURCE_BARRIER barrier;
		ZeroMemory(&barrier, sizeof(barrier));
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = m_pRenderTarget[m_FrameIndex].Get();
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		m_pCmdList->ResourceBarrier(1, &barrier);
	}

	void DX12Base::EndResourceBarrier() {
		D3D12_RESOURCE_BARRIER barrier;
		ZeroMemory(&barrier, sizeof(barrier));
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = m_pRenderTarget[m_FrameIndex].Get();
		barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		m_pCmdList->ResourceBarrier(1, &barrier);
	}

	void DX12Base::ClearRenderTargetView(const float* clearColor) {
		auto handleRTV = m_pRtvHeap->GetCPUDescriptorHandleForHeapStart();
		handleRTV.ptr += (m_FrameIndex * m_RtvDescriptorSize);
		m_pCmdList->ClearRenderTargetView(handleRTV, clearColor, 0, nullptr);
	}

	void DX12Base::ClearDepthStencilView(float depth, UINT8 stencil) {
		auto handleDSV = m_pDsvHeap->GetCPUDescriptorHandleForHeapStart();
		m_pCmdList->ClearDepthStencilView(handleDSV, D3D12_CLEAR_FLAG_DEPTH, depth, stencil, 0, nullptr);
	}

	HRESULT DX12Base::Step() {
		Update();
		Render();
		return S_OK;
	}

	void DX12Base::Update() {

	}

	void DX12Base::Render() {
		// スワップチェーンイメージ内インデックス取得
		m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();

		// コマンドアロケータとコマンドリストをリセット
		m_pCmdAllocator[m_FrameIndex]->Reset();
		m_pCmdList->Reset(m_pCmdAllocator[m_FrameIndex].Get(), nullptr);

		BeginResourceBarrier();

		const float clearColor[] = { 0.1f, 0.25f, 0.5f, 1.0f };
		ClearRenderTargetView(clearColor);
		ClearDepthStencilView(1.0f, 0);

		EndResourceBarrier();

		// 描画コマンドの積み処理終了
		m_pCmdList->Close();

		// コマンド実行
		ID3D12CommandList* lists[] = { m_pCmdList.Get() };
		pCmdQueue->ExecuteCommandLists(_countof(lists), lists);

		// 表示する
		m_pSwapChain->Present(1, 0);

		WaitForGpu();
	}

	HRESULT DX12Base::Release() {
		// コマンドの終了を待機
		WaitForGpu();

		// イベントハンドルを閉じる
		CloseHandle(m_FenceEvent);
		m_FenceEvent = nullptr;

		for (UINT i = 0; i < SwapChainBufferCount; ++i) {
			m_pRenderTarget[i].Reset();
		}

		m_pDepthStencil.Reset();

		m_pSwapChain.Reset();
		m_pFence.Reset();
		m_pCmdList.Reset();
		pCmdQueue.Reset();
		m_pDevice.Reset();

		return S_OK;
	}

	void DX12Base::WaitForGpu() {
		// シグナル状態にしてフェンス値を増加
		const UINT64 fence = m_FenceValue;
		auto hr = pCmdQueue->Signal(m_pFence.Get(), fence);
		if (FAILED(hr)) {
			OutputDebugString(_T("Failed : ID3D12CommandQueue::Single()"));
			return;
		}
		m_FenceValue++;

		// 完了を待機
		if (m_pFence->GetCompletedValue() < fence) {
			hr = m_pFence->SetEventOnCompletion(fence, m_FenceEvent);
			if (FAILED(hr)) {
				OutputDebugString(_T("Failed : ID3D12Fence::SetEventOnCompletation"));
				return;
			}

			WaitForSingleObject(m_FenceEvent, INFINITE);
		}

		// フレームバッファ番号を更新
		m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();
	}
}