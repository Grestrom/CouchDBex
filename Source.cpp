#include <curl.7.30.0.2\build\native\include\curl\curl.h>
#include <windows.h>
#include "resource.h"
#include <time.h> 


char str1[1000000];
char str2[1000000];
char str3[1000000];
char obor[1000000];
char id[11];
char k[] = "k";
char dd[] = ":";
char WR1[] = "{\"id\"\:\"";
char WR2[] = "\"word\"\:\"";
char WR3[] = "\",\"change\"\:\"";
char WR4[] = "\"}";
void idmaker()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{

		id[i] = rand()%10-'0';
	}
	return;
}
void Oborot()
{
	for (int i = 0; i < strlen(str1); i++)
	{
		obor[i] = str1[strlen(str1) - i - 1];
	}
	obor[strlen(str1)] = str1[strlen(str1)];
}

void ProcessingWR()
{
	idmaker();
	Oborot();
	str2[0] = k[1];
	strcat(str2, WR1);
	strcat(str2, id);
	strcat(str2, WR2);
	strcat(str2, str1);
	strcat(str2, WR3);
	strcat(str2, obor);
	strcat(str2, WR4);
	//str2 = WR1+id+WR2+s1+WR3+obor+WR4
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
		i += 40+dl; 
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
BOOL CALLBACK Dlgproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
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

