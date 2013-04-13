//
//  main.cpp
//  DZ1
//
//  Created by Filip Beć on 4/13/13.
//  Copyright (c) 2013 Filip Beć. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
using namespace std;

vector< set<int> > V;
stack<int> hamPath;
int N;

//rekurzivna metoda koja ispituje postoji li hamiltonov ciklus
// @param start     - pocetni cvor iz kojeg krecemo
// @param i         - trenutni cvor
// @param visited   - vec posjeceni cvorovi

bool isHamiltonian(int start, int i, set<int> visited = set<int>())
{
    visited.insert(i);
    
    //provjerimo ako smo bili u svima i ako ima brid do pocetnog znaci da je gotovo
    if (visited.size() == N) {
        if (V[i].find(start) != V[i].end()) {
            hamPath.push(start);
            hamPath.push(i);
            return true;
        }
        return false;
    }

    for (set<int>::iterator it = V[i].begin(); it != V[i].end(); ++it) {
        //ako nismo jos bili u tom cvoru idemo u njega
        if (visited.find(*it) == visited.end()) {
            if (isHamiltonian(start, *it, visited)) {
                hamPath.push(i);
                return true;
            }
        }
    }
    
    return false;
}

void printHamPath()
{
    while (hamPath.size() > 1) {
        printf("%d -> ", hamPath.top());
        hamPath.pop();
    }
    printf("%d\n", hamPath.top());
}


int main(int argc, const char * argv[])
{
    FILE *f;
#ifndef DEBUG
    if (argc != 2) {
        fprintf(stderr, "Programu je potrebno kao argument zadati putanju datoteke s podacima o grafu.\n");
        return 0;
    }
    
    f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "Open fail.\n");
        return 0;
    }
#else
    f = stdin;
#endif
    
    fscanf(f, "%d", &N);
    
    //pripremamo strukturu za cuvanje bridova
    for (int i = 0; i < N; ++i) {
        V.push_back(set<int>());
    }
    
    //ucitavamo bridove
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int x;
            fscanf(f, "%d", &x);
            if (x == 1) {
                V[i].insert(j);
                V[j].insert(i);
            }
        }
    }
    
#ifdef DEBUG
    //ispis bridova
    printf("\n");
    for (int i = 0; i < N; ++i) {
        printf("%d:\n", i);
        for (set<int>::iterator it = V[i].begin(); it != V[i].end(); ++it) {
            printf("\t%d\n", *it);
        }
    }
#endif
    
    //provjera je li graf hamiltonovski
    bool isHam = false;
    for (int i = 0; i < V.size(); ++i) {
        if (isHamiltonian(i, i)) {
            printf("1\n");
            isHam = true;
            break;
        }
    }
    
    if (!isHam) {
        printf("0\n");
    } else {
#ifdef DEBUG
        //ispis hamiltonovog ciklusa
        printHamPath();
#endif
    }
    
    return 0;
}

