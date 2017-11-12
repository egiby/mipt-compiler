#include <iostream>
#include "PrinterDemo.h"

int main() {
    std::cout << "Hello!" << std::endl;

    NSyntaxTree::PrinterDemo pd;
    pd.PrintDemo("./graph.gv");

    return 0;
}