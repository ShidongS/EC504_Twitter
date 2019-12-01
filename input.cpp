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
	string line;
	int i = 0;
	ifstream myfile ("SampleInputForProject.txt");
	if (myfile.is_open())
  	{
    	while ( getline (myfile,line) )
    	{
      		//cout << line << '\n';
      		Twits.push_back(line);
      		char * str = new char [line.length()+1];;
      		strcpy (str, line.c_str());
      		char * rest = str;
      		char * p;
      		while ((p = strtok_r(rest, " ,.?!:;", &rest)))
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