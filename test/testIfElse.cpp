#include "test.hpp"
#include "../include/context.hpp"


int main() {
    Context context;
    int program_len = 1024;

    string program =
    "int x;"
    "int y;"
    "int z;"
    "x = 2;"
    "y = 3;"
    "z = 4;"
    "if(x / 2 == 1) {"
        "y = y + 1;"
    "} else {"
        "y = z - 3;"
    "}";

    string expected;
    expected.reserve(program_len);
    string lbl1 = context.createLabel(), lbl2 = context.createLabel();
    expected.append(AOperation("LOADi", 1, "x%0").toString());
    expected.append(AOperation("LOADi", 1, "y%0").toString());
    expected.append(AOperation("LOADi", 1, "z%0").toString());
    expected.append(AOperation("MOV", 2, "x%0", "2").toString());
    expected.append(AOperation("MOV", 2, "y%0", "3").toString());
    expected.append(AOperation("MOV", 2, "z%0", "4").toString());
    expected.append(AOperation("DIV", 3, "%0", "x%0", "2").toString());
    expected.append(AOperation("CEQ", 3, "%1", "%0", "1").toString());
    expected.append(AOperation("JZ", 2, "%1", lbl1.c_str()).toString());
    expected.append(AOperation("ADD", 3, "%2", "y%0", "1").toString());
    expected.append(AOperation("MOV", 2, "y%0", "%2").toString());
    expected.append(AOperation("JMP", 1, lbl2.c_str()).toString());
    expected.append(ALabel(lbl1).toString());
    expected.append(AOperation("SUB", 3, "%3", "z%0", "3").toString());
    expected.append(AOperation("MOV", 2, "y%0", "%3").toString());
    expected.append(ALabel(lbl2).toString());

    return runTest(program, expected, program_len, "IfElse");
}