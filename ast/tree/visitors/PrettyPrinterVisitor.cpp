#include "PrettyPrinterVisitor.h"

namespace NSyntaxTree {

    void PrettyPrinterVisitor::printVertex(const INode *node, const std::string &label) {
        outPut << "\tnode" << node << "[label=\"" << label << "\"]\n";
    }

    void PrettyPrinterVisitor::printVertex(const std::string &node, const std::string &label) {
        outPut << "\tnode" << node << "[label=\"" << label << "\"]\n";
    }

    void PrettyPrinterVisitor::printEdge(const INode *from, const INode *to) {
        outPut << "\tnode" << from << "->" << "node" << to << "\n";
    }

    void PrettyPrinterVisitor::printEdge(const INode *from, const INode *to, const std::string &label) {
        outPut << "\tnode" << from << "->" << "node" << to << "[label=\"" << label << "\"]\n";
    }

    void PrettyPrinterVisitor::printEdge(const std::string &from, const std::string &to) {
        //outPut << "\t" << from << "->" << to << "\n";
        outPut << "\tnode" << from << "->" << to << "\n";
    }

    void PrettyPrinterVisitor::printEdge(const std::string &from, const INode *to) {
        outPut << "\t" << from << "->" << "node" << to << "\n";
    }

    void PrettyPrinterVisitor::printEdge(const INode *from, const std::string &to) {
        outPut << "\tnode" << from << "->" << to << "\n";
    }

    void PrettyPrinterVisitor::Visit(const Program *node) {
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
    }

    void PrettyPrinterVisitor::Visit(const ClassDeclaration *node) {
        printVertex(node, "Class " + node->nameId + " extends " + node->extendsId);

        if (node->varDeclarations != nullptr) {
            for (const auto &var : *(node->varDeclarations)) {
                var->Accept(this);
                printEdge(node, var.get());
            }
        }

        if (node->methodDeclarations != nullptr) {
            for (const auto &method : *(node->methodDeclarations)) {
                method->Accept(this);
                printEdge(node, method.get());
            }
        }
    }

    void PrettyPrinterVisitor::Visit(const MainClass *node) {
        printVertex(node, "Main " + node->nameId + " mainArgsId " + node->mainArgsId);
        node->mainStatement->Accept(this);
        printEdge(node, (node->mainStatement).get());
    }

    void PrettyPrinterVisitor::Visit(const VarDeclaration *node) {
        printVertex(node, node->type.id + " " + node->id);
    }

    void PrettyPrinterVisitor::Visit(const MethodDeclaration *node) {
        std::string label = "method" + node->nameId;
        switch ((node->returnType).type) {
            case CLASS:
                label = label + " returnType: CLASS " + node->returnType.id;
                break;
            case INT:
                label = label + " returnType: INT";
                break;
            case BOOL:
                label = label + " returnType: BOOL";
                break;
            case INT_ARRAY:
                label = label + " returnType: INT_ARRAY";
                break;
        }  

        for (const auto arg : node->args) {
            switch (arg.first.type) {
                case CLASS:
                    label = label + " arg: CLASS " + arg.first.id + " " + arg.second;
                    break;
                case INT:
                    label = label + " arg: INT " + arg.second;
                    break;
                case BOOL:
                    label = label + " arg: BOOL" + arg.second;
                    break;
                case INT_ARRAY:
                    label = label + " arg INT_ARRAY " + arg.second;
                    break;
            }
        }
        printVertex(node, label); 

        if (node->localVars != nullptr) {
            for (const auto &var : *(node->localVars)) {
                var->Accept(this);
                printEdge(node, var.get(), "local var");
            }
        }
        if (node->statements != nullptr) {
            for (const auto &statement : *(node->statements)) {
                statement->Accept(this);
                printEdge(node, statement.get());
            }
        }

        node->returnExpression->Accept(this);
        printEdge(node, (node->returnExpression).get(), "return");
    }

