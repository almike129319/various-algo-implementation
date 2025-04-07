#include<bits/stdc++.h>
using namespace std;
#define int long long

class comparator{
    //funtor for comapring two integers
    bool operator()(int a,int b){
        return a>b;
    }
};

class graph_algorithm{
    //this class has graph atributes and parent to different graph algorithms

    public:
    //constructor
    graph_algorithm(){}         //default cons
    graph_algorithm(vector<vector<int>> adj_list_inp,vector<int> hype_score_inp){

        adj_list=adj_list_inp;
        hype_scores=hype_score_inp;
        no_ofvertices=(int)hype_scores.size()-1;
    }

    virtual void query(){}             // virtual funtion and calls required children depending on query
    virtual void print(){}             //prints the output for coresponding algo in correseponding format
    
    virtual bool cycle_there(){return false;}
    
    int no_ofvertices;
    vector<vector<int>>  adj_list;     // contains edge u--->v
    vector<int> hype_scores;           //contains scores for each vertex
    
};

class is_cycle: public graph_algorithm{ //this class has a algorithm for detecting cycles
                                        //inherited from grpah algorithm
    public:
    
    //constructor
    is_cycle (vector<vector<int>> adj_list_inp,vector<int> hype_score_inp)
    :graph_algorithm(adj_list_inp,hype_score_inp){}

    void query(){                   //algorithm for detecting cycles;
                                    // dfs on all nodes with keeping track with vs vector     
        int n=no_ofvertices;
        
        vector<int> vis(n+1,-1);    //visited vector sets -1 for not vis, 0 for processing, 1 for visited
        cycle_present=false;
        for(int i=1;i<=n;i++){
            
            if(vis[i]==-1) {
                if(dfs(i,vis)) cycle_present=true;
            }
        }
        
    } 

    bool dfs(int node,vector<int> &vis){        //dfs algo for detectng cycles
    
        vis[node]=0;
        for(auto child:adj_list[node]){

            if(vis[child]==0) {                 //if child is processing then there is cycle
                return true;
            }
            if(vis[child]==-1) {
                if(dfs(child,vis)) return true;
            }
        }
        vis[node]=1;                            //node and all its childen were checked
        return false;
    }

    bool cycle_present;                         // is true if graph has a cycle flase otherwidse
    void print(){
        if(cycle_present==1) cout<<"YES"<<'\n';
        else cout<<"NO"<<'\n';
    }
    bool cycle_there(){ return cycle_present;}
};
class indep_comp : public graph_algorithm{

    //algo for finding storngly connected components
    //inherited from graph algorithm
    
    public:
    //constructor
    indep_comp (vector<vector<int>> adj_list_inp,vector<int> hype_score_inp)
    :graph_algorithm(adj_list_inp,hype_score_inp){}

    vector<vector<int>> reverse_adj;
    vector<int> completion_order;
    vector<vector<int>> condensed_graph;
    vector<int> hype_scores_condensed;
    vector<int> dp;
    int dfs_type;
    int max_scc;
    int no_ofsccs;
    int a;
    int maxhype;
    int temphype;
    
    virtual void print(){                 //prints the max scc and no_scc in the graph 
        cout<<no_ofsccs<<' '<<max_scc<<'\n';
    }

