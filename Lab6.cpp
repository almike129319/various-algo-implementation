#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define mod 1000000007



class currency_sorter{
    public:
   
    void operator()(vector<int64_t> &serial_numbers){
        int64_t end=serial_numbers.size();
        quick_sort(serial_numbers,0,end-1);
    }

    void quick_sort(vector<int64_t> &vec,int64_t start,int64_t end){          //uses quick sort and sorts the vector
        if(end-start==1) {
            if(vec[start]>vec[end]) swap(vec[start],vec[end]);
            return;
        }
        if(start>=end) return;
      
        int m=partition(vec,start,end);
        quick_sort(vec,start,m-1);
        quick_sort(vec,m+1,end);
    }
    int partition(vector<int64_t> &vec,int64_t start,int64_t end){
       int64_t pivot=vec[end];
        int64_t i=start;
        for(int64_t j=start;j<end;j++){
            if(vec[j]<=pivot){
                swap(vec[i],vec[j]);
                i++;    
            }
        }
        swap(vec[end],vec[i]);
        return i;
    }

};
class fibinocci_generator{

    public:

    void operator()(int64_t i){
        cout<<fib(i)<<'\n';
    }
    
    int fib(int64_t i){                              //generates ith fibinocci number
        int64_t mat[2][2] = {{1, 1}, {1, 0}};
        int64_t res[2][2];
        matrix_exp(mat, i-1, res);
        
        return res[0][0] % mod;
    }
    void matrix_exp(int64_t mat[][2],int64_t n,int64_t res[2][2]){   

        if(n==1) {
            res[0][0]=mat[0][0];
            res[0][1]=mat[0][1];
            res[1][0]=mat[1][0];
            res[1][1]=mat[1][1];
            return;
        };
        if(n==0) {
            res[0][0]=1;
            res[0][1]=0;
            res[1][0]=0;
            res[1][1]=1;
            return;
        }
        int64_t mat1[2][2];
        matrix_exp(mat,n/2,mat1);

        matrix_mult(mat1,mat1);
        
        if(n%2==1) matrix_mult(mat1,mat);
        for(int a=0;a<2;a++){
            for(int b=0;b<2;b++){
                res[a][b]=mat1[a][b];
            }
        }
        
        return;
    }
    void matrix_mult(int64_t mat1[][2],int64_t mat2[][2]){
        
        int64_t a00=((mat1[0][0]*mat2[0][0])%mod+(mat1[0][1]*mat2[1][0])%mod)%mod;
        int64_t a01=((mat1[0][0]*mat2[0][1])%mod+(mat1[0][1]*mat2[1][1])%mod)%mod;
        int64_t a10=((mat1[1][0]*mat2[0][0])%mod+(mat1[1][1]*mat2[1][0])%mod)%mod;
        int64_t a11=((mat1[1][0]*mat2[0][1])%mod+(mat1[1][1]*mat2[1][1])%mod)%mod;
        mat1[0][0]=a00;
        mat1[0][1]=a01;
        mat1[1][0]=a10;
        mat1[1][1]=a11;
        return;
    }

};
class prime_calculator{

    public:
    
    void primes_inrange(vector<int64_t> &primes,int64_t l,int64_t r){           //prints all the prime numbers that are present in the range [L,R]
        
        int64_t p;
        vector<bool> isprime2(r-l+1,true);
        for(int i=0;i<(int64_t)primes.size();i++){
            p=primes[i];

            int64_t j=p*p;
            if(j<l) {
                j=(l/p)*p;
                if(j<l) j+=p;
            }
            for(;j<=r;j+=p){
                isprime2[j-l]=false;
            }
        
        }
        vector<int64_t> primes1;
        for(int64_t i=0;i<r-l+1;i++){
            if(isprime2[i]) cout<<(i+l)<<' ';
        }
        cout<<endl;
        
    }
    void primessum_inrange(vector<int64_t> &primes,int l,int r){        //returns the sum of all prime numbers that are present in the range [L,R]
        
        int sum=0;
        int64_t p;
        vector<bool> isprime2(r-l+1,true);
        for(int i=0;i<(int64_t)primes.size();i++){
            p=primes[i];

            int64_t j=p*p;
            if(j<l) {
                j=(l/p)*p;
                if(j<l) j+=p;
            }
            for(;j<=r;j+=p){
                isprime2[j-l]=false;
            }
        
        }
        vector<int64_t> primes1;
        for(int64_t i=0;i<r-l+1;i++){
            if(isprime2[i]) sum+=(i+l);
        }
        
        cout<<sum<<'\n';
    }
};
class number_analyser:public prime_calculator{

