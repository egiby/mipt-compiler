#include <ast/TreeBuilder.h>
#include <ast/tree/visitors/PrettyPrinterVisitor.h>

#include <irt/translator/IRPrettyPrinter.h>
#include <irt/translator/Canoniser.h>


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

    std::unique_ptr<NIRTree::StmWrapper> stmWrapper(
        new NIRTree::StmWrapper(
            //new NIRTree::LabelStm(helperLabel, {})
            new NIRTree::Exp(new NIRTree::Binop(NIRTree::AND, new NIRTree::Const(43, {}), new NIRTree::Const(44, {}), {}), {})
        )
    );
    std::unique_ptr<NIRTree::ExprWrapper> expWrapper(
        new NIRTree::ExprWrapper (
            new NIRTree::Call (
                new NIRTree::Const(43, {}),
                new NIRTree::ExpList(new NIRTree::Const(43, {}), new NIRTree::Const(43, {}), {}),
                {}
            )
        )
    );

    std::unique_ptr<NIRTree::ExprWrapper> expWrapper2(
        new NIRTree::ExprWrapper(
            new NIRTree::Binop(NIRTree::AND, new NIRTree::Const(43, {}), new NIRTree::Const(44, {}), {})
        )
    );

    std::unique_ptr<NIRTree::StmWrapper> stmWrapperDeep(
        new NIRTree::StmWrapper(
            new NIRTree::Seq(new NIRTree::Move(new NIRTree::Binop(NIRTree::OR, new NIRTree::Const(43, {}), 
                    new NIRTree::Const(44, {}), {}), new NIRTree::Const(42, {}), {}),
                new NIRTree::Jump(helperLabel, {}), {}
            )
        )
    );

    // book (1)
    std::unique_ptr<NIRTree::ExprWrapper> expWrapper3(
        new NIRTree::ExprWrapper(
            new NIRTree::ESeq(
                new NIRTree::LabelStm(NIRTree::LabelHolder::GetLabel("s1"), {}),
                new NIRTree::ESeq(
                    new NIRTree::LabelStm(NIRTree::LabelHolder::GetLabel("s2"), {}),
                    new NIRTree::Name("e", {}),
                    {}
                ),
                {}
            )
        )
    );

    // book (2)
    std::unique_ptr<NIRTree::ExprWrapper> expWrapper4(
        new NIRTree::ExprWrapper(
            new NIRTree::Binop(
                NIRTree::AND,
                new NIRTree::ESeq(
                    new NIRTree::LabelStm(NIRTree::LabelHolder::GetLabel("s"), {}),
                    new NIRTree::Name("e1", {}),
                    {}
                ),
                new NIRTree::Name("e2", {}),
                {}
            )
        )
    );

    std::unique_ptr<NIRTree::ExprWrapper> expWrapper5(
        new NIRTree::ExprWrapper(
            new NIRTree::Mem(
                new NIRTree::ESeq(
                    new NIRTree::LabelStm(NIRTree::LabelHolder::GetLabel("s"), {}),
                    new NIRTree::Name("e1", {}),
                    {}
                ),
                {}
            )
        )
    );

    std::unique_ptr<NIRTree::StmWrapper> stmWrapper6(
        new NIRTree::StmWrapper(
            new NIRTree::CJump(
                NIRTree::CJump::EQ, 
                new NIRTree::ESeq(
                    new NIRTree::LabelStm(NIRTree::LabelHolder::GetLabel("s"), {}),
                    new NIRTree::Name("e1", {}),
                    {}
                ),
                new NIRTree::Name("e2", {}),
                NIRTree::LabelHolder::GetLabel("l1"),
                NIRTree::LabelHolder::GetLabel("l2"),
                {}
            )
        )
    );

    // book (4)
    std::unique_ptr<NIRTree::ExprWrapper> expWrapper7(
        new NIRTree::ExprWrapper(
            new NIRTree::Binop(
                NIRTree::AND,
                new NIRTree::Name("e1", {}),
                new NIRTree::ESeq(
                    new NIRTree::LabelStm(NIRTree::LabelHolder::GetLabel("s"), {}),
                    new NIRTree::Name("e2", {}),
                    {}
                    ),
                {}
            )
        )
    );

    std::unique_ptr<NIRTree::StmWrapper> stmWrapper8(
        new NIRTree::StmWrapper(
            new NIRTree::CJump(
                NIRTree::CJump::EQ,
                new NIRTree::Name("e1", {}),
                new NIRTree::ESeq(
                    new NIRTree::LabelStm(NIRTree::LabelHolder::GetLabel("s"), {}),
                    new NIRTree::Name("e2", {}),
                    {}
                ),
                NIRTree::LabelHolder::GetLabel("l1"),
                NIRTree::LabelHolder::GetLabel("l2"),
                {}
            )
        )
    );

    // book (3)
    std::unique_ptr<NIRTree::ExprWrapper> expWrapper9(
        new NIRTree::ExprWrapper(
            new NIRTree::Binop(
                NIRTree::AND,
                new NIRTree::Unop(NIRTree::Unop::NOT, new NIRTree::Name("e1", {}), {}),
                new NIRTree::ESeq(
                    new NIRTree::LabelStm(NIRTree::LabelHolder::GetLabel("s"), {}),
                    new NIRTree::Name("e2", {}),
                    {}
                    ),
                {}
            )
        )
    );

    std::unique_ptr<NIRTree::StmWrapper> stmWrapper10(
        new NIRTree::StmWrapper(
            new NIRTree::CJump(
                NIRTree::CJump::EQ,
                new NIRTree::Unop(NIRTree::Unop::NOT, new NIRTree::Name("e1", {}), {}),
                new NIRTree::ESeq(
                    new NIRTree::LabelStm(NIRTree::LabelHolder::GetLabel("s"), {}),
                    new NIRTree::Name("e2", {}),
                    {}
                ),
                NIRTree::LabelHolder::GetLabel("l1"),
                NIRTree::LabelHolder::GetLabel("l2"),
                {}
            )
        )
    );

    // call
    std::unique_ptr<NIRTree::ExprWrapper> expWrapper11(
        new NIRTree::ExprWrapper(
            new NIRTree::Call(
                //new NIRTree::Const(41, {}),
                new NIRTree::ESeq(
                    new NIRTree::LabelStm(NIRTree::LabelHolder::GetLabel("s"), {}),
                    new NIRTree::Name("e2", {}),
                    {}
                ),
                new NIRTree::ExpList(
                    new NIRTree::Const(42, {}),
                    new NIRTree::Const(43, {}),
                    {}),
                {}
            )
        )
    );

    // binop with call
    std::unique_ptr<NIRTree::ExprWrapper> expWrapper12(
        new NIRTree::ExprWrapper(
            new NIRTree::Binop(
                NIRTree::AND,
                new NIRTree::Unop(NIRTree::Unop::NOT, new NIRTree::Name("e1", {}), {}),
                new NIRTree::Call(
                    new NIRTree::Const(41, {}),
                    new NIRTree::ExpList(
                        new NIRTree::Const(42, {}),
                        new NIRTree::Const(43, {}),
                        {}
                    ),
                    {}
                ),
                {}    
            )
        )
    );

    /*globalRoot.roots = {&node1, &node2, &binop, &eseq, &call, &mem, &unop, &temp1, &temp2,
        &name, &jump, &move, &cjump, &labelStm, &seq,
        &stmWrapper, &expWrapper, stmWrapperDeep.get()};*/

    //auto &wrapperO = expWrapper12;
    //auto &wrapperO = stmWrapperDeep;
    //auto &wrapperO = expWrapper11;
    auto &wrapperO = stmWrapper8;

    globalRoot.roots = {wrapperO.get()};

    irPrinter.Visit(&globalRoot);

    outIrt.close();

    {
        std::unique_ptr<NIRTree::StmWrapper> wrapper =
        NIRTree::Canoniser::RemoveEseqsFromSubtree(std::move(wrapperO));
    
        std::ofstream outIrt("./graph_irt_canonise.gv");
        NIRTree::IRPrettyPrinter irPrinter(outIrt);
        auto globalRoot = NIRTree::GlobalIRTParent();

        globalRoot.roots = {wrapper.get()};
        irPrinter.Visit(&globalRoot);
        outIrt.close();
    }
    return 0;
}