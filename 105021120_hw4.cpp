//
//  main.cpp
//  algo_hw4
//
//  Created by 朱世耘 on 2019/12/16.
//  Copyright © 2019 sy_chu. All rights reserved.
//
// input:K,V,E
// adj_matrix [i][j] = i到j的距離

#include <iostream>
# define MAX 10000000000

using std::cin;
using std::cout;
using std::endl;

class edge{
public:
    int start;
    int end;
    long long weight;
    
    edge(int a,int b,long long c){
        start=a;
        end=b;
        weight=c;
    }
    edge(){}
};

struct Map {
    int V, E;
    long long* dist;
    long long** adj_matrix;
    edge* list;
    virtual void read_input() = 0;
    virtual void process() = 0;
    virtual void output() = 0;
    virtual ~Map() {}
    
    void initial_data(){
        cin>>V>>E;
        adj_matrix=new long long*[V];
        for (int i=0; i<V; i++) {
            adj_matrix[i]=new long long[V];
        }
        for (int i=0; i<V; i++) {
            for (int j=0; j<V; j++) {
                adj_matrix[i][j]=MAX;
            }
        }
        int x,y;
        long long z;
        for (int i=0; i<E; i++) {
            cin>>x>>y>>z;
            adj_matrix[x][y]=z;
        }
    }
    void initial_list(){
        int x,y;
        long long z;
        cin>>V>>E;
        list=new edge[E];
        for (int i=0; i<E; i++) {
            cin>>x>>y>>z;
            list[i]=edge(x,y,-z);
        }
        dist=new long long[V];
        for (int i=0; i<V; i++) {
            dist[i]=MAX;
        }
    }
};



class LosSantosMap: public Map {
    void reverse_matrix(){
        long long tmp;
        for (int i=0; i<V; i++) {
            for (int j=i+1; j<V; j++) {
                tmp=adj_matrix[i][j];
                adj_matrix[i][j]=adj_matrix[j][i];
                adj_matrix[j][i]=tmp;
            }
        }
    }
    int min(long long* dist,bool* finish){
        int tmp=-1;
        for (int i=0; i<V; i++) {
            if (finish[i]==false) {
                if (tmp==-1) {
                    tmp=i;
                }
                if (dist[i]<dist[tmp]) {
                    tmp=i;
                }
            }
        }
        return tmp;
    }
    void relax(int s){
        for (int i=0; i<V; i++) {
            if (dist[s]+adj_matrix[s][i]<dist[i]) {
                dist[i]=dist[s]+adj_matrix[s][i];
            }
        }
    }
    void dijkstra(){
        int s;
        bool finish[V];
        for (int i=0; i<V; i++) {
            finish[i]=false;
        }
        dist=new long long[V];
        for (int i=0; i<V; i++) {
            dist[i]=MAX;
        }
        dist[0]=0;
        for (int i=0; i<V; i++) {
            s=min(dist,finish);
            finish[s]=true;
            relax(s);
        }
    }
    
public:
    void read_input() override {
        initial_data();
        reverse_matrix();
    }
    void process() override {
        dijkstra();
    }
    void output() override {
        for (int i=0; i<V; i++) {
            if (dist[i]!=MAX) {
                cout<<dist[i]<<endl;
            }
            else{
                cout<<"INF"<<endl;
            }
        }
    }
};

class PortalChambersMap: public Map {
    void floyd_warshall(){
        for (int k=0; k<V; k++) {
            for (int i=0; i<V; i++) {
                for (int j=0; j<V; j++) {
                    if (adj_matrix[i][k]+adj_matrix[k][j]<adj_matrix[i][j]) {
                        adj_matrix[i][j]=adj_matrix[i][k]+adj_matrix[k][j];
                    }
                }
            }
        }
    }
public:
    void read_input() override {
        initial_data();
    }
    
    void process() override {
        floyd_warshall();
    }
    void output() override {
        for (int i=0; i<V; i++) {
            if (adj_matrix[i][i]!=MAX) {
                cout<<adj_matrix[i][i]<<endl;
            }
            else{
                cout<<"INF"<<endl;
            }
        }
    }
};

class SkyrimMap: public Map {
    void bellman_ford(){
        dist[0]=0;
        for (int i=0; i<V-1; i++) {
            for (int j=0; j<E; j++) {
                if (dist[list[j].end]>dist[list[j].start]+list[j].weight) {
                    dist[list[j].end]=dist[list[j].start]+list[j].weight;
                }
            }
        }
    }
    bool remain_same(){
        long long old[V];
        for (int i=0; i<E; i++) {
            old[i]=dist[i];
        }
        for (int j=0; j<E; j++) {
            if (dist[list[j].end]>dist[list[j].start]+list[j].weight) {
                dist[list[j].end]=dist[list[j].start]+list[j].weight;
            }
        }
        for (int i=0; i<E; i++) {
            if(old[i]!=dist[i]){
                return false;
            }
        }
        return 1;
    }
public:
    void read_input() override {
        initial_list();
    }
    void process() override {
        bellman_ford();
    }
    void output() override {
        if (remain_same()==true) {
            cout<<"FALSE"<<endl;
        }
        else{
            cout<<"TRUE"<<endl;
        }
    }
};

class BlightTownMap: public Map {
public:
    void read_input() override {

    }
    void process() override {

    }
    void output() override {
        cout<<"TRUE"<<endl;
    }
};

int main(void)
{
    int T, map_kind;
    Map* map;
    cin >> T;
    while (T--) {
        cin >> map_kind;
        switch (map_kind) {
            case 1: map = new LosSantosMap(); break;
            case 2: map = new PortalChambersMap(); break;
            case 3: map = new SkyrimMap(); break;
            case 4: map = new BlightTownMap(); break;
            default: return 1;
        }
        map->read_input();
        map->process();
        map->output();
    }
    
    return 0;
}

