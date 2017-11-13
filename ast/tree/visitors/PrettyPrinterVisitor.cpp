#include "PrettyPrinterVisitor.h"

namespace NSyntaxTree {

    void PrettyPrinterVisitor::printVertex(const INode* node, const std::string label) {
        outPut << "\tnode" << node << "[label=\"" << label << "\"]\n";
    }

    void PrettyPrinterVisitor::printVertex(const std::string node, const std::string label) {
        outPut << "\tnode" << node << "[label=\"" << label << "\"]\n";
    }

    void PrettyPrinterVisitor::printEdge(const INode* from, const INode * to){
        outPut << "\tnode" << from << "->" << "node" << to << "\n";
    }

    void PrettyPrinterVisitor::printEdge(const INode* from, const INode * to, std::string label){
        outPut << "\tnode" << from << "->" << "node" << to << "[label=\"" << label << "\"]\n";
    }

    void PrettyPrinterVisitor::printEdge(std::string from, std::string to){
        outPut << "\t" << from << "->" << to << "\n";
    }
    void PrettyPrinterVisitor::printEdge(std::string from, const INode* to){
        outPut << "\t"<< from << "->" << "node" << to << "\n";
    }

    void PrettyPrinterVisitor::printEdge(const INode* from, std::string to) {
         outPut << "\tnode" << from << "->" << to << "\n";
    }
        
    void PrettyPrinterVisitor::Visit(const Program* node) {
        //outPut.open(path.c_str());
        outPut << "digraph g {\n" << "\n";

        this->printVertex(node, std::string("Program"));

        node->mainClass->Accept(this);
        printEdge(node, (node->mainClass).get());

        if (node->classes != nullptr) {
            for (const auto &cl : *(node->classes)) {
                cl->Accept(this);
                printEdge(node, cl.get());
            }
        }

        outPut << "}";
        //outPut.close();
    }    

    void PrettyPrinterVisitor::Visit(const ClassDeclaration* node) {
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

    void PrettyPrinterVisitor::Visit(const MainClass* node) {
        printVertex(node, "Main " + node->nameId + " mainArgsId " + node->mainArgsId);
        node->mainStatement->Accept(this);
        printEdge(node, (node->mainStatement).get());
    }

    void PrettyPrinterVisitor::Visit(const VarDeclaration* node) {
        printVertex(node, node->type.id +" "+ node->id);
    }

    void PrettyPrinterVisitor::Visit(const MethodDeclaration* node) {
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

    void PrettyPrinterVisitor::Visit(const Statements* node) {
        printVertex(node, "statements");
        if (node->statements != nullptr) {
            for (const auto& statement : *(node->statements)){
                statement->Accept(this);
                printEdge(node, statement.get());
            }
        }
    }

    void PrettyPrinterVisitor::Visit(const IfStatement* node) {
        printVertex(node, "If");
        node->condition->Accept(this);
        printEdge(node, (node->condition).get(), "condition");
        node->trueStatement->Accept(this);
        printEdge(node, (node->trueStatement).get(), "True");
        node->falseStatement->Accept(this);
        printEdge(node, (node->falseStatement).get(), "False");
    }

    void PrettyPrinterVisitor::Visit(const WhileStatement* node) {
        printVertex(node, "while");
        node->condition->Accept(this);
        printEdge(node, (node->condition).get(), "condition");
        node->trueStatement->Accept(this);
        printEdge(node, (node->trueStatement).get(), "true statement");
    }

    void PrettyPrinterVisitor::Visit(const PrintlnStatement* node) {
        printVertex(node, "println");
        node->toPrint->Accept(this);
        printEdge(node, (node->toPrint).get());
    }

    void PrettyPrinterVisitor::Visit(const AssignStatement* node) {
        printVertex(node, node->lvalue + "=");
        node->rvalue->Accept(this);
        printEdge(node, (node->rvalue).get(), "rvalue");
    }

    void PrettyPrinterVisitor::Visit(const ArrayElementAssignmentStatement* node) {
        printVertex(node, "array " + node->arrayId + "elem assign");
        node->index->Accept(this);
        printEdge(node, (node->index).get(), "index");
        node->rvalue->Accept(this);
        printEdge(node, (node->rvalue).get());
    }

    void PrettyPrinterVisitor::Visit(const BinaryExpression* node) {
        printVertex(node, "binary exp " + node->type);
        node->left->Accept(this);
        node->right->Accept(this);
        printEdge(node, (node->left).get(), "left");
        printEdge(node, (node->right).get(), "right");
    }

    void PrettyPrinterVisitor::Visit(const ArrayElementAccessExpression* node) {
        printVertex(node, "AccessToElement");
        node->array->Accept(this);
        printEdge(node, (node->array).get(), "array");
        node->index->Accept(this);
        printEdge(node, (node->index).get(), "index");
    }

    void PrettyPrinterVisitor::Visit(const ArrayLengthExpression* node) {
        printVertex(node, "lengthExpresstion");
        node->array->Accept(this);
        printEdge(node, (node->array).get(), "array");
    }

    void PrettyPrinterVisitor::Visit(const MethodCallExpression* node) {
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

    void PrettyPrinterVisitor::Visit(const IntegerLiteralExpression* node) {
        printVertex(node, "int " + std::to_string(node->value));
    }

    void PrettyPrinterVisitor::Visit(const BoolLiteralExpression* node) {
        printVertex(node, "bool " + std::to_string(node->value));
    }

    void PrettyPrinterVisitor::Visit(const IdentifierExpression* node) {
        printVertex(node, "identifier " + (node->identifier));
    }

    void PrettyPrinterVisitor::Visit(const ThisExpression* node) {
        printVertex(node, "this");
    }

    void PrettyPrinterVisitor::Visit(const NewIntArrayExpression* node) {
        printVertex(node, "new int[]");
        node->size->Accept(this);
        printEdge(node, (node->size).get(), "size");
    }

    void PrettyPrinterVisitor::Visit(const NewExpression* node) {
        printVertex(node, "new " + (node->classId));
    }

    void PrettyPrinterVisitor::Visit(const NegateExpression* node) {
        printVertex(node, "negate");
        node->expression->Accept(this);
        printEdge(node, (node->expression).get());
    }

    /*void PrettyPrinterVisitor::Visit(const Program *node) {
        PrintIndent();
        out << "Program:\n";

        level++;
        node->mainClass->Accept(this);

        for (const auto& classDeclaration: node->classes) {
            classDeclaration->Accept(this);
        }
        level--;
    }

    void PrettyPrinterVisitor::Visit(const ClassDeclaration *node) {
        PrintIndent();
        out << "Class " << node->nameId;
        if (!node->extendsId.empty())
            out << " extends " << node->extendsId;
        out << ":\n";

        level++;
        for (const auto& varDeclaration: node->varDeclarations) {
            varDeclaration->Accept(this);
        }

        for (const auto& methodDeclaration: node->methodDeclarations) {
            methodDeclaration->Accept(this);
        }
        level--;
    }

    void PrettyPrinterVisitor::Visit(const MainClass *node) {
        PrintIndent();
        out << "MAIN:\n";

        level++;
        level--;
    }*/
}