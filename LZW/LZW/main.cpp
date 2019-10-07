#include<stdio.h>
#include<iostream>
#include<map>
#include<string>
#include<list>
#define N 1000
using namespace std;

list<int> encodeResult;
list<string> decodeResult;
class map_value_finder
{
public:
	map_value_finder(const std::string &cmp_string) :m_s_cmp_string(cmp_string) {}
	bool operator ()(const std::map<int, std::string>::value_type &pair)
	{
		return pair.second == m_s_cmp_string;
	}
private:
	const std::string &m_s_cmp_string;
};

class LZW{
public:
	char encodestr[N];
	int decodelist[N];
	int idlecode = 256;
	map<int, string> dictionary;//´Êµä
	
	LZW() {
		encodestr[0] = '\0';
		for (int i = 0; i < N; i++) {
			this->decodelist[i] = INT_MAX;
		}
	}

	void initDic() {//³õÊ¼»¯×Öµä
		for (int i = 0; i < 256; i++) {
			dictionary.insert(pair<int,string>(i, (char)i + ""));
		}
	}

	int isContain(map<int,string> dic, string s) {
		map<int, string>::iterator it;
		for (it = dic.begin(); it != dic.end(); it++) {
			if (it->second == s) {
				return it->first;
			}
			else {
				return -1;
			}   
		}
	}

	void encode() {
		string P = "";//Ç°×º
		string C = "";//ºó×º
		int temp;
		for (int i = 0; i < strlen(encodestr);i++) {
			C = P + encodestr[i];
			temp = isContain(dictionary, C);
			if ( temp > -1) {
				P = C;
			}
			else {
				dictionary.insert(pair<int,string>(idlecode,C));
				encodeResult.push_back(isContain(dictionary,P));
				P = "" + encodestr[i];
			}
		}
		if (P!="") {
			encodeResult.push_back(isContain(dictionary,P));
		}
	}

};
void main() {
	LZW lzw;
	cin >> lzw.encodestr;
	lzw.encode();
	while (!encodeResult.empty()) {
		cout << encodeResult.front();
		encodeResult.pop_front();
	}
	system("pause");
}