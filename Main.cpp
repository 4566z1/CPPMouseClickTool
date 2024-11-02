#define _CRT_SECURE_NO_WARNINGS
#include "Main.h"

DWORD THREAD_MAX = NULL;
DWORD TIME_SLEEP = NULL;

// 鼠标连点事件
UINT CALLBACK MouseEvent(LPVOID) {
	// 模拟鼠标
	while (1) {
		if (FLAG == TRUE)
			break;
		mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
		mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
		if(TIME_SLEEP != 0)
			Sleep(TIME_SLEEP);
	}
	return 0;
}

int main() {
/*-------------------------------------------------------------------------------*/

	R:
	// 编辑主界面
	system("color 04");
	std::cout << "\t\t|------------------------------------------|" << endl;
	std::cout << "\t\t|                鼠标连点器                |" << endl;
	std::cout << "\t\t|                BY 4566Z1                 |" << endl;
	std::cout << "\t\t|                Version 3.0               |" << endl;
	std::cout << "\t\t|------------------------------------------|" << endl;
	std::cout << "[!] 注意事项 计算机能识别的有效点击 最多也就是百次左右每秒" << endl;
	std::cout << "[!] 理论上该程序可以达到上万次每秒, 但是计算机无法识别" << endl;
	std::cout << "[*] 如果延迟为0 则开启暴力模式(卡顿)" << endl;
	std::cout << "[*] 设置鼠标击键延迟: ";
	scanf("%d", &TIME_SLEEP);	// 等待用户输入
	std::cout << "[*] 设置线程数: ";
	scanf("%d", &THREAD_MAX);	// 等待用户输入
	rewind(stdin);	// 刷新输入缓存区， 妈的智障fflush现在不能用了
	if (TIME_SLEEP < 0|| THREAD_MAX <= 0) {
		system("cls");
		std::cout << "[!] 输入不合法." << endl;
		Sleep(2000);
		goto R;
	}

/*-------------------------------------------------------------------------------*/
	system("cls");
	// 分配内存
	ThreadPool *ThreadPool1 = new ThreadPool;

	// 初始化线程池
	ThreadPool1->InitThreadPool(THREAD_MAX, MouseEvent);
	cout << "[*] 请等待线程全部加载完毕.." << endl;
	Sleep(2000);

T:
	system("cls");
	cout << "[*]  TAB 开始连点   " << endl
		<< "[*] 鼠标右键取消连点 " << endl
		<< "[*]   ESC 退出程序   " << endl
		<< "[-] 当前线程上线: " << THREAD_MAX << endl;
	while (1) {
		if (GetKeyState(VK_ESCAPE) < 0) {
			delete ThreadPool1;	// 删除 类对象 调用析构函数
			goto EXIT;
		}
		if (GetKeyState(VK_TAB) < 0)
			break;
		Sleep(1);	// 防止占用 CPU 时间片
	}

	ThreadPool1->StartThreadPool();	// 唤醒线程

	std::cout << "[*] 线程工作中.." << endl;
	while (1) {
		if (GetKeyState(VK_ESCAPE) < 0) {
			delete ThreadPool1;	// 删除 类对象 调用析构函数
			goto EXIT;
		}
		if (GetKeyState(VK_RBUTTON) < 0)
			break;
		Sleep(1);   // 防止占用 CPU 时间片
	}

	ThreadPool1->SuspendThreadPool();
	cout << "[*] 正在挂起线程.." << endl;
	Sleep(1000);
	goto T;
	EXIT:
	return 0;
}