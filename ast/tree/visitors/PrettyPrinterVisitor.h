#pragma once

#include "IVisitor.h"

#include <iostream>

#include <fstream>
#include <string>
#include "ast/tree/INode.h"
#include "ast/tree/Program.h"
#include "ast/tree/Expression.h"
#include "ast/tree/Statement.h"
#include "ast/tree/Class.h"

namespace NSyntaxTree {
    class PrettyPrinterVisitor : public IVisitor {

        std::ostream& outPut;
        //std::string path;
        //int level;

        void PrintIndent();
    public:
        //inline explicit PrettyPrinterVisitor(std::ostream& out = std::cout) : out(out), level(0) {}
        inline explicit PrettyPrinterVisitor(std::ostream& _outPut = std::cout) : outPut(_outPut) {}
        ~PrettyPrinterVisitor() {}

        void printVertex(const INode* node, const std::string label);
        void printVertex(const std::string node, const std::string label);
        void printEdge(const INode* from, const INode * to);
        void printEdge(const INode* from, const INode * to, const std::string label);
        void printEdge(std::string from, std::string to);
        void printEdge(std::string from, const INode* to);
        void printEdge(const INode* from, std::string to);

        void Visit(const Program *) override;

        void Visit(const ClassDeclaration *) override;
        void Visit(const MainClass *) override;

        void Visit(const VarDeclaration *) override;

        void Visit(const MethodDeclaration *) override;

        void Visit(const Statements *) override;
        void Visit(const IfStatement *) override;
        void Visit(const WhileStatement *) override;
        void Visit(const PrintlnStatement *) override;
        void Visit(const AssignStatement *) override;
        void Visit(const ArrayElementAssignmentStatement *) override;

        void Visit(const BinaryExpression *) override;
        void Visit(const ArrayElementAccessExpression *) override;
        void Visit(const ArrayLengthExpression *) override;
        void Visit(const MethodCallExpression *) override;
        void Visit(const IntegerLiteralExpression *) override;
        void Visit(const BoolLiteralExpression *) override;
        void Visit(const IdentifierExpression *) override;
        void Visit(const ThisExpression *) override;
        void Visit(const NewIntArrayExpression *)  override;
        void Visit(const NewExpression *) override;
        void Visit(const NegateExpression *) override;
    };
}
