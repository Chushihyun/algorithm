//
//  105021120_hw2.cpp
//  algoritm
//
//  Created by 朱世耘 on 2019/10/2.
//  Copyright © 2019 sy_chu. All rights reserved.
//

#include <iostream>
using namespace std;

int main() {
    int n;
    cin>>n;
    int A[n];
    int B[n];
    for (int i=0; i<n; i++) {
        cin>>A[i];
    }
    for (int i=0; i<n; i++) {
        cin>>B[i];
    }
    int A_begin=0, B_begin=0;
    int A_end=n-1, B_end=n-1;
    int A_mid,B_mid;
    
    while ((A_end-A_begin+1)>=3 && (B_end-B_begin+1)>=3) {
        A_mid = (A_begin + A_end)/2;
        B_mid = (B_begin + B_end)/2;
        if ( A[A_mid] > B[B_mid] ) {
            if ((A_end-A_begin+1)%2==1) {
                A_end=A_mid;
                B_begin=B_mid;
            }
            else{
                A_end=A_mid+1;
                B_begin=B_mid;
            }
        }
        else{
            if ((A_end-A_begin+1)%2==1) {
                B_end=B_mid;
                A_begin=A_mid;
            }
            else{
                B_end=B_mid+1;
                A_begin=A_mid;
            }
        }
    }
    int ans=0;
    if (A[A_begin]>B[B_begin]) {
        ans+=A[A_begin];
    }
    else{
        ans+=B[B_begin];
    }
    if (A[A_end]>B[B_end]) {
        ans+=B[B_end];
    }
    else{
        ans+=A[A_end];
    }
    cout<<(ans/2)<<endl;
    
    return 0;
}
