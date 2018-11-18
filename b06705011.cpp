#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>
using namespace std;

bool cmp(pair<int,int>a,pair<int,int>b)                                         //for sort comparison
{
    if(a.first==b.first)
        return a.second<b.second;
    return a.first<b.first;
}

int main(int argc, char **argv)
{
    int n=0;
    pair<int,int> *left_node,*right_node;
    vector<int> ans;
    int left, height, right;

    //file input

    ifstream in(argv[1]);
    streambuf *cinbuf=cin.rdbuf();
    cin.rdbuf(in.rdbuf());

    cin>>n;
    left_node=new pair<int,int>[n];
    right_node=new pair<int,int>[n];

    for(int i=0;i<n;i++)
    {
        cin>>left>>height>>right;
        left_node[i].first=left, left_node[i].second=height;
        right_node[i].first=right, right_node[i].second=height;
    }

    //sort left_node and right_node base on bool cmp(pair<int,int>,pair<int,int>)

    sort(left_node,left_node+n,cmp);
    sort(right_node,right_node+n,cmp);

    //push 0 into max_height as initial value

    priority_queue<int> max_height;
    max_height.push(0);

    unordered_map<int,int> to_delete;

    int l=0,r=0,previous=0,previous_node=0,point=0;

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
            to_delete[right_node[r].second]++;
            while(!max_height.empty()&&to_delete[max_height.top()]>0)
            {
                to_delete[max_height.top()]--;
                max_height.pop();
            }
            point=right_node[r].first;
            r++;
        }

        int current=max_height.top();

        if(current!=previous)
        {
            if(previous_node==point)
            {
                ans.pop_back();
                ans.pop_back();
            }
            ans.push_back(point);
            ans.push_back(current);
            previous=current;
            previous_node=point;
        }
    }

    cout<<ans[0];
    for(int i=1;i<ans.size()-1;i++)
        cout<<" "<<ans[i];

    cin.rdbuf(cinbuf);
    return 0;
}
