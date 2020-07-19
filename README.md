# 五子棋游戏
基于C++ MFC实现的的五子棋游戏

## 主要功能
### 1、棋盘棋子绘制
**其盘绘制**
void CMy05gobangView::OnPaint()
{
	// 不要为绘制消息而调用 CWnd::OnPaint()
	 SetWindowPos(NULL,0,0,800,630,SWP_NOMOVE);
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

**棋子绘制**
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
	if(point.x>20 && point.x < 620 &&point.y>20 && point.y<620)
	{

		if(whitefirst && ellipse[_m][_n]==0)
		{
			//白棋绘制
			pOldBrush2 = pDC->SelectObject(&brush2);
			pDC->Ellipse(_x-15,_y-15,_x+15,_y+15);
			pDC->SelectObject(pOldBrush2);
			ellipse[_m][_n] = -1;
			m2 = _m;
			n2 = _n;
			whitefirst = false;
		}else if(!whitefirst && ellipse[_m][_n]==0){
			//黑棋绘制	
			pOldBrush = pDC->SelectObject(&brush);
			pDC->Ellipse(_x-15,_y-15,_x+15,_y+15);
			pDC->SelectObject(pOldBrush);
			ellipse[_m][_n] = 1;
			m1=_m;
			n1 = _n;
			whitefirst = true;
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

### 2、输赢判定
**主要判定垂直、水平、左斜45°、右斜45°是个方向的输赢情况**
void CMy05gobangView::vertial(int x,int y)
{
	
	int top = (y - 4) >= 0 ? (y - 4) : 0;
	int bottom = (y + 4) <= 15 ? (y + 4) : 15;
	for (top; top < bottom - 4; top++) {
		int total = ellipse[x][top] + ellipse[x][top + 1] + 
			ellipse[x][top + 2]+ ellipse[x][top + 3] + ellipse[x][top + 4];
		if (total == 5) {
			::MessageBox(NULL, _T("黑棋获胜!"), _T("游戏结束"), MB_OK);
			bWin = true;
			return;
		}
		else if (total == -5) {
			::MessageBox(NULL, _T("白棋获胜!"), _T("游戏结束"), MB_OK);
			wWin = true;
			return;
		}
	}
}
void CMy05gobangView::horizontal(int x,int y)
{
	int left = (x - 4) >= 0 ? (x - 4) : 0;
	int right = (x + 4) <= 15 ? (x + 4) : 15;
	for (left; left <= right - 4; left++) {
		int total = ellipse[left][y] + ellipse[left + 1][y] +
			ellipse[left + 2][y] + ellipse[left + 3][y] + ellipse[left + 4][y];
		if (total == 5) {
			::MessageBox(NULL, _T("黑棋获胜!"), _T("游戏结束"), MB_OK);
			bWin = true;
			return;
		}
		else if (total == -5) {
			::MessageBox(NULL, _T("白棋获胜!"), _T("游戏结束"), MB_OK);
			wWin = true;
			return;
		}
	}
}
void CMy05gobangView::left(int x,int y)
{
	int top = (y - 4) >= 0 ? (y - 4) : 0;
	int bottom = (y + 4) <= 15 ? (y + 4) : 15;
	int left = (x - 4) >= 0 ? (x - 4) : 0;
	int right = (x + 4) <= 15 ? (x + 4) : 15;
	if (x - left > y - top) {
		left = x - (y - top);
	}
	else {
		top = y - (x - left);
	}

	if (right - x > bottom - y) {
		right = x + bottom - y;
	}
	else {
		bottom = y + right - x;
	}
	for (left;left <= right - 4; left++) {
		int total = ellipse[left][top] + ellipse[left + 1][top + 1] +
			ellipse[left + 2][top + 2] + ellipse[left + 3][top + 3] +
			ellipse[left + 4][top + 4];
		top++;
		if (total == 5) {
			::MessageBox(NULL, _T("黑棋获胜!"), _T("游戏结束"), MB_OK);
			bWin = true;
			return;
		}
		else if (total == -5) {
			::MessageBox(NULL, _T("白棋获胜!"), _T("游戏结束"), MB_OK);
			wWin = true;
			return;
		}
	}
}
void CMy05gobangView::right(int x,int y)
{
	int top = (y - 4) >= 0 ? (y - 4) : 0;
	int bottom = (y + 4) <= 15 ? (y + 4) : 15;
	int left = (x - 4) >= 0 ? (x - 4) : 0;
	int right = (x + 4) <= 15 ? (x + 4) : 15;
	if (x - left > y - top) {
		left = x - (y - top);
	}
	else {
		top = y - (x - left);
	}

	if (right - x > bottom - y) {
		right = x + bottom - y;
	}
	else {
		bottom = y + right - x;
	}
	for (left;left < right - 4; left++) {
		int total = ellipse[left][bottom] + ellipse[left + 1][bottom - 1] +
			ellipse[left + 2][bottom - 2] + ellipse[left + 3][bottom - 3] +
			ellipse[left + 4][bottom - 4];
		bottom--;
		if (total == 5) {
			::MessageBox(NULL, _T("黑棋获胜!"), _T("游戏结束"), MB_OK);
			bWin = true;
			return;
		}
		else if (total == -5) {
			::MessageBox(NULL, _T("白棋获胜!"), _T("游戏结束"), MB_OK);
			wWin = true;
			return;
		}
	}
}


### 3、开始新游戏
//新游戏
void CMy05gobangView::OnNewGameBtn() {
	for (int i = 0;i < 15;i++)
	{
		for (int j = 0;j < 15;j++)
		{
			ellipse[i][j] = 0;
		}
	}
	bWin = false;
	wWin = false;
	whitefirst = true;
	Invalidate();
}

### 4、悔棋操作
//悔棋
void CMy05gobangView::OnRollback(CCmdUI *pCmdUI) {
	pCmdUI->Enable(isChessChange());
}

void CMy05gobangView::OnRollbackBtn() {
	if (whitefirst) {
		ellipse[m2][n2] = 0;
		whitefirst = false;
	}
	else {
		ellipse[m1][n1] = 0;
		whitefirst = true;
	}
	isEditUndoClick = true;
	int sum = 0;
	for (int j = 0;j < 15;j++)
	{
		for (int m = 0;m <15;m++)
		{
			sum += abs(ellipse[j][m]);
		}
	}
	if (sum == 0)
	{
		whitefirst = true;
	}
	Invalidate();
}

### 修改背景样式
void CMy05gobangView::OnOptions(CCmdUI *pCmdUI) {
	//backgroundColor数值为1时切换为绿色
	if (backgroundColor == 1) {
		pCmdUI->SetCheck(mColor == GREEN);
		pCmdUI->Enable(mColor != GREEN);
		backgroundColor = 2;
	}
	//backgroundColor数值为2时切换为蓝色
	else if (backgroundColor == 2) {
		pCmdUI->SetCheck(mColor == BLUE);
		pCmdUI->Enable(mColor != BLUE);
		backgroundColor = 3;
	}
	//backgroundColor数值为3时切换为黄色
	else if (backgroundColor == 3) {
		pCmdUI->SetCheck(mColor == YELLOW);
		pCmdUI->Enable(mColor != YELLOW);
		backgroundColor = 1;
	}
}

void CMy05gobangView::OnOptionsBtn() {
	//backgroundColor数值为1时切换为绿色
	if (backgroundColor == 1) {
		mColor = GREEN;
		Invalidate(TRUE);
		backgroundColor = 2;
	}
	//backgroundColor数值为2时切换为蓝色
	else if (backgroundColor == 2) {
		mColor = BLUE;
		Invalidate(TRUE);
		backgroundColor = 3;
	}
	//backgroundColor数值为3时切换为黄色
	else if (backgroundColor == 3) {
		mColor = YELLOW;
		Invalidate(TRUE);
		backgroundColor = 1;
	}
}
## 运行结果

![github](https://github.com/cchangcs/WuZiQi/blob/master/show.jpg "github")  
