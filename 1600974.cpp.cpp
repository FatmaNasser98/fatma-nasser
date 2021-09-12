#include <iostream>5
#include <math.h>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<stdio.h>
#include<string>
#include<vector>
#include <map>
#include <set>
#include<cmath>
#include<conio.h>
#include<algorithm>

using namespace std;
pair<int,int> mark(int i,string equation);
bool isstring(char charr);
void Num_Vars(vector<map<string,double> >v_map);
void Equation_I(vector<map<string,double> >v_map,int row1);
void Column(vector<map<string,double> >v_map,string column);
void Add(vector<map<string,double> >v_map,int row1,int row2);
void Subtract(vector<map<string,double> >v_map,int row1,int row2);
void Substitute(vector<map<string,double> >v_map,string colum,int row1,int row2);
void D(vector<map<string,double> >v_map);
void DD(vector<map<string,double> >v_map,string colum);
double D_Value(vector<map<string,double> >v_map);
void Solve(vector<map<string,double> >v_map);

int main()
{
    string equation,element;
    double num_of_equation;
    string number;
    vector<string>v_str;
    map<string,double> map_row;
    map<string,double>::iterator it;
    vector<map<string,double> >v_map;
    pair<int,int> twomarks;
    vector<vector<string> >vv;
    //cout<<"Please Enter Number Of Equation"<<endl;
    cin>>num_of_equation;
    //cout<<"Please Enter Equations"<<endl;
    for(int k=0;k<num_of_equation;k++)
    {
        char charr;

        string element;
        cin>>equation;
        if(equation[0]!='-')
        {
            twomarks=mark(0,equation);
            if((twomarks.first==1&&twomarks.second==1)||(twomarks.first==0&&twomarks.second==0)){charr='+'; }
            else if((twomarks.first==0&&twomarks.second==1)||(twomarks.first==1&&twomarks.second==0)) {charr='-';}
        }
        for( int i=0;i<equation.size();i++)
        {
            if(equation[i]!='-'||i!=0)
            {
                if(isstring(equation[i]))
                {
                    vector<char>v_cahr;
                    string name;
                    while(equation[i]!='-'&&equation[i]!='+'&&equation[i]!='='&&i<equation.size())
                    {
                         if(isstring(equation[i])) v_cahr.push_back(equation[i]);
                         else name+=equation[i];
                         i++;
                    }
                    sort(v_cahr.begin(),v_cahr.end());
                    for(int t=0;t<v_cahr.size();t++)
                    element+=v_cahr[t];
                    element+=name;
                    name.clear();
                    v_cahr.clear();
                    if(i==equation.size())i--;
                }

                else if(equation[i]!='-'&&equation[i]!='+'&&equation[i]!='=') {number+=equation[i]; }
                if((equation[i]=='-'&&equation[i-1]!='=')||equation[i]=='+'||equation[i]=='='||i==equation.size()-1)
                {

                    if(number.size()==0)number+='1';
                    stringstream convert;
                    double num;
                    convert<<number;
                    convert>>num;
                    if(charr=='-'){num*=-1;}
                    map_row[element]+=num;
                    element.clear();
                    number.clear();
                }
            }
            if(equation[i]=='='&&equation[i+1]!='-')
            {
                twomarks=mark(i+1,equation);
                if((twomarks.first==1&&twomarks.second==1)||(twomarks.first==0&&twomarks.second==0)){charr='+'; }
                else if((twomarks.first==0&&twomarks.second==1)||(twomarks.first==1&&twomarks.second==0)) {charr='-';}
            }
            else if(equation[i]=='-'||equation[i]=='+')
            {
                twomarks=mark(i+1,equation);
                if((twomarks.first==1&&twomarks.second==1)||(twomarks.first==0&&twomarks.second==0)){ charr=equation[i];}
                else if((twomarks.first==0&&twomarks.second==1)||(twomarks.first==1&&twomarks.second==0))
                {
                    if(equation[i]=='+')charr='-';
                    else if(equation[i]=='-')charr='+';
                }
            }
        }
        v_map.push_back(map_row);
        map_row.clear();
    }
    for(int i=0;i<v_map.size();i++)
    {
        map_row=v_map[i];
        for(it=map_row.begin();it!=map_row.end();it++)
        {
            if(it!=map_row.begin())
            {
                bool isfind=false;
                for(int k=0;k<v_str.size();k++)
                {
                    if(v_str[k]==it->first)isfind=true;
                }
                if(!isfind)v_str.push_back(it->first);
            }
        }
    }
    for(int i=0;i<v_map.size();i++)
    {
        map_row=v_map[i];
        for(int k=0;k<v_str.size();k++)
        {
            bool isfind=false;
            for(it=map_row.begin();it!=map_row.end();it++)
            {
                if(it!=map_row.begin())
                {
                    if(it->first==v_str[k])isfind=true;
                }
            }
            if(!isfind){map_row[v_str[k]]=0; }
        }
        v_map[i]=map_row;
    }
    //cout<<"Please Enter Operation if you finish enter 00"<<endl;
    string s;
    int row1,row2;
    string colum;
    cin>>s;
    while(s!="00")
    {
    if(s=="num_vars")Num_Vars(v_map);
    else if(s=="equation"){cin>>row1;Equation_I(v_map,row1);}
    else if(s=="column"){cin>>colum;Column(v_map,colum);}
    else if(s=="add"){cin>>row1>>row2;Add(v_map,row1,row2);}
    else if(s=="subtract"){cin>>row1>>row2;Subtract(v_map,row1,row2);}
    else if(s=="substitute"){cin>>colum>>row1>>row2;Substitute(v_map,colum,row1,row2);}
    else if(s=="D")D(v_map);
    else if(s=="DD") {cin>>colum; DD(v_map,colum);}
    else if(s=="D_value") cout<<D_Value(v_map)<<endl;
    else if(s=="solve") Solve(v_map);
    cin>>s;
    }


    return 0;
}
pair<int,int> mark(int i,string equation)
{
    pair<int,int>twomarks;
    int markone =0;
    int marktwo =0;
    int start=i;
    while(equation[start]!='-'&&equation[start]!='+'&&equation[start]!='='&&start<equation.size())
    {
       if( isstring(equation[start])) {markone=1; }
        start++;
    }

    start=i;
    while(start<equation.size())
    {
        if(equation[start]=='='){marktwo=1;}
        start++;
    }
    twomarks.first=markone;
    twomarks.second=marktwo;
    return twomarks;

}
void Num_Vars(vector<map<string,double> >v_map)
{
    map<string,double> m_total,map_row;
    map<string,double>::iterator it;
    for(int i=0;i<v_map.size();i++)
    {
        map_row=v_map[i];
        for(it=map_row.begin();it!=map_row.end();it++){m_total[it->first]+=it->second;}
    }
    cout<<m_total.size()-1<<endl;
}
bool isstring(char charr)
{
    bool ischar=false;
    if(charr>=65&&charr<=90)ischar=true;
    else if(charr>=97&&charr<=122)ischar=true;
    return ischar;
}
void Column(vector<map<string,double> >v_map,string column)
{
    map<string,double> map_row;
    map<string,double>::iterator it;
    for(int i=0;i<v_map.size();i++)
    {
        map_row=v_map[i];
        for(it=map_row.begin();it!=map_row.end();it++)
        {
            if(it->first==column)cout<<it->second<<endl;
        }
    }
}
void Equation_I(vector<map<string,double> >v_map,int row1)
{
    map<string,double> map_row;
    map<string,double>::iterator it;
    int num=0;
    map_row=v_map[row1-1];
    for(it=map_row.begin();it!=map_row.end();it++)
    {
        num++;
        if(it!=map_row.begin())
        {
            if(it->second>=0&&num!=2)cout<<"+";
            cout<<it->second<<it->first;
        }
    }
    it=map_row.begin();
    cout<<"="<<it->second<<it->first<<endl;
}

