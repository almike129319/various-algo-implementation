#include<bits/stdc++.h>
using namespace std;
#define int64_t long long
class Comparator{             // class contain funtor compares the numbers according to the order of sorting 
    public:

    Comparator(string inp){     
        order_ofsorting=inp;
    }

    bool operator() (int64_t a,int64_t b) {     //operator overloading compares a,b according to order of sorting
        if(order_ofsorting=="ascending"){
            return a<=b; 
        }
        else if(order_ofsorting=="descending"){
            return a>=b;
        }
        return true;
    }
    string order_ofsorting;     
};

class tupple4{                 //class contains 4-tupple of coordinates of players
    public:
    tupple4(int64_t a=0,int64_t b=0,int64_t c=0,int64_t d=0) 
    {
        x1=a;
        y1=b;
        x2=c;
        y2=d;
    }
    int64_t x1,x2,y1,y2;
};

class quantumboard{                            //class describes the board that they play
    
    public:

    void operator >>(){
        
    }
    void sort_rows(Comparator comparator){     //sorts the rows of the board according to the order of sorting given  
        
        for(int64_t i=0;i<size_of_board;i++){
            sort_rows(0,size_of_board-1,i,comparator);
        }
        set_linear_board();
    
    }
    void sort_rows(int64_t left, int64_t right, int64_t row_num,Comparator comp){   //overloaded function which implements the sorting

        if(left-right==0) return;
        if(right-left==1){
            if(!comp(board[row_num][left],board[row_num][right])) 
                swap(board[row_num][left],board[row_num][right]);
        }
        int64_t mid=(left+right)/2;

        sort_rows(left,mid,row_num,comp);
        sort_rows(mid+1,right,row_num,comp);

        merge(left,right,row_num,comp);

    }
    void merge(int64_t left,int64_t right,int64_t row_num,Comparator comp){     //merges two sorted arrays;
        
        int64_t mid=(left+right)/2;
        
        vector<int64_t> temp(right-left+1,0);

        int64_t i=left;
        int64_t j=mid+1;
        int64_t k=0;

        for(;i<=mid;i++){
            while(j<=right&&!comp(board[row_num][i],board[row_num][j])){
                temp[k]=board[row_num][j];
                j++;k++;
            }
            temp[k]=board[row_num][i];
            k++;
        }
        while(j<=right){
            temp[k]=board[row_num][j];
            j++;
            k++;
        }
        for(int64_t i=left;i<=right;i++){
            board[row_num][i]=temp[i-left];
        }
        return;
    }
    void count_inversions(){                            //prints no.of inversions in linear_board
        
        cout<<count_inversions(0,(size_of_board)*(size_of_board)-1)<<'\n';
        set_linear_board();

    }
    int64_t count_inversions(int64_t left, int64_t right){          //overloaded function to count inversions by divide and conquer

        if(right-left==0){
            return 0;
        }
        if(right-left==1){

            if(linear_board[left]>linear_board[right]) {
                swap(linear_board[left],linear_board[right]);
                return 1;
            }
            else return 0;
        }

        int64_t mid=(left+right)/2;
        int64_t left_count=count_inversions(left,mid);
        int64_t right_count=count_inversions(mid+1,right);

        int64_t across= merge_count(left,right);
        return left_count+right_count+across;
    }
    int64_t merge_count(int64_t left,int64_t right){        //merges two sorted arrays an counts inversions across them

        int64_t mid=(left+right)/2;
        
        vector<int64_t> temp(right-left+1,0);
        
        int64_t i=left;
        int64_t j=mid+1;
        int64_t k=0;
        int64_t inversions=0;

        for(;i<=mid;i++){
            while(j<=right&&linear_board[i]>linear_board[j]){
                
                temp[k]=linear_board[j];
                inversions+=mid-i+1;
                j++;
                k++;
            }
            temp[k]=linear_board[i];
            k++;
        }
        while(j<=right){
            temp[k]=linear_board[j];
            j++;
            k++;
        }
        for(int64_t i=left;i<=right;i++){
            linear_board[i]=temp[i-left];
        }
        return inversions;
    }
    void display(){                             //displays the current state of board
        
        int64_t n=board.size();
        for(int64_t i=0;i<n;i++){
            for(auto value:board[i]){
                cout<<value<<' ';
            }
            cout<<'\n';
        }

    }

    void set_linear_board(){                //sets the linear board according to main board
       linear_board.clear();
        for(int64_t i=0;i<size_of_board;i++){
            for(int64_t j=0;j<size_of_board;j++){
                linear_board.push_back(board[i][j]);
            }
        }
    }

