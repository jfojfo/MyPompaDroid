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
			//以FrameSize == DesignResolutionSize时的坐标设定
			CCPoint pt = CCPointZero;
			switch (wParam)
			{
			case 'A':   //向左
				{
					pt = ccp(25, 255);
				}
				break;
			case 'D':   //向右
				{
					pt = ccp(95, 256);
				}
				break;
			case 'W':   //向上
				{
					pt = ccp(63, 214);
				}
				break;
			case 'S':   //向下
				{
					pt = ccp(62, 290);
				}
				break;
			case 'J':   //攻击
				{
					pt = ccp(367, 277);
				}
				break;
			case 'K':   //跳跃
				{
					pt = ccp(445, 247);
				}
				break;
			default:
				return 0;
			}
			if (GetKeyState('D') & 0x8000)
			{
				if (GetKeyState('W') & 0x8000)      //右上角
				{
					pt = ccp(91, 227);
				}
				else if (GetKeyState('S') & 0x8000) //右下角
				{
					pt = ccp(91, 284);
				}
			}
			else if (GetKeyState('A') & 0x8000)
			{
				if (GetKeyState('W') & 0x8000)      //左上角
				{
					pt = ccp(36, 227);
				}
				else if (GetKeyState('S') & 0x8000) //左下角
				{
					pt = ccp(36, 284);
				}
			}

			CCEGLView* eglView = CCEGLView::sharedOpenGLView();
			CCSize originalDesignResolutionSize = CCSizeMake(480, 320);     //原始的设计分辨率大小
			ResolutionPolicy eResolutionPolicy = kResolutionFixedWidth;     //分辨率策略
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