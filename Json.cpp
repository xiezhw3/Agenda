//
//  Json.cpp
//  agenda
//
//  Created by wc on 14-6-29.
//  Copyright (c) 2014年 wc. All rights reserved.
//

#include "Json.h"
#include <sstream>
#include <iostream>
#include <string>

Json::Json() {}

Json::~Json() {}

int Json::splitNum(std::string& str) {
    std::string tmp;
    std::stringstream strss(str);
    while (std::getline(strss, tmp, ':')) {
        ;
	}
    int num;
    std::istringstream snum(tmp);
	snum >> num;
	return num;
}

std::vector<std::string> Json::splitRecordList(std::string& str) {
    std::stringstream strs(str);
    std::string tmp;
    std::vector<std::string> record;
    int i = 0;
	while (std::getline(strs, tmp, '\"')) {
        ++i;
        if (i % 2 == 0)
            record.push_back(tmp);
	}
    return record;
}