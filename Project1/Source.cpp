#include <iostream>
#include <string>
#include <vector>
using namespace std;



vector<int> getSpaces(string* str)
{
	vector<int> arr {};

	int offset = 0;
	while(true)
	{
		offset = str->find(' ', ++offset);

		if(offset == string::npos)
			break;


		arr.push_back(offset);
	}

	return arr;
}



void handleString(string* str)
{
	auto indexes = getSpaces(str);

	int i = 0;
	while(str->length() % 60 != 0)
	{
		string::const_iterator it = str->begin() + indexes[i];
		str->insert(it, ' ');

		for(int j = i; j < indexes.size(); ++j)
			++indexes[j];

		if(++i == indexes.size())
			i = 0;
	}
}



int main()
{
	string hello = "vo pole beryoza stoyala";
	string hello2 = "vo pole kudravaya stoyala";
	string hello3 = "luli luli stoyala";
	string hello4 = "vipila 100 gramm i upala";

	handleString(&hello);
	handleString(&hello2);
	handleString(&hello3);
	handleString(&hello4);

	cout << hello << endl;
	cout << hello2 << endl;
	cout << hello3 << endl;
	cout << hello4 << endl;


	cout << endl;
	system("pause");
	return 0;
}