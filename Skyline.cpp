#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

bool cmp(pair<int,int>a,pair<int,int>b)
{
    if(a.first==b.first)
        return a.second<b.second;
    return a.first<b.first;
}

int main()
{
    int n;
    cin>>n;

    pair<int,int> left_node[n],right_node[n];
    vector<int> ans;

    int left, height, right;
    for(int i=0;i<n;i++)
    {
        cin>>left>>height>>right;
        left_node[i].first=left, left_node[i].second=height;
        right_node[i].first=right, right_node[i].second=height;
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
