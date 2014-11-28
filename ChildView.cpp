
// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "DrivingDemo.h"
#include "ChildView.h"
#include "Util.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	
	m_car = new Car();
	m_car->setParams(
			 163.000000 ,  //x

			 360.000000,   //y

			 0.100614,     //ratio

			 4415, //����(mm) 4415  

			  1674,  //���(mm) 1674  

              1415, //�߶�(mm) 1415  

			   2471, //���(mm) 2471  

				1429, //ǰ�־�(mm) 1429 

				1422,  //���־�(mm) 1422  

				381 //��ֱ̥��(mm) 381  R15 inch 
				);
	//163.000000 , 360.000000,0.150614
	//m_car = new Car(124.000000 , 295.000000 , 1);
	//ԭ��900,2500
}

CChildView::~CChildView()
{
	delete m_car;
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView ��Ϣ�������

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	
	// TODO: �ڴ˴������Ϣ����������
	
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
	m_car->draw(dc);
}

BOOL CChildView::PreTranslateMessage(MSG* pMsg) 
{ 
if (pMsg->message==WM_KEYDOWN) 
{ 
	switch( pMsg->wParam ) 
	{ 
 		case 'W': 
		{
			Util::LOG(L"forward");
			//m_wheel->go_foward();
			m_car->go_forward();
			Invalidate();
		}
		break;
		case 'S': 
		{
			Util::LOG(L"backward");
			//m_wheel->go_backward();
			m_car->go_backward();
			Invalidate();
		}
		break;
		case 'A': 
		{
			Util::LOG(L"moveleft");
			//m_wheel->go_backward();
			m_car->Translate(-1,0,0);
			Invalidate();
		}
		break;
		case 'D': 
		{
			Util::LOG(L"moveright");
			//m_wheel->go_backward();
			m_car->Translate(1,0,0);
			Invalidate();
		}
		break;
		case VK_LEFT: 
		{
			//Util::LOG(L"left");
			m_car->turn_left();
			//m_car->Scale(0.999);
			Invalidate();
		}
		break;
		case VK_RIGHT: 
		{
			//Util::LOG(L"right");
			m_car->turn_right();
			//m_car->Scale(1.001);
			Invalidate();
		}
		break;
	} 
} 
else 
if (pMsg->message==WM_KEYUP) 
{ 
BOOL bCtrl=::GetKeyState(VK_CONTROL)&0x8000; 
BOOL bShift=::GetKeyState(VK_SHIFT)&0x8000; 
// only gets here if CTRL key is pressed 

	
}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) return TRUE;  
	return CWnd::PreTranslateMessage(pMsg); 
} 
