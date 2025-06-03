#include "ComputeShader.h"

#include <iostream>
#include <string>

#include "ColdTable/Graphics/GraphicsDevice.h"

ColdTable::ComputeShader::ComputeShader(const ComputeShaderDesc& desc) : Base({}), _context(desc.context)
{
    // Verify compute shader is supported
    if (desc.sourceDevice->_d3dDevice->GetFeatureLevel() < D3D_FEATURE_LEVEL_11_0)
    {
        D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS hwopts = { 0 };
        (void)desc.sourceDevice->_d3dDevice->CheckFeatureSupport(D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS, &hwopts, sizeof(hwopts));
        if (!hwopts.ComputeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x)
        {
            printf("DirectCompute is not supported by this device\n");
            return;
        }
    }

    // Compile shader
    ID3DBlob* csBlob = nullptr;
    ColdTableGraphicsLogThrowOnFail(CompileComputeShader(desc.sourceFile, "CSMain", desc.sourceDevice->_d3dDevice, &csBlob),
        "Failed compiling compute shader");

    // Create shader
    ColdTableGraphicsLogThrowOnFail(desc.sourceDevice->_d3dDevice->CreateComputeShader(csBlob->GetBufferPointer(), csBlob->GetBufferSize(), nullptr, &_computeShader),
        "Failed to create compute shader");

    csBlob->Release();

    // Create input buffer
    inputBuffer = nullptr;

    D3D11_BUFFER_DESC bufferDesc{};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(float) * 36;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;

    D3D11_SUBRESOURCE_DATA initData{};
    initData.pSysMem = desc.inputArray;

    // Create resource view for input
    bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    ColdTableGraphicsLogThrowOnFail(desc.sourceDevice->_d3dDevice->CreateBuffer(&bufferDesc, &initData, &inputBuffer),
        "CreateBuffer failed.");

    D3D11_SHADER_RESOURCE_VIEW_DESC resViewDesc{};
    resViewDesc.Format = DXGI_FORMAT_R32_TYPELESS;
    resViewDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
    resViewDesc.BufferEx.FirstElement = 0;
    resViewDesc.BufferEx.NumElements = bufferDesc.ByteWidth / 4;
    resViewDesc.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;

	ColdTableGraphicsLogThrowOnFail(
        desc.sourceDevice->_d3dDevice->CreateShaderResourceView(inputBuffer, &resViewDesc, &resourceView),
        "Create resource view fail");

    _context->UpdateSubresource(inputBuffer, NULL, NULL, desc.inputArray, NULL, NULL);

    // Create unordered access view for output
	bufferDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
    ColdTableGraphicsLogThrowOnFail(
        desc.sourceDevice->_d3dDevice->CreateBuffer(&bufferDesc, &initData, &outputBuffer),
        "CreateBuffer failed.");

    D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc{};
    uavDesc.Format = DXGI_FORMAT_R32_TYPELESS;
    uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    uavDesc.Buffer.FirstElement = 0;
    uavDesc.Buffer.NumElements = bufferDesc.ByteWidth / 4;
    uavDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;

    ColdTableGraphicsLogThrowOnFail(
        desc.sourceDevice->_d3dDevice->CreateUnorderedAccessView(outputBuffer, &uavDesc, &unorderedAccessView),
        "Create unordered access view fail.");

    // Create staging buffer
    D3D11_BUFFER_DESC stagingDesc{};
    stagingDesc.Usage = D3D11_USAGE_STAGING;
    stagingDesc.ByteWidth = sizeof(float) * 36;
    stagingDesc.BindFlags = 0;
    stagingDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    stagingDesc.MiscFlags = 0;

    _stagingBuffer = nullptr;
    ColdTableGraphicsLogThrowOnFail(
        desc.sourceDevice->_d3dDevice->CreateBuffer(&stagingDesc, nullptr, &_stagingBuffer), 
        "Create staging buffer fail.");
}

ColdTable::ComputeShader::~ComputeShader()
{
    // Clean up
    if (_computeShader)
		_computeShader->Release();

    if (unorderedAccessView)
        unorderedAccessView->Release();
}

float* ColdTable::ComputeShader::ReadBuffer()
{
    _context->CopyResource(_stagingBuffer, outputBuffer);
    _context->Flush();

    D3D11_MAPPED_SUBRESOURCE mappedResource{};
    HRESULT hr = _context->Map(_stagingBuffer, 0, D3D11_MAP_READ, 0, &mappedResource);

    float* array = new float[36];
	if (SUCCEEDED(hr))
    {
        float* data = reinterpret_cast<float*>(mappedResource.pData);
        for (UINT i = 0; i < 36; ++i)
        {
            array[i] = data[i];
        }
        _context->Unmap(_stagingBuffer, 0);  
    } else
    {
        char* errorMsg = nullptr;
        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            hr,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR)&errorMsg,
            0,
            nullptr);

        std::string message = errorMsg ? errorMsg : "Unknown error";
        if (errorMsg)
            LocalFree(errorMsg);

        std::cout << message << std::endl;
    }

    return array;

}

HRESULT ColdTable::ComputeShader::CompileComputeShader(_In_ LPCWSTR srcFile, _In_ LPCSTR entryPoint,
                                                       _In_ Microsoft::WRL::ComPtr<ID3D11Device> device, _Outptr_ ID3DBlob** blob)
{
    if (!srcFile || !entryPoint || !device || !blob)
        return E_INVALIDARG;

    *blob = nullptr;

    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    flags |= D3DCOMPILE_DEBUG;
#endif

    // We generally prefer to use the higher CS shader profile when possible as CS 5.0 is better performance on 11-class hardware
    LPCSTR profile = (device->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "cs_5_0" : "cs_4_0";

    const D3D_SHADER_MACRO defines[] =
    {
        "EXAMPLE_DEFINE", "1",
        NULL, NULL
    };

    ID3DBlob* shaderBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;
    HRESULT hr = D3DCompileFromFile(srcFile, nullptr, nullptr,
        entryPoint, profile,
        NULL, NULL, &shaderBlob, &errorBlob);
    ColdTableGraphicsLogThrowOnFail(hr, (char*)errorBlob->GetBufferPointer());
    /*if (FAILED(hr))
    {
        if (errorBlob)
        {
            OutputDebugStringA((char*)errorBlob->GetBufferPointer());
            errorBlob->Release();
        }

        if (shaderBlob)
            shaderBlob->Release();

        return hr;
    }*/

    *blob = shaderBlob;

    return hr;
}