    void PrettyPrinterVisitor::Visit(const Statements *node) {
        printVertex(node, "statements");
        if (node->statements != nullptr) {
            for (const auto &statement : *(node->statements)) {
                statement->Accept(this);
                printEdge(node, statement.get());
            }
        }
    }

    void PrettyPrinterVisitor::Visit(const IfStatement *node) {
        printVertex(node, "If");
        node->condition->Accept(this);
        printEdge(node, (node->condition).get(), "condition");
        node->trueStatement->Accept(this);
        printEdge(node, (node->trueStatement).get(), "True");
        node->falseStatement->Accept(this);
        printEdge(node, (node->falseStatement).get(), "False");
    }

    void PrettyPrinterVisitor::Visit(const WhileStatement *node) {
        printVertex(node, "while");
        node->condition->Accept(this);
        printEdge(node, (node->condition).get(), "condition");
        node->trueStatement->Accept(this);
        printEdge(node, (node->trueStatement).get(), "true statement");
    }

    void PrettyPrinterVisitor::Visit(const PrintlnStatement *node) {
        printVertex(node, "println");
        node->toPrint->Accept(this);
        printEdge(node, (node->toPrint).get());
    }

    void PrettyPrinterVisitor::Visit(const AssignStatement *node) {
        printVertex(node, node->lvalue + "=");
        node->rvalue->Accept(this);
        printEdge(node, (node->rvalue).get(), "rvalue");
    }

    void PrettyPrinterVisitor::Visit(const ArrayElementAssignmentStatement *node) {
        printVertex(node, "array " + node->arrayId + "elem assign");
        node->index->Accept(this);
        printEdge(node, (node->index).get(), "index");
        node->rvalue->Accept(this);
        printEdge(node, (node->rvalue).get());
    }

    void PrettyPrinterVisitor::Visit(const BinaryExpression *node) {
        printVertex(node, "binary exp " + node->type);
        node->left->Accept(this);
        node->right->Accept(this);
        printEdge(node, (node->left).get(), "left");
        printEdge(node, (node->right).get(), "right");
    }

    void PrettyPrinterVisitor::Visit(const ArrayElementAccessExpression *node) {
        printVertex(node, "AccessToElement");
        node->array->Accept(this);
        printEdge(node, (node->array).get(), "array");
        node->index->Accept(this);
        printEdge(node, (node->index).get(), "index");
    }

    void PrettyPrinterVisitor::Visit(const ArrayLengthExpression *node) {
        printVertex(node, "lengthExpresstion");
        node->array->Accept(this);
        printEdge(node, (node->array).get(), "array");
    }

    void PrettyPrinterVisitor::Visit(const MethodCallExpression *node) {
        printVertex(node, "methodCall");
        node->object->Accept(this);
        printEdge(node, (node->object).get(), "method " + node->nameId);

        if (node->args != nullptr) {
            for (const auto &arg : *(node->args)) {
                arg->Accept(this);
                printEdge(node, arg.get(), "arg");
            }
        }
    }

    void PrettyPrinterVisitor::Visit(const IntegerLiteralExpression *node) {
        printVertex(node, "int " + std::to_string(node->value));
    }

    void PrettyPrinterVisitor::Visit(const BoolLiteralExpression *node) {
        printVertex(node, "bool " + std::to_string(node->value));
    }

    void PrettyPrinterVisitor::Visit(const IdentifierExpression *node) {
        printVertex(node, "identifier " + (node->identifier));
    }

    void PrettyPrinterVisitor::Visit(const ThisExpression *node) {
        printVertex(node, "this");
    }

    void PrettyPrinterVisitor::Visit(const NewIntArrayExpression *node) {
        printVertex(node, "new int[]");
        node->size->Accept(this);
        printEdge(node, (node->size).get(), "size");
    }

    void PrettyPrinterVisitor::Visit(const NewExpression *node) {
        printVertex(node, "new " + (node->classId));
    }

    void PrettyPrinterVisitor::Visit(const NegateExpression *node) {
        printVertex(node, "negate");
        node->expression->Accept(this);
        printEdge(node, (node->expression).get());
    }
}