#include <curl.7.30.0.2\build\native\include\curl\curl.h>
#include <curl.7.30.0.2\build\native\lib\v110\x64\Release\dynamic\libcurl.lib>
#include <windows.h>
#include "resource.h"


char str1[1000000];
char str2[1000000];
char str3[1000000];

void Processing()
{
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
		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.0.1:5984/words/all_docs");

		curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, "admin:12345");

		curl_easy_setopt(curl, CURLOPT_READDATA, &str3);

		curl_easy_cleanup(curl);

	}

	Processing();

	return;
}
void Reverse()
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.0.1:5984/words/all_docs");

		curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, "admin:12345");

		curl_easy_setopt(curl, CURLOPT_READDATA, &str3);

		curl_easy_cleanup(curl);
	}

	Processing();

	return;
}

BOOL CALLBACK Dlgproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			MessageBox(hwnd, "Accepted", "OK", MB_OK);
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

