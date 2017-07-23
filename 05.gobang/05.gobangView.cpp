
// 05.gobangView.cpp : CMy05gobangView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "05.gobang.h"
#endif

#include "05.gobangDoc.h"
#include "05.gobangView.h"
#include<math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy05gobangView

IMPLEMENT_DYNCREATE(CMy05gobangView, CView)

BEGIN_MESSAGE_MAP(CMy05gobangView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy05gobangView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_EDIT_UNDO, &CMy05gobangView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CMy05gobangView::OnUpdateEditUndo)
	ON_COMMAND(ID_OPTION_OPTION, &CMy05gobangView::OnOptionGreen)
	ON_UPDATE_COMMAND_UI(ID_OPTION_OPTION, &CMy05gobangView::OnUpdateOptionGreen)
	ON_COMMAND(ID_OPTION_BLUE, &CMy05gobangView::OnOptionBlue)
	ON_UPDATE_COMMAND_UI(ID_OPTION_BLUE, &CMy05gobangView::OnUpdateOptionBlue)
	ON_COMMAND(ID_OPTION_YELLOW, &CMy05gobangView::OnOptionYellow)
	ON_UPDATE_COMMAND_UI(ID_OPTION_YELLOW, &CMy05gobangView::OnUpdateOptionYellow)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_SCRL, &CMy05gobangView::OnUpdateTip)
	ON_COMMAND(ID_FILE_NEW1, &CMy05gobangView::OnFileNew)
END_MESSAGE_MAP()

//用于保存棋盘上的点的状态
	int CMy05gobangView::ellipse[15][15] =
							{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	bool CMy05gobangView::isEditUndoClick = false;
	bool CMy05gobangView::isSaveGameClick = false;
	int CMy05gobangView::mColor = 0;
	int CMy05gobangView::GREEN = 0;
	int CMy05gobangView::BLUE = 1;
	int CMy05gobangView::YELLOW = 2;
	int CMy05gobangView::i = 0;
	int CMy05gobangView::m1 = 0;
	int CMy05gobangView::m2 = 0;
	int CMy05gobangView::n1 = 0;
	int CMy05gobangView::n2 = 0;

// CMy05gobangView 构造/析构

bool bWin = false;
bool wWin = false;

CMy05gobangView::CMy05gobangView()
{
	// TODO: 在此处添加构造代码
}

CMy05gobangView::~CMy05gobangView()
{
}

BOOL CMy05gobangView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMy05gobangView 绘制

void CMy05gobangView::OnDraw(CDC* /*pDC*/)
{
	CMy05gobangDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMy05gobangView 打印


void CMy05gobangView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy05gobangView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMy05gobangView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMy05gobangView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CMy05gobangView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy05gobangView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy05gobangView 诊断

#ifdef _DEBUG
void CMy05gobangView::AssertValid() const
{
	CView::AssertValid();
}

void CMy05gobangView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy05gobangDoc* CMy05gobangView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy05gobangDoc)));
	return (CMy05gobangDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy05gobangView 消息处理程序


void CMy05gobangView::OnPaint()
{
	// 不要为绘制消息而调用 CWnd::OnPaint()
	 SetWindowPos(NULL,0,0,660,630,SWP_NOMOVE);
	 CPaintDC dc(this); // 用于绘制的设备上下文
	 CRect   rect;  
	 GetClientRect(rect);  
	 switch(mColor)
	{
		case 0:
			{
				  dc.FillSolidRect(rect,RGB(0,255,0));
			}
			 break;
		 case 1:
			 {
				  dc.FillSolidRect(rect,RGB(0,0,255));
			 }
			 break;
		 case 2:
			 {
				   dc.FillSolidRect(rect,RGB(255,255,0));
			 }
			 break;
		 default:
			 break;
	} 
	 CClientDC cdc(this);
	 for(int i = 40;i <= 600;i = i + 40)
	 {
		cdc.MoveTo(40,i);
		cdc.LineTo(600,i);
		cdc.MoveTo(i,40);
	    cdc.LineTo(i,600);
	 }
	 CDC *pDC;
	 pDC = GetDC();
	 CBrush brush;
	 brush.CreateSolidBrush(RGB(0,0,0));
	 CBrush *pOldBrush;
	 CBrush brush2;
	 brush2.CreateSolidBrush(RGB(255,255,255));
	 CBrush *pOldBrush2;
	 for(int j =0;j < 15;j++)
	 {
		for(int m = 0;m <15 ;m++)
		{
			if(ellipse[j][m] == 1)
			{
				pOldBrush = pDC->SelectObject(&brush);
				pDC->Ellipse(j*40-15,m*40-15,j*40+15,m*40+15);
				pDC->SelectObject(pOldBrush);
			}else if(ellipse[j][m] == -1){
				pOldBrush2 = pDC->SelectObject(&brush2);
				pDC->Ellipse(j*40-15,m*40-15,j*40+15,m*40+15);
				pDC->SelectObject(pOldBrush2);
			}
		}
	 }
}

void CMy05gobangView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	while(bWin)
	{
		::MessageBox(NULL,_T("Black Win!"),_T("Game Over"),MB_OK);
		return;
	}
	while(wWin)
	{
		::MessageBox(NULL,_T("White Win!"),_T("Game Over"),MB_OK);
		return;
	}
	CDC *pDC;
	pDC = GetDC();
	CBrush brush;
	brush.CreateSolidBrush(RGB(0,0,0));
	CBrush *pOldBrush;
	CBrush brush2;
	brush2.CreateSolidBrush(RGB(255,255,255));
	CBrush *pOldBrush2;
	int _x = point.x - (point.x%40);
	int _y = point.y - (point.y%40);
	if(point.x%40>20)
	{
		_x = _x + 40;
	}
	if(point.y%40>20)
	{
		_y = _y + 40;
	}
	int _m = _x/40;
	int _n = _y/40;
	if(point.x>40 && point.x < 600 &&point.y>40 && point.y<600)
	{

		if(i % 2 == 0&&ellipse[_m][_n]!=1&&ellipse[_m][_n]!=-1)
		{
			pOldBrush2 = pDC->SelectObject(&brush2);
			pDC->Ellipse(_x-15,_y-15,_x+15,_y+15);
			pDC->SelectObject(pOldBrush2);
			ellipse[_m][_n] = -1;
			m2 = _m;
			n2 = _n;
			i++;
		}else if(i % 2 == 1 && ellipse[_m][_n]!=1 && ellipse[_m][_n]!=-1){
			pOldBrush = pDC->SelectObject(&brush);
			pDC->Ellipse(_x-15,_y-15,_x+15,_y+15);
			pDC->SelectObject(pOldBrush);
			ellipse[_m][_n] = 1;
			m1=_m;
			n1 = _n;
			i++;
		}
	}
	if((m1 != 0 && n1 !=0) || (m2 !=0 && n2 != 0))
	{
		isEditUndoClick = false;
		isSaveGameClick = true;
	}
	vertial(_m,_n);
	horizontal(_m,_n);
	left(_m,_n);
	right(_m,_n);
}

