#include <iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <string>

using namespace std;

class JsonParser {
    public:

        void init() {
            ifstream file("problem.json");
            reader.parse(file, jsonData);
        }

        string getVar(int idx) {
            return jsonData["Variables"][idx].asString();
        }

        string ConstraintFn(int idx) {
            return jsonData["Constraints"][idx]["function"].asString();
        }

        string ConstraintFirst(int idx) {
            return jsonData["Constraints"][idx]["elem1"].asString();
        }

        string ConstraintSecond(int idx) {
            return jsonData["Constraints"][idx]["elem2"].asString();
        }

        int min() {
            return jsonData["Domain"]["min"].asInt();
        }

        int max() {
            return jsonData["Domain"]["max"].asInt();
        }

        int varSize() {
            return jsonData["Variables"].size();
        }

        int constraintSize() {
            return jsonData["Constraints"].size();
        } 

    private:
        Json::Value jsonData;
        Json::Reader reader;
};