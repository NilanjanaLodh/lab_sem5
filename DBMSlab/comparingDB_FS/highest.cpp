#include <fstream>
#include <bits/stdc++.h>
#include "Row.cpp"
using namespace std;
int main(int argc, char * argv[])
{
    ifstream f(argv[1]);
    string line;
    string header;

    getline(f,header);
    cout<<header<<endl;
    

    int total_rows=0;
    vector<Row> sheet;
    while(getline(f,line))
    {
        total_rows++;
        Row r(line);
        sheet.push_back(r);
    }
    cout<<total_rows<<" rows in table"<<endl<<endl;


    cout<<"SELECT : "<<endl;
    int entries, colnum;
    cout<<"top ";
    cin>>entries;
    cout<<"by field num ";
    cin>>colnum;
    
    sort(sheet.begin(),sheet.end(),RowComparator_int(colnum));
    entries=min(entries,total_rows);

    int i;
    for(i=0;i<entries;i++)
    {
        sheet[i].print();
        cout<<endl;
    }
}
