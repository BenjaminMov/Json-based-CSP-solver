
bool lt(int a, int b) {return a < b;}
bool gt(int a, int b) {return a > b;}
bool eq(int a, int b) {return a == b;}
bool leq(int a, int b) {return a <= b;}
bool geq(int a, int b) {return a >= b;}

void initFunction() {
    fn["LessThan"] = &lt;
    fn["GreaterThan"] = &gt;
    fn["Equal"] = &eq;
    fn["LessOrEqual"] = &leq;
    fn["GreaterOrEqual"] = &geq;
}  