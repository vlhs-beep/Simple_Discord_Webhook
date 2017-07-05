// Simple Webhook
// Webhooks are a low-effort way to post messages to channels in Discord. They do not require a bot user or authentication to use.

#include <iostream>
#include <fstream>
#include <sstream>
#include <CkHttpRequestW.h>
#include <CkHttpW.h>
#include <CkHttpResponseW.h>

using namespace std;

void main(void)
{
	CkHttpRequestW req;
	CkHttpW http;

	bool success;

	//  Any string unlocks the component for the 1st 30 days.
	success = http.UnlockComponent(L"Anything for 30-day trial");
	if (success != true) {
		wprintf(L"%s\n", http.lastErrorText());
		return;
	}

	// Load the message from a file.
	std::ifstream file("data/text/message.txt");
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string str = buffer.str();
	std::cout << str;
	// String To WString
	wstring wsTmp(str.begin(), str.end());
	// Convert to const WCHAR*
	const wchar_t * discordMessage = wsTmp.c_str();
	//  The following "Accept" header may be set, but it really isn't necessary:
	http.SetRequestHeader(L"Accept", L"application/json");

	const wchar_t *jsonText = discordMessage;

	CkHttpResponseW *resp = 0;
	resp = http.PostJson2(L"https://discordapp.com/api/webhooks/332031657810853888/T0ZGSMUw7OlIly2-mKpSnXbO-XA0ZuL-dt8V5ycc9l9WI4yni1kFNbE7fG_F4r_g5TdA", L"application/json", jsonText);
	if (resp == 0) {
		wprintf(L"%s\n", http.lastErrorText());
	}
	else {
		//  Display the JSON response.
		wprintf(L"%s\n", resp->bodyStr());
		delete resp;
	}
}
