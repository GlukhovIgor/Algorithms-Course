//#include "edx-io.hpp"

#include <string>
//#include <cstdio>
#include <fstream>
//#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cmath>
//#include <iostream>

//    FILE *fin = fopen("../input.txt", "rb+");
//    FILE *fout = fopen("../output.txt", "wb+");
//    FILE *fin = fopen("input.txt", "rb+");
//    FILE *fout = fopen("output.txt", "wb+");
//std::ifstream fin("../input.txt", std::ios::binary);
//std::ofstream fout("../output.txt",std::ios::binary);
std::ofstream fout("output.txt",std::ios::binary);
std::ifstream fin("input.txt", std::ios::binary);

int m = 21;
int mask[] = {321, 264 ,311 ,281 ,284, 323, 337, 342 ,268 ,262 ,261, 313, 267 ,330, 302, 294, 295 ,276, 278, 286};

struct map_enum{
    std::string key;
    std::string value;
    map_enum * prev = nullptr;
    map_enum * next = nullptr;
};

map_enum * last = nullptr;
long long p = 997;
long long N = 1 << m;
const std::string DELETED ="DELETED";
const std::string NIL ="NIL";
double A = 0.6180339887;



long long hash_string(std::string * s){
    long long sum = 0;
    for(int i = 0 ; i < s->length(); i++)
        sum += mask[i] * (*s)[i];
    return sum;
}

int h1(long long x){
    return int(N * fmod(x*A , 1));
}

int h2(long long x){
    return int(x % p + 1);
}

void add(map_enum* a, std::string * key, std::string * value){
    long long x = hash_string(key);
    int cur = h1(x);
    int delta = h2(x);
    int deleted = -1;
    while(a[cur].key != NIL){
        if( a[cur].key == DELETED && deleted == -1)
            deleted = cur;
        if( a[cur].key == *key) {
            a[cur].value = *value;
            return;
        }
        cur += delta;
        if(cur >= N)
            cur %= N;
    }
    if(deleted != -1){
        cur = deleted;
    }
    a[cur].key = *key;
    a[cur].value = *value;
    a[cur].prev = last;
    a[cur].next = nullptr;
    if(last != nullptr)
        last->next = &a[cur];
    last = &a[cur];
}

void map_delete(map_enum* a, std::string * key){
    long long x = hash_string(key);
    int cur = h1(x);
    int delta = h2(x);
    while(a[cur].key != NIL){
        if( a[cur].key == *key) {
            a[cur].key = DELETED;
            if(last == &a[cur])
                last = a[cur].prev;
            if (a[cur].prev!= nullptr){
                a[cur].prev->next = a[cur].next;
            }
            if (a[cur].next!= nullptr){
                a[cur].next->prev = a[cur].prev;
            }
            return;
        }
        cur += delta;
        if(cur >= N)
            cur %= N;
    }

}

//bool map_isContained(long long* a, long long x){
//    int cur = h1(x);
//    int delta = h2(x);
//    while(a[cur] != NIL){
//        if( a[cur] == x) {
//            return true;
//        }
//        cur += delta;
//        if(cur >= N)
//            cur %= N;
//    }
//    return false;
//}

map_enum get(map_enum* a, std::string * key) {
    long long x = hash_string(key);
    int cur = h1(x);
    int delta = h2(x);
    while(a[cur].key != NIL){
        if( a[cur].key == *key) {
            map_enum t = a[cur];
            return a[cur];
        }
        cur += delta;
        if(cur >= N)
            cur %= N;
    }
    map_enum empty;
    empty.value = "<none>";
    return empty;
}
int main() {

    map_enum* a = new map_enum[N];
    for(int i = 0 ; i  < N; i++)
        a[i].key = NIL;
    long long n, cur , delta, deleted;
    fin >> n ;
    std::string key;
    std::string value;
    std::string c;
    for(int i = 0 ; i < n; i++){
        fin>>c;
        if(c == "put") {
            fin >> key >> value;
            add(a, &key, &value);
        } else if(c == "delete") {
            fin >> key;
            map_delete(a, &key);
        } else if(c == "get") {
            fin>> key;
            fout << get(a, &key).value << "\n";
        } else if(c == "next") {
            fin >> key;
            map_enum* t = get(a,&key).next;
            if(t != nullptr)
                fout << t->value << "\n";
            else
                fout << "<none>\n";
        } else if(c == "prev") {
            fin >> key;
            map_enum* t = get(a,&key).prev;
            if(t != nullptr)
                fout << t->value << "\n";
            else
                fout << "<none>\n";
        }
    }


    fin.close();
    fout.close();

    return 0;
}