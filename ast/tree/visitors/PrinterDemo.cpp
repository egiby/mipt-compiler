#include "PrinterDemo.h"


namespace NSyntaxTree {

    PrinterDemo::PrinterDemo() {
        PrintDemo("./tmp.gv");
    }

    void PrinterDemo::PrintDemo(std::string path) {
        const Program *demoProgram = CreateDemoTree();

        /*Эта часть должна быть в конструкторе PrettyPrinterVisitor, я полагаю*/
        outPut.open(path.c_str());
        outPut << "digraph g {\n" << "\n";
        /**/

        printVertex(demoProgram, std::string("Program"));

        /*Эта часть должна быть в деструкторе PrettyPrinterVisitor, я полагаю*/
        outPut << "}";
        outPut.close();
    }

    const Program* CreateDemoTree() {
        Program program;

        int value = 5;
        IntegerLiteralExpression integerLiteralExp(value);
        PrintlnStatement printLnStatement(&integerLiteralExp);
        MainClass mainClass("nameId", "mainClassArgsId", &printLnStatement);

        program.mainClass = std::unique_ptr<MainClass>(&mainClass);
        program.classes = nullptr;

        return &program;
    }

    void PrinterDemo::printVertex(const INode* node, const std::string label){
        outPut << "\tnode" << node << "[label=\"" << label << "\"]\n";
    }

    void PrinterDemo::printEdge(const INode* from, const INode * to){
        outPut << "\tnode" << from << "->" << "node" << to << "\n";
    }

    void PrinterDemo::printEdge(const INode* from, const INode * to, std::string label){
        outPut << "\tnode" << from << "->" << "node" << to << "[label=\"" << label << "\"]\n";
    }

    void PrinterDemo::printEdge(std::string from, std::string to){
        outPut << "\t" << from << "->" << to << "\n";
    }
    void PrinterDemo::printEdge(std::string from, const INode* to){
        outPut << "\t"<< from << "->" << "node" << to << "\n";
    }

    void PrinterDemo::Visit(const Program* node) {
        this->printVertex(node, std::string("Program"));

        node->mainClass->Accept(this);
        printEdge(node, (node->mainClass).get());

        for (const auto& cl : *(node->classes)){
            cl->Accept(this);
            printEdge(node, cl.get());
        }
    }    

    void PrinterDemo::Visit(const ClassDeclaration* node) {
        printVertex(node, "Class " + node->nameId + " extends " + node->extendsId);

        for (const auto& var : *(node->varDeclarations)) {
            var->Accept(this);
            printEdge(node, var.get());
        }

        for (const auto& method : *(node->methodDeclarations)){
            method->Accept(this);
            printEdge(node, method.get());
        }
    }

    void PrinterDemo::Visit(const MainClass* node) {
        printVertex(node, "Main " + node->nameId + " mainArgsId" + node->mainArgsId);
        
        node->mainStatement->Accept(this);
        printEdge(node, (node->mainStatement).get());
    }

    void PrinterDemo::Visit(const VarDeclaration* node) {
        printVertex(node, node->type.id +" "+ node->id);
    }

    void PrinterDemo::Visit(const MethodDeclaration* node) {
        printVertex(node, "method " + node->returnType.id + " " + node->nameId);
        
        /*for (const auto arg : node->args){
            printEdge(node, arg, "arg");
        }

        for (auto var : node->vars){
            var->accept(this);
            printEdge(node, var, "var");
        }
        for (auto statement : node->statements){
            statement->accept(this);
            printEdge(node, statement);
        }
        

        node->res->accept(this);
        printEdge(node, node->res, "return");*/
    }
}
