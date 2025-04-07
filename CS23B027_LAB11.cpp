#include<bits/stdc++.h>
using namespace std;
#define int long long
template<typename type>
class min_heap{

    public:
    // class that contains the implementations of the min heap;
    min_heap(){ n=0;}

    int size(){                 //returns the size of the min_heap
        return n;
    }
    void push(type t){          //pushes an element into min_heap
        if(n==0) {n++;vec.push_back(t); return;}
        else{
            n++;
            vec.push_back(t);
            int par_ind=(n-2)/2;
            int cur=n-1;
            while(par_ind>=0 and vec[par_ind]>vec[cur]){
                
                swap(vec[par_ind],vec[cur]);
                cur=par_ind;
                par_ind=(cur-1)/2;
                
            }
        }
    }
    void pop() {           
        if(n==0) return;
        if(n==1) {vec.pop_back();n--;return;}
    
        vec[0]=vec[n-1];
        vec.pop_back();
        n--;
    
        int i=0;
        
        while(true) {
            int c1=2*i+1,c2=2*i+2,mn=i;
    
            if(c1<n&&vec[c1]<vec[mn]) mn=c1;
            if(c2<n&&vec[c2]<vec[mn]) mn=c2;
    
            if(mn==i) break;
            
            swap(vec[i],vec[mn]);
            i=mn;
        }
    }    
    bool empty(){               //returns true if min_heap is empty,false otherwise
        return n==0;
    }
    type top(){                 //returns the top element of the min_heap
        return vec[0];
    }
    private:
    int n;             // no.of elements currently in the min_heap
    vector<type> vec; //vector is containser used for storing elements of min_heap;
};

class node{
    //contains the atributes of the node
    public:
    //constructors
    node (){}
    node(string roomid_inp){
        roomid=roomid_inp;

        dist=LONG_LONG_MAX;
        p=0;
    }

    bool operator > (node a){
        return roomid>a.roomid;
    }

    void insert_connection(node * neighbour,int weight){    //inserts one connections into the node
        connections.push_back({neighbour,weight});
    }
    
    int get_dist() {return dist;}
    void set_dist(int d) {dist=d;}

    int p;
    int dist; //contains min dist from source
    string roomid;  //room id of the given node
    vector<pair<node*,int>> connections;    //vector containing the connections from this room to other ones
};

class tup3{
    //contains the atributes of the tuple
    public:
    tup3(){}
    tup3(int b,node * a,int c){
        second=a;
        first=b;
        level=c;
    }
    bool operator > (const tup3 a){
        return first>a.first;
    }
    bool operator < (const tup3 a){
        return first<a.first;
    }
    bool operator == (tup3 a){
        return first==a.first;
    }
    node * second;   //contains the room
    int first;      //contains the distance from the source
    int level;    
};
class castle{

        //contains the atributess of the castle(like rooms and connections between them)
    public:
    castle(){}
    int shortest_path(string a, string b) {      
        
        node *s=mp[a];
        
        unordered_map<string,int> dist1;
        unordered_map<string,int> dist0;
        
        for(auto i:mp) {
            dist1[i.first]=LONG_LONG_MAX;
            dist0[i.first]=LONG_LONG_MAX;
        }
        min_heap<tup3> pq;
        
        dist1[a]=0;
        dist0[a]=0;
        pq.push(tup3(0, s, 0));
    
        while(!pq.empty()){
            
            node *temp=pq.top().second;
            int d=pq.top().first;
            int level=pq.top().level;
            pq.pop();
            
            if (temp->roomid == b && level % 2 == 0) return d;
            
            for (auto child:temp->connections) {
                
                node *next=child.first;
                int nd=d+child.second;
                int next_dist=dist1[next->roomid];
                
                if((level+1)%2==0){
                    next_dist=dist0[next->roomid];
                }

                if (nd<next_dist) {
                    if((level+1)%2==0) dist0[next->roomid]=nd;
                    else dist1[next->roomid]=nd;
                    pq.push(tup3(nd,next,level + 1));
                }
            }
        }
        return -1;
    }
    
    private:
    int no_ofrooms;     //no of rooms in the castle
    unordered_map<string,node*> mp;   //maps the roomid to the corresponding node
    friend istream &operator >>(istream& stream,castle & c);    
};
istream &operator >>(istream& stream,castle & c){

    stream>>c.no_ofrooms;
    int m;
    stream>>m;
    string str;
    for(int i=0;i<c.no_ofrooms;i++){
        stream>>str;
        c.mp[str]=new node(str);
    }
    string a,b;
    int w;
    for(int i=0;i<m;i++){
        stream>>a>>b>>w;
        c.mp[a]->insert_connection(c.mp[b],w);
        c.mp[b]->insert_connection(c.mp[a],w);
    }
    return stream;
}

int32_t main(){

    castle c;
    cin>>c;
    string start,end;
    cin>>start>>end;
    
    cout<<c.shortest_path(start,end);
}


