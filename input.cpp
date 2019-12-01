#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
void setUpdatabase(string word, int i){
	cout<<word<<"	"<<i<<endl;
}

int main()
{
	vector<string> Twits;      
	char line[300];
	int i = 0;
	ifstream myfile ("abcnews-date-text.csv");
	if (myfile.is_open())
  	{
    	while ( myfile.getline(line, 300, '\n') )
    	{
      		//cout << line << '\n';
      		Twits.push_back(line);
      		//char * str = new char [line.length()+1];;
      		//strcpy (str, line.c_str());
      		char * rest = line;
      		char * p;
      		while ((p = strtok_r(rest, " ,.?!:;-", &rest)))
      		{
      			setUpdatabase(p,i);
      			//cout<<p<<"	"<<i<<endl;
      		}
  			i++;
    	}
    	myfile.close();
  	}

  	else cout << "Unable to open file"; 

  	return 0;
}