//
// Created by black on 08.02.2022.
//

#ifndef ZALICZENIE_HEADER_H
#define ZALICZENIE_HEADER_H

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <vector>

using namespace std;

typedef vector<vector<string>> ROM;
typedef vector<string> SVC;

bool comm(string* acc,int* err,ROM* rooms, SVC* services, SVC* types);
void home();
void errf();
void load(ROM* rooms, SVC* services, SVC* types);
void save(ROM* rooms, SVC* services, SVC* types);

#endif //ZALICZENIE_HEADER_H
