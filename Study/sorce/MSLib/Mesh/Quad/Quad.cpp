#include "Quad.h"
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#include <tchar.h> // Debug������p
#include "../../Screen/Screen.h"
#include "../../Camera/CameraManager.h"

namespace MSLib {
	namespace Mesh {
		struct Vertex {
			Math::float3 Position;
			Math::float3 Normal;
			Math::float2 TexCoord;
			Math::float4 Color;
		};


		Quad::Quad() {

		}

		Quad::~Quad() {

		}

		void Quad::Initialize(ComPtr<ID3D12Device> pDevice) {
			// Signature
			{
				HRESULT hr;
				// �f�B�X�N���v�^�����W�̐ݒ�
				D3D12_DESCRIPTOR_RANGE range;
				range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
				range.NumDescriptors = 1;
				range.BaseShaderRegister = 0;
				range.RegisterSpace = 0;
				range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

				// ���[�g�p�����[�^�̐ݒ�
				D3D12_ROOT_PARAMETER root_parameters;
				root_parameters.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
				root_parameters.ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
				root_parameters.DescriptorTable.NumDescriptorRanges = 1;
				root_parameters.DescriptorTable.pDescriptorRanges = &range;

				// ���[�g�V�O�j�`���̐ݒ�
				D3D12_ROOT_SIGNATURE_DESC root_signature_desc{};
				root_signature_desc.NumParameters = 1;
				root_signature_desc.pParameters = &root_parameters;
				root_signature_desc.NumStaticSamplers = 0;
				root_signature_desc.pStaticSamplers = nullptr;
				root_signature_desc.Flags =
					D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
					D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
					D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
					D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
					D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

				ComPtr<ID3DBlob> pSignature;
				ComPtr<ID3DBlob> pError;

				hr = D3D12SerializeRootSignature(
					&root_signature_desc,
					D3D_ROOT_SIGNATURE_VERSION_1,
					pSignature.GetAddressOf(),
					pError.GetAddressOf());
				if (FAILED(hr)) {
					OutputDebugString(_T("Failed : D3D12SerializeRootSignature"));
					return;
				}
				hr = pDevice->CreateRootSignature(
					0,
					pSignature->GetBufferPointer(),
					pSignature->GetBufferSize(),
					IID_PPV_ARGS(m_signature.GetAddressOf()));
				if (FAILED(hr)) {
					OutputDebugString(_T("Failed : CreateRootSignature"));
					return;
				}
			}

			// PipelineStateObject
			{
				HRESULT hr;
				ComPtr<ID3DBlob> pVSBlob;
				ComPtr<ID3DBlob> pPSBlob;
				ComPtr<ID3DBlob> pError;

#if defined(_DEBUG)
				UINT compile_flag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
				UINT compile_flag = 0;
#endif

				// �R���p�C���ςݒ��_�V�F�[�_��ǂݍ���
				//hr = D3DReadFileToBlob(_T("shader/VS"), pVSBlob.GetAddressOf());
				hr = D3DCompileFromFile(
					_T("sorce/MSLib/Shader/SimpleVS.hlsl"),
					nullptr,
					nullptr,
					"VSFunc",
					"vs_5_0",
					compile_flag,
					0,
					pVSBlob.GetAddressOf(),
					pError.GetAddressOf());
				if (FAILED(hr)) {
					OutputDebugString((LPCTSTR)pError->GetBufferPointer());
					return;
				}

				// �R���p�C���ς݃s�N�Z���V�F�[�_��ǂݍ���
				//hr = D3DReadFileToBlob(_T("shader/PS"), pPSBlob.GetAddressOf());
				hr = D3DCompileFromFile(_T("sorce/MSLib/Shader/SimplePS.hlsl"),
					nullptr,
					nullptr,
					"PSFunc",
					"ps_5_0",
					compile_flag,
					0,
					pPSBlob.GetAddressOf(),
					pError.GetAddressOf());
				if (FAILED(hr)) {
					OutputDebugString(_T("Failed : D3DReadFileToBlob"));
					return;
				}

				// ���̓��C�A�E�g�̐ݒ�
				D3D12_INPUT_ELEMENT_DESC inputElements[] = {
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
					{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
					{ "VTX_COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
				};

				// ���X�^���C�U�[�X�e�[�g�̐ݒ�
				D3D12_RASTERIZER_DESC descRS;
				descRS.FillMode = D3D12_FILL_MODE_SOLID;
				descRS.CullMode = D3D12_CULL_MODE_NONE;
				descRS.FrontCounterClockwise = FALSE;
				descRS.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
				descRS.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
				descRS.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
				descRS.DepthClipEnable = TRUE;
				descRS.MultisampleEnable = FALSE;
				descRS.AntialiasedLineEnable = FALSE;
				descRS.ForcedSampleCount = 0;
				descRS.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

				// �����_�[�^�[�Q�b�g�̃u�����h�ݒ�
				D3D12_RENDER_TARGET_BLEND_DESC descRTBS = {
					FALSE,
					FALSE,
					D3D12_BLEND_ONE,
					D3D12_BLEND_ZERO,
					D3D12_BLEND_OP_ADD,
					D3D12_BLEND_ONE,
					D3D12_BLEND_ZERO,
					D3D12_BLEND_OP_ADD,
					D3D12_LOGIC_OP_NOOP,
					D3D12_COLOR_WRITE_ENABLE_ALL
				};

				// �u�����h�X�e�[�g�̐ݒ�
				D3D12_BLEND_DESC descBS;
				descBS.AlphaToCoverageEnable = FALSE;
				descBS.IndependentBlendEnable = FALSE;
				for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) {
					descBS.RenderTarget[i] = descRTBS;
				}

				// �p�C�v���C���X�e�[�g�̐ݒ�
				D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
				desc.InputLayout.pInputElementDescs = inputElements;
				desc.InputLayout.NumElements = _countof(inputElements);
				desc.pRootSignature = m_signature.Get();
				desc.VS.pShaderBytecode = reinterpret_cast<UINT8*>(pVSBlob->GetBufferPointer());
				desc.VS.BytecodeLength = pVSBlob->GetBufferSize();
				desc.PS.pShaderBytecode = reinterpret_cast<UINT8*>(pPSBlob->GetBufferPointer());
				desc.PS.BytecodeLength = pPSBlob->GetBufferSize();
				desc.RasterizerState = descRS;
				desc.BlendState = descBS;
				desc.DepthStencilState.DepthEnable = FALSE;
				desc.DepthStencilState.StencilEnable = FALSE;
				desc.SampleMask = UINT_MAX;
				desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
				desc.NumRenderTargets = 1;
				desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
				desc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
				desc.SampleDesc.Count = 1;
				desc.SampleDesc.Quality = 0;

				// �p�C�v���C���X�e�[�g�𐶐�
				hr = pDevice->CreateGraphicsPipelineState(&desc, IID_PPV_ARGS(m_pPipelineState.GetAddressOf()));
				if (FAILED(hr)) {
					OutputDebugString(_T("Failed : CreateGraphicsPipelineState"));
					return;
				}
			}

			// ���_�o�b�t�@�̐���
			{
				// ���_�f�[�^
				Vertex vertices[] = {
					{{ 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
					{{ 1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
					{{ -1.0f, -1.0f, 0.0f }, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
				};

				// �q�[�v�v���p�e�B
				D3D12_HEAP_PROPERTIES prop;
				prop.Type = D3D12_HEAP_TYPE_UPLOAD;
				prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
				prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
				prop.CreationNodeMask = 1;
				prop.VisibleNodeMask = 1;

				// ���\�[�X�̐ݒ�
				D3D12_RESOURCE_DESC desc;
				desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
				desc.Alignment = 0;
				desc.Width = sizeof(vertices);
				desc.Height = 1;
				desc.DepthOrArraySize = 1;
				desc.MipLevels = 1;
				desc.Format = DXGI_FORMAT_UNKNOWN;
				desc.SampleDesc.Count = 1;
				desc.SampleDesc.Quality = 0;
				desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
				desc.Flags = D3D12_RESOURCE_FLAG_NONE;

				// ���\�[�X�𐶐�
				HRESULT hr = pDevice->CreateCommittedResource(
					&prop,
					D3D12_HEAP_FLAG_NONE,
					&desc,
					D3D12_RESOURCE_STATE_GENERIC_READ,
					nullptr,
					IID_PPV_ARGS(m_pVertexBuffer.GetAddressOf()));
				if (FAILED(hr)) {
					OutputDebugString(_T("Failed : CreateCommittedResource"));
					return;
				}

				// �}�b�v����
				UINT8* pData;
				hr = m_pVertexBuffer->Map(0, nullptr, reinterpret_cast<void**>(&pData));
				if (FAILED(hr)) {
					OutputDebugString(_T("Failed : Map"));
					return;
				}

				// ���_�f�[�^���R�s�[
				memcpy(pData, vertices, sizeof(vertices));

				// �A���}�b�v����
				m_pVertexBuffer->Unmap(0, nullptr);

				// ���_�o�b�t�@�r���[�̐ݒ�
				m_VertexBufferView.BufferLocation = m_pVertexBuffer->GetGPUVirtualAddress();
				m_VertexBufferView.StrideInBytes = sizeof(Vertex);
				m_VertexBufferView.SizeInBytes = sizeof(vertices);
			}

			// �萔�o�b�t�@�p�f�B�X�N���v�^�q�[�v�𐶐�
			{
				D3D12_DESCRIPTOR_HEAP_DESC desc = {};
				desc.NumDescriptors = 1;
				desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
				desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

				HRESULT hr = pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(m_pCbvHeap.GetAddressOf()));
				if (FAILED(hr)) {
					OutputDebugString(_T("Failed : CreateDescriptorHeap"));
					return;
				}
			}

			// �萔�o�b�t�@�𐶐�
			{
				// �q�[�v�v���p�e�B�̐ݒ�
				D3D12_HEAP_PROPERTIES prop = {};
				prop.Type = D3D12_HEAP_TYPE_UPLOAD;
				prop.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
				prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
				prop.CreationNodeMask = 1;
				prop.VisibleNodeMask = 1;

				// ���\�[�X�̐ݒ�
				D3D12_RESOURCE_DESC desc = {};
				desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
				desc.Alignment = 0;
				desc.Width = (sizeof(ResConstantBuffer) + 255) & ~255;
				desc.Height = 1;
				desc.DepthOrArraySize = 1;
				desc.MipLevels = 1;
				desc.Format = DXGI_FORMAT_UNKNOWN;
				desc.SampleDesc.Count = 1;
				desc.SampleDesc.Quality = 0;
				desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
				desc.Flags = D3D12_RESOURCE_FLAG_NONE;

				// ���\�[�X�𐶐�
				HRESULT hr = pDevice->CreateCommittedResource(
					&prop,
					D3D12_HEAP_FLAG_NONE,
					&desc,
					D3D12_RESOURCE_STATE_GENERIC_READ,
					nullptr,
					IID_PPV_ARGS(m_pConstantBuffer.GetAddressOf()));
				if (FAILED(hr)) {
					OutputDebugString(_T("Failed : CreateCommittedResource"));
					return;
				}

				// �萔�o�b�t�@�r���[�̐ݒ�
				D3D12_CONSTANT_BUFFER_VIEW_DESC bufferDesc = {};
				bufferDesc.BufferLocation = m_pConstantBuffer->GetGPUVirtualAddress();
				bufferDesc.SizeInBytes = (sizeof(ResConstantBuffer) + 255) & ~255;

				// �萔�o�b�t�@�r���[�𐶐�
				pDevice->CreateConstantBufferView(&bufferDesc, m_pCbvHeap->GetCPUDescriptorHandleForHeapStart());

				// �}�b�v����B�A�v���I���܂�Unmap���Ȃ�
				// "Keeping things mapped for the lifetime of the resource is okay." �Ƃ̂��ƁB
				hr = m_pConstantBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_pCbvDataBegin));
				if (FAILED(hr)) {
					OutputDebugString(_T("Failed : Map"));
					return;
				}
			}
		}

		void Quad::Pre(ComPtr<ID3D12GraphicsCommandList>& pCmdList) {
			// �萔�o�b�t�@�f�[�^�̐ݒ�
			transform.SetPos(0.0f, 0.0f, 5.0f);
			transform.Rotate(0.0f, 4.0f, 0.0f);
			m_ConstantBufferData.World = transform.GetWorld();
			m_ConstantBufferData.View = GetCameraManager()->Get("mainCamera")->GetView();
			m_ConstantBufferData.Proj = GetCameraManager()->Get("mainCamera")->GetProjection();
			// �R�s��
			memcpy(m_pCbvDataBegin, &m_ConstantBufferData, sizeof(m_ConstantBufferData));

			pCmdList->SetPipelineState(m_pPipelineState.Get());
			pCmdList->SetDescriptorHeaps(1, m_pCbvHeap.GetAddressOf());
			pCmdList->SetGraphicsRootSignature(m_signature.Get());
			pCmdList->SetGraphicsRootDescriptorTable(0, m_pCbvHeap->GetGPUDescriptorHandleForHeapStart());
		}

		void Quad::Render(ComPtr<ID3D12GraphicsCommandList>& pCmdList) {
			// �v���~�e�B�u�g�|���W�[�̐ݒ�
			pCmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// ���_�o�b�t�@�r���[��ݒ�
			pCmdList->IASetVertexBuffers(0, 1, &m_VertexBufferView);

			// �`��R�}���h�𐶐�
			pCmdList->DrawInstanced(3, 1, 0, 0);
		}

		void Quad::Release() {
			m_pConstantBuffer->Unmap(0, nullptr);
			m_pConstantBuffer.Reset();
			m_pCbvHeap.Reset();
			m_pVertexBuffer.Reset();
			m_VertexBufferView.BufferLocation = 0;
			m_VertexBufferView.SizeInBytes = 0;
			m_VertexBufferView.StrideInBytes = 0;
			m_pPipelineState.Reset();
			m_signature.Reset();
		}
	}
}