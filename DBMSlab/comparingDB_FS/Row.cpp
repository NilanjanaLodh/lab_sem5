#ifndef ROW
#define ROW
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;
int string_to_int(string str)
{
    istringstream ss(str);
    int x;
    ss >> x;
    return x;

}
class RowComparator_int;

class Row
{
    int n;//the number of fields
    vector<string> data;
    public:
        friend class RowComparator_int;
        Row(int _n):n(_n),data(_n,""){}
        Row(string line)
        {
            n=0;
            vector<string> tdata;
            stringstream ss(line);
            string tmp;
            while(getline(ss,tmp,','))
            {
                n++;
                tdata.push_back(tmp);
            }
            data=tdata;
        }
        void print()
        {
            int i;
            for(i=0;i<n-1;i++)
            {
                cout<<data[i]<<",";
            }
            cout<<data[n-1];
            cout<<endl;
        }
        string getField(int k)
        {
            return data[k];
        }
        void setRow(string line)
        {
            stringstream ss(line);
            string tmp;
            while(getline(ss,tmp,','))
            {
                data.push_back(tmp);
            }
        }
};
class RowComparator_int
{
//    cout<<"inside Row comparator"<<endl;
    int k;
    public:
        RowComparator_int(int k)//k is the column number according to which things will be sorted
        {
            this->k =k;
        }
        bool operator() (const Row &r1, const Row &r2)
        {
            int x1= string_to_int(r1.data[k]);
            int x2= string_to_int(r2.data[k]);
            
            return x1>x2;
        }
};

#endif
