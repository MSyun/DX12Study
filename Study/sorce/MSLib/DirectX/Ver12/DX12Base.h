#pragma once


#include "../DXBase.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

using namespace Microsoft::WRL;


// TODO : RenderTargetViewは別クラスで管理・生成したほうがよさそう
// ゲーム中には変わらんけど数変更は普通にある
namespace MSLib {
	constexpr UINT SwapChainBufferCount = 2;

	class DX12Base : public IDXBase {
	public:
		explicit DX12Base(ApplicationBase* app);
		virtual ~DX12Base();

		virtual HRESULT Initialize() override;
		virtual HRESULT Step() override;
		virtual HRESULT Release() override;

	protected:
		virtual void SettingCommandQueue(D3D12_COMMAND_QUEUE_DESC* desc);
		virtual void SettingSwapChain(DXGI_SWAP_CHAIN_DESC1* desc);
		virtual void SettingRenderTargetViewHeapDesc(D3D12_DESCRIPTOR_HEAP_DESC* desc);
		virtual void SettingDepthStencilViewHeapDesc(D3D12_DESCRIPTOR_HEAP_DESC* desc);
		virtual void SettingRenderTargetViewDesc(D3D12_RENDER_TARGET_VIEW_DESC* desc);
		virtual void SettingDepthHeapProperties(D3D12_HEAP_PROPERTIES* desc);
		virtual void SettingDepthResourceDesc(D3D12_RESOURCE_DESC* desc);
		virtual void SettingDepthClearValue(D3D12_CLEAR_VALUE* clearValue);
		virtual void SettingDepthStencilViewDesc(D3D12_DEPTH_STENCIL_VIEW_DESC* desc);
		virtual void SettingViewport(D3D12_VIEWPORT* viewport);

	private:
		void WaitForGpu();

		virtual void Update();
		virtual void Render();

		UINT DebugCheck();
		HRESULT CreateFactory(ComPtr<IDXGIFactory4>* pFactory, UINT debugFlag);
		HRESULT CreateDevice(IDXGIFactory4* pFactory, ComPtr<IDXGIAdapter1>* adapter);
		HRESULT CreateSwapChain(IDXGIFactory4* pFactory, DXGI_SWAP_CHAIN_DESC1* desc);
		HRESULT CreateDescriptorHeap(
			D3D12_DESCRIPTOR_HEAP_DESC* desc,
			ID3D12DescriptorHeap** heap,
			UINT* descSize);
		HRESULT CreateRenderTargetView();
		HRESULT CreateDepthStencilView();

	protected:
		D3D12_VIEWPORT m_Viewport;
		D3D12_RECT m_ScissorRect;
		ComPtr<IDXGISwapChain3> m_pSwapChain;
		ComPtr<ID3D12Device> m_pDevice;
		ComPtr<ID3D12Resource> m_pRenderTarget[SwapChainBufferCount];
		ComPtr<ID3D12Resource> m_pDepthStencil;
		ComPtr<ID3D12CommandAllocator> m_pCmdAllocator[SwapChainBufferCount];
		ComPtr<ID3D12CommandQueue> pCmdQueue;
		ComPtr<ID3D12DescriptorHeap> m_pRtvHeap;
		ComPtr<ID3D12DescriptorHeap> m_pDsvHeap;
		ComPtr<ID3D12GraphicsCommandList> m_pCmdList;
		ComPtr<ID3D12Fence> m_pFence;
		HANDLE m_FenceEvent;
		UINT64 m_FenceValue;
		UINT m_FrameIndex;
		UINT m_RtvDescriptorSize;
		UINT m_DsvDescriptorSize;
	};
};