#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>
using namespace std;

bool cmp(pair<int,int>a,pair<int,int>b)
{
    if(a.first==b.first)
        return a.second<b.second;
    return a.first<b.first;
}

int main()
{
    int n=0;
    pair<int,int> *left_node,*right_node;
    vector<int> ans;
    int left, height, right;

    ifstream file("input.txt");
    if(file.is_open())
    {
        file>>n;
        left_node=new pair<int,int>[n];
        right_node=new pair<int,int>[n];
        for(int i=0;i<n;i++)
        {
            file>>left>>height>>right;
            left_node[i].first=left, left_node[i].second=height;
            right_node[i].first=right, right_node[i].second=height;
        }
        file.close();
    }
    else
    {
        cout<<"Can't read \"input.txt\""<<endl;
        return 0;
    }

    sort(left_node,left_node+n,cmp);
    sort(right_node,right_node+n,cmp);

    priority_queue<int> max_height;
    max_height.push(0);
    unordered_map<int,int> to_deleted;

    int l=0,r=0,previous=0,point=0;
    while(l<n||r<n)
    {
        bool flag=false;
        if(l<n)
        {
            if(left_node[l].first<=right_node[r].first)
            {
                max_height.push(left_node[l].second);
                point=left_node[l].first;
                l++;
                flag=true;
            }
        }
        if(!flag)
        {
            to_deleted[right_node[r].second]++;
            while(!max_height.empty()&&to_deleted[max_height.top()]>0)
            {
                to_deleted[max_height.top()]--;
                max_height.pop();
            }
            point=right_node[r].first;
            r++;
        }
        int current=max_height.top();
        if(current!=previous)
        {
            ans.push_back(point);
            ans.push_back(current);
            previous=current;
        }
    }
    for(int i=0;i<ans.size()-1;i++)
        cout<<ans[i]<<" ";
    cout<<endl;
    return 0;
}