void CMy05gobangView::vertial(int x,int y)
{
	int xx,yy;
	if(x < 5)
	{
		xx = 0;
	}else{
		xx = x-5;
	}
	if(y < 5)
	{
		yy = 0;
	}else{
		yy = y-5;
	}
	int i,j,a;
		//竖向判断
	for(i = yy;i<15;i++)
	{
		a = 0;
		for(j = i;j < i+5;j++)
		{
			a = a+ellipse[x][j];		
			if(a >= 5)
			{
				::MessageBox(NULL,_T("Black Win!"),_T("Game Over"),MB_OK);
				bWin = true;
				return;
			}
			if(a <= -5)
			{
				::MessageBox(NULL,_T("White Win!"),_T("Game Over"),MB_OK);
				wWin = true;
				return;
			}				
		}

	}

}
void CMy05gobangView::horizontal(int x,int y)
{
	int xx,yy;
	if(x < 5)
	{
		xx = 0;
	}else{
		xx = x-5;
	}
	if(y < 5)
	{
		yy = 0;
	}else{
		yy = y-5;
	}
	int i,j,a;
	//横向判断
	for(i = xx;i < 15;i++)
	{
		a = 0;
		for(j = i;j<i+5;j++)
		{
			a = a+ellipse[j][y];
			//五个都是黑棋
			if(a >= 5)
			{
				::MessageBox(NULL,_T("Black Win!"),_T("Game Over"),MB_OK);
				bWin = true;
				return;
			}
			//五个都是黑棋
			if(a <= -5)
			{
				::MessageBox(NULL,_T("White Win!"),_T("Game Over"),MB_OK);
				wWin = true;
				return;
			}
		}
	}
}
void CMy05gobangView::left(int x,int y)
{
	int xx,yy;
	if(x < 4)
	{
		xx = 0;
	}else{
		xx = x-4;
	}
	if(y < 4)
	{
		yy = 0;
	}else{
		yy = y-4;
	}
	int i,j,a;
	//向右下角
	//判断起点位置
	if(x < y)
	{
		if(xx == 0)
		{
			yy = y -x;
		}
	}else{
		if( yy == 0)
		{
			xx = x - y;
		}
	}
	int over = 0;
	do{
		a = 0;
		for(i=0;i<5;i++){ 
			if((xx+i)<19||(yy+i)<19)
			{ 
				a=a+ellipse[xx+i][yy+i];
				if(a==5){
					::MessageBox(NULL,_T("Black Win!"),_T("Game Over"),MB_OK);
					bWin = true;
					return;
				}
				if(a==-5){ 
					::MessageBox(NULL,_T("White Win!"),_T("Game Over"),MB_OK);
					wWin = true;
						return;
				}
			}else
			{
				over = 1;
			}
		}
		xx = xx + 1;
		yy = yy + 1;
	}while(over == 0);
}
void CMy05gobangView::right(int x,int y)
{
	int xx,yy;
	if(x < 4)
	{
		xx = 0;
	}else{
		xx = x-4;
	}
	if(y < 4)
	{
		yy = 0;
	}else{
		yy = y-4;
	}
	int i,j,a;
	//向左下角
	if(y > (18-x))
	{
		if(x > 13)
		{
			yy = y -(18-x);
			xx = 18;
		}
		else{
			yy = y-4;
			xx = x + 4;
		}
	}else{
		if(y < 5)
		{
			xx = x + y;
			yy = 0;
		}else{
			yy = y -4;
			xx = x + 4;
		}
	}
	int over = 0;
	do{
		a = 0;
		for(int i = 0;i < 5;i++)
		{
			if((xx-i)>=0||(yy+i)<19)
			{
				a = a+ellipse[xx-i][yy+i];
				if(a==5){
					::MessageBox(NULL,_T("Black Win!"),_T("Game Over"),MB_OK);
					bWin = true;
					return;
				}
				if(a==-5){ 
					::MessageBox(NULL,_T("White Win!"),_T("Game Over"),MB_OK);
					wWin = true;
					return;
				}
			}else{
				over =1;
			}
			
		}
		xx = xx-1;
		yy = yy+1;
	}while(over == 0);
}


