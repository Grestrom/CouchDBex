#include <curl.7.30.0.2\build\native\include\curl\curl.h>
#include <windows.h>
#include "resource.h"


char str1[1000000];
char str2[1000000];
char str3[1000000];
char k[] = "k";
char dd[] = ":";
void ProcessingWR()
{
	//сделать в правильном формате ввод из строки 1 и засунуть в строку 2
	//придумать как делать ид
	return;
}

void ProcessingR()
{
	int c = 0;
	int i = strcspn(str3, k)+6;
	for (int j = 0; j < str3[strcspn(str3, dd)+1]-'0';j++)
	{
		int dl = 0;
		while (str3[i] != '\"')
		{
			str1[c] = str3[i];
			c++;
			i++;
			dl++;
		}
		str1[c] = '\n';
		c++;
		i += 17+ strcspn(str3, k)+6;
	}
	return;
}

void Write()
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();


	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.0.1:5984/words/all_docs");

		curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, "admin:12345");
		
		ProcessingWR();
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str2);

		curl_easy_cleanup(curl);
	}
	return;
}

void Word()
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();


	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.0.1:5984/words/_design/view2/_view/view2");

		curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, "admin:12345");

		curl_easy_setopt(curl, CURLOPT_READDATA, &str3);

		curl_easy_cleanup(curl);

	}

	ProcessingR();

	return;
}
void Reverse()
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.0.1:5984/words/_design/view1/_view/view1");

		curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, "admin:12345");

		curl_easy_setopt(curl, CURLOPT_READDATA, &str3);

		curl_easy_cleanup(curl);
	}

	ProcessingR();

	return;
}

HWND hs1;
char text[] = {"Type the word..."};
BOOL CALLBACK Dlgproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) //готово
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		hs1 = GetDlgItem(hwnd, IDS1);
		SendMessage(hs1, WM_SETTEXT, 0, (LPARAM)text);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			SendMessage(hs1, WM_GETTEXT, (WPARAM)255, (LPARAM)str1);
			SendMessage(hs1, WM_SETTEXT, 0, (LPARAM)text);
			Write();
			MessageBox(hwnd, str1, "OK", MB_OK);
			break;
		case IDWORD:
			Word();
			MessageBox(hwnd, str1, "Word", MB_OK);
			break;
		case IDREV:
			Reverse();
			MessageBox(hwnd, str1, "Reverse", MB_OK);
			break;
		case IDEXIT:
			EndDialog(hwnd, 0);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		return FALSE;
	}
	return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (Dlgproc), 0);
	return 0;
}