    public:
    
    bool is_squarefree(vector<int64_t> &primes,int64_t x){                  //returns true if it is square free, else returns false.

            int64_t p;
            for(int64_t i=0;i<(int64_t)primes.size();i++){
                p=primes[i];
                if(p*p>x) break;
                if(x%(p*p)==0) return false;
            }
             return true;
        
    }
    int64_t count_divisors(int64_t x){                 //returns the total number of divisors of X.
        
        int64_t cnt=0;
        int64_t i;
        for(i=1;i*i<x;i++){
            if(x%i==0) cnt+=2;
        }
        if(x==i*i) cnt+=1;
        return cnt;
    }
    int64_t sum_ofdivisors(int64_t x){                 //returns the sum of all divisors of X.

        int64_t sum=0;
        int64_t i;
        for(i=1;i*i<x;i++){
            if(x%i==0) {
                sum+=i;
                sum+=(x/i);
            }
        }
        if(x==(i*i)) sum+=i;
        return sum;
    }
};

vector<int64_t> primes_until_1e6(){

    vector<bool> isprime(1000002,true);
    vector<int64_t> primes;
    for(int64_t i=2;i<=1000000;i++){
            
        if(!isprime[i]) continue;
        
        primes.push_back(i);
        for(int64_t j=i*i;j<=1000000;j+=i){
            isprime[j]=false;
        }
    }
    return primes;
}

int32_t main(){

    int n;
    cin>>n;
    
    if(n==1){  
        int noof_oper;
        cin>>noof_oper;
        while(noof_oper--){                             //calls currency_sorter class
            
            int size;
            cin>>size;
            vector<int> serial_numbers(size);
            for(int i=0;i<size;i++) cin>>serial_numbers[i];
            currency_sorter cs;
            cs(serial_numbers);
            for(int i=0;i<size;i++) cout<<serial_numbers[i]<<' ';
            cout<<'\n';
        }
    }
    else if(n==2){
        int64_t noof_oper;
        cin>>noof_oper;
        int64_t i;
        while(noof_oper--){
            cin>>i;
            fibinocci_generator f;
            f(i);
        }
    }
    else if(n==3){
        int noof_oper;
        cin>>noof_oper;
        vector<int64_t> primes=primes_until_1e6();
        while(noof_oper--){

            string str;
            int64_t l,r;
            cin>>str>>l>>r;
            prime_calculator p;
            if(l==1) l++;
            if(str=="printPrimes") {
                p.primes_inrange(primes,l,r);
            }
            else p.primessum_inrange(primes,l,r);
        }
    }
    else if(n==4){
        int noof_oper;
        cin>>noof_oper;
        vector<int64_t> primes=primes_until_1e6();
        while(noof_oper--){
            string str;
            int64_t x;
            cin>>str>>x;
            number_analyser n;
            if(str=="isSquareFree"){
                if(n.is_squarefree(primes,x)) cout<<"yes"<<'\n';
                else cout<<"no"<<'\n';
            } 
            else if(str=="countDivisors"){
                cout<<n.count_divisors(x)<<'\n';
            }
            else {
                cout<<n.sum_ofdivisors(x)<<'\n';
            }
        }        
    }
}