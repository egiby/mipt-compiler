#include "IRPrettyPrinter.h"

namespace NIRTree {
    void IRPrettyPrinter::printVertex(const INode *node, const std::string &label) {
        outPut << "\tnode" << node << "[label=\"" << label << "\"]\n";
    }

    void IRPrettyPrinter::printEdge(const INode *from, const INode *to) {
        outPut << "\tnode" << from << "->" << "node" << to << "\n";
    }

    void IRPrettyPrinter::Visit(const Binop *node) {
        printVertex(node, std::string("Binop"));

        node->leftExp->Accept(this);
        printEdge(node, (node->leftExp).get());

        node->rightExp->Accept(this);
        printEdge(node, (node->rightExp).get());
    }

    void IRPrettyPrinter::Visit(const Call *node) {
        printVertex(node, std::string("Call"));

        node->funcExp->Accept(this);
        printEdge(node, (node->funcExp).get());

        node->args->Accept(this);
        printEdge(node, (node->args).get());
    }
    
    void IRPrettyPrinter::Visit(const Const *node) {
        printVertex(node, std::to_string(node->value));
    }
    
    void IRPrettyPrinter::Visit(const ESeq *node) {
        printVertex(node, std::string("ESeq"));
        
        node->stm->Accept(this);
        printEdge(node, (node->stm).get());

        node->exp->Accept(this);
        printEdge(node, (node->exp).get());
    }

    void IRPrettyPrinter::Visit(const Mem *node) {
        printVertex(node, std::string("Mem"));

        node->exp->Accept(this);
        printEdge(node, (node->exp).get());
    }
    
    void IRPrettyPrinter::Visit(const Name *node) {
        printVertex(node, std::string("Name"));

        // TODO!
        //node->label->Accept(this);
        //printEdge(node, node->label);
    }
        
    void IRPrettyPrinter::Visit(const Temp *node) {
        printVertex(node, std::string("Temp")); // ?
    }
        
    void IRPrettyPrinter::Visit(const Unop *node) {
        printVertex(node, std::string("Unop"));

        node->expression->Accept(this);
        printEdge(node, (node->expression).get());
    }

    void IRPrettyPrinter::Visit(const CJump *node) {
        printVertex(node, std::string("CJump"));

        node->leftExpr->Accept(this);
        printEdge(node, (node->leftExpr).get());

        node->rightExpr->Accept(this);
        printEdge(node, (node->rightExpr).get());

        // some problems with label

        //node->trueLabel->Accept(this);
        //printEdge(node, (node->trueLabel));

        //node->falseLabel->Accept(this);
        //printEdge(node, (node->falseLabel));
    }
   
    void IRPrettyPrinter::Visit(const Exp *node) {
        printVertex(node, std::string("Exp"));

        node->expr->Accept(this);
        printEdge(node, (node->expr).get());
    }
        
    void IRPrettyPrinter::Visit(const Jump *node) {
        printVertex(node, std::string("Jump"));

        // TODO: label
    }
        
    void IRPrettyPrinter::Visit(const Label *node) {
        // TODO
    }
        
    void IRPrettyPrinter::Visit(const Move *node) {
        printVertex(node, std::string("Move"));
        
        node->dst->Accept(this);
        printEdge(node, (node->dst).get());

        node->src->Accept(this);
        printEdge(node, (node->src).get());
    }
    
    void IRPrettyPrinter::Visit(const Seq *node) {
        printVertex(node, std::string("Seq"));
    }
/*
    void Visit(const ExprWrapper *node) {

    }
        
    void Visit(const StmWrapper *node) {

    }*/
}