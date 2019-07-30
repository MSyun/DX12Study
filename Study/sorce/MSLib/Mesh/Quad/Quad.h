#pragma once

#include <d3d12.h>
#include <wrl.h>

using namespace Microsoft::WRL;

#include "../../Math/Math.h"
#pragma comment(lib, "d3d12.lib")
#include "../../Transform/Transform.h"


namespace MSLib {
	namespace Mesh {
		struct ResConstantBuffer {
			Math::Matrix World;
			Math::Matrix View;
			Math::Matrix Proj;
		};


		class Quad {
		public:
			Quad();
			virtual ~Quad();

			void Initialize(ComPtr<ID3D12Device> pDevice);
			void Render(ComPtr<ID3D12GraphicsCommandList>& pCmdList);
			void Release();
			void Pre(ComPtr<ID3D12GraphicsCommandList>& pCmdList);

			Transform* GetTransform() { return &transform; }
		private:
			ComPtr<ID3D12RootSignature> m_signature;
			ComPtr<ID3D12PipelineState> m_pPipelineState;
			ComPtr<ID3D12Resource> m_pVertexBuffer;
			D3D12_VERTEX_BUFFER_VIEW m_VertexBufferView;
			ComPtr<ID3D12DescriptorHeap> m_pCbvHeap;
			ComPtr<ID3D12Resource> m_pConstantBuffer;
			ResConstantBuffer m_ConstantBufferData;
			UINT8* m_pCbvDataBegin;

			Transform transform;
		};
	}
}