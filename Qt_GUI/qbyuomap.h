#ifndef QBYUOMAP_H
#define QBYUOMAP_H
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <QString>
#include <cstring>
#include <unordered_map>
#include <time.h>
#include <QObject>
#include <QStringList>
#include "mydatabase.h"
using namespace std;

class QByUoMap:public QObject
{
    Q_OBJECT
public:
    QByUoMap();


public slots:

    QStringList searchAll(QString);

    void acceptFilePath(QString);

    void acceptSearchChar(QString);

signals:
    void sendSearchResult(QStringList);
    void readFileOk(bool);
    void searchOk(bool);
        void sendClock(double);
protected:
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
    //int readWords(string inputFile, myDatabase myDB, vector<string> &Twits);
    int readFile(myDatabase& myDB, vector<string> &Twits, string fileName);

    bool TestMode; // Print database out.

private:
    QString filepath;
    clock_t startt, endt;
    double TT2;

    myDatabase myDB;
    vector<SentNode> SentArr;
    vector<string> sents;
    int sentCount = 0;
    string sent;
};

#endif // QBYUOMAP_H