void Add(vector<map<string,double> >v_map,int row1,int row2)
{
    map<string,double> map_row1,map_row2,map_sum;
    map<string,double>::iterator it;
    map_row1=v_map[row1-1];
    map_row2=v_map[row2-1];
    for(it=map_row1.begin();it!=map_row1.end();it++){map_sum[it->first]+=it->second;}
    for(it=map_row2.begin();it!=map_row2.end();it++){map_sum[it->first]+=it->second;}
    int num=0;
    for(it=map_sum.begin();it!=map_sum.end();it++)
    {
        num++;
        if(it!=map_sum.begin())
        {
            if(it->second>=0&&num!=2)cout<<"+";
            cout<<it->second<<it->first;
        }
    }
    it=map_sum.begin();
    cout<<"="<<it->second<<it->first<<endl;
}

void Subtract(vector<map<string,double> >v_map,int row1,int row2)
{
    map<string,double> map_row1,map_row2,map_sum;
    map<string,double>::iterator it;
    map_row1=v_map[row1-1];
    map_row2=v_map[row2-1];
    for(it=map_row1.begin();it!=map_row1.end();it++){map_sum[it->first]+=it->second;}
    for(it=map_row2.begin();it!=map_row2.end();it++){map_sum[it->first]-=it->second;}
    int num=0;
    for(it=map_sum.begin();it!=map_sum.end();it++)
    {
        num++;
        if(it!=map_sum.begin())
        {
            if(it->second>=0&&num!=2)cout<<"+";
            cout<<it->second<<it->first;
        }
    }
    it=map_sum.begin();
    cout<<"="<<it->second<<it->first<<endl;
}
void Substitute(vector<map<string,double> >v_map,string colum,int row1,int row2)
{
    map<string,double> map_row1,map_row2,map_sum;
    map<string,double>::iterator it,it1,it2;
    map_row1=v_map[row1-1];
    map_row2=v_map[row2-1];
    it1=map_row1.find(colum);
    it2=map_row2.find(colum);
    for(it=map_row1.begin();it!=map_row1.end();it++){it->second*=it2->second;}
    for(it=map_row2.begin();it!=map_row2.end();it++){it->second*=(-it1->second);}
    for(it=map_row1.begin();it!=map_row1.end();it++){map_sum[it->first]+=it->second;}
    for(it=map_row2.begin();it!=map_row2.end();it++){map_sum[it->first]+=it->second;}
    int num=0;
    for(it=map_sum.begin();it!=map_sum.end();it++)
    {
        num++;
        if(it!=map_sum.begin())
        {
            if(it->second>0&&num!=2)cout<<"+";
            if(it->second!=0)cout<<it->second<<it->first;
        }
    }
    it=map_sum.begin();
    cout<<"="<<it->second<<it->first<<endl;
}
void D(vector<map<string,double> >v_map)
{
    map<string,double> map_row;
    map<string,double>::iterator it;
    for(int i=0;i<v_map.size();i++)
    {
        map_row=v_map[i];
        for(it=map_row.begin();it!=map_row.end();it++)
        {
            if(it==map_row.begin())it++;
            cout<<it->second<<" ";
        }
        cout<<endl;
    }
}

