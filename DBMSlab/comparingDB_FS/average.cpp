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
//    cout<<total_rows<<" rows in table"<<endl<<endl;


    cout<<"AVG : "<<endl;
    int  colnum;
    cout<<"by field num ";
    cin>>colnum;
    
    int i;
    double sum=0;
    for(i=0;i<total_rows;i++)
    {
        sum+=string_to_int(sheet[i].getField(colnum));
    }
    if(total_rows==0)
        cout<<"Empty table: invalid operation"<<endl;

    else
        cout<<sum/total_rows<<endl;
}
