#include <ast/TreeBuilder.h>
#include <ast/tree/visitors/PrettyPrinterVisitor.h>

#include <irt/translator/IRPrettyPrinter.h>

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {

    std::ofstream outIrt("./graph_irt.gv");

    NIRTree::IRPrettyPrinter irPrinter(outIrt);

    auto globalRoot = NIRTree::GlobalIRTParent();

    auto node1 = NIRTree::Const(12, {});
    auto binop = NIRTree::Binop(NIRTree::AND, new NIRTree::Const(43, {}), new NIRTree::Const(44, {}), {});
    auto eseq = NIRTree::ESeq(new NIRTree::Exp(new NIRTree::Const(42, {}), {}),
        new NIRTree::Const(43, {}), {});
    auto call = NIRTree::Call(new NIRTree::Const(43, {}),
        new NIRTree::ExpList(new NIRTree::Const(43, {}), new NIRTree::Const(43, {}), {}), {});
    auto mem = NIRTree::Mem(new NIRTree::Const(12, {}), {});
    auto unop = NIRTree::Unop(NIRTree::Unop::NOT, new NIRTree::Const(12, {}), {});
    auto temp1 = NIRTree::Temp("temp1", {});
    auto temp2 = NIRTree::Temp(123, {});
    auto name = NIRTree::Name("namename", {});

    auto node2 = NIRTree::Exp(new NIRTree::Const(42, {}), {});
    NIRTree::Label *helperLabel = NIRTree::LabelHolder::GetLabel(name.label->String());
    auto jump = NIRTree::Jump(helperLabel, {});
    auto move = NIRTree::Move(new NIRTree::Const(42, {}), new NIRTree::Const(42, {}), {});
    auto cjump = NIRTree::CJump(NIRTree::CJump::EQ, 
        new NIRTree::Const(42, {}),
        new NIRTree::Const(42, {}),
        helperLabel, helperLabel, {});
    auto labelStm = NIRTree::LabelStm(helperLabel, {});
    auto seq = NIRTree::Seq(new NIRTree::Jump(helperLabel, {}),
        new NIRTree::Jump(helperLabel, {}), {});

    NIRTree::StmWrapper stmWrapper(new NIRTree::LabelStm(helperLabel, {}));
    NIRTree::ExprWrapper expWrapper(new NIRTree::Call(new NIRTree::Const(43, {}),
        new NIRTree::ExpList(new NIRTree::Const(43, {}), new NIRTree::Const(43, {}), {}), {}));

    NIRTree::StmWrapper stmWrapperDeep(
        new NIRTree::Seq(new NIRTree::Move(new NIRTree::Binop(NIRTree::OR, new NIRTree::Const(43, {}), 
                new NIRTree::Const(44, {}), {}), new NIRTree::Const(42, {}), {}),
            new NIRTree::Jump(helperLabel, {}), {})
    );
    

    globalRoot.roots = {&node1, &node2, &binop, &eseq, &call, &mem, &unop, &temp1, &temp2,
        &name, &jump, &move, &cjump, &labelStm, &seq,
        &stmWrapper, &expWrapper, &stmWrapperDeep};

    irPrinter.Visit(&globalRoot);

    outIrt.close();

    return 0;
}