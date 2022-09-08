// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// DigitalEarthView.cpp: CDigitalEarthView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DigitalEarth.h"
#endif

#include "DigitalEarthDoc.h"
#include "DigitalEarthView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDigitalEarthView

IMPLEMENT_DYNCREATE(CDigitalEarthView, CView)

BEGIN_MESSAGE_MAP(CDigitalEarthView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CDigitalEarthView 构造/析构

CDigitalEarthView::CDigitalEarthView() noexcept
{
	mOSG = 0;
	mThreadHandle = 0;

}

CDigitalEarthView::~CDigitalEarthView()
{
}

BOOL CDigitalEarthView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDigitalEarthView 绘图

void CDigitalEarthView::OnDraw(CDC* /*pDC*/)
{
	CDigitalEarthDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CDigitalEarthView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDigitalEarthView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDigitalEarthView 诊断

#ifdef _DEBUG
void CDigitalEarthView::AssertValid() const
{
	CView::AssertValid();
}

void CDigitalEarthView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDigitalEarthDoc* CDigitalEarthView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDigitalEarthDoc)));
	return (CDigitalEarthDoc*)m_pDocument;
}
#endif //_DEBUG


// CDigitalEarthView 消息处理程序


int CDigitalEarthView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	mOSG = new COSGObject(m_hWnd);

	return 0;
}


BOOL CDigitalEarthView::OnEraseBkgnd(CDC* pDC)
{
	if (0 == mOSG)
	{
		return CView::OnEraseBkgnd(pDC);
	}
	else
	{
		return FALSE;
	}

	return CView::OnEraseBkgnd(pDC);
}


void CDigitalEarthView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	mOSG->InitOSG();
	mThreadHandle = (HANDLE)_beginthread(&COSGObject::Render, 0, mOSG);
}
