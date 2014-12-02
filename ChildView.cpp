
// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "DrivingDemo.h"
#include "ChildView.h"
#include "Util.h"
#include "SpaceTurnRight.h"
#include "SpaceReverseParking.h"
#include "SpaceSideParking.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_space = NULL;
	m_car = new Car();
	m_car->setParams(
			 163.000000 ,  //x

			 360.000000,   //y

			 4415, //����(mm) 4415  

			  1674,  //���(mm) 1674  

              1415, //�߶�(mm) 1415  

			   2471, //���(mm) 2471  

				1429, //ǰ�־�(mm) 1429 

				1422,  //���־�(mm) 1422  

				381, //��ֱ̥��(mm) 381  R15 inch 

				200 //��̥���
				);
	m_car->Scale( 0.100614 );     //ratio
	m_car->Rotate(0);
	//163.000000 , 360.000000,0.150614
	//m_car = new Car(124.000000 , 295.000000 , 1);
	//ԭ��900,2500
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_UPDATE_COMMAND_UI(ID_MENU_ITEM_RADIUS, &CChildView::OnMenuItemRadius)
	ON_UPDATE_COMMAND_UI(ID_MENU_ITEM_OUTSIDE_FRONT_CAR, &CChildView::OnMenuItemOutsideFrontCar)
	ON_UPDATE_COMMAND_UI(ID_MENU_ITEM_OUTSIDE_FRONT_WHEEL, &CChildView::OnMenuItemOutsideFrontWheel)
	ON_UPDATE_COMMAND_UI(ID_MENU_ITEM_OUTSIDE_REAR_WHEEL, &CChildView::OnMenuItemOutsideRearWheel)
	
	ON_COMMAND(ID_ITEM_RIGHT_TURN, &CChildView::OnItemRightTurn)
	ON_COMMAND(ID_ITEM_FREE, &CChildView::OnItemFree)
	ON_COMMAND(ID_APP_EXIT, &CChildView::OnAppExit)
	ON_COMMAND(ID_MENU_ITEM_RADIUS, &CChildView::OnMenuItemRadius)
	ON_COMMAND(ID_MENU_ITEM_OUTSIDE_FRONT_CAR, &CChildView::OnMenuItemOutsideFrontCar)
	ON_COMMAND(ID_MENU_ITEM_OUTSIDE_FRONT_WHEEL, &CChildView::OnMenuItemOutsideFrontWheel)
	ON_COMMAND(ID_MENU_ITEM_OUTSIDE_REAR_WHEEL, &CChildView::OnMenuItemOutsideRearWheel)
	ON_COMMAND(ID_ITEM_REVERSE_PARKING, &CChildView::OnItemReverseParking)
	ON_COMMAND(ID_ITEM_SIDE_PARKING, &CChildView::OnItemSideParking)
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
	//CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	//˫����
	 CRect rect;//���������ͼ�����С�ľ���  
	 CDC *pDC;
     CDC MemDC;   //�������ݵ��ڴ�DC  
	 CBitmap MemBitmap;  //��������
	 GetClientRect(&rect);   //��ȡ�ͻ��������С
     pDC=GetDC();
	 //ѡ����ͻ��������С��ͬ��λ�ô�������λͼ
	MemDC.CreateCompatibleDC(pDC);
	MemBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	MemDC.SelectObject(&MemBitmap);   //��λͼѡ���ڴ���
	MemDC.FillSolidRect(rect,RGB(255,255,255));
	
	
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
	if(m_space!=NULL) m_space->draw(MemDC);

	m_car->draw(MemDC);

	 pDC->BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&MemDC,0,0,SRCCOPY);

	 MemDC.DeleteDC();
	 MemBitmap.DeleteObject();
	 ReleaseDC(pDC);
}
BOOL CChildView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}
BOOL CChildView::PreTranslateMessage(MSG* pMsg) 
{ 
if (pMsg->message==WM_KEYDOWN) 
{ 
	switch( pMsg->wParam ) 
	{ 
 		case 'W': 
		{
			//m_car->Translate(0,-1,0);
		   //if(m_space!=NULL)	m_space->Translate(0,-1,0);
			Invalidate(FALSE);
		}
		break;
		case 'S': 
		{
			//m_car->Translate(0,1,0);
		 	//if(m_space!=NULL) m_space->Translate(0,1,0);
			Invalidate(FALSE);
		}
		break;
		case 'A': 
		{
			//m_car->Translate(-1,0,0);
		 	//if(m_space!=NULL) m_space->Translate(-1,0,0);
			Invalidate(FALSE);
		}
		break;
		case 'D': 
		{
			//m_car->Translate(1,0,0);
			//if(m_space!=NULL) m_space->Translate(1,0,0);
			Invalidate(FALSE);
		}
		break;
		case VK_UP: 
		{
			//Util::LOG(L"left");
			m_car->go_forward();
			Invalidate(FALSE);
		}
		break;
		case VK_DOWN: 
		{
			//Util::LOG(L"left");
			m_car->go_backward();
			//m_car->Scale(0.999);
			 
			Invalidate(FALSE);
		}
		break;
		case VK_LEFT: 
		{
			//Util::LOG(L"left");
			m_car->turn_left();
			//m_car->Scale(0.999);
			 
			Invalidate(FALSE);
		}
		break;
		case VK_RIGHT: 
		{
			//Util::LOG(L"right");
			m_car->turn_right();
			//m_car->Scale(1.001);
		 
			Invalidate(FALSE);
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
/*
typedef enum{
	TYPE_GUIDE_LINE_RADIUS,
	TYPE_GUIDE_LINE_OUTSIDE_FRONT_CAR,
	TYPE_GUIDE_LINE_OUTSIDE_FRONT_WHEEL,
	TYPE_GUIDE_LINE_OUTSIDE_REAR_WHEEL,
	TYPE_TURN_RIGHT
}MENU_ITEM_TYPE;*/
BOOL check_guide_line[4]={FALSE};
//MENU_ITEM_TYPE m_type;

void CChildView::OnMenuItemRadius(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(check_guide_line[0]);	  
	
}
void CChildView::OnMenuItemOutsideFrontCar(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(check_guide_line[1]);	  
}
void CChildView::OnMenuItemOutsideFrontWheel(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(check_guide_line[2]);	  
}
void CChildView::OnMenuItemOutsideRearWheel(CCmdUI *pCmdUI)
{
	pCmdUI->SetRadio(check_guide_line[3]);	  
}
void CChildView::OnMenuItemRadius()
{
	// TODO: �ڴ���������������
	Util::LOG(L"OnMenuItemRadius");
	check_guide_line[0] = !check_guide_line[0];
	m_car->m_show_guide_line[0]=check_guide_line[0];
	Invalidate();
}

void CChildView::OnMenuItemOutsideFrontCar()
{
	// TODO: �ڴ���������������
	check_guide_line[1] = !check_guide_line[1];
	m_car->m_show_guide_line[1]=check_guide_line[1];
	Invalidate();
}


void CChildView::OnMenuItemOutsideFrontWheel()
{
	// TODO: �ڴ���������������
	check_guide_line[2] = !check_guide_line[2];
	m_car->m_show_guide_line[2]=check_guide_line[2];
	Invalidate();
}


void CChildView::OnMenuItemOutsideRearWheel()
{
	// TODO: �ڴ���������������
	check_guide_line[3] = !check_guide_line[3];
	m_car->m_show_guide_line[3]=check_guide_line[3];
	Invalidate();
}
//����ģʽ
void CChildView::OnItemFree()
{
	// TODO: �ڴ���������������
	if(m_space!=NULL)
	{
		delete m_space;
		m_space = NULL;
	}
	Invalidate();
}
//ֱ��ת��ģʽ
void CChildView::OnItemRightTurn()
{
	// TODO: �ڴ���������������
	if(m_space!=NULL)
	{
		delete m_space;
		m_space = NULL;
	}
	if(m_car!=NULL)
	{
		delete m_car;
		m_car = NULL;
	}
	m_space = new SpaceTurnRight();
	((SpaceTurnRight*)m_space)->setParams( 684 ,  //x
										   685   //y
						 );
	m_car = new Car;
	m_car->setParams(
			 163.000000 ,  //x

			 600,   //y

			 4415, //����(mm) 4415  

			  1674,  //���(mm) 1674  

              1415, //�߶�(mm) 1415  

			   2471, //���(mm) 2471  

				1429, //ǰ�־�(mm) 1429 

				1422,  //���־�(mm) 1422  

				381, //��ֱ̥��(mm) 381  R15 inch 

				200 //��̥���
				);
	m_car->Rotate(0);
	m_car->Scale( 0.100614 );     //ratio

	((SpaceTurnRight*)m_space)->setCar(m_car);
	m_space->Scale(m_car->m_dRatio);
	Invalidate();

	for(int i=0;i<4;++i)
    m_car->m_show_guide_line[i] = check_guide_line[i];
}


void CChildView::OnItemReverseParking()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	if(m_space!=NULL)
	{
		delete m_space;
		m_space = NULL;
	}
	if(m_car!=NULL)
	{
		delete m_car;
		m_car = NULL;
	}
	m_space = new SpaceReverseParking();
	((SpaceReverseParking*)m_space)->setParams( 684 ,  //x
										   364   //y
						 );
	m_car = new Car;
	m_car->setParams(
			 402 ,  //x

			 96,   //y

			 4415, //����(mm) 4415  

			  1674,  //���(mm) 1674  

              1415, //�߶�(mm) 1415  

			   2471, //���(mm) 2471  

				1429, //ǰ�־�(mm) 1429 

				1422,  //���־�(mm) 1422  

				381, //��ֱ̥��(mm) 381  R15 inch 

				200 //��̥���
				);
	m_car->Rotate(90);
	m_car->Scale( 0.06 );     //ratio

	((SpaceReverseParking*)m_space)->setCar(m_car);
	m_space->Scale(m_car->m_dRatio);
	
	Invalidate();

	for(int i=0;i<4;++i)
    m_car->m_show_guide_line[i] = check_guide_line[i];
}



void CChildView::OnItemSideParking()
{
	// TODO: �ڴ���������������
	if(m_space!=NULL)
	{
		delete m_space;
		m_space = NULL;
	}
	if(m_car!=NULL)
	{
		delete m_car;
		m_car = NULL;
	}
	m_space = new SpaceSideParking();
	((SpaceSideParking*)m_space)->setParams( 703.000000,171.000000   //x,y
						 );
	m_car = new Car;
	m_car->setParams(
			1051.000000,254.000000,//x,y

			 4415, //����(mm) 4415  

			  1674,  //���(mm) 1674  

              1415, //�߶�(mm) 1415  

			   2471, //���(mm) 2471  

				1429, //ǰ�־�(mm) 1429 

				1422,  //���־�(mm) 1422  

				381, //��ֱ̥��(mm) 381  R15 inch 

				200 //��̥���
				);
	m_car->Rotate(-90);
	m_car->Scale( 0.06 );     //ratio

	((SpaceSideParking*)m_space)->setCar(m_car);
	m_space->Scale(m_car->m_dRatio);
	
	Invalidate();

	for(int i=0;i<4;++i)
    m_car->m_show_guide_line[i] = check_guide_line[i];
}


void CChildView::OnAppExit()
{
	// TODO: �ڴ���������������
	//PostMessage(WM_CLOSE);//���
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(),WM_CLOSE,0,0);
//	DestroyWindow();
	Util::LOG(L"OnAppExit");
}
CChildView::~CChildView()
{
	//DestroyWindow(); 
	if(m_car!=NULL)
	delete m_car;
	if(m_space!=NULL)
	delete m_space;
    Util::LOG(L"~CChildView");
}

