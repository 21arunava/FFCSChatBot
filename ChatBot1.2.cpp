

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <stdlib.h>

using namespace std;

const int MAX_RESP = 3;
const string delim = "?!.;,";

//typedef vector<string> vstring;

vector<string> find_match( string input);
void copy(char *array[], vector<string> &v);
void preprocess_input(string &str);
void UpperCase( string &str );
void cleanString(string &str);
bool isPunc(char c);

typedef struct {
	char *input;
	char *responses[MAX_RESP];
}record;

record KnowledgeBase[] = {
	{"WHAT IS YOUR NAME",
	{"MY NAME IS CHATTERBOT2.",
	 "YOU CAN CALL ME CHATTERBOT2.",
	 "WHY DO YOU WANT TO KNOW MY NAME?"}
	},

	{"HI",
	{"HI THERE!",
	 "HOW ARE YOU?",
	 "HI!"}
	},

	{"HOW ARE YOU",
	{"I'M DOING FINE!",
	"I'M DOING WELL AND YOU?",
	"WHY DO YOU WANT TO KNOW HOW AM I DOING?"}
	},

	{"WHO ARE YOU",
	{"I'M AN A.I PROGRAM.",
	 "I THINK THAT YOU KNOW WHO I'M.",
	 "WHY ARE YOU ASKING?"}
	},

	{"ARE YOU INTELLIGENT",
	{"YES,OFCORSE.",
	 "WHAT DO YOU THINK?",
	 "ACTUALY,I'M VERY INTELLIENT!"}
	},

	{"ARE YOU REAL",
	{"DOES THAT QUESTION REALLY MATERS TO YOU?",
	 "WHAT DO YOU MEAN BY THAT?",
	 "I'M AS REAL AS I CAN BE."}
	}
};

size_t nKnowledgeBaseSize = sizeof(KnowledgeBase)/sizeof(KnowledgeBase[0]);


int main()
{
	srand((unsigned) time(NULL));

	string sInput = "";
	string sResponse = "";
	string sPreviousResponse = "";

	while(1) {
		cout << ">";
		sPreviousResponse = sResponse;
		getline(cin, sInput);
		preprocess_input(sInput);
		vector<string> responses = find_match(sInput);
		if(sInput == "BYE") {
			cout << "IT WAS NICE TALKING TO YOU USER, SEE YOU NEXT TIME!" << endl;
			break;
		} else if(responses.size() == 0) {
			cout << "I'M NOT SURE IF I UNDERSTAND WHAT YOU ARE TALKING ABOUT." << endl;
		} else {
			int nSelection = rand() % MAX_RESP;
			sResponse = responses[nSelection];
			// avoids repeating the same response
			if(sResponse == sPreviousResponse) {
				responses.erase(responses.begin() + nSelection);
				nSelection = rand() % responses.size();
				sResponse = responses[nSelection];
			}
			cout << sResponse <<endl;
		}
	}

	return 0;
}

void preprocess_input(string &str) {
	cleanString(str);
	UpperCase(str);
}

vector<string> find_match(string input) {
	vector<string> result;
	for(int i = 0; i < nKnowledgeBaseSize; ++i) {
		if(string(KnowledgeBase[i].input) == input) {
			copy(KnowledgeBase[i].responses, result);
			return result;
		}
	}
	return result;
}

void copy(char *array[], vector<string> &v) {
	for(int i = 0; i < MAX_RESP; ++i) {
		v.push_back(array[i]);
	}
}

void UpperCase( string &str ) {
	int len = str.length();
	for( int i = 0; i < len; i++ ) {
		if ( str[i] >= 'a' && str[i] <= 'z' ) {
			str[i] -= 'a' - 'A';
		}
	}
}

bool isPunc(char c) {
	return delim.find(c) !=string::npos;
}

void cleanString( string &str ) {
	int len = str.length();
	string temp = "";

	char prevChar = 0;

	for(int i = 0; i < len; ++i) {
		if( (str[i] == ' ' && prevChar != ' ') || !isPunc(str[i]) ) {
			temp += str[i];
			prevChar = str[i];
		}
		else if(prevChar != ' ' && isPunc(str[i])) {
			temp += ' ';
		}
	}
	str = temp;
}
