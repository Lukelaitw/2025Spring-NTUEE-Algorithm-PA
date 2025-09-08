// **************************************************************************
//  File       [maxPlanarSubset.cpp]
//  Author     [Yu-Heng Lai]
//  Synopsis   [The main program of 2025 spring Algorithm PA2]
// **************************************************************************
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include "../lib/tm_usage.h"
using namespace std;

int buildM(int i, int j, vector<int>& data,vector<vector<int>>& M){
    if(i >= j) return 0;
    if(M[i][j] != -1) return M[i][j];
    int k = data[j];
    if(k < i || k > j){
        M[i][j] = buildM(i, j-1, data, M);
    }
    else if(k == i){
        M[i][j] = buildM(i+1, j-1, data, M) + 1;
    }
    else{
        if(buildM(i, j-1, data , M) < buildM(i, k-1, data, M) + buildM(k+1, j-1, data, M) + 1){
            M[i][j] = buildM(i, k-1,data, M) + buildM(k+1, j-1, data, M) + 1;
        }
        else{
            M[i][j] = buildM(i, j-1, data, M);
        }
    }
    return M[i][j];
}




void buildResult(int i, int j,const vector<int>& data,const vector<vector<int>>& M,vector<pair<int,int>>& result) {
    if (i >= j) return;
    int k = data[j];
    if(k < i || k > j){
        buildResult(i, j-1, data, M,  result);
    }
    else if(k == i){
        result.emplace_back(k, j);
        buildResult(i+1, j-1, data, M,  result);
    }
    else{
        if(M[i][j] == M[i][j-1]){
            buildResult(i, j-1, data, M,  result);
        }
        else{
            result.emplace_back(k, j);
            buildResult(i, k-1, data, M,  result);
            buildResult(k+1, j-1, data, M,  result);
        }
    }
}


void help_message() {
    cout << "Usage: ./bin/mps <input_file> <output_file>" << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        help_message();
        return 0;
    }
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;
    
    
    int n;
    fin >> n;
    int a, b, junk;
    
    vector<int> data(n, -1);
    
    for (int i = 0; i < n / 2; i++){
        fin >> a >> b;
        data[a] = b;
        data[b] = a;
    }
    fin >> junk;
    
    
    tmusg.periodStart();

    
    
    
    vector<vector<int>> M(n, vector<int>(n, -1));
    
    
    
    buildM(0,n-1,data,M);
    
    
    
    
    
    tmusg.getPeriodUsage(stat);
   
    cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms"
           << endl;
    cout << "memory: " << stat.vmPeak << "KB" << endl;
    
    


    // write outputs and sort the results
    vector<pair<int,int>> result;
    buildResult(0, n-1, data ,M, result);
    sort(result.begin(), result.end(),[](const pair<int,int>& a, const pair<int,int>& b){
             return a.first < b.first;
         });
    

    
    
    
    fout << M[0][n-1] << "\n";
    for (auto &p : result) {
        fout << p.first << " " << p.second << "\n";
    }
    return 0;
}
