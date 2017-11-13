#include "PrinterDemo.h"
#include <iostream>

namespace NSyntaxTree {

    PrinterDemo::PrinterDemo() {}

    void PrinterDemo::PrintDemo(std::string path) {
        Program demoProgram;
        CreateDemoTree(demoProgram);

        /*Эта часть должна быть в конструкторе PrettyPrinterVisitor, я полагаю*/
        outPut.open(path.c_str());
        outPut << "digraph g {\n" << "\n";
        /**/

        Visit(&demoProgram);

        /*Эта часть должна быть в деструкторе PrettyPrinterVisitor, я полагаю*/
        outPut << "}";
        outPut.close();
    }

    void PrinterDemo::CreateDemoTree(Program &program) {
        int value = 5;
        IntegerLiteralExpression *integerLiteralExp = new IntegerLiteralExpression(value);
        PrintlnStatement *printLnStatement = new PrintlnStatement(integerLiteralExp);
        MainClass *mainClass = new MainClass("nameId", "mainClassArgsId", printLnStatement);

        program.mainClass = std::unique_ptr<MainClass>(mainClass);
        program.classes = nullptr;
    }

    void PrinterDemo::printVertex(const INode* node, const std::string label) {
        outPut << "\tnode" << node << "[label=\"" << label << "\"]\n";
    }

