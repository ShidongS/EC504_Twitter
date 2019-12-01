#include<iostream>
#include<sstream>
#include<vector>
#include<map>
#include<string>
#include <algorithm>
#include <iterator>


using namespace std;

bool TestMode = true; // Print database out.

struct SentNode{
	int SentNo;
	int count;
	//string sent;

	SentNode(int i){
		SentNo = i;
		count = 0;
		//sent = "";
	}
};

class myDatabase{
private:
	map<string, map<int,int> > Database;
	/*
		In each database node:
		{
			string: word;
			map:
			{
				int #OfSentence;
				int #HappenInSentence;
			}
		}
	*/

public:
	void setUpDatabase(string word, int i);
	void searchWord(string word, vector<SentNode> &SentArr);
	void printAll();
};

void Initialization(int sentCount, vector<SentNode> &SentArr);
void searchSent(string Sent, vector<SentNode> &SentArr, int sentCount, myDatabase myDB);

/*-------------HEAP---------------*/
int compareNode(vector<SentNode> &SentArr, int i, int j);
//void swap(vector<SentNode> &SentArr, int i, int j);
void maxHeapify(vector<SentNode> &SentArr, int n, int i);
void Heapify(vector<SentNode> &SentArr, int n);
void CheckHeapOrder(vector<SentNode> &SentArr,int n);
void HeapSort(vector<SentNode> &SentArr, int n);
/*------------END_HEAP-------------*/

void printTenSent(vector<SentNode> &SentArr, int n, vector<string> sents);
void printAllNode(vector<SentNode> &SentArr, vector<string> sents);

int main(){

	myDatabase myDB;
	vector<string> sents;

	int sentCount;

	// INSERT WORDS
	myDB.setUpDatabase("word",2);
	
	if(TestMode) myDB.printAll();
/*
	string sent;
	cin>>sent;

	vector<SentNode> SentArr;

	if(sentCount==0) {
		cout<<"No sentences read, please check your input\n";
		return -1;
	}

	Initialization(sentCount, SentArr);

	searchSent(sent, SentArr, sentCount, myDB);

	if(TestMode){ 
		cout<<"-----------Before Heap Sort----------------\n";
		printAllNode(SentArr, sents);
	}

	HeapSort(SentArr, sentCount);

	if(TestMode){ 
		cout<<"-----------After Heap Sort----------------\n";
		printAllNode(SentArr, sents);
	}
	
	cout<<"--------------Results----------------\n";

	printTenSent(SentArr, sentCount, sents);
*/
	return 0;
}

void printTenSent(vector<SentNode> &SentArr, int n, vector<string> sents){
	for(int i = n; i > (n-10)&& i > 0; i--){
		cout<<sents[SentArr[i].SentNo]<<endl;
	}
}

void printAllNode(vector<SentNode> &SentArr, vector<string> sents){
	for(vector<SentNode>::iterator it = SentArr.begin(); it != SentArr.end(); it++){
		cout<<"--------------"<<endl;
		cout<<it.SentNo<<" "<<it.count<<endl;
		cout<<sents[it.SentNo]<<endl;
	}
}

void myDatabase::printAll(){

	for(map<string, map<int,int> >::iterator it = Database.begin(); it != Database.end();it++){
		cout<<it->first<<endl;
		for(map<int,int>::iterator it1 = it->second.begin(); it1 != it->second.end();it1++){
			cout<<it1->first<<" "<<it1->second<<endl;
		}
	}
}

void myDatabase::setUpDatabase(string word, int i){
	map<string, map<int,int> >::iterator it;
	it = Database.find(word);

	if(it==Database.end()){
		map<int, int> inner;
		inner.insert(std::make_pair(i, 1));
		Database.insert(std::make_pair(word, inner));
	}
	else{
		map<int, int>::iterator innerIt;
		innerIt = it->second.find(i);
		if(innerIt != it->second.end()){
			innerIt->second++;
		}
		else{
			it->second.insert(std::make_pair(i, 1));
		}
	}
}

