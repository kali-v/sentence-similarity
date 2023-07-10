#include "shashtable.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdlib>

Dist0HashTable::Dist0HashTable(int capacity) {
    this->table.reserve(capacity);
    this->capacity = capacity;
}

int Dist0HashTable::hash(std::string sentence, int cap) {
    ulong long hash = 1;
    for (char c : sentence) {
        hash = (31 * hash + 7 * c) % cap;
    }
    return hash;
};

int Dist0HashTable::insert(char* value) {
    int hash_val = this->hash(value, capacity);
    if (this->table[hash_val] == nullptr) {
        this->table[hash_val] = value;
        return 0;
    }
    return 1;
}

char* Dist0HashTable::get(int key) { return this->table[key]; }

Dist1HashTable::Dist1HashTable() {
    this->wcm = 101; // word count max
    this->ccm = 101; // character count max

    this->table.resize(wcm);
    for (int i = 0; i < wcm; i++) {
        this->table[i].resize(ccm);
    }
}

int Dist1HashTable::insert(std::string value) {
    int sval = 0;
    int wc = 0;
    int cc = 0;
    int dist = 0;
    int split_it = 2;
    int w_sens = 600; // max allowable diff in sums of chars

    for (char cr : value) {
        if (cr == ' ') wc++;
        if (cc > (int)(value.length() / split_it)) {
            dist = sval;
            sval = 0;
            split_it--;
        }
        cc++;
        sval += cr;
    }

    std::vector<int> hash{dist + sval, dist, sval};

    cc /= 5;
    cc = cc < ccm - 1 ? cc : ccm - 2;
    wc = wc < wcm - 1 ? wc : wcm - 2;

    int f = 0;
    if (wc > 0) {
#pragma omp parallel for
        for (int i = 0; i < this->table[wc - 1][cc].size(); i++) {
            if (((hash[1] == this->table[wc - 1][cc][i][1]) != (hash[2] == this->table[wc - 1][cc][i][2]))) {
                if (abs(hash[0] - this->table[wc - 1][cc][i][0]) < w_sens) {
                    f = 1;
                    i = this->table[wc - 1][cc].size();
                }
            }
        }
    }

    if (f == 0) {
#pragma omp parallel for
        for (int i = 0; i < this->table[wc + 1][cc].size(); i++) {
            if (((hash[1] == this->table[wc + 1][cc][i][1]) != (hash[2] == this->table[wc + 1][cc][i][2]))) {
                if (abs(hash[0] - this->table[wc + 1][cc][i][0]) < w_sens) {
                    f = 1;
                    i = this->table[wc + 1][cc].size();
                }
            }
        }
    }

    if (f == 1) return 1;

    this->table[wc][cc].push_back(hash);

    return 0;
}
