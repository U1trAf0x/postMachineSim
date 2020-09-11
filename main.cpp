#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
using namespace std;

// This is Post machine simulator made by
// Strizhkin Denis for studying purposes
// 11th September 2020

// Funtion declaration
void programmStart(string &str, vector <string> &prog, int &j, ifstream &file);
void print(string &s, int &j, int &step);
void outLoaded(string &str, vector <string> &prog, int &j);

int main()
{
	// variables declaration/initialization
	string str = "";
	vector <string> prog;
	int j, step = 1;
	ifstream file;
	file.open("prog");

	// get variable values;
	programmStart(str, prog, j, file);

	// output loaded values;
	outLoaded(str, prog, j);

	// start programm and initialize/declare some variables
	int i = 0;
	char type;
	while (j >= 0 & j < str.size()) 
	{
		print(str, j, step);
		step++;
		type = prog[i][0];
		switch (type) {
			case 'L':
				j--;
				i = stoi(prog[i].substr(1));
				break;
			case 'R':
				j++;
				i = stoi(prog[i].substr(1));
				break;
			case '1':
				str.replace(j, 1, "1");
				i = stoi(prog[i].substr(1));
				break;
			case '0':
				str.replace(j, 1, "0");
				i = stoi(prog[i].substr(1));
				break;
			case '?':
				{
					int indOfQ = prog[i].find('?');
					int indOfS = prog[i].find(',');
					if (str[j] == '1')
						i = stoi(prog[i].substr(indOfQ + 1, indOfS - indOfQ));
					else
						i = stoi(prog[i].substr(indOfS + 1));
				}
				break;
			case 's':
				cout << "Programm have finished\n\n";
				return 0;
			default:
				cout << "Error: Unexpected symbol\n\n";
                                return 0;
		}
		this_thread::sleep_for(1s);
	}
	cout << "Programm have finished\n\n";
	return 0;
}

void programmStart(string &str, vector <string> &prog, int &j, ifstream &file)
{
	cout << "This is Post machine simulator made by\nStrizhkin Denis for studying purposes\n11th September 2020\n***\n\n";
	string temp;
	getline(file, temp);
	while (temp != "progEnd")
	{
		int indOfCB = temp.find(')');
                prog.push_back(temp.substr(indOfCB + 1));
                getline(file, temp);
	}
	cout << "prog ok\n";
	getline(file, str);
	cout << "str ok\n";
	getline(file, temp);
	j = stoi(temp.substr(2));
	cout << "j ok\n***\n\n";
	cout << "prog file have been loaded\n***\n\n";
}

void outLoaded(string &str, vector <string> &prog, int &j)
{
	cout << "Current programm:\n";
	for (auto line : prog)
		cout << line + "\n";
	cout << "Current string:\n" << str + "\n" << "Current J:\n" << j << "\n***\n\n";	
}

void print(string &str, int &j, int &step)
{
	cout << "This is step #" << step << "\n" + str + "\n";
	for (int i = 0; i < j; i++)
		cout << ' ';
	cout << "^\n***\n\n";
}
