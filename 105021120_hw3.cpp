//
//  main.cpp
//  algorithm_hw3
//
//  Created by 朱世耘 on 2019/11/5.
//  Copyright © 2019 sy_chu. All rights reserved.
//

#include <iostream>
#include <limits>
#include <stdio.h>

#include <cstdlib>
using namespace std;

int main() {
    
    //freopen("example.txt", "r", stdin);
    long long N,A,B,W;
    // N=天數, A=每天讀書減少作業量, B=連續x天讀書增加x*B作業, W= total work
    cin>>N>>A>>B>>W;
    // D[i]=第i天睡覺增加作業量
    long long D[N+2];
    for (int i=1; i<=N; i++) {
        cin>>D[i];
    }
    D[N+1]=0;
    //chart[i]=第i天睡覺的最佳情況
    long long chart[N+2];
    for (int i=0; i<=N+1; i++) {
        chart[i]=numeric_limits<int>::max();
    }
    // chart[i]=min(chart[j]+( j+1 天 ~ i-1 天 都不睡覺)) 0 <= j < i
    chart[0]=W;
    long long sum;
    int key=0;
    for (long long i=1; i<=N+1; i++) {
        for (long long j=key; j<i; j++) {
            sum=chart[j]-(A*(i-j-1))+(B*(i-j-1)*(i-j)/2);
            if (sum<chart[i]) {
                chart[i]=sum;
                key=j;
            }
        }
        chart[i]+=(D[i]);
    }
    cout<<chart[N+1]<<endl;
    
}


//x代表連續讀書天數
//第i天讀書 -A+x*B
//第i天休息 +D[i]
//chart[i]存的是第i天若睡覺的最佳解
//更新方式為chart[i]=min(chart[j]+第j+1到i-1都讀書的結果),j from 0 to i-1
//因此可以考慮到所有的結果，由於D[N+1]設成0，所以chart[N+1]就會找出前面所有情況的min


/*

 function(int N, int A, int B, int W, int D[N]){
 
    //initialize
    D[N+1]=0;
    long long chart[N+2];
    chart[0]=W;
    chart[i]=inf; for i from 1 to N+1
    long long sum;
 
    //start dp
    for( i from 1 to N+1 ){
        for( j from 0 to i-1){
            sum=chart[j]-(A*(i-j-1))+(B*(i-j-1)*(i-j)/2);
            if (sum<chart[i]) {
                chart[i]=sum;
            }
        }
        chart[i]+=D[i];
    }
    return chart[N+1];
 }
 
 
 
 */

