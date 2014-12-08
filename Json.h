//
//  Json.h
//  agenda
//
//  Created by wc on 14-6-29.
//  Copyright (c) 2014年 wc. All rights reserved.
//

#ifndef __agenda__Json__
#define __agenda__Json__

#include <iostream>
#include <list>
#include <string>
#include <vector>

class Json {
public:
    Json();
    ~Json();
    int splitNum(std::string&);
    std::vector<std::string> splitRecordList(std::string&);
private:
};

#endif /* defined(__agenda__Json__) */