    vector<vector<int64_t>> board;                  //2d-matrix representation of board
    vector<int64_t> linear_board;                   // linear representation of matrix (row after row)
    int64_t size_of_board;                          // contains sizeof board
};
class ICF_players{                              //class contains player coordinate and helps in setting the matches between players
    
    public:
    
    void closest_pair(){                        //prints the closest pair of coordinates
        
        int64_t n=player_coord.size();
        
        tupple4 ans=closest_pair(0,n-1);

        if(player_index[{ans.x1,ans.y1}]>player_index[{ans.x2,ans.y2}])
            swap(ans.x1,ans.x2),swap(ans.y1,ans.y2);
        
        cout<<ans.x1<<' '<<ans.y1<<' '
            <<ans.x2<<' '<<ans.y2<<'\n';

    }
    tupple4 closest_pair(int64_t left,int64_t right){
        
        if(right-left==0){
            return tupple4(player_coord[left].first,player_coord[left].second,
                    player_coord[right-1].first,player_coord[right-1].second);
        }
        if(right-left==1){
            return tupple4(player_coord[left].first,player_coord[left].second,
                player_coord[right].first,player_coord[right].second);
        }

        int64_t mid=(left+right)/2;
        tupple4 l=closest_pair(left,mid);
        
        tupple4 r=closest_pair(mid+1,right);
        tupple4 ans=l;
        double d=distance(l);
        if(distance(r)<d){
            ans=r;
            d=distance(r);
        }

        int64_t x=(player_coord[mid].first+player_coord[mid+1].first)/2;
        vector<pair<int64_t,int64_t>> strip;
        for(int64_t i=left;i<=right;i++){
            if(abs(player_coord[i].first-x)<=d){
                strip.push_back(player_coord[i]);
            }
        }
        
        int64_t n=strip.size();
        if(n==0||n==1) return ans;
        
        sort(strip.begin(),strip.end(),[](pair<int64_t,int64_t> a,pair<int64_t,int64_t> b){
            return a.second<b.second;
        });
        
        tupple4 temp;

        for(int64_t i=0;i<n;i++){

            temp.x1=strip[i].first;
            temp.y1=strip[i].second;
            for(int64_t j=i+1;j<min(i+16,n);j++){
               
                temp.x2=strip[j].first;
                temp.y2=strip[j].second;
                double tempdis=distance(temp);
                if(tempdis==d) {
                   if(min(ans.x1,ans.x2)>min(temp.x1,temp.x2)){
                       ans=temp;
                   }
                   else if(min(ans.y1,ans.y2)>min(temp.y1,temp.y2)){
                       ans=temp;
                   }
                }
                if(tempdis<d) {
                    ans=temp;
                    d=tempdis;
                }
            }
        }
        
        return ans;
    }
    int64_t distance(tupple4 t){                 //returns the distance between two points
        
        return ((t.x1-t.x2)*(t.x1-t.x2)+(t.y1-t.y2)*(t.y1-t.y2));
    
    }

    vector<pair<int64_t,int64_t>> player_coord;         //contains (x,y) of players
    map<pair<int64_t,int64_t>,int64_t> player_index;        //contains index of player
};

int32_t main(){

    string cmd;
    cin>>cmd;

    quantumboard qb;
    ICF_players ip;
    while(cmd!="END"){
        if(cmd=="CREATE_2D"){
            int64_t n,a;
            cin>>n;

            qb.size_of_board=n;
            qb.board.resize(n);
            
            for(int64_t i=0;i<n;i++)
                for(int64_t j=0;j<n;j++){
                    cin>>a;
                    qb.board[i].push_back(a);
                }

            qb.set_linear_board();
           
        }
        else if(cmd=="SORT_2D"){
            
            string str;
            cin>>str;

            Comparator comp(str);

            qb.sort_rows(comp);
        }
        else if(cmd=="INVERSION_2D"){

            qb.count_inversions();

        }
        else if(cmd=="DISPLAY_2D"){
            qb.display();
        }
        else if(cmd=="CLOSEST_2D"){
            int64_t num_points;
            cin>>num_points;
            
            ip.player_coord.resize(num_points);

            for(int64_t i=0;i<num_points;i++){
                cin>>ip.player_coord[i].first>>ip.player_coord[i].second;
                ip.player_index[ip.player_coord[i]]=i;
            }
            sort(ip.player_coord.begin(),ip.player_coord.end());

            ip.closest_pair();
        }

        cin>>cmd;
    }
}