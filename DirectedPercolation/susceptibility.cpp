// Directed percolation of neural network
#include <bits/stdc++.h>
using namespace std;

int rand01(double p){
    // probability p return 1, else 0
    double x=1.0*rand()/RAND_MAX;
    return x<p;
}

const int T=10000, N=500, n=5, K=10;
double sigma=1;
// total time / # of neurons / # of states / mean # of output neurons
struct DP{
    int state[T][N];
    int active[T];
    double h[T][N]; //external stumulation
    int sz;
    vector<pair<int,double> > v[N]; // v[i]: neurons connected to i
    void init(double p,double H){  // p=0.005, h=0
        int x[N];
        for(int i=0;i<N;i++)
            for(int j=0;j<T;j++)
                h[j][i]=H;
        for(int i=0;i<N;i++) {
            state[0][i]=rand01(p);
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
                double p=1-h[t][i];
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
    printf("branching ratio: susceptiblity\n");
    for(sigma=0.2;sigma<=1.9;sigma+=0.1){
        dp.init(0,0.002);
        dp.run();
        double a1=0,sd1=0;
        for(int j=0;j<T;j++) a1+=dp.active[j];
        a1/=T;

        dp.init(0,0.003);
        dp.run();
        double a2=0,sd2=0;
        for(int j=0;j<T;j++) a2+=dp.active[j];
        a2/=T;

        printf("%.1f: %.1f\n",sigma,(a2-a1)/0.001/N);
    }
    /*FILE* f=fopen("a.txt","w");
    for(int i=0;i<T;i++){
        fprintf(f,"%d\n",dp.active[i]);
    }
    fclose(f);*/
    return 0;
}