void CMy05gobangView::OnEditUndo()
{
	// TODO: 在此添加命令处理程序代码
	ellipse[m1][n1] = 0;
	ellipse[m2][n2] = 0;
	isEditUndoClick = true;
	int sum = 0;
	for(int j =0;j < 15;j++)
	{
		for(int m = 0;m <15 ;m++)
		{
			sum += abs(ellipse[j][m]);
		}
	}
	if(sum == 0)
	{
		i = 0;
	}
	Invalidate();
}

BOOL CMy05gobangView::isChessChange()
{
	if(bWin || wWin || isEditUndoClick)
	{
		return false;
	}
	int sum = 0;
	for(int j =0;j < 15;j++)
	{
		for(int m = 0;m <15 ;m++)
		{
			sum += abs(ellipse[j][m]);
		}
	}
	if(sum == 0)
	{
		return false;
	}
	if((m1 != 0 && n1 !=0) || (m2 !=0 && n2 != 0))
	{
		return true;
	}
	return false;
}

void CMy05gobangView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable(isChessChange());
}

void CMy05gobangView::OnOptionGreen()
{
	// TODO: 在此添加命令处理程序代码
	mColor = GREEN;
	Invalidate(TRUE);
}


void CMy05gobangView::OnUpdateOptionGreen(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI ->SetCheck(mColor == GREEN);
	pCmdUI->Enable(mColor != GREEN);
}


void CMy05gobangView::OnOptionBlue()
{
	// TODO: 在此添加命令处理程序代码
	mColor = BLUE;
	Invalidate(TRUE);
}


void CMy05gobangView::OnUpdateOptionBlue(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI ->SetCheck(mColor == BLUE);
	pCmdUI->Enable(mColor != BLUE);
}


void CMy05gobangView::OnOptionYellow()
{
	// TODO: 在此添加命令处理程序代码
	mColor = YELLOW;
	Invalidate(TRUE);
}


void CMy05gobangView::OnUpdateOptionYellow(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI ->SetCheck(mColor == YELLOW);
	pCmdUI->Enable(mColor != YELLOW);
}

void CMy05gobangView::OnUpdateTip(CCmdUI *pCmdUI)
{
	if(i % 2 == 0)
	{
		pCmdUI->SetText(_T("White"));
	}else if(i % 2 == 1){
		pCmdUI->SetText(_T("Black"));	
	}
}

void CMy05gobangView::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	for(int i = 0;i < 15;i++)
	{
		for(int j = 0;j < 15;j++)
		{
			ellipse[i][j] = 0;
		}
	}
	bWin = false;
	wWin = false;
	i=0;
	Invalidate();
}
