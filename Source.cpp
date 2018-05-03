#include <C:\Users\Антон\Documents\Visual Studio 2015\Projects\CouchDBex\packages\curl.7.30.0.2\build\native\include\curl\curl.h>
#include <C:\Users\Антон\Documents\Visual Studio 2015\Projects\CouchDBex\packages\curl.7.30.0.2\build\native\lib\v110\x64\Release\dynamic\libcurl.lib>
#include <windows.h>
#include "resource.h"

/*int main()
{
	
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	

	if (curl) 
	{ 

				
		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.0.1:5984/words/all_docs" );

		curl_easy_setopt(curl, CURLOPT_HEADER, 1);

		curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, "admin:12345");
		for (int)
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.0.1:5984/words/all_docs");
		curl_easy_cleanup(curl);
	}

	return 0;
}*/
BOOL CALLBACK Dlgproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	char str1[1000] = "abc\nabcdefb\nfbjsbjsbhlsdbjhdsbjdb";
	char str2[1000];

	for (int i = 0; i < strlen(str1); i++)
	{
		str2[i] = str1[strlen(str1) - i - 1];
	}
	str2[strlen(str1)] = str1[strlen(str1)];
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			MessageBox(hwnd, "Принято", "OK", MB_OK);
			break;
		case IDWORD:
			MessageBox(hwnd, str1, "Word", MB_OK);
			break;
		case IDREV:
			MessageBox(hwnd, str2, "Reverse", MB_OK);
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