    void query(){   //algo for scc

        int n=no_ofvertices;
        reverse_adj.resize(n+1);
        condensed_graph.resize(n+1);
        hype_scores_condensed.push_back(0);

        for(int i=1;i<=n;i++){
            for(int edge : adj_list[i]){
                reverse_adj[edge].push_back(i);
            }
        }

        vector<int> vis(n+1,-1);
        dfs_type=1;
        
        for(int i=1;i<=n;i++){
            if(vis[i]==-1) { 
                dfs(i,vis); 
            }
        }

        max_scc=0;
        no_ofsccs=0;
        maxhype=0;
        temphype=0;
        dfs_type=2;
        
        for(int i=0;i<=n;i++) vis[i]=-1;
        
        for(int i=n-1;i>=0;i--){

            if(vis[completion_order[i]]==-1){
                
                no_ofsccs++;
                a=0;
                temphype=0;
                
                dfs(completion_order[i],vis);
               
                hype_scores_condensed.push_back(temphype);
                max_scc=max(a,max_scc);
                
            }
        }
        for(int i=no_ofsccs+1;i<=n;i++) hype_scores[i]=0;
        //for(int i=1;i<=n;i++) cout<<i<<' '<<vis[i]<<' '<<hype_scores_condensed[i]<<'\n';
        condensed_graph.resize(no_ofsccs+1);

        for(int i=1;i<=n;i++){

            for(auto edge:adj_list[i]){
                if(vis[i]==vis[edge]) continue;
                condensed_graph[vis[i]].push_back(vis[edge]);
            }
        }
        /*for(int i=1;i<=n;i++)
            for(auto edge:condensed_graph[i]){
            cout<<i<<' '<<edge<<'\n';
        }*/

        dfs_type=3;
        for(int i=0;i<=n;i++) vis[i]=-1;
        dp.resize(no_ofsccs+1,0);

        for(int i=1;i<=no_ofsccs;i++){

            if(vis[i]==-1) dfs(i,vis);
        }

    }
    void dfs(int node,vector<int> &vis){

        vis[node]=0; 

        if(dfs_type==1){
            for(auto child:adj_list[node]){
        
                if(vis[child]==-1) {
                    dfs(child,vis);
                }
            }
            completion_order.push_back(node);
        }
        else if(dfs_type==2){
            
            temphype+=hype_scores[node];
            for(auto child:reverse_adj[node]){
                if(vis[child]==-1) {
                    dfs(child,vis);
                }
            }
            a++;
            vis[node]=no_ofsccs;   
        }
        else if(dfs_type==3){

            int max_child=0;
            for(auto child:condensed_graph[node]){
                if(vis[child]==-1) {
                    dfs(child,vis);
                }
                max_child = max(max_child,dp[child]);
            }

            dp[node]=hype_scores_condensed[node]+max_child;
            maxhype=max(maxhype,dp[node]);
        }
       
    }
    
    
};
class valid_order :public graph_algorithm{ //this class contains algo for topological sorting(valid order)
    
    public:
    
    //constructor
    valid_order (vector<vector<int>> adj_list_inp,vector<int> hype_score_inp)
    :graph_algorithm(adj_list_inp,hype_score_inp){}

    vector<int> order;      //contians valid order
    void print(){
        for(int i=0;i<no_ofvertices;i++) cout<<order[i]<<' ';
        cout<<'\n';
    }
    void query(){           //function containing algo for valid order
        
        int n=no_ofvertices;
        vector<int> indeg(n+1,0);
        for(int i=1;i<n+1;i++){
            for(auto edge:adj_list[i]){
                indeg[edge]++;
            }
        }
        vector<int> par;
        priority_queue<int,vector<int>,greater<int>> q;
        for(int i=1;i<=n;i++){
            if(indeg[i]==0) q.push(i);
        }    
        while(!q.empty()){
            
            int node=q.top();
            q.pop();
                
            for(int edge:adj_list[node]){
                indeg[edge]--;
                if(indeg[edge]==0) q.push(edge);
            }

            order.push_back(node);
        }
    } 
};
class max_hype : public indep_comp { //this class contains algo for find path with max hype
    
    public:
    
    //constructor
    max_hype(vector<vector<int>> adj_list_inp,vector<int> hype_score_inp)
    :indep_comp(adj_list_inp,hype_score_inp){}
    
    void print () {
        cout<<maxhype<<'\n';
    }
};
int32_t main(){

    int n;      //no.of vertices
    int m;     //no.of edges
    int q;    //no.of queries
    cin>>n>>m;

    vector<int> hype_scores(n+1);           //contains scores for each vertex
    vector<vector<int>> adj_list(n+1);      // contains edge u--->v


    for(int i=1;i<=n;i++){
        cin>>hype_scores[i];
    }
    
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adj_list[u].push_back(v);
    }

    graph_algorithm * a = new is_cycle(adj_list,hype_scores);   //obj for calculating query of type1(finding cycles)
    graph_algorithm * b = new indep_comp(adj_list,hype_scores); //obj for claculating query of type2(finding sccs)
    graph_algorithm * c =new valid_order(adj_list,hype_scores); //obj for calculating query of type 3(topo sort)
    graph_algorithm * d =new max_hype(adj_list,hype_scores);    //obj for calculating query of type 4(max path) 

    int type;
    a->query();
    b->query();
    if(!a->cycle_there())c->query();
    d->query();

    cin>>q;
    for(int i=0;i<q;i++){
        
        cin>>type;
        if(type==1) a->print();
        else if(type==2) b->print();
        else if(type==3) {
                if(!a->cycle_there()) c->print();
                else cout<<"NO"<<'\n';
        }
        else if(type==4) d->print();
    }
}
