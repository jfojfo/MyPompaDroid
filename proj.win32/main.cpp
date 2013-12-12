#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

LRESULT myWndProcHook(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("MyPompaDroid");
    eglView->setFrameSize(480, 320);
	eglView->setWndProc(myWndProcHook);
    return CCApplication::sharedApplication()->run();
}

LRESULT myWndProcHook(UINT message, WPARAM wParam, LPARAM lParam, BOOL* pProcessed)
{
	switch (message)
	{
	case WM_KEYDOWN:
	case WM_KEYUP:
		{
			//��FrameSize == DesignResolutionSizeʱ�������趨
			CCPoint pt = CCPointZero;
			switch (wParam)
			{
			case 'A':   //����
				{
					pt = ccp(25, 255);
				}
				break;
			case 'D':   //����
				{
					pt = ccp(95, 256);
				}
				break;
			case 'W':   //����
				{
					pt = ccp(63, 214);
				}
				break;
			case 'S':   //����
				{
					pt = ccp(62, 290);
				}
				break;
			case 'J':   //����
				{
					pt = ccp(367, 277);
				}
				break;
			case 'K':   //��Ծ
				{
					pt = ccp(445, 247);
				}
				break;
			default:
				return 0;
			}
			if (GetKeyState('D') & 0x8000)
			{
				if (GetKeyState('W') & 0x8000)      //���Ͻ�
				{
					pt = ccp(91, 227);
				}
				else if (GetKeyState('S') & 0x8000) //���½�
				{
					pt = ccp(91, 284);
				}
			}
			else if (GetKeyState('A') & 0x8000)
			{
				if (GetKeyState('W') & 0x8000)      //���Ͻ�
				{
					pt = ccp(36, 227);
				}
				else if (GetKeyState('S') & 0x8000) //���½�
				{
					pt = ccp(36, 284);
				}
			}

			CCEGLView* eglView = CCEGLView::sharedOpenGLView();
			CCSize originalDesignResolutionSize = CCSizeMake(480, 320);     //ԭʼ����Ʒֱ��ʴ�С
			ResolutionPolicy eResolutionPolicy = kResolutionFixedWidth;     //�ֱ��ʲ���
			CCSize obDesignResolutionSize = eglView->getDesignResolutionSize();
			int offsetWidth = obDesignResolutionSize.width - originalDesignResolutionSize.width;
			int offsetheight = obDesignResolutionSize.height - originalDesignResolutionSize.height;
			CCSize obScreenSize = eglView->getFrameSize();
			int offsetWidth2 = obScreenSize.width - originalDesignResolutionSize.width;
			int offsetheight2 = obScreenSize.height - originalDesignResolutionSize.height;
			switch (eResolutionPolicy)
			{
			case kResolutionExactFit:
				{
					//...
				}
				break;
			case kResolutionNoBorder:
				{
					//...
				}
				break;
			case kResolutionShowAll:
				{
					pt.x += offsetWidth2 / 2;
					pt.y += offsetheight2 / 2;
				}
				break;
			case kResolutionFixedHeight:
				{
					//...
				}
				break;
			case kResolutionFixedWidth:
				{
					pt.y += offsetheight;
				}
				break;
			}

			pt.x *= eglView->getScaleX();
			pt.y *= eglView->getScaleY();

			int id = wParam;
			if (message == WM_KEYDOWN)
			{
				eglView->handleTouchesBegin(1, &id, &pt.x, &pt.y);
			}
			else
			{
				eglView->handleTouchesEnd(1, &id, &pt.x, &pt.y);
			}

			*pProcessed = TRUE;
		}
		break;
	}

	return 0;
}