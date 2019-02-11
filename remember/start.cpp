#include <windows.h>
#include <stdlib.h>
#include <time.h>

int part=-1;

int times=0,times2=0,times3=0,times4=0;
int Select=1;
int input[30]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int num[30]={0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0};
TCHAR strnum[31][2];
int ds = 0,min_sec=500,min_sec2=3000,rem_time=300;
int digit[4]={0,0,0,0};
bool istime1=false,istime2=false,istime100;

void Write(HWND hwnd,bool is15)
{
	DWORD h;
	HANDLE file = CreateFile(TEXT("data.dat"),
				GENERIC_READ|GENERIC_WRITE,
				0,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	if(is15)
	{
		for(times=0;times<15;times++)
		{
			itoa(num[times],strnum[times],10);
			if(!WriteFile(file,strnum[times],lstrlen(strnum[times]),&h,NULL))
			{
				DWORD dwError = GetLastError() ;
				char chErrorBuf[10];
				wsprintf(chErrorBuf,TEXT("�ļ�д����󣬴�����룺WRITE_%d"),dwError);
				MessageBox(hwnd,chErrorBuf,TEXT("WRITE ERROR"),MB_OK|MB_ICONERROR);
				CloseHandle(file);
				PostQuitMessage( 0 );
			}
		}
	}
	else
	{
		for(times=0;times<30;times++)
		{
			itoa(num[times],strnum[times],10);
			if(!WriteFile(file,strnum[times],lstrlen(strnum[times]),&h,NULL))
			{
				DWORD dwError = GetLastError() ;
				char chErrorBuf[10];
				wsprintf(chErrorBuf,TEXT("�ļ�д����󣬴�����룺WRITE_%d"),dwError);
				MessageBox(hwnd,chErrorBuf,TEXT("WRITE ERROR"),MB_OK|MB_ICONERROR);
				CloseHandle(file);
				PostQuitMessage( 0 );
			}
		}
	}
	CloseHandle(file);
}





void Read(HWND hwnd)
{
	DWORD FileSize,h;
	HANDLE file = CreateFile(TEXT("data.dat"),
				GENERIC_READ|GENERIC_WRITE,
				0,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	FileSize = GetFileSize(file,NULL);
	if(FileSize==INVALID_FILE_SIZE && GetLastError()!=NO_ERROR)
	{
		MessageBox(hwnd,TEXT("�ļ���ȡ��С����"),TEXT("READ ERROR"),MB_OK|MB_ICONERROR);
		CloseHandle(file);
		PostQuitMessage( 0 );
	}
	SetFilePointer(file, 0, NULL, FILE_BEGIN);
	if(FileSize<18)
	{
		for(times=0;times<15;times++)
		{
			if(!ReadFile(file,strnum[times],1,&h,NULL))//������ļ���......
			{
				DWORD dwError = GetLastError() ;
				char chErrorBuf[10];
				wsprintf(chErrorBuf,TEXT("�ļ�������󣬴�����룺READ_%d"),dwError);
				MessageBox(hwnd,chErrorBuf,TEXT("READ ERROR"),MB_OK|MB_ICONERROR);
				CloseHandle(file);
				PostQuitMessage( 0 );
			}
			num[times]=atoi(strnum[times]);
		}
		part=2;
		min_sec=0;
	}
	else
	{
		for(times=0;times<30;times++)
		{
			if(!ReadFile(file,strnum[times],1,&h,NULL))//������ļ���......
			{
				DWORD dwError = GetLastError() ;
				char chErrorBuf[10];
				wsprintf(chErrorBuf,TEXT("�ļ�������󣬴�����룺READ_%d"),dwError);
				MessageBox(hwnd,chErrorBuf,TEXT("READ ERROR"),MB_OK|MB_ICONERROR);
				CloseHandle(file);
				PostQuitMessage( 0 );
			}
			num[times]=atoi(strnum[times]);
		}
		part=5;
		min_sec2=0;
	}
	InvalidateRect(hwnd,NULL,true);
	CloseHandle(file);
}




LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	HBRUSH WindowBrush = CreateSolidBrush(RGB(80,80,80));
	HPEN WindowPen = CreatePen(PS_SOLID,0,RGB(80,80,80));
	RECT WindowRect;
	RECT TITLE={0,0,1000,100};
	RECT DES={0,150,1000,400};
	RECT SELECT[4]={{8,8,248,392},
					{256,8,496,392},
					{504,8,744,392},
					{752,8,992,392}};
	RECT EASYOR_TITLE[4]={{8,8,248,200},
					{256,8,496,200},
					{504,8,744,200},
					{752,8,992,200}};
	RECT EASYOR_DES[4]={{8,200,248,392},
					{256,200,496,392},
					{504,200,744,392},
					{752,200,992,392}};
	RECT TEXT[15]={{20,150,70,250},
					{85,150,135,250},
					{150,150,200,250},
					{215,150,265,250},
					{280,150,330,250},
					{345,150,395,250},
					{410,150,460,250},
					{475,150,525,250},
					{540,150,590,250},
					{605,150,655,250},
					{670,150,720,250},
					{735,150,785,250},
					{800,150,850,250},
					{865,150,915,250},
					{930,150,980,250}};
	RECT TEXTS[15]={{20,100,70,150},
					{85,100,135,150},
					{150,100,200,150},
					{215,100,265,150},
					{280,100,330,150},
					{345,100,395,150},
					{410,100,460,150},
					{475,100,525,150},
					{540,100,590,150},
					{605,100,655,150},
					{670,100,720,150},
					{735,100,785,150},
					{800,100,850,150},
					{865,100,915,150},
					{930,100,980,150}};
	RECT TEXT30[30]={{9,175,34,225},
					{42,175,67,225},
					{75,175,100,225},
					{108,175,133,225},
					{141,175,166,225},
					{174,175,199,225},
					{207,175,232,225},
					{240,175,265,225},
					{273,175,298,225},
					{306,175,331,225},
					{339,175,364,225},
					{372,175,397,225},
					{405,175,430,225},
					{438,175,463,225},
					{471,175,496,225},
					{504,175,529,225},
					{537,175,562,225},
					{570,175,595,225},
					{603,175,628,225},
					{636,175,661,225},
					{669,175,694,225},
					{702,175,727,225},
					{735,175,760,225},
					{768,175,793,225},
					{801,175,826,225},
					{834,175,859,225},
					{867,175,892,225},
					{900,175,925,225},
					{933,175,958,225},
					{966,175,991,225}};
	RECT TEXT30S[30]={{9,125,34,175},
					{42,125,67,175},
					{75,125,100,175},
					{108,125,133,175},
					{141,125,166,175},
					{174,125,199,175},
					{207,125,232,175},
					{240,125,265,175},
					{273,125,298,175},
					{306,125,331,175},
					{339,125,364,175},
					{372,125,397,175},
					{405,125,430,175},
					{438,125,463,175},
					{471,125,496,175},
					{504,125,529,175},
					{537,125,562,175},
					{570,125,595,175},
					{603,125,628,175},
					{636,125,661,175},
					{669,125,694,175},
					{702,125,727,175},
					{735,125,760,175},
					{768,125,793,175},
					{801,125,826,175},
					{834,125,859,175},
					{867,125,892,175},
					{900,125,925,175},
					{933,125,958,175},
					{966,125,991,175}};
	RECT TIME[4]={{10,380,15,390},{15,380,20,390},{25,380,30,390},{20,380,25,390}};
	RECT MIN5[5]={{450,280,470,320},{470,280,490,320},{510,280,530,320},{530,280,550,320},{490,280,510,320}};
	HDC hdc ;                //�豸�������
	PAINTSTRUCT ps ;         //���ƽṹ
	int i=0;
	static POINT Mouse,Mouse1;
	static HFONT TextFont = CreateFont(
			100,      //������߼��߶�
			0,       //�߼�ƽ���ַ����
			0,           //��ˮƽ�ߵĽǶ�
			0,           //���߷�λ�Ƕ�
			FW_REGULAR,  //���Σ�����
			FALSE,       //���Σ�б��
			FALSE,       //���Σ��»���
			FALSE,       //���Σ�����
			DEFAULT_CHARSET,          //�ַ���
			OUT_DEFAULT_PRECIS,      //�������
			CLIP_DEFAULT_PRECIS,     //���ؾ���
			PROOF_QUALITY,           //���Ʒ��
			FIXED_PITCH | FF_MODERN, //��б��
			"Inconsolata"            //����
			);
	static HFONT TextFont5 = CreateFont(
			40,      //������߼��߶�
			0,       //�߼�ƽ���ַ����
			0,           //��ˮƽ�ߵĽǶ�
			0,           //���߷�λ�Ƕ�
			FW_REGULAR,  //���Σ�����
			FALSE,       //���Σ�б��
			FALSE,       //���Σ��»���
			FALSE,       //���Σ�����
			DEFAULT_CHARSET,          //�ַ���
			OUT_DEFAULT_PRECIS,      //�������
			CLIP_DEFAULT_PRECIS,     //���ؾ���
			PROOF_QUALITY,           //���Ʒ��
			FIXED_PITCH | FF_MODERN, //��б��
			"Inconsolata"            //����
			);

	static HFONT TextFontS = CreateFont(
			50,      //������߼��߶�
			0,       //�߼�ƽ���ַ����
			0,           //��ˮƽ�ߵĽǶ�
			0,           //���߷�λ�Ƕ�
			FW_REGULAR,  //���Σ�����
			FALSE,       //���Σ�б��
			FALSE,       //���Σ��»���
			FALSE,       //���Σ�����
			DEFAULT_CHARSET,          //�ַ���
			OUT_DEFAULT_PRECIS,      //�������
			CLIP_DEFAULT_PRECIS,     //���ؾ���
			PROOF_QUALITY,           //���Ʒ��
			FIXED_PITCH | FF_MODERN, //��б��
			"Inconsolata"            //����
			);

	static HFONT TextFontSS = CreateFont(
			10,      //������߼��߶�
			0,       //�߼�ƽ���ַ����
			0,           //��ˮƽ�ߵĽǶ�
			0,           //���߷�λ�Ƕ�
			FW_REGULAR,  //���Σ�����
			FALSE,       //���Σ�б��
			FALSE,       //���Σ��»���
			FALSE,       //���Σ�����
			DEFAULT_CHARSET,          //�ַ���
			OUT_DEFAULT_PRECIS,      //�������
			CLIP_DEFAULT_PRECIS,     //���ؾ���
			PROOF_QUALITY,           //���Ʒ��
			FIXED_PITCH | FF_MODERN, //��б��
			"Inconsolata"            //����
			);

	static HFONT EASYOR = CreateFont(
			50,      //������߼��߶�
			0,       //�߼�ƽ���ַ����
			0,           //��ˮƽ�ߵĽǶ�
			0,           //���߷�λ�Ƕ�
			FW_REGULAR,  //���Σ�����
			FALSE,       //���Σ�б��
			FALSE,       //���Σ��»���
			FALSE,       //���Σ�����
			DEFAULT_CHARSET,          //�ַ���
			OUT_DEFAULT_PRECIS,      //�������
			CLIP_DEFAULT_PRECIS,     //���ؾ���
			PROOF_QUALITY,           //���Ʒ��
			FIXED_PITCH | FF_MODERN, //��б��
			"�����ƺڼ���_501L"            //����
			);

	static HFONT EASYORS = CreateFont(
			15,      //������߼��߶�
			0,       //�߼�ƽ���ַ����
			0,           //��ˮƽ�ߵĽǶ�
			0,           //���߷�λ�Ƕ�
			FW_REGULAR,  //���Σ�����
			FALSE,       //���Σ�б��
			FALSE,       //���Σ��»���
			FALSE,       //���Σ�����
			DEFAULT_CHARSET,          //�ַ���
			OUT_DEFAULT_PRECIS,      //�������
			CLIP_DEFAULT_PRECIS,     //���ؾ���
			PROOF_QUALITY,           //���Ʒ��
			FIXED_PITCH | FF_MODERN, //��б��
			"�����ƺ�_503L"            //����
			);

	static bool isRbutDn = false;
	static bool isLbutDn = false;

	static bool isrand=false;

	if(!isrand)
	{
		srand(time(NULL));
		for(i=0;i<30;i++)
			num[i]=rand()%10;
		isrand = true;
	}

	/*switch( message )        //����õ�����Ϣ
	{
	case WM_CREATE:          //���ڴ������ʱ��������Ϣ
		//MessageBox( hwnd, TEXT("�����Ѵ������!"), TEXT("�ҵĴ���"), MB_OK | MB_ICONINFORMATION ) ;
		return 0;

	case WM_PAINT:           //������������Чʱ��������Ϣ
		//hdc = BeginPaint( hwnd, &ps ) ;
		//GetClientRect( hwnd, &rect ) ;
		//DrawText( hdc, TEXT( "Hello, �������Լ��Ĵ���!" ), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
		//EndPaint( hwnd, &ps ) ;
		return 0 ;

	case WM_LBUTTONDOWN:     //���������������µ���Ϣ
		//MessageBox( hwnd, TEXT("�����������¡�"), TEXT("����"), MB_OK | MB_ICONINFORMATION ) ;
		return 0;

	case WM_DESTROY:         //�����ڹر�ʱ����Ϣ
		//MessageBox( hwnd, TEXT("�رճ���!"), TEXT("����"), MB_OK | MB_ICONINFORMATION ) ;
		PostQuitMessage( 0 ) ;
		return 0;
	}*/
	switch( message )
	{
		case WM_MOUSEMOVE:
			hdc=GetDC(hwnd);
			GetCursorPos(&Mouse);
			ScreenToClient(hwnd,&Mouse);
			if(isLbutDn)
			{
				GetWindowRect(hwnd,&WindowRect);
				MoveWindow(hwnd,WindowRect.left+Mouse.x-Mouse1.x,WindowRect.top+Mouse.y-Mouse1.y,1000,400,true);
				ReleaseDC(hwnd,hdc);
				return 0;
			}
			ReleaseDC(hwnd,hdc);
			return 0;


		case WM_RBUTTONDOWN:
			isRbutDn = true;
			return 0;

		case WM_RBUTTONUP:
			if(isRbutDn)
			{	
				if(istime2)
				{
					isRbutDn = false;
					return 0;
				}
				DeleteObject(TextFont);
				if(istime1)
				{
					KillTimer(hwnd,1);
					istime1=false;
				}
				PostQuitMessage( 0 );
			}
			return 0;

		case WM_LBUTTONDOWN:
			hdc=GetDC(hwnd);
			isLbutDn = true;
			GetCursorPos(&Mouse1);
			ScreenToClient(hwnd,&Mouse1);
			if(isRbutDn)
				isRbutDn = false;
			ReleaseDC(hwnd,hdc);
			return 0;

		case WM_LBUTTONUP:
			isLbutDn = false;
			return 0;

		case WM_DESTROY:
			if(istime1)
			{
				KillTimer(hwnd,1);
				istime1=false;
			}
			if(istime2)
			{
				KillTimer(hwnd,2);
				istime2=false;
			}
			PostQuitMessage( 0 ) ;
			return 0;

	}










	if(part==-1)
	{
		switch(message)
		{
		case WM_PAINT:
			{
			hdc = BeginPaint( hwnd, &ps ) ;
			SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(110,190,40)));
			SelectObject(hdc,CreateSolidBrush(RGB(110,190,40)));
			Rectangle(hdc,SELECT[0].left,SELECT[0].top,SELECT[0].right,SELECT[0].bottom);
			SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(50,50,50)));
			SelectObject(hdc,CreateSolidBrush(RGB(50,50,50)));
			for(times=1;times<4;times++)
				Rectangle(hdc,SELECT[times].left,SELECT[times].top,SELECT[times].right,SELECT[times].bottom);
			SelectObject(hdc,EASYOR);
			SetBkMode(hdc,TRANSPARENT);
			SetTextColor(hdc,RGB(255,255,255));
			DrawText( hdc, TEXT( "��" ), -1, &EASYOR_TITLE[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
			DrawText( hdc, TEXT( "��" ), -1, &EASYOR_TITLE[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
			DrawText( hdc, TEXT( "��" ), -1, &EASYOR_TITLE[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
			DrawText( hdc, TEXT( "����" ), -1, &EASYOR_TITLE[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
			SelectObject(hdc,EASYORS);
			DrawText( hdc, TEXT( "15λ����\n5����\n\n\n����ʱ���ѡ\n30��\n20��\n15��" ), -1, &EASYOR_DES[0], DT_CENTER | DT_VCENTER ) ;
			DrawText( hdc, TEXT( "15λ����\n30����\n\n\n����ʱ���ѡ\n30��\n20��\n15��" ), -1, &EASYOR_DES[1], DT_CENTER | DT_VCENTER ) ;
			DrawText( hdc, TEXT( "30λ����\n30����\n\n\n����ʱ���ѡ\n90��\n70��\n60��" ), -1, &EASYOR_DES[2], DT_CENTER | DT_VCENTER ) ;
			DrawText( hdc, TEXT( "�Ѷȸ���" ), -1, &EASYOR_DES[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
			EndPaint( hwnd, &ps ) ;
			return 0;
			}
		case WM_KEYDOWN://green:110,190,40 yellow:240,230,60 red:230,30,30 blue:20,70,160
			{
			hdc=GetDC(hwnd);
			if(wParam==39||wParam==40)
			{
				switch(Select)
				{
				case 1:Select=2;SetTimer(hwnd,101,15,NULL);SetTimer(hwnd,106,15,NULL);break;
				case 2:Select=3;SetTimer(hwnd,102,15,NULL);SetTimer(hwnd,107,15,NULL);break;
				case 3:Select=4;SetTimer(hwnd,103,15,NULL);SetTimer(hwnd,108,15,NULL);break;
				case 4:Select=1;SetTimer(hwnd,104,15,NULL);SetTimer(hwnd,105,15,NULL);break;
				}
			}
			if(wParam==37||wParam==38)
			{
				switch(Select)
				{
				case 1:Select=4;SetTimer(hwnd,101,15,NULL);SetTimer(hwnd,108,15,NULL);break;
				case 2:Select=1;SetTimer(hwnd,102,15,NULL);SetTimer(hwnd,105,15,NULL);break;
				case 3:Select=2;SetTimer(hwnd,103,15,NULL);SetTimer(hwnd,106,15,NULL);break;
				case 4:Select=3;SetTimer(hwnd,104,15,NULL);SetTimer(hwnd,107,15,NULL);break;
				}
			}
			if(wParam==13)
			{
				part=-2;
				InvalidateRect(hwnd,NULL,true);
			}
			ReleaseDC(hwnd,hdc);
			return 0;
			}
		case WM_TIMER:
			{
			hdc=GetDC(hwnd);
			switch(wParam)
			{
			case 101://chu 0
				{
				static int times101=0;
				if(times101>=11)
				{
					times101=0;
					KillTimer(hwnd,101);
					break;
				}
				SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(110-times101*6,190-times101*14,40+times101)));
				SelectObject(hdc,CreateSolidBrush(RGB(110-times101*6,190-times101*14,40+times101)));
				Rectangle(hdc,SELECT[0].left,SELECT[0].top,SELECT[0].right,SELECT[0].bottom);
				SelectObject(hdc,EASYOR);
				SetBkMode(hdc,TRANSPARENT);
				SetTextColor(hdc,RGB(255,255,255));
				DrawText( hdc, TEXT( "��" ), -1, &EASYOR_TITLE[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
				SelectObject(hdc,EASYORS);
				DrawText( hdc, TEXT( "15λ����\n5����\n\n\n����ʱ���ѡ\n30��\n20��\n15��" ), -1, &EASYOR_DES[0], DT_CENTER | DT_VCENTER ) ;
				times101++;
				break;
				}
			case 102://zhong 0
				{
				static int times101=0;
				if(times101>=11)
				{
					times101=0;
					KillTimer(hwnd,102);
					break;
				}
				SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(240-times101*19,230-times101*18,60-times101)));
				SelectObject(hdc,CreateSolidBrush(RGB(240-times101*19,230-times101*18,60-times101)));
				Rectangle(hdc,SELECT[1].left,SELECT[1].top,SELECT[1].right,SELECT[1].bottom);
				SelectObject(hdc,EASYOR);
				SetBkMode(hdc,TRANSPARENT);
				SetTextColor(hdc,RGB(255,255,255));
				DrawText( hdc, TEXT( "��" ), -1, &EASYOR_TITLE[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
				SelectObject(hdc,EASYORS);
				DrawText( hdc, TEXT( "15λ����\n30����\n\n\n����ʱ���ѡ\n30��\n20��\n15��" ), -1, &EASYOR_DES[1], DT_CENTER | DT_VCENTER ) ;
				times101++;
				break;
				}
			case 103://gao 0
				{
				static int times101=0;
				if(times101>=11)
				{
					times101=0;
					KillTimer(hwnd,103);
					break;
				}
				SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(230-times101*18,30+times101*2,30+times101*2)));
				SelectObject(hdc,CreateSolidBrush(RGB(230-times101*18,30+times101*2,30+times101*2)));
				Rectangle(hdc,SELECT[2].left,SELECT[2].top,SELECT[2].right,SELECT[2].bottom);
				SelectObject(hdc,EASYOR);
				SetBkMode(hdc,TRANSPARENT);
				SetTextColor(hdc,RGB(255,255,255));
				DrawText( hdc, TEXT( "��" ), -1, &EASYOR_TITLE[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
				SelectObject(hdc,EASYORS);
				DrawText( hdc, TEXT( "30λ����\n30����\n\n\n����ʱ���ѡ\n90��\n70��\n60��" ), -1, &EASYOR_DES[2], DT_CENTER | DT_VCENTER ) ;
				times101++;
				break;
				}
			case 104://huiyi 0
				{
				static int times101=0;
				if(times101>=11)
				{
					times101=0;
					KillTimer(hwnd,104);
					break;
				}
				SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(20+times101*3,70-times101*2,160-times101*11)));
				SelectObject(hdc,CreateSolidBrush(RGB(20+times101*3,70-times101*2,160-times101*11)));
				Rectangle(hdc,SELECT[3].left,SELECT[3].top,SELECT[3].right,SELECT[3].bottom);
				SelectObject(hdc,EASYOR);
				SetBkMode(hdc,TRANSPARENT);
				SetTextColor(hdc,RGB(255,255,255));
				DrawText( hdc, TEXT( "����" ), -1, &EASYOR_TITLE[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
				SelectObject(hdc,EASYORS);
				DrawText( hdc, TEXT( "�Ѷȸ���" ), -1, &EASYOR_DES[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
				times101++;
				break;
				}
			case 105://chu 1
				{
				static int times106=0;
				if(times106>=11)
				{
					times106=0;
					KillTimer(hwnd,105);
					break;
				}
				SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(50+times106*6,50+times106*14,50-times106)));
				SelectObject(hdc,CreateSolidBrush(RGB(50+times106*6,50+times106*14,50-times106)));
				Rectangle(hdc,SELECT[0].left,SELECT[0].top,SELECT[0].right,SELECT[0].bottom);
				SelectObject(hdc,EASYOR);
				SetBkMode(hdc,TRANSPARENT);
				SetTextColor(hdc,RGB(255,255,255));
				DrawText( hdc, TEXT( "��" ), -1, &EASYOR_TITLE[0], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
				SelectObject(hdc,EASYORS);
				DrawText( hdc, TEXT( "15λ����\n5����\n\n\n����ʱ���ѡ\n30��\n20��\n15��" ), -1, &EASYOR_DES[0], DT_CENTER | DT_VCENTER ) ;
				times106++;
				break;
				}
			case 106://zhong 1
				{
				static int times106=0;
				if(times106>=11)
				{
					times106=0;
					KillTimer(hwnd,106);
					break;
				}
				SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(50+times106*19,50+times106*18,50+times106)));
				SelectObject(hdc,CreateSolidBrush(RGB(50+times106*19,50+times106*18,50+times106)));
				Rectangle(hdc,SELECT[1].left,SELECT[1].top,SELECT[1].right,SELECT[1].bottom);
				SelectObject(hdc,EASYOR);
				SetBkMode(hdc,TRANSPARENT);
				SetTextColor(hdc,RGB(255,255,255));
				DrawText( hdc, TEXT( "��" ), -1, &EASYOR_TITLE[1], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
				SelectObject(hdc,EASYORS);
				DrawText( hdc, TEXT( "15λ����\n30����\n\n\n����ʱ���ѡ\n30��\n20��\n15��" ), -1, &EASYOR_DES[1], DT_CENTER | DT_VCENTER ) ;
				times106++;
				break;
				}
			case 107://gao 1
				{
				static int times106=0;
				if(times106>=11)
				{
					times106=0;
					KillTimer(hwnd,107);
					break;
				}
				SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(50+times106*18,50-times106*2,50-times106*2)));
				SelectObject(hdc,CreateSolidBrush(RGB(50+times106*18,50-times106*2,50-times106*2)));
				Rectangle(hdc,SELECT[2].left,SELECT[2].top,SELECT[2].right,SELECT[2].bottom);
				SelectObject(hdc,EASYOR);
				SetBkMode(hdc,TRANSPARENT);
				SetTextColor(hdc,RGB(255,255,255));
				DrawText( hdc, TEXT( "��" ), -1, &EASYOR_TITLE[2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
				SelectObject(hdc,EASYORS);
				DrawText( hdc, TEXT( "30λ����\n30����\n\n\n����ʱ���ѡ\n90��\n70��\n60��" ), -1, &EASYOR_DES[2], DT_CENTER | DT_VCENTER ) ;
				times106++;
				break;
				}
			case 108://huiyi 1
				{
				static int times106=0;
				if(times106>=11)
				{
					times106=0;
					KillTimer(hwnd,108);
					break;
				}
				SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(50-times106*3,50+times106*2,50+times106*11)));
				SelectObject(hdc,CreateSolidBrush(RGB(50-times106*3,50+times106*2,50+times106*11)));
				Rectangle(hdc,SELECT[3].left,SELECT[3].top,SELECT[3].right,SELECT[3].bottom);
				SelectObject(hdc,EASYOR);
				SetBkMode(hdc,TRANSPARENT);
				SetTextColor(hdc,RGB(255,255,255));
				DrawText( hdc, TEXT( "����" ), -1, &EASYOR_TITLE[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
				SelectObject(hdc,EASYORS);
				DrawText( hdc, TEXT( "�Ѷȸ���" ), -1, &EASYOR_DES[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
				times106++;
				break;
				}
			}
			ReleaseDC(hwnd,hdc);
			return 0;
			}
			
		}
	}


	if(part==-2)
	{
		switch(message)
		{
		case WM_PAINT:
			if(Select==4)
			{
				Read(hwnd);
				return 0;
			}
			hdc = BeginPaint( hwnd, &ps ) ;
			SelectObject(hdc,EASYOR);
			SetBkMode(hdc,TRANSPARENT);
			SetTextColor(hdc,RGB(255,255,255));
			DrawText( hdc, TEXT( "������ʼ" ), -1, &TITLE, DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
			SelectObject(hdc,EASYORS);
			if(Select==1||Select==2)
			{
				DrawText( hdc, TEXT( "���¼���ʼ��ʱ\n\n\n��1 - 30s\n\n��2 - 20s\n\n��3 - 15s\n\n��4 - 30sƵ��\n\n��5 - 15sƵ��" ), -1, &DES, DT_CENTER | DT_VCENTER ) ;
			}
			else if(Select==3)
			{
				DrawText( hdc, TEXT( "���¼���ʼ��ʱ\n\n\n��1 - 90s\n\n��2 - 70s\n\n��3 - 60s\n\n��4 - 90sƵ��\n\n��5 - 60sƵ��" ), -1, &DES, DT_CENTER | DT_VCENTER ) ;
			}
			EndPaint( hwnd, &ps ) ;
			return 0;
		case WM_KEYDOWN:
			if(wParam==49||wParam==97)
			{
				switch(Select)
				{
				case 1:rem_time=300;min_sec=500;part=1;InvalidateRect(hwnd,NULL,true);return 0;
				case 2:rem_time=300;min_sec=3000;part=1;InvalidateRect(hwnd,NULL,true);return 0;
				case 3:rem_time=900;part=4;InvalidateRect(hwnd,NULL,true);return 0;
				}
			}
			else if(wParam==50||wParam==98)
			{
				switch(Select)
				{
				case 1:rem_time=200;min_sec=500;part=1;InvalidateRect(hwnd,NULL,true);return 0;
				case 2:rem_time=200;min_sec=3000;part=1;InvalidateRect(hwnd,NULL,true);return 0;
				case 3:rem_time=700;part=4;InvalidateRect(hwnd,NULL,true);return 0;
				}
			}
			else if(wParam==51||wParam==99)
			{
				switch(Select)
				{
				case 1:rem_time=150;min_sec=500;part=1;InvalidateRect(hwnd,NULL,true);return 0;
				case 2:rem_time=150;min_sec=3000;part=1;InvalidateRect(hwnd,NULL,true);return 0;
				case 3:rem_time=600;part=4;InvalidateRect(hwnd,NULL,true);return 0;
				}
			}
			return 0;
		}
	}



	if(part==0)
	{
		if(message==WM_KEYDOWN)
		{
			if(wParam==13)
			{
				part=4;
				InvalidateRect(hwnd,NULL,true);
				return 0;
			}
		}
	}

	if(part==1)//chu jiyi
	{
		/*if(message == WM_PAINT)
		{
			hdc = BeginPaint( hwnd, &ps ) ;
			GetClientRect( hwnd, &WindowRect ) ;
			DrawText( hdc, TEXT( "Hello!" ), -1, &WindowRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
			EndPaint( hwnd, &ps ) ;
		}*/
		switch(message)
		{
		case WM_TIMER:
			{
			if(ds>=rem_time)
			{
				KillTimer(hwnd,1);
				istime1=false;
				part++;
				InvalidateRect(hwnd,NULL,true);
				return 0;
			}
			hdc=GetDC(hwnd);
			ds++;
			SelectObject(hdc,TextFontSS);
			SetBkColor(hdc,RGB(80,80,80));
			SetTextColor(hdc,RGB(255,255,255));
			for(times=100;times>=1;times/=10)
			{
				if(times==100)
					times4=0;
				digit[times4]=(ds/times)%10;
				times4++;
			}
			for(times3=0;times3<3;times3++)
			{
				switch(digit[times3])
				{
				case 0:DrawText( hdc, TEXT( "0" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 1:DrawText( hdc, TEXT( "1" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 2:DrawText( hdc, TEXT( "2" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 3:DrawText( hdc, TEXT( "3" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 4:DrawText( hdc, TEXT( "4" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 5:DrawText( hdc, TEXT( "5" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 6:DrawText( hdc, TEXT( "6" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 7:DrawText( hdc, TEXT( "7" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 8:DrawText( hdc, TEXT( "8" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 9:DrawText( hdc, TEXT( "9" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				}
			}
			DrawText( hdc, TEXT( "." ), -1, &TIME[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
			ReleaseDC(hwnd,hdc);
			return 0;
			}
		case WM_PAINT:
			hdc = BeginPaint( hwnd, &ps ) ;
			GetClientRect( hwnd, &WindowRect ) ;

			SetTimer(hwnd,1,93,NULL);
			istime1=true;
			//��������
			SelectObject(hdc,TextFont);
			SetBkColor(hdc,RGB(50,50,50));
			SetTextColor(hdc,RGB(255,255,255));

			SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(50,50,50)));
			SelectObject(hdc,CreateSolidBrush(RGB(50,50,50)));
			
			for(times=0;times<15;times++)
				Rectangle(hdc,TEXT[times].left,TEXT[times].top,TEXT[times].right,TEXT[times].bottom);
			/*Rectangle(hdc,85,150,135,250);
			Rectangle(hdc,150,150,200,250);
			Rectangle(hdc,215,150,265,250);
			Rectangle(hdc,280,150,330,250);
			Rectangle(hdc,345,150,395,250);
			Rectangle(hdc,410,150,460,250);
			Rectangle(hdc,475,150,525,250);
			Rectangle(hdc,540,150,590,250);
			Rectangle(hdc,605,150,655,250);
			Rectangle(hdc,670,150,720,250);
			Rectangle(hdc,735,150,785,250);
			Rectangle(hdc,800,150,850,250);
			Rectangle(hdc,865,150,915,250);
			Rectangle(hdc,930,150,980,250);*/
			for(times2=0;times2<15;times2++)
			{
				switch(num[times2])
				{
				case 0:DrawText( hdc, TEXT( "0" ), -1, &TEXT[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 1:DrawText( hdc, TEXT( "1" ), -1, &TEXT[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 2:DrawText( hdc, TEXT( "2" ), -1, &TEXT[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 3:DrawText( hdc, TEXT( "3" ), -1, &TEXT[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 4:DrawText( hdc, TEXT( "4" ), -1, &TEXT[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 5:DrawText( hdc, TEXT( "5" ), -1, &TEXT[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 6:DrawText( hdc, TEXT( "6" ), -1, &TEXT[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 7:DrawText( hdc, TEXT( "7" ), -1, &TEXT[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 8:DrawText( hdc, TEXT( "8" ), -1, &TEXT[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 9:DrawText( hdc, TEXT( "9" ), -1, &TEXT[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				}
			}


			EndPaint( hwnd, &ps ) ;
			return 0;


		case WM_KEYDOWN:
			if(wParam==13)
			{
				part++;
				if(istime1)
				{
					KillTimer(hwnd,1);
					istime1=false;
				}
				InvalidateRect(hwnd,NULL,true);
				return 0;
			}
		}
	}

	if(part==2)//15wei shuru
	{
		static int position=0;

		switch(message)
		{
		case WM_PAINT:
			Write(hwnd,true);
			hdc = BeginPaint( hwnd, &ps ) ;
			GetClientRect( hwnd, &WindowRect ) ;

			SelectObject(hdc,TextFontSS);
			SetBkColor(hdc,RGB(80,80,80));
			SetTextColor(hdc,RGB(255,255,255));
			for(times3=0;times3<3;times3++)
			{
				switch(digit[times3])
				{
				case 0:DrawText( hdc, TEXT( "0" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 1:DrawText( hdc, TEXT( "1" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 2:DrawText( hdc, TEXT( "2" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 3:DrawText( hdc, TEXT( "3" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 4:DrawText( hdc, TEXT( "4" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 5:DrawText( hdc, TEXT( "5" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 6:DrawText( hdc, TEXT( "6" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 7:DrawText( hdc, TEXT( "7" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 8:DrawText( hdc, TEXT( "8" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 9:DrawText( hdc, TEXT( "9" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				}
			}
			DrawText( hdc, TEXT( "." ), -1, &TIME[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;

			SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(50,50,50)));
			SelectObject(hdc,CreateSolidBrush(RGB(50,50,50)));
			
			for(times3=0;times3<15;times3++)
				Rectangle(hdc,TEXT[times3].left,TEXT[times3].top,TEXT[times3].right,TEXT[times3].bottom);

			SetTimer(hwnd,2,1000,NULL);
			istime2=true;

			EndPaint( hwnd, &ps ) ;
			return 0;

		case WM_TIMER:
			{
				hdc=GetDC(hwnd);
				SelectObject(hdc,TextFont5);
				SetBkColor(hdc,RGB(80,80,80));
				SetTextColor(hdc,RGB(255,255,255));
				for(times3=1000;times3>=1;times3/=10)
				{
					if(min_sec<=0)
					{
						SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(80,80,80)));
						SelectObject(hdc,CreateSolidBrush(RGB(80,80,80)));
						Rectangle(hdc,450,280,550,320);
						istime2=false;
						KillTimer(hwnd,2);
						return 0;
					}
					if(min_sec%100==99)
						min_sec-=40;
					if(times3==1000)
						times4=0;
					switch((min_sec/times3)%10)
					{
					case 0:DrawText( hdc, TEXT( "0" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 1:DrawText( hdc, TEXT( "1" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 2:DrawText( hdc, TEXT( "2" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 3:DrawText( hdc, TEXT( "3" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 4:DrawText( hdc, TEXT( "4" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 5:DrawText( hdc, TEXT( "5" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 6:DrawText( hdc, TEXT( "6" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 7:DrawText( hdc, TEXT( "7" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 8:DrawText( hdc, TEXT( "8" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 9:DrawText( hdc, TEXT( "9" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					}
					times4++;
				}
				DrawText( hdc, TEXT( ":" ), -1, &MIN5[4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
				min_sec--;
				ReleaseDC(hwnd,hdc);
				return 0;
			}
		case WM_KEYDOWN:
			{
			if(istime2)
				return 0;
			hdc=GetDC(hwnd);
			SelectObject(hdc,TextFont);
			SetBkColor(hdc,RGB(50,50,50));
			SetTextColor(hdc,RGB(255,255,255));
			SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(50,50,50)));
			SelectObject(hdc,CreateSolidBrush(RGB(50,50,50)));
			if(wParam==13)
			{
				part++;
				InvalidateRect(hwnd,NULL,true);
				return 0;
			}
			if(wParam==8)
			{
				if(position==0)
					return 0;
				position--;
				input[position]=-1;
				Rectangle(hdc,TEXT[position].left,TEXT[position].top,TEXT[position].right,TEXT[position].bottom);
				return 0;
			}
			if(wParam>=48&&wParam<=57)
			{
				if(position>=15)
					return 0;
				switch(wParam)
				{
				case 48:input[position]=0;DrawText( hdc, TEXT( "0" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 49:input[position]=1;DrawText( hdc, TEXT( "1" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 50:input[position]=2;DrawText( hdc, TEXT( "2" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 51:input[position]=3;DrawText( hdc, TEXT( "3" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 52:input[position]=4;DrawText( hdc, TEXT( "4" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 53:input[position]=5;DrawText( hdc, TEXT( "5" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 54:input[position]=6;DrawText( hdc, TEXT( "6" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 55:input[position]=7;DrawText( hdc, TEXT( "7" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 56:input[position]=8;DrawText( hdc, TEXT( "8" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 57:input[position]=9;DrawText( hdc, TEXT( "9" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				}
			}

			else if(wParam>=96&&wParam<=105)
			{
				if(position>=15)
					return 0;
				switch(wParam)
				{
				case 96:input[position]=0;DrawText( hdc, TEXT( "0" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 97:input[position]=1;DrawText( hdc, TEXT( "1" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 98:input[position]=2;DrawText( hdc, TEXT( "2" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 99:input[position]=3;DrawText( hdc, TEXT( "3" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 100:input[position]=4;DrawText( hdc, TEXT( "4" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 101:input[position]=5;DrawText( hdc, TEXT( "5" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 102:input[position]=6;DrawText( hdc, TEXT( "6" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 103:input[position]=7;DrawText( hdc, TEXT( "7" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 104:input[position]=8;DrawText( hdc, TEXT( "8" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 105:input[position]=9;DrawText( hdc, TEXT( "9" ), -1, &TEXT[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				}
			}

			ReleaseDC(hwnd,hdc);
			return 0;
			}
		}
	}
	if(part==3)//15wei t&f
	{
		switch(message)
		{
		case WM_PAINT:
			hdc = BeginPaint( hwnd, &ps ) ;
			GetClientRect( hwnd, &WindowRect ) ;

			SelectObject(hdc,TextFontSS);
			SetBkColor(hdc,RGB(80,80,80));
			SetTextColor(hdc,RGB(255,255,255));
			for(times3=0;times3<3;times3++)
			{
				switch(digit[times3])
				{
				case 0:DrawText( hdc, TEXT( "0" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 1:DrawText( hdc, TEXT( "1" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 2:DrawText( hdc, TEXT( "2" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 3:DrawText( hdc, TEXT( "3" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 4:DrawText( hdc, TEXT( "4" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 5:DrawText( hdc, TEXT( "5" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 6:DrawText( hdc, TEXT( "6" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 7:DrawText( hdc, TEXT( "7" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 8:DrawText( hdc, TEXT( "8" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 9:DrawText( hdc, TEXT( "9" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				}
			}
			DrawText( hdc, TEXT( "." ), -1, &TIME[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;

			SelectObject(hdc,TextFont);
			SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(50,50,50)));
			SelectObject(hdc,CreateSolidBrush(RGB(50,50,50)));
			
			for(times3=0;times3<15;times3++)
				Rectangle(hdc,TEXT[times3].left,TEXT[times3].top,TEXT[times3].right,TEXT[times3].bottom);
	
			for(times3=0;times3<15;times3++)
			{
				if(input[times3]==-1)
					continue;
				if(input[times3]==num[times3])
				{
					SetBkColor(hdc,RGB(50,50,50));
					SetTextColor(hdc,RGB(0,255,0));
					switch(input[times3])
					{
					case 0:DrawText( hdc, TEXT( "0" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 1:DrawText( hdc, TEXT( "1" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 2:DrawText( hdc, TEXT( "2" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 3:DrawText( hdc, TEXT( "3" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 4:DrawText( hdc, TEXT( "4" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 5:DrawText( hdc, TEXT( "5" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 6:DrawText( hdc, TEXT( "6" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 7:DrawText( hdc, TEXT( "7" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 8:DrawText( hdc, TEXT( "8" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 9:DrawText( hdc, TEXT( "9" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					}
				}
				else
				{
					SetBkColor(hdc,RGB(50,50,50));
					SetTextColor(hdc,RGB(255,0,0));
					switch(input[times3])
					{
					case 0:DrawText( hdc, TEXT( "0" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 1:DrawText( hdc, TEXT( "1" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 2:DrawText( hdc, TEXT( "2" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 3:DrawText( hdc, TEXT( "3" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 4:DrawText( hdc, TEXT( "4" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 5:DrawText( hdc, TEXT( "5" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 6:DrawText( hdc, TEXT( "6" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 7:DrawText( hdc, TEXT( "7" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 8:DrawText( hdc, TEXT( "8" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 9:DrawText( hdc, TEXT( "9" ), -1, &TEXT[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					}
				}
			}
			SelectObject(hdc,TextFontS);
			SetBkColor(hdc,RGB(80,80,80));
			SetTextColor(hdc,RGB(255,255,255));
			for(times3=0;times3<15;times3++)
			{
				switch(num[times3])
				{
				case 0:DrawText( hdc, TEXT( "0" ), -1, &TEXTS[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 1:DrawText( hdc, TEXT( "1" ), -1, &TEXTS[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 2:DrawText( hdc, TEXT( "2" ), -1, &TEXTS[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 3:DrawText( hdc, TEXT( "3" ), -1, &TEXTS[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 4:DrawText( hdc, TEXT( "4" ), -1, &TEXTS[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 5:DrawText( hdc, TEXT( "5" ), -1, &TEXTS[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 6:DrawText( hdc, TEXT( "6" ), -1, &TEXTS[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 7:DrawText( hdc, TEXT( "7" ), -1, &TEXTS[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 8:DrawText( hdc, TEXT( "8" ), -1, &TEXTS[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 9:DrawText( hdc, TEXT( "9" ), -1, &TEXTS[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				}
			}

			EndPaint( hwnd, &ps ) ;
			return 0;
		}
		
	}
	if(part==4)//30wei
	{
		switch(message)
		{
		case WM_TIMER:
			{
			if(ds>=rem_time)
			{
				KillTimer(hwnd,1);
				istime1=false;
				part++;
				InvalidateRect(hwnd,NULL,true);
				return 0;
			}
			hdc=GetDC(hwnd);
			ds++;
			SelectObject(hdc,TextFontSS);
			SetBkColor(hdc,RGB(80,80,80));
			SetTextColor(hdc,RGB(255,255,255));
			for(times=100;times>=1;times/=10)
			{
				if(times==100)
					times4=0;
				digit[times4]=(ds/times)%10;
				times4++;
			}
			for(times3=0;times3<3;times3++)
			{
				switch(digit[times3])
				{
				case 0:DrawText( hdc, TEXT( "0" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 1:DrawText( hdc, TEXT( "1" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 2:DrawText( hdc, TEXT( "2" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 3:DrawText( hdc, TEXT( "3" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 4:DrawText( hdc, TEXT( "4" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 5:DrawText( hdc, TEXT( "5" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 6:DrawText( hdc, TEXT( "6" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 7:DrawText( hdc, TEXT( "7" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 8:DrawText( hdc, TEXT( "8" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 9:DrawText( hdc, TEXT( "9" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				}
			}
			DrawText( hdc, TEXT( "." ), -1, &TIME[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
			ReleaseDC(hwnd,hdc);
			return 0;
			}
		case WM_PAINT:
			hdc = BeginPaint( hwnd, &ps ) ;
			GetClientRect( hwnd, &WindowRect ) ;

			SetTimer(hwnd,1,93,NULL);
			istime1=true;
			//��������
			SelectObject(hdc,TextFontS);
			SetBkColor(hdc,RGB(50,50,50));
			SetTextColor(hdc,RGB(255,255,255));

			SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(50,50,50)));
			SelectObject(hdc,CreateSolidBrush(RGB(50,50,50)));
			
			for(times=0;times<30;times++)
				Rectangle(hdc,TEXT30[times].left,TEXT30[times].top,TEXT30[times].right,TEXT30[times].bottom);
			/*Rectangle(hdc,85,150,135,250);
			Rectangle(hdc,150,150,200,250);
			Rectangle(hdc,215,150,265,250);
			Rectangle(hdc,280,150,330,250);
			Rectangle(hdc,345,150,395,250);
			Rectangle(hdc,410,150,460,250);
			Rectangle(hdc,475,150,525,250);
			Rectangle(hdc,540,150,590,250);
			Rectangle(hdc,605,150,655,250);
			Rectangle(hdc,670,150,720,250);
			Rectangle(hdc,735,150,785,250);
			Rectangle(hdc,800,150,850,250);
			Rectangle(hdc,865,150,915,250);
			Rectangle(hdc,930,150,980,250);*/
			for(times2=0;times2<30;times2++)
			{
				switch(num[times2])
				{
				case 0:DrawText( hdc, TEXT( "0" ), -1, &TEXT30[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 1:DrawText( hdc, TEXT( "1" ), -1, &TEXT30[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 2:DrawText( hdc, TEXT( "2" ), -1, &TEXT30[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 3:DrawText( hdc, TEXT( "3" ), -1, &TEXT30[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 4:DrawText( hdc, TEXT( "4" ), -1, &TEXT30[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 5:DrawText( hdc, TEXT( "5" ), -1, &TEXT30[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 6:DrawText( hdc, TEXT( "6" ), -1, &TEXT30[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 7:DrawText( hdc, TEXT( "7" ), -1, &TEXT30[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 8:DrawText( hdc, TEXT( "8" ), -1, &TEXT30[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 9:DrawText( hdc, TEXT( "9" ), -1, &TEXT30[times2], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				}
			}


			EndPaint( hwnd, &ps ) ;
			return 0;


		case WM_KEYDOWN:
			if(wParam==13)
			{
				part++;
				if(istime1)
				{
					KillTimer(hwnd,1);
					istime1=false;
				}
				InvalidateRect(hwnd,NULL,true);
				return 0;
			}
		}
	}
	if(part==5)
	{
		static int position=0;

		switch(message)
		{
		case WM_PAINT:
			Write(hwnd,false);
			hdc = BeginPaint( hwnd, &ps ) ;
			GetClientRect( hwnd, &WindowRect ) ;

			SelectObject(hdc,TextFontSS);
			SetBkColor(hdc,RGB(80,80,80));
			SetTextColor(hdc,RGB(255,255,255));
			for(times3=0;times3<3;times3++)
			{
				switch(digit[times3])
				{
				case 0:DrawText( hdc, TEXT( "0" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 1:DrawText( hdc, TEXT( "1" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 2:DrawText( hdc, TEXT( "2" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 3:DrawText( hdc, TEXT( "3" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 4:DrawText( hdc, TEXT( "4" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 5:DrawText( hdc, TEXT( "5" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 6:DrawText( hdc, TEXT( "6" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 7:DrawText( hdc, TEXT( "7" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 8:DrawText( hdc, TEXT( "8" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 9:DrawText( hdc, TEXT( "9" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				}
			}
			DrawText( hdc, TEXT( "." ), -1, &TIME[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;

			SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(50,50,50)));
			SelectObject(hdc,CreateSolidBrush(RGB(50,50,50)));
			
			for(times3=0;times3<30;times3++)
				Rectangle(hdc,TEXT30[times3].left,TEXT30[times3].top,TEXT30[times3].right,TEXT30[times3].bottom);

			SetTimer(hwnd,2,1000,NULL);
			istime2=true;

			EndPaint( hwnd, &ps ) ;
			return 0;

		case WM_TIMER:
			{
				hdc=GetDC(hwnd);
				SelectObject(hdc,TextFont5);
				SetBkColor(hdc,RGB(80,80,80));
				SetTextColor(hdc,RGB(255,255,255));
				for(times3=1000;times3>=1;times3/=10)
				{
					if(min_sec2<=0)
					{
						SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(80,80,80)));
						SelectObject(hdc,CreateSolidBrush(RGB(80,80,80)));
						Rectangle(hdc,450,280,550,320);
						istime2=false;
						KillTimer(hwnd,2);
						return 0;
					}
					if(min_sec2%100==99)
						min_sec2-=40;
					if(times3==1000)
						times4=0;
					switch((min_sec2/times3)%10)
					{
					case 0:DrawText( hdc, TEXT( "0" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 1:DrawText( hdc, TEXT( "1" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 2:DrawText( hdc, TEXT( "2" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 3:DrawText( hdc, TEXT( "3" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 4:DrawText( hdc, TEXT( "4" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 5:DrawText( hdc, TEXT( "5" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 6:DrawText( hdc, TEXT( "6" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 7:DrawText( hdc, TEXT( "7" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 8:DrawText( hdc, TEXT( "8" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 9:DrawText( hdc, TEXT( "9" ), -1, &MIN5[times4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					}
					times4++;
				}
				DrawText( hdc, TEXT( ":" ), -1, &MIN5[4], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;
				min_sec2--;
				ReleaseDC(hwnd,hdc);
				return 0;
			}
		case WM_KEYDOWN:
			{
			if(istime2)
				return 0;
			hdc=GetDC(hwnd);
			SelectObject(hdc,TextFontS);
			SetBkColor(hdc,RGB(50,50,50));
			SetTextColor(hdc,RGB(255,255,255));
			SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(50,50,50)));
			SelectObject(hdc,CreateSolidBrush(RGB(50,50,50)));
			if(wParam==13)
			{
				part++;
				InvalidateRect(hwnd,NULL,true);
				return 0;
			}
			if(wParam==8)
			{
				if(position==0)
					return 0;
				position--;
				input[position]=-1;
				Rectangle(hdc,TEXT30[position].left,TEXT30[position].top,TEXT30[position].right,TEXT30[position].bottom);
				return 0;
			}
			if(wParam>=48&&wParam<=57)
			{
				if(position>=30)
					return 0;
				switch(wParam)
				{
				case 48:input[position]=0;DrawText( hdc, TEXT( "0" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 49:input[position]=1;DrawText( hdc, TEXT( "1" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 50:input[position]=2;DrawText( hdc, TEXT( "2" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 51:input[position]=3;DrawText( hdc, TEXT( "3" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 52:input[position]=4;DrawText( hdc, TEXT( "4" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 53:input[position]=5;DrawText( hdc, TEXT( "5" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 54:input[position]=6;DrawText( hdc, TEXT( "6" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 55:input[position]=7;DrawText( hdc, TEXT( "7" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 56:input[position]=8;DrawText( hdc, TEXT( "8" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 57:input[position]=9;DrawText( hdc, TEXT( "9" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				}
			}

			else if(wParam>=96&&wParam<=105)
			{
				if(position>=30)
					return 0;
				switch(wParam)
				{
				case 96:input[position]=0;DrawText( hdc, TEXT( "0" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 97:input[position]=1;DrawText( hdc, TEXT( "1" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 98:input[position]=2;DrawText( hdc, TEXT( "2" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 99:input[position]=3;DrawText( hdc, TEXT( "3" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 100:input[position]=4;DrawText( hdc, TEXT( "4" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 101:input[position]=5;DrawText( hdc, TEXT( "5" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 102:input[position]=6;DrawText( hdc, TEXT( "6" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 103:input[position]=7;DrawText( hdc, TEXT( "7" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 104:input[position]=8;DrawText( hdc, TEXT( "8" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				case 105:input[position]=9;DrawText( hdc, TEXT( "9" ), -1, &TEXT30[position], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;position++;break;
				}
			}

			ReleaseDC(hwnd,hdc);
			return 0;
			}
		}
	}
	if(part==6)
	{
		switch(message)
		{
		case WM_PAINT:
			hdc = BeginPaint( hwnd, &ps ) ;
			GetClientRect( hwnd, &WindowRect ) ;

			SelectObject(hdc,TextFontSS);
			SetBkColor(hdc,RGB(80,80,80));
			SetTextColor(hdc,RGB(255,255,255));
			for(times3=0;times3<3;times3++)
			{
				switch(digit[times3])
				{
				case 0:DrawText( hdc, TEXT( "0" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 1:DrawText( hdc, TEXT( "1" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 2:DrawText( hdc, TEXT( "2" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 3:DrawText( hdc, TEXT( "3" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 4:DrawText( hdc, TEXT( "4" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 5:DrawText( hdc, TEXT( "5" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 6:DrawText( hdc, TEXT( "6" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 7:DrawText( hdc, TEXT( "7" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 8:DrawText( hdc, TEXT( "8" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 9:DrawText( hdc, TEXT( "9" ), -1, &TIME[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				}
			}
			DrawText( hdc, TEXT( "." ), -1, &TIME[3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;

			SelectObject(hdc,TextFontS);
			SelectObject(hdc,CreatePen(PS_SOLID,0,RGB(50,50,50)));
			SelectObject(hdc,CreateSolidBrush(RGB(50,50,50)));
			
			for(times3=0;times3<30;times3++)
				Rectangle(hdc,TEXT30[times3].left,TEXT30[times3].top,TEXT30[times3].right,TEXT30[times3].bottom);
	
			for(times3=0;times3<30;times3++)
			{
				if(input[times3]==-1)
					continue;
				if(input[times3]==num[times3])
				{
					SetBkColor(hdc,RGB(50,50,50));
					SetTextColor(hdc,RGB(0,255,0));
					switch(input[times3])
					{
					case 0:DrawText( hdc, TEXT( "0" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 1:DrawText( hdc, TEXT( "1" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 2:DrawText( hdc, TEXT( "2" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 3:DrawText( hdc, TEXT( "3" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 4:DrawText( hdc, TEXT( "4" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 5:DrawText( hdc, TEXT( "5" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 6:DrawText( hdc, TEXT( "6" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 7:DrawText( hdc, TEXT( "7" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 8:DrawText( hdc, TEXT( "8" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 9:DrawText( hdc, TEXT( "9" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					}
				}
				else
				{
					SetBkColor(hdc,RGB(50,50,50));
					SetTextColor(hdc,RGB(255,0,0));
					switch(input[times3])
					{
					case 0:DrawText( hdc, TEXT( "0" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 1:DrawText( hdc, TEXT( "1" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 2:DrawText( hdc, TEXT( "2" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 3:DrawText( hdc, TEXT( "3" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 4:DrawText( hdc, TEXT( "4" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 5:DrawText( hdc, TEXT( "5" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 6:DrawText( hdc, TEXT( "6" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 7:DrawText( hdc, TEXT( "7" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 8:DrawText( hdc, TEXT( "8" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					case 9:DrawText( hdc, TEXT( "9" ), -1, &TEXT30[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
					}
				}
			}
			SelectObject(hdc,TextFont5);
			SetBkColor(hdc,RGB(80,80,80));
			SetTextColor(hdc,RGB(255,255,255));
			for(times3=0;times3<30;times3++)
			{
				switch(num[times3])
				{
				case 0:DrawText( hdc, TEXT( "0" ), -1, &TEXT30S[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 1:DrawText( hdc, TEXT( "1" ), -1, &TEXT30S[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 2:DrawText( hdc, TEXT( "2" ), -1, &TEXT30S[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 3:DrawText( hdc, TEXT( "3" ), -1, &TEXT30S[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 4:DrawText( hdc, TEXT( "4" ), -1, &TEXT30S[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 5:DrawText( hdc, TEXT( "5" ), -1, &TEXT30S[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 6:DrawText( hdc, TEXT( "6" ), -1, &TEXT30S[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 7:DrawText( hdc, TEXT( "7" ), -1, &TEXT30S[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 8:DrawText( hdc, TEXT( "8" ), -1, &TEXT30S[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				case 9:DrawText( hdc, TEXT( "9" ), -1, &TEXT30S[times3], DT_SINGLELINE | DT_CENTER | DT_VCENTER ) ;break;
				}
			}

			EndPaint( hwnd, &ps ) ;
			return 0;
		}
		
	}

	return DefWindowProc( hwnd, message, wParam, lParam ) ;        //DefWindowProc���������Զ������Ϣ������û�д�������Ϣ
}

























int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow )
{
	static TCHAR szAppName[] = TEXT("MyWindow") ;
	HWND hwnd ;
	MSG msg ;
	WNDCLASS wndclass ;        //����һ�����������

	//����Ϊ���������wndclass������
	wndclass.style = CS_HREDRAW | CS_VREDRAW ;                         //������ʽ
	wndclass.lpszClassName = szAppName ;                               //��������
	wndclass.lpszMenuName = NULL ;                                     //���ڲ˵�:��
	wndclass.hbrBackground = CreateSolidBrush(RGB(80,80,80)) ;    //���ڱ�����ɫ
	wndclass.lpfnWndProc = WndProc ;                                   //���ڴ�����
	wndclass.cbWndExtra = 0 ;                                          //����ʵ����չ:��
	wndclass.cbClsExtra = 0 ;                                          //��������չ:��
	wndclass.hInstance = hInstance ;                                   //����ʵ�����
	wndclass.hIcon = LoadIcon( NULL, IDI_APPLICATION ) ;               //������С��ͼ��:ʹ��ȱʡͼ��
	wndclass.hCursor = LoadCursor( NULL, IDC_ARROW ) ;                 //���ڲ��ü�ͷ���

	if( !RegisterClass( &wndclass ) )
	{    //ע�ᴰ����, ���ע��ʧ�ܵ���������ʾ
		MessageBox( NULL, TEXT("����ע��ʧ��!"), TEXT("����"), MB_OK | MB_ICONERROR ) ;
		return 0 ;
	}

	hwnd = CreateWindow(                   //��������
		szAppName,                 //��������
		TEXT("REM"),           //���ڱ���
		WS_POPUP,       //���ڵķ��
		0,             //���ڳ�ʼ��ʾλ��x:ʹ��ȱʡֵ
		0,             //���ڳ�ʼ��ʾλ��y:ʹ��ȱʡֵ
		1000,             //���ڵĿ��:ʹ��ȱʡֵ
		400,             //���ڵĸ߶�:ʹ��ȱʡֵ
		NULL,                      //������:��
		NULL,                      //�Ӳ˵�:��
		hInstance,                 //�ô���Ӧ�ó����ʵ����� 
		NULL                       //
	) ;

	ShowWindow( hwnd, iCmdShow ) ;        //��ʾ����
	UpdateWindow( hwnd ) ;                //���´���

	while( GetMessage( &msg, NULL, 0, 0 ) )        //����Ϣ�����л�ȡ��Ϣ
	{
		TranslateMessage( &msg ) ;                 //���������Ϣת��Ϊ�ַ���Ϣ
		DispatchMessage( &msg ) ;                  //�ַ����ص�����(���̺���)
	}
	return msg.wParam ;
}