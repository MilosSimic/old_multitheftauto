/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*               (Shared logic for modifications)
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        core/CWebView.h
*  PURPOSE:     Web view class
*
*****************************************************************************/

#ifndef __CWEBVIEW_H
#define __CWEBVIEW_H

#undef GetNextSibling
#include <core/CWebViewInterface.h>
#include <core/CWebBrowserEventsInterface.h>
#include <cef3/include/cef_app.h>
#include <cef3/include/cef_browser.h>
#include <cef3/include/cef_client.h>
#include <cef3/include/cef_render_handler.h>
#include <d3d9.h>
#include <SString.h>
#include <mmdeviceapi.h>
#include <audiopolicy.h>
#define GetNextSibling(hwnd) GetWindow(hwnd, GW_HWNDNEXT) // Re-define the conflicting macro

class CWebView : public CWebViewInterface, private CefClient, private CefRenderHandler, private CefLoadHandler, private CefRequestHandler
{
public:
    CWebView                    ( unsigned int uiWidth, unsigned int uiHeight, bool bIsLocal, CWebBrowserItem* pWebBrowserRenderItem, bool bTransparent = false );
    ~CWebView                   ();
    //Awesomium::WebView*         GetAwesomiumView () { return m_pWebView; };
    void                        SetWebBrowserEvents ( CWebBrowserEventsInterface* pInterface ) { m_pEventsInterface = pInterface; };

    // Exported methods
    bool LoadURL                ( const SString& strURL, bool bFilterEnabled = true );
    bool IsLoading              ();
    void GetURL                 ( SString& outURL );
    void GetTitle               ( SString& outTitle );
    void SetRenderingPaused     ( bool bPaused );
    void Focus                  ();
    void ClearTexture           ();

    void ExecuteJavascript      ( const SString& strJavascriptCode );

    void InjectMouseMove        ( int iPosX, int iPosY );
    void InjectMouseDown        ( eWebBrowserMouseButton mouseButton );
    void InjectMouseUp          ( eWebBrowserMouseButton mouseButton );
    void InjectMouseWheel       ( int iScrollVert, int iScrollHorz );
    void InjectKeyboardEvent    ( const CefKeyEvent& keyEvent );

    bool IsLocal                ()                                                  { return m_bIsLocal; };
    void SetTempURL             ( const SString& strTempURL )                       { m_strTempURL = strTempURL; };

    bool SetAudioVolume         ( float fVolume );


    // CefClient methods
    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override { return this; };
    virtual CefRefPtr<CefLoadHandler>   GetLoadHandler() override { return this; };
    virtual CefRefPtr<CefRequestHandler>GetRequestHandler() override { return this; };
    
    // CefRenderHandler methods
    virtual bool GetViewRect    ( CefRefPtr<CefBrowser> browser, CefRect& rect ) override;
    virtual void OnPaint        ( CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType paintType, const CefRenderHandler::RectList& dirtyRects, const void* buffer, int width, int height ) override;
    virtual void OnCursorChange ( CefRefPtr<CefBrowser> browser, CefCursorHandle cursor ) override;

    // CefLoadHandler methods
    virtual void OnLoadStart    ( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame ) override;
    virtual void OnLoadEnd      ( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode ) override;
    virtual void OnLoadError    ( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefLoadHandler::ErrorCode errorCode, const CefString& errorText, const CefString& failedURL ) override;
    
    // CefRequestHandler implementation
    virtual bool OnBeforeBrowse( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool isRedirect ) override;
    virtual bool OnBeforeResourceLoad ( CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request ) override;

    // Static javascript method implementations
    //static void Javascript_triggerEvent(Awesomium::WebView* pWebView, const Awesomium::JSArray& args);

protected:
    void ConvertURL ( const CefString& url, SString& convertedURL );
    
private:
    CefRefPtr<CefBrowser> m_pWebView;
    CWebBrowserItem*    m_pWebBrowserRenderItem;

    bool                m_bIsLocal;
    SString             m_strTempURL;
    POINT               m_vecMousePosition;

    //CJSMethodHandler    m_JSMethodHandler;
    CWebBrowserEventsInterface* m_pEventsInterface;

public:
    // Implement smartpointer methods (all Cef-classes require that since they are derived from CefBase)
    IMPLEMENT_REFCOUNTING(CWebView);
};

#endif
