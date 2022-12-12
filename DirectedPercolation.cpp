// Directed percolation of neural network
#include <bits/stdc++.h>
using namespace std;

int rand01(double p){
    // probability p return 1, else 0
    double x=1.0*rand()/RAND_MAX;
    return x<p;
}

const int T=1000, N=1000, n=5, K=10;
const double sigma=1;
// total time / # of neurons / # of states / mean # of output neurons
struct DP{
    int state[T][N];
    int active[T];
    int sz;
    vector<pair<int,double> > v[N]; // v[i]: neurons conneted ot i
    void init(){
        int x[N];
        for(int i=0;i<N;i++) {
            state[0][i]=rand01(0.005);
            x[i]=i;
            v[i].clear();
        }
        for(int j=0;j<N;j++) {
            random_shuffle(x,x+N);
            int now=K,k=0;
            while(now){
                if(x[k]==j){
                    k++;
                    continue;
                }
                v[x[k]].push_back(pair<int,double>(j,sigma/K));
                k++;
                now--;
            }
        }
    }
    void update(int t){
        for(int i=0;i<N;i++){
            if(state[t-1][i]>0) state[t][i]=(state[t-1][i]+1)%n;
            else {
                double p=1;
                for(pair<int,double> P:v[i])
                    if(state[t-1][P.first]==1) p*=(1-P.second);
                p=1-p;
                if(rand01(p)) state[t][i]=1;
                else state[t][i]=0;
            }
        }
    }
    void run(){
        for(int t=1;t<T;t++)
            update(t);
        sz=0;
        for(int t=0;t<T;t++){
            active[t]=0;
            for(int i=0;i<N;i++){
                if(state[t][i]>0)
                    active[t]++;
            }
            sz+=active[t];
        }
    }
} dp;

int main(){
    srand(time(NULL));
    dp.init();
    dp.run();
    //for(int t=0;t<40;t+=2)  printf("%d:%d\n",t,dp.active[t]);
    int exps=10000;
    vector<int> size;
    for(int i=0;i<exps;i++){
        dp.init();
        dp.run();
        size.push_back(dp.sz);
        printf("%d: %d\n",i,dp.sz);
    }
    int P[1000]={0};
    int szbin=50;
    for(int i=0;i<exps;i++){
        if(size[i]<3000) P[size[i]/szbin]++;
    }
    for(int i=0;i<3000/szbin;i++)
        printf("%d\n",P[i]);
    return 0;
}
