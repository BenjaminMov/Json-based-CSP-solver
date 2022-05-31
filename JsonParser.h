#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#pragma once

using namespace std;

class JsonParser {
    public: 
        void init();
        string getVar(int idx);
        string ConstraintFn(int idx);
        string ConstraintFirst(int idx);
        string ConstraintSecond(int idx);
        int min();
        int max();
        int varSize();
        int constraintSize();

    private:
        Json::Value jsonData;
        Json::Reader reader;
};