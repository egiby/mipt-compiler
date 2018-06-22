#include "DotPrinter.h"

void NUtil::DotPrinter::printVertex(const std::string &node, const std::string &label) {
        outPut << "\tnode" << node << "[label=\"" << label << "\"]\n";
}

void NUtil::DotPrinter::printEdge(const std::string &from, const std::string &to) {
        outPut << "\tnode" << from << "->" << to << "\n";
}