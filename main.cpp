#include <bits/stdc++.h>
#define numeroDeNodosMaximos 1000008
using namespace std;
int N;
int memo[22][numeroDeNodosMaximos];
int nivel[numeroDeNodosMaximos];
vector <int> arbol[numeroDeNodosMaximos];
void inicializaLCA(){
    for(int i=1;1 << i <=N;i++){
        for(int j=1;j<=N;j++){
            memo[i][j]=memo[i-1][memo[i-1][j]];
        }
    }
}
int sacaLogaritmo(int x){
    if(x==0){
        return 0;
    }
    int i=0;
    while((1 << i) <= x){
        i++;
    }
    return i-1;
}
int LCA(int a,int b){
    if(nivel[a]<nivel[b]){
        a ^= b;
        b ^= a;
        a ^= b;
    }
    int log=sacaLogaritmo(nivel[a]);
    for(log=log;log>=0;log--){
        if(nivel[memo[log][a]]>=nivel[b]){
            a=memo[log][a];
        }
    }
    ///anteriormente se nivelaron ambos nodos
    if(a==b){
        return a;
    }
    log=sacaLogaritmo(nivel[a]);
    for(log=log;log>=0;log--){
        if(memo[log][a]!=memo[log][b]){
            a=memo[log][a];
            b=memo[log][b];
        }
    }
    if(a==b){
        return a;
    }
    return memo[0][a];
}
void leerArbol(){
    cin>>N;
    for(int i=1;i<=N;i++){
        cin>>memo[0][i];
        if(memo[0][i]!=i){
            arbol[memo[0][i]].push_back(i);
        }
    }
}
void leerQueries(){
    int a , b /*, Q*/;
    /*cin>>Q;
    for(int i=1;i<=Q;i++){
        cin>>a>>b;
        cout<<LCA(a,b)<<"\n";
    }*/
    while(1){
        cin>>a>>b;
        cout<<LCA(a,b)<<"\n";
    }
}
void ponerNivelesANodos(int nodoAct,int nivelAct){
    nivel[nodoAct]=nivelAct;
    for(unsigned int i=0;i<arbol[nodoAct].size();i++){
        ponerNivelesANodos(arbol[nodoAct][i],nivelAct+1);
    }
}
int main()
{
    ios_base::sync_with_stdio(0);/*cin.tie(0);*/
    leerArbol();
    ponerNivelesANodos(1,0);
    inicializaLCA();
    leerQueries();
    return 0;
}
