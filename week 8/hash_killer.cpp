//#include "edx-io.hpp"

#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cmath>
#include <map>
#include <set>

//    FILE *fin = fopen("../input.txt", "rb+");
//    FILE *fout = fopen("../output.txt", "wb+");
//    FILE *fin = fopen("input.txt", "rb+");
//    FILE *fout = fopen("output.txt", "wb+");
//std::ifstream fin("../input.txt", std::ios::binary);
//std::ofstream fout("../output.txt",std::ios::binary);
std::ofstream fout("output.txt", std::ios::binary);
std::ifstream fin("input.txt", std::ios::binary);



std::string answer[10];
int hashOf(std::string s, int multiple) {
    int rv = 0;
    for (int i = 0; i < s.length(); ++i) {
        rv = multiple * rv + s[i];
    }
    return rv;
}


int main() {
    const int Q = 11;
    const int N = 1 << Q;
    int m2 = 5;
    int m1 = 7;
    std::map<int, int> d;
    int n;
    fin >> n;
    std::string s = "";
    std::vector<std::pair<int,int>> ans;
//    fout<<N<<"\n";
    std::set<std::string> uniq;
        s = "";
        for (int i = 0; i <= N; i++)
            s += 'a' + __builtin_popcount(i) % 2;

        for (int i = 0; i < N; i+=16) {
            for (int j = 0; i + j <= N; j +=16) {
                std::string temp = s.substr(i, j);
                if (uniq.count(temp))
                    continue;
                int hash = hashOf(temp,m1);
//                int hash2 = hashOf(temp,m2);
                if (hash == -1608748800 )
                    ans.push_back(std::make_pair(i, j));
                if (d.count(hash)) {
                    d[hash]++;
                } else {
                    d[hash] = 1;
                }
                uniq.insert(temp);
            }
        }
//    std::map<int, int> set;
//    for (auto key : d) {
//        set[key.second] = key.first;
//    }
//    for (auto key : set) {
//        fout << key.first << " " << key.second << "\n";
//    }
//    for (auto key : ans) {
//        fout << key.first << " " << key.second << " "<< hashOf(s.substr(key.first,key.second),m2)<< " " << s.substr(key.first,key.second) << "\n";
//    }
//    bool f = false;
    std::set<std::pair<int,int>> temp;
    for (auto key : ans) {
        temp.insert(key);
    }

    for(int i = 2; i < 1024; i++){
        int hash = hashOf(s.substr(temp.begin()->first,temp.begin()->second),i);
        for(auto key : temp){
            if(hash != hashOf(s.substr(key.first,key.second),i))
                temp.erase(key);
        }
    }

//    for (auto key : temp) {
//        fout << key.first << " " << key.second << " "<< hashOf(s.substr(key.first,key.second),m2)<< " " << s.substr(key.first,key.second) << "\n";
//    }
    int count = 0;
    for (auto key1 : temp) {
        for (auto key2 : temp) {
            for (auto key3 : temp) {
                for (auto key4 : temp) {
                    for (auto key5 : temp) {
                        for (auto key6 : temp) {
                            if(count >= n)
                                break;
                            fout<<s.substr(key1.first,key1.second)
                                <<s.substr(key2.first,key2.second)
                                <<s.substr(key3.first,key3.second)
                                <<s.substr(key4.first,key4.second)
                                <<s.substr(key5.first,key5.second)
                                <<s.substr(key6.first,key6.second)<<"\n";
                            count++;
                        }
                        if(count >= n)
                            break;
                    }
                    if(count >= n)
                        break;
                }
                if(count >= n)
                    break;
            }
            if(count >= n)
                break;
        }
        if(count >= n)
            break;
    }


    fin.close();
    fout.close();

    return 0;
}