    void PrinterDemo::printVertex(const std::string node, const std::string label) {
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

    void PrinterDemo::printEdge(const INode* from, std::string to) {
         outPut << "\tnode" << from << "->" << to << "\n";
    }

    void PrinterDemo::Visit(const Program* node) {
        //std::cout << "Visiting program node" << std::endl;
        this->printVertex(node, std::string("Program"));

        //std::cout << "Going to visit main class" << std::endl;
        node->mainClass->Accept(this);
        printEdge(node, (node->mainClass).get());

        //std::cout << "Going to visit classes" << std::endl;
        if (node->classes != nullptr) {
            for (const auto &cl : *(node->classes)) {
                //std::cout << "Class visiting started" << std::endl;
                cl->Accept(this);
                printEdge(node, cl.get());
            }
        }
    }    

    void PrinterDemo::Visit(const ClassDeclaration* node) {
        printVertex(node, "Class " + node->nameId + " extends " + node->extendsId);

        if (node->varDeclarations != nullptr) {
            for (const auto& var : *(node->varDeclarations)) {
                var->Accept(this);
                printEdge(node, var.get());
            }
        }

        if (node->methodDeclarations != nullptr) {
            for (const auto& method : *(node->methodDeclarations)){
                method->Accept(this);
                printEdge(node, method.get());
            }
        }
    }

    void PrinterDemo::Visit(const MainClass* node) {
        printVertex(node, "Main " + node->nameId + " mainArgsId " + node->mainArgsId);
        node->mainStatement->Accept(this);
        printEdge(node, (node->mainStatement).get());
    }

    void PrinterDemo::Visit(const VarDeclaration* node) {
        printVertex(node, node->type.id +" "+ node->id);
    }

    void PrinterDemo::Visit(const MethodDeclaration* node) {
        //printVertex(node, "method " + node->returnType.id + " " + node->nameId);
        printVertex(node, "method " + node->nameId);
        switch ((node->returnType).type) {
            case CLASS:
                printVertex("CLASS " + node->returnType.id, "returnType");
                printEdge(node, "CLASS " + node->returnType.id);
                break;
            case INT:
                printVertex("INT " + node->nameId, "returnType");
                printEdge(node, "INT " + node->nameId);
                break;
            case BOOL:
                printVertex("BOOL " + node->nameId, "returnType");
                printEdge(node, "BOOL " + node->nameId);
                break;
            case INT_ARRAY:
                printVertex("INT_ARRAY " + node->nameId, "returnType");
                printEdge(node, "INT_ARRAY " + node->nameId);
                break;
        }
        
        for (const auto arg : node->args) {
            switch(arg.first.type) {
                case CLASS:
                    printVertex("CLASS " + arg.first.id + " " + arg.second, "arg");
                    printEdge(node, "CLASS " + arg.first.id + " " + arg.second);
                    break;
                case INT:
                    printVertex("INT " + arg.second, "arg");
                    printEdge(node, "INT " + arg.second);
                    break;
                case BOOL:
                    printVertex("BOOL " + arg.second, "arg");
                    printEdge(node, "BOOL " + arg.second);
                    break;
                case INT_ARRAY:
                    printVertex("INT_ARRAY " + arg.second, "arg");
                    printEdge(node, "INT_ARRAY " + arg.second);
                    break;
            }
        }

        if (node->localVars != nullptr) {
            for (const auto& var : *(node->localVars)) {
                var->Accept(this);
                printEdge(node, var.get(), "local var");
            }
        }
        if (node->statements != nullptr) {
            for (const auto& statement : *(node->statements)) {
               statement->Accept(this);
                printEdge(node, statement.get());
            }
        }
        
        node->returnExpression->Accept(this);
        printEdge(node, (node->returnExpression).get(), "return");
    }

    void PrinterDemo::Visit(const Statements* node) {
        printVertex(node, "statements");
        if (node->statements != nullptr) {
            for (const auto& statement : *(node->statements)){
                statement->Accept(this);
                printEdge(node, statement.get());
            }
        }
    }

    void PrinterDemo::Visit(const IfStatement* node) {
        printVertex(node, "If");
        node->condition->Accept(this);
        printEdge(node, (node->condition).get(), "condition");
        node->trueStatement->Accept(this);
        printEdge(node, (node->trueStatement).get(), "True");
        node->falseStatement->Accept(this);
        printEdge(node, (node->falseStatement).get(), "False");
    }

    void PrinterDemo::Visit(const WhileStatement* node) {
        printVertex(node, "while");
        node->condition->Accept(this);
        printEdge(node, (node->condition).get(), "condition");
        node->trueStatement->Accept(this);
        printEdge(node, (node->trueStatement).get(), "true statement");
    }

    void PrinterDemo::Visit(const PrintlnStatement* node) {
        printVertex(node, "println");
        node->toPrint->Accept(this);
        printEdge(node, (node->toPrint).get());
    }

    void PrinterDemo::Visit(const AssignStatement* node) {
        printVertex(node, node->lvalue + "=");
        node->rvalue->Accept(this);
        printEdge(node, (node->rvalue).get(), "rvalue");
    }

    void PrinterDemo::Visit(const ArrayElementAssignmentStatement* node) {
        printVertex(node, "array " + node->arrayId + "elem assign");
        node->index->Accept(this);
        printEdge(node, (node->index).get(), "index");
        node->rvalue->Accept(this);
        printEdge(node, (node->rvalue).get());
    }

    void PrinterDemo::Visit(const BinaryExpression* node) {
        printVertex(node, "binary exp " + node->type);
        node->left->Accept(this);
        node->right->Accept(this);
        printEdge(node, (node->left).get(), "left");
        printEdge(node, (node->right).get(), "right");
    }

    void PrinterDemo::Visit(const ArrayElementAccessExpression* node) {
        printVertex(node, "AccessToElement");
        node->array->Accept(this);
        printEdge(node, (node->array).get(), "array");
        node->index->Accept(this);
        printEdge(node, (node->index).get(), "index");
    }

    void PrinterDemo::Visit(const ArrayLengthExpression* node) {
        printVertex(node, "lengthExpresstion");
        node->array->Accept(this);
        printEdge(node, (node->array).get(), "array");
    }

    void PrinterDemo::Visit(const MethodCallExpression* node) {
        printVertex(node, "methodCall");
        node->object->Accept(this);
        printEdge(node, (node->object).get(), "method " + node->nameId);
        
        if (node->args != nullptr) {
            for (const auto& arg : *(node->args)){
               arg->Accept(this);
                printEdge(node, arg.get(), "arg");
            }
        }
    }

    void PrinterDemo::Visit(const IntegerLiteralExpression* node) {
        printVertex(node, "int " + std::to_string(node->value));
    }

    void PrinterDemo::Visit(const BoolLiteralExpression* node) {
        printVertex(node, "bool " + std::to_string(node->value));
    }

    void PrinterDemo::Visit(const IdentifierExpression* node) {
        printVertex(node, "identifier " + (node->identifier));
    }

    void PrinterDemo::Visit(const ThisExpression* node) {
        printVertex(node, "this");
    }

    void PrinterDemo::Visit(const NewIntArrayExpression* node) {
        printVertex(node, "new int[]");
        node->size->Accept(this);
        printEdge(node, (node->size).get(), "size");
    }

    void PrinterDemo::Visit(const NewExpression* node) {
        printVertex(node, "new " + (node->classId));
    }

    void PrinterDemo::Visit(const NegateExpression* node) {
        printVertex(node, "negate");
        node->expression->Accept(this);
        printEdge(node, (node->expression).get());
    }
}