void DD(vector<map<string,double> >v_map,string colum)
{
    map<string,double> map_row;
    map<string,double>::iterator it,it2;
    for(int i=0;i<v_map.size();i++)
    {
        map_row=v_map[i];
        for(it=map_row.begin();it!=map_row.end();it++)
        {
            if(it==map_row.begin())it2=it;
            else if(it->first==colum)cout<<it2->second<<" ";
            else cout<<it->second<<" ";
        }
        cout<<endl;
    }
}
double D_Value(vector<map<string,double> >v_map)
{
    double arr[100][100];
    int n=v_map.size();
    map<string,double> map_row;
    map<string,double>::iterator it;
    for(int i=0;i<v_map.size();i++)
    {
        map_row=v_map[i];
        int j=0;
        for(it=map_row.begin();it!=map_row.end();it++)
        {
            if(it!=map_row.begin())
            {
                arr[i][j]=it->second;
                j++;
            }
        }
    }
    int k=0;
    double long num=1;
    for(int j=n-1;j>0;j--)
    {

        double y=arr[k][j];
        num*=y;
        for(int i=n-1;i>=0;i--)
            {arr[k][i]=arr[k][i]/y; }
        for(int i=j-1;i>=0;i--)
        {
            int t=0;
            double d=arr[k][i];
            while(t<n)
            {
                arr[t][i]+=(arr[t][j]*(-d));
                t++;
            }
        }
        k++;
    }
    num*=-arr[n-1][0];
    if(num==-0)num=0;
    return num;
}
void Solve(vector<map<string,double> >v_map)
{
    vector<map<string,double> >v_element;
    map<string,double> map_row,map_element,map_equation;
    map<string,double>::iterator it,it2;
    vector<string>v_string;
    map_equation=v_map[0];
    double base=D_Value(v_map);
    for(it=map_equation.begin();it!=map_equation.end();it++)
    {
        if(it!=map_equation.begin())v_string.push_back(it->first);
    }
    int num=0;
    while(num<v_string.size())
    {
        for(int i=0;i<v_map.size();i++)
        {
            map_row=v_map[i];
            for(it=map_row.begin();it!=map_row.end();it++)
            {
                map_element[" "]=0;
                if(it==map_row.begin())it2=it;
                else if(it->first==v_string[num])map_element[it->first]=it2->second;
                else map_element[it->first]=it->second;
            }
            v_element.push_back(map_element);
            map_element.clear();
        }
        cout<<v_string[num]<<"="<<D_Value(v_element)/base<<endl;
        v_element.clear();
        num++;
    }
}
