

#ifndef VISUAL_DEBUG_HPP
#define VISUAL_DEBUG_HPP
#pragma  once 
#include <vector>
#include <assert.h>
#include "d3d11sdklayers.h"
#include <dxgidebug.h>

#if defined(_DEBUG) || defined(PROFILE)
#define SETDBGNAME_COM(pObj) (SetDebugObjectName(pObj.Get(), #pObj))
#define SETDBGNAME(pObj) (SetDebugObjectName(pObj, #pObj))
#else
#define SETDBGNAME_COM(pObj)
#define SETDBGNAME(pObj)
#endif

#if !defined(H_FAIL)
#define H_FAIL(hr) (hr != S_OK)
#endif

class DebugInterface
{
public:
#if defined(_DEBUG) || defined(PROFILE)
    DebugInterface()
        : m_hDxgiDebugDLL{::LoadLibraryExW(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32)} {};
    HRESULT Init(  ID3D11Device *pDevice) // Device is initialized at this point
    {
        if (pDevice == nullptr)
            return ERROR_NOINTERFACE;

        HRESULT hr{};
        m_pDevice = pDevice;

        // function pointer typedef of to retrieve debugging interface from dll
        typedef HRESULT(__stdcall * DXGIGetDebugInterface)(REFIID, void **);

        assert( m_hDxgiDebugDLL);

        // populate function pointers
        const auto pDXGIGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
            reinterpret_cast<void *>(::GetProcAddress(m_hDxgiDebugDLL, "DXGIGetDebugInterface")));

        if (H_FAIL(hr = pDXGIGetDebugInterface(__uuidof(IDXGIDebug), (VOID **)&m_pDebug)))
            return hr;

        if (H_FAIL(hr = pDXGIGetDebugInterface(__uuidof(IDXGIInfoQueue), (VOID **)&m_pGIInfoQueue)))
            return hr;

        if (H_FAIL(hr = pDevice->QueryInterface(__uuidof(ID3D11Debug), (VOID **)&m_pSDKLayerDebug)))
            return hr;
        if (H_FAIL(hr = pDevice->QueryInterface(__uuidof(ID3D11InfoQueue), (VOID **)&m_pInfoQueue)))
            return hr;
 
        DXGI_INFO_QUEUE_MESSAGE_ID InitialDenyList[]{294, 3146080};

        for (auto &each : InitialDenyList)
            PushDeniedMessage(each);

        return S_OK;
    };

    template <typename IDXObject, UINT TNameLength>
    inline static void SetDebugObjectName(IDXObject *pObject, const char (&name)[TNameLength])
    {
        static_assert(std::is_convertible_v<IDXObject *, ID3D11DeviceChild *> ||
                          std::is_convertible_v<IDXObject *, IDXGIObject *>,
                      "neither pObject or any of its bases is a DirectX interface");

        if (pObject)
        {
            pObject->SetPrivateData(WKPDID_D3DDebugObjectName, sizeof(name) - 1, name);
        }
    };

    void PushDeniedMessage(DXGI_INFO_QUEUE_MESSAGE_ID &ID)
    {
        HRESULT hr{};
        static DXGI_INFO_QUEUE_FILTER filter{};
        filter.DenyList.NumIDs = 1;
        filter.DenyList.pIDList = &ID;
        H_FAIL(hr = m_pGIInfoQueue->AddStorageFilterEntries(DXGI_DEBUG_ALL, &filter));
    };

    void PullDebugMessage()
    {
        static std::vector<char> pMessageBuffer(1024, '\0');
        while (m_MessagePointer < m_pGIInfoQueue->GetNumStoredMessagesAllowedByRetrievalFilters(DXGI_DEBUG_ALL))
        {

            unsigned long long messageLength{};
            m_pGIInfoQueue->GetMessage(DXGI_DEBUG_ALL, m_MessagePointer, NULL, &messageLength);
            pMessageBuffer.reserve(messageLength);

            DXGI_INFO_QUEUE_MESSAGE *pMessage{reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE *>(pMessageBuffer.data())};
            m_pGIInfoQueue->GetMessage(DXGI_DEBUG_ALL, m_MessagePointer, pMessage, &messageLength);
            m_MessagePointer++;

            std::cout << pMessage->pDescription << '\n';

            PushDeniedMessage(pMessage->ID);
        };
    };

    void Report()
    {
        m_pSDKLayerDebug->ReportLiveDeviceObjects(D3D11_RLDO_SUMMARY | D3D11_RLDO_DETAIL);
        m_pDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
    };

    virtual ~DebugInterface()
    {

        if (m_pGIInfoQueue != nullptr && m_pDevice != nullptr)
            PullDebugMessage();

        Report();

        if (m_hDxgiDebugDLL)
            ::FreeLibrary(m_hDxgiDebugDLL);
    };

private:
    const ID3D11Device *m_pDevice{};
    ID3D11Debug *m_pSDKLayerDebug{};
    IDXGIDebug *m_pDebug{};
    IDXGIInfoQueue *m_pGIInfoQueue{};
    ID3D11InfoQueue *m_pInfoQueue{};
    UINT64 m_MessagePointer{};
    HMODULE m_hDxgiDebugDLL{nullptr};

#endif
};

#endif