void myDatabase::searchWord(string word, vector<SentNode> &SentArr){
	map<string, map<int,int> >::iterator it;
	it = Database.find(word);

	for(map<int,int>::iterator it1=it->second.begin(); it1!= it->second.end(); it1++){
		SentArr[it1->first].count += it1->second;
	}
}

void Initialization(int sentCount, vector<SentNode> &SentArr){
	if(SentArr.size()==0)
		for(int i = 0; i <= sentCount; i++){  // SentNode(0) is used to make index start from 1
			SentNode tmp = SentNode(i);
			SentArr.push_back(tmp);
		}
	else
		for(int i = 0; i <= sentCount; i++){  // SentNode(0) is used to make index start from 1
			SentArr[i].SentNo = i;
			SentArr[i].count = 0;
		}
}

void searchSent(string Sent, vector<SentNode> &SentArr, int sentCount, myDatabase myDB){
	Initialization(sentCount, SentArr);
	Sent = "Somewhere down the road";
    istringstream iss(Sent);

    do
    {
        string subs;
        iss >> subs;
        myDB.searchWord(subs,SentArr);
    } while (iss);

}



/*-------------HEAP---------------*/


int compareNode(vector<SentNode> &SentArr, int i, int j){
	if(SentArr[i].count<SentArr[j].count){
		return -1;
	}
	else if(SentArr[i].count==SentArr[j].count){
		return 0;
	}
	else{
		return 1;
	}
}
/*
void swap(vector<SentNode> &SentArr, int i, int j){
	int tmpNo;
	int tmpCount;
	string tmpStr;

	tmpNo = SentArr[i].SentNo;
	tmpCount = SentArr[i].count;
	tmpStr = SentArr[i].sent;

	SentArr[i].SentNo = SentArr[j].SentNo;
	SentArr[i].count = SentArr[j].count;
	SentArr[i].sent = SentArr[j].sent;

	SentArr[j].SentNo = tmpNo;
	SentArr[j].count = tmpCount;
	SentArr[j].sent = tmpStr;
}
*/
// Heap[l]>Heap[i] is compareNode(SentArr, l, i) > 0;
// swap(l,i) is swap(SentArr, l, i)
void maxHeapify(vector<SentNode> &SentArr, int n, int i)
{
  int l = i*2;
  int r = i*2+1;
  int largest = -1;

  if(l<=n&&(compareNode(SentArr, l, i) > 0))
    largest = l;
  else largest = i;

  if(r<=n&&compareNode(SentArr, r, largest) > 0)
    largest = r;

  if(largest!=i){
  	iter_swap(SentArr.begin() + i, SentArr.begin() + largest);
  	//swap(SentArr, i, largest);
    maxHeapify(SentArr, n, largest);
  }
}

 void Heapify(vector<SentNode> &SentArr, int n)
 {
  for(int i = int((n+1)/2); i > 0; i--)
    maxHeapify(SentArr, n, i);
 }

 void CheckHeapOrder(vector<SentNode> &SentArr,int n)
 {  
  int l;
  int r;
  int largest;
  for(int i = 1; i < n/2; i++){
      l = i*2;
      r = i*2+1;
      largest = i;

      if(l<=n&&compareNode(SentArr, l, i)>0)
        cout<<"Order Wrong"<<endl;

      if(r<=n&&compareNode(SentArr, r, largest)>0)
        cout<<"Order Wrong"<<endl;
  }
 }

void HeapSort(vector<SentNode> &SentArr, int n)
{
  Heapify(SentArr, n);
  CheckHeapOrder(SentArr,n);
  int tmp;

  for(int i = n; i >= 2; i--){
  	iter_swap(SentArr.begin() + 1, SentArr.begin() + i);

  	//swap(SentArr,1,i);

    maxHeapify(SentArr, i-1, 1);  
  }
}
