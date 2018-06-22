#include "CodeGeneration.h"

#include "InstructionSet.h"

#include <code_generation/Instructions.h>
#include <irt/ISubtreeWrapper.h>
#include <irt/NodeTypes.h>

namespace NCodeGeneration {

    const InstructionList& Muncher::CreateInstructionsList()
    {
        generation();
        return instructionsList;
    }

    void Muncher::generation()
    {
        for( auto& stm : stmList ) {
            munchStm( stm.get() );
        }
    }

    void Muncher::munchStm(const IStm* s) {

        if (const Move* move = dynamic_cast<const Move*>(s)) {
            munchMove(move->src.get(), move->dst.get());
        }
        else if (const Jump* jump = dynamic_cast<const Jump*>(s)) {
            munchJump(jump->label);
        }
        else if (const CJump* jumpc = dynamic_cast<const CJump*>(s)) {
            munchJumpC(jumpc->leftExpr.get(), jumpc->rightExpr.get(), jumpc->trueLabel, jumpc->jumpType);
        }
        else if (const LabelStm* labelstm = dynamic_cast<const LabelStm*>(s)) {
            munchLabelStm(labelstm->label);
        }
        else if( const Exp* exp = dynamic_cast<const Exp*>(s)) {
            munchExp(exp->expr.get());
        }
        else {
            assert(false);
        }
    }

    void Muncher::munchMove(const IExp* source, const IExp* destination) {
        if(const Mem* temp = dynamic_cast<const Mem*>(source)) {
            munchMove(temp, destination);
        } else if (const Mem* temp = dynamic_cast<const Mem*>(destination)) {
            munchMove(source, temp);
        } else if(const Temp* temp = dynamic_cast<const Temp*>(destination)){
            munchMove(source, temp);
        } else {
            emit(new RegMove("MOV %0 %1", munchExp(source), munchExp(destination)));
        }
    }

    const Temp* Muncher::munchExp(const IExp* exp) {
        //MEM
        if(  const Mem* mem = dynamic_cast<const Mem*>(exp) ) {
            return munchMem(mem);
        }
        //BINOP
        if( const Binop* binop = dynamic_cast<const Binop*>(exp) ) {
            return munchBinop(binop);
        }
        //CONST
        if(const Const* c = dynamic_cast<const Const*>(exp)) {
            Temp* returnedReg = new Temp("Const");
            instructionsList.registers.emplace_back(returnedReg);
            emit(new RegMove("MOV %0 " + std::to_string(c->value), c, returnedReg));
            return returnedReg;
        }
        //TEMP
        if(const Temp* c = dynamic_cast<const Temp*>(exp)) {
            return c;
        }
        //CALL
        if(const Call* call = dynamic_cast<const Call*>(exp)) {
            return munchCall(call);
        }
        //NAME
        if(const Name* name = dynamic_cast<const Name*>(exp)) {
            const Temp* result = new Temp("Name");
            instructionsList.registers.emplace_back(result);
            const Const* constPtr = nullptr;
            emit(new RegMove("MOV %0" + name->label->String(), constPtr, result));
            return result;
        }
        //UNARY
        if(const Unop* unary = dynamic_cast<const Unop*>(exp)) {
            const Temp* result;
            switch (unary->type) {
                case Unop::NOT:
                    result = new Temp("NOT");
                    instructionsList.registers.emplace_back(result);
                    emit(new RegMove("MOV %0 %1", munchExp(unary->expression.get()), result));
                    emit(new CISCOperation("NOT %0", std::move(TempList({result})),
                                                std::move(TempList({result}))));
                    return result;
                default:
                    assert(false);
                    break;
            }
        }
        assert(false);
    }

    const IInstruction* Muncher::emit(const IInstruction* nextInstruction)
    {
        instructionsList.instructions.emplace_back( nextInstruction );
        return nextInstruction;
    }

    void Muncher::munchMove(const Mem* source, const IExp* destination) {
        // MOVE(MEM(BINOP(...))
        const Binop* binop = dynamic_cast<const Binop*>(source->exp.get());
        if (binop && (binop->binop == Binop::PLUS) ) {
            // MOVE(MEM(BINOP(PLUS, e1, CONST(i))), e2)
            if(const Const* c = dynamic_cast<const Const*>(binop->rightExp.get())) {
                emit(new RegMove("MOV %0 [%1+" + std::to_string(c->value) + "]",
                                      munchExp(binop->leftExp.get()), munchExp(destination)));
            }
                // MOVE(MEM(BINOP(PLUS, CONST(i), e1)), e2)
            else if(const Const* c = dynamic_cast<const Const*>(binop->leftExp.get())) {
                emit(new RegMove("MOV %0 [%1+" + std::to_string(c->value) + "]",
                                      munchExp(binop->rightExp.get()), munchExp(destination)));
            }
                // MOVE(MEM())
            else {
                emit(new RegMove("MOV %0 [%1]",
                                      munchExp(binop), munchExp(destination)));
            }
        }
            // MOVE(MEM(e1), e2)
        else if(const Temp* temp = dynamic_cast<const Temp*>(source->exp.get()) ) {
            emit(new RegMove("MOV %0 %1",
                                  temp, munchExp(destination)));
        } else {
            emit(new RegMove("MOV %0 [%1]",
                                  munchExp(source->exp.get()), munchExp(destination)));
        }
    }

    void Muncher::munchMove(const IExp* source, const Mem* destination)
    {
        // MOVE(MEM(BINOP(...))
        const Binop* binop = dynamic_cast<const Binop*>(destination->exp.get());
        if (binop && (binop->binop == Binop::PLUS) ) {
            // MOVE(MEM(BINOP(PLUS, e1, CONST(i))), e2)
            if(const Const* c = dynamic_cast<const Const*>(binop->rightExp.get())) {
                emit(new RegMove("MOV [%0 + " + std::to_string(c->value) + "] %1",
                                      std::move(TempList({munchExp(source), munchExp(binop->leftExp.get())}))));
            }
                // MOVE(MEM(BINOP(PLUS, CONST(i), e1)), e2)
            else if(const Const* c = dynamic_cast<const Const*>(binop->leftExp.get())) {
                emit(new RegMove("MOV [%0 + " + std::to_string(c->value) + "] %1",
                                      std::move(TempList({munchExp(source), munchExp(binop->rightExp.get())}))));
            }
                // MOVE(MEM())
            else {
                emit(new RegMove("MOV [%0] %1",
                                      std::move(TempList({munchExp(source), munchExp(binop)}))));
            }
        }
            // MOVE(MEM(e1), e2)
        else  {
            emit(new RegMove("MOV [%0] %1",
                                  std::move(TempList({munchExp(source), munchExp(destination->exp.get())}))));
        }
    }

    void Muncher::munchMove(const IExp* source, const Temp* destination) {
        // MOVE(TEMP(t1), e)
        emit(new RegMove("MOV %0 %1", munchExp(source), destination));
    }

    TempList Muncher::munchExpList(const ExpList* list)
    {
        const IExp* head = list->head.get();
        const IExp* tail = list->tail.get();
        TempList temps;
        if(const ExpList* subList = dynamic_cast<const ExpList*>(head)) {
            TempList subTemps = munchExpList(subList);
            temps.insert(temps.end(), subTemps.begin(), subTemps.end());
        } else {
            temps.push_back(munchExp(head));
        }
        if(const ExpList* subList = dynamic_cast<const ExpList*>(tail)) {
            TempList subTemps = munchExpList(subList);
            temps.insert(temps.end(), subTemps.begin(), subTemps.end());
        } else if( tail != nullptr ){
            temps.push_back(munchExp(tail));
        }
        return temps;
    }

    const Temp* Muncher::munchMem(const Mem* mem)
    {
        //MEM(BINOP)
        const Binop* binop = dynamic_cast<const Binop*>(mem->exp.get());
        if( binop && binop->binop == Binop::PLUS)
        {
            //MEM(BINOP(PLUS, e1, CONST(i)))
            if(const Const* c = dynamic_cast<const Const*>(binop->rightExp.get()))
            {
                const Temp* left = munchExp(binop->leftExp.get());
                Temp* returnedReg = new Temp("MEM(BINOP(PLUS, e1, CONST(i)))");
                instructionsList.registers.emplace_back(returnedReg);
                emit(new RegMove("MOV %0 [%1 + " + std::to_string(c->value) + "]",
                                      left, returnedReg));
                return returnedReg;
            }
                //MEM(BINOP(PLUS, CONST(i), e1))
            else if(const Const* c = dynamic_cast<const Const*>(binop->leftExp.get()))
            {
                const Temp* right = munchExp(binop->rightExp.get());
                Temp* returnedReg = new Temp("MEM(BINOP(PLUS, CONST(i), e1))");
                instructionsList.registers.emplace_back(returnedReg);
                emit(new RegMove("MOV %0 [%1 + " + std::to_string(c->value) + "]",
                                      right, returnedReg));
                return returnedReg;
            }
                //MEM(e1)
            else {
                Temp* returnedReg = new Temp("MEM(e1)");
                instructionsList.registers.emplace_back(returnedReg);
                emit(new RegMove("MOV %0 [%1]", munchExp(binop), returnedReg));
                return returnedReg;
            }
        }

            //MEM(CONST(i))
        else if (const Const* c = dynamic_cast<Const*>(mem->exp.get())) {
            Temp* returnedReg = new Temp("MEM(Const(i))");
            instructionsList.registers.emplace_back(returnedReg);
            emit(new RegMove("MOV %0 [" + std::to_string(c->value) + "]",
                                  c, returnedReg));
            return returnedReg;
        }
            //MEM(e1)
        else {
            const Temp* e1 = munchExp(mem->exp.get());
            Temp* returnedReg = new Temp("MEM(e1)");
            instructionsList.registers.emplace_back(returnedReg);
            emit(new RegMove("MOV %0 [%1]", e1, returnedReg));
            return returnedReg;
        }

    }

    const Temp*Muncher::munchCall(const Call* call)
    {
        const Temp* eax = new Temp("EAX", {}, EAX);
        instructionsList.registers.emplace_back(eax);
        TempList listArgs(munchExpList(call->args.get()));
        if(const Mem* mem = dynamic_cast<const Mem*>(call->funcExp.get())) {
            const Temp* funcAddress = dynamic_cast<const Temp*>(mem->exp.get());
            assert(funcAddress);
            listArgs.push_back(funcAddress);
            emit(new CISCOperation("CALL [%" + std::to_string(listArgs.size() - 1) +"]", std::move(listArgs),
                                        std::move(TempList())));
            return eax;
        }
        if(const Name* name = dynamic_cast<const Name*>(call->funcExp.get())) {
            emit(new CISCOperation("CALL " + name->label->String(), std::move(listArgs),
                                        std::move(TempList())));
            return eax;
        }
        assert(false);
    }

    const Temp* Muncher::munchBinop(const Binop* binop)
    {
        switch (binop->binop) {
            case Binop::PLUS:
                return munchBinopRegular(binop, "ADD ");
            case Binop::MINUS:
                return munchBinopRegular(binop, "SUB ");
            case Binop::OR:
                return munchBinopRegular(binop, "OR ");
            case Binop::AND:
                return munchBinopRegular(binop, "AND ");
            case Binop::MULTIPLY:
                return munchBinopMul(binop);
            default:
                assert(false);
                break;
        }
    }

    const Temp* Muncher::munchBinopRegular(const Binop* binop, const std::string& prefix)
    {
        Temp* returnReg = new Temp("BINOP(Regular)");
        instructionsList.registers.emplace_back(returnReg);
        //BINOP(_, e1, Const)
        if( const Const* left = dynamic_cast<const Const*>(binop->leftExp.get()) ) {
            emit(new RegMove("MOV %0 %1", munchExp(binop->rightExp.get()), returnReg));
            emit(new CISCOperation(prefix + "%0 " + std::to_string(left->value),
                                        std::move(TempList({returnReg})), std::move(TempList({returnReg}))));
            return returnReg;
        }
            //BINOP(_, Const, e1)
        else if(const Const* right = dynamic_cast<const Const*>(binop->rightExp.get())) {
            emit(new RegMove("MOV %0 %1", munchExp(binop->leftExp.get()), returnReg));
            emit(new CISCOperation(prefix + "%0 " + std::to_string(right->value),
                                        std::move(TempList({returnReg})), std::move(TempList({returnReg}))));
            return returnReg;
        }
            //BINOP(_, e1, e2)
        else {
            emit(new RegMove("MOV %0 %1", munchExp(binop->leftExp.get()), returnReg));
            emit(new CISCOperation(prefix + "%0 %1",
                                        std::move(TempList({munchExp(binop->rightExp.get())})),
                                        std::move(TempList({returnReg}))));
            return returnReg;
        }
    }

    const Temp*Muncher::munchBinopMul(const Binop* binop)
    {
        Temp* returnReg = new Temp("BINOP(Regular)");
        instructionsList.registers.emplace_back(returnReg);
        //BINOP(MUL, e1, Const)
        if( const Const* left = dynamic_cast<const Const*>(binop->leftExp.get()) ) {
            emit(new CISCOperation("IMUL %0 %1 " + std::to_string(left->value),
                                        std::move(TempList({munchExp(binop->rightExp.get())})),
                                        std::move(TempList({returnReg}))));
            return returnReg;
        }
            //BINOP(MUL, Const, e1)
        else if(const Const* right = dynamic_cast<const Const*>(binop->rightExp.get())) {
            emit(new CISCOperation("IMUL %0 %1 " + std::to_string(right->value),
                                        std::move(TempList({munchExp(binop->leftExp.get())})),
                                        std::move(TempList({returnReg}))));
            return returnReg;
        }
            //BINOP(MUL, e1, e2)
        else {
            emit(new RegMove("MOV %0 %1", munchExp(binop->leftExp.get()), returnReg));
            emit(new CISCOperation("IMUL %0 %1",
                                        std::move(TempList({munchExp(binop->rightExp.get())})),
                                        std::move(TempList({returnReg}))));
            return returnReg;
        }
    }

    void Muncher::munchJump(const Label* LabelToJump) {
        emit(new CISCOperation("JMP %l", std::move(TempList()),
                                    std::move(TempList()), std::move(LabelList({LabelToJump}))));
    }

    void Muncher::munchJumpC(const IExp* conditionLeftExpression, const IExp* conditionRightExpression,
                             const Label* trueLabel,
                             CJump::EJumpType jumpType)
    {
        if(const Const* c = dynamic_cast<const Const*>(conditionLeftExpression)) {
            const Temp* e = munchExp(conditionRightExpression);
            emit(new CISCOperation("CMP %0 " + std::to_string(c->value), std::move(TempList({e})), std::move(TempList())));
        }
        else if(const Const* c = dynamic_cast<const Const*>(conditionRightExpression)) {
            const Temp* e = munchExp(conditionLeftExpression);
            emit(new CISCOperation("CMP %0 " + std::to_string(c->value), std::move(TempList({e})), std::move(TempList())));
        }
        else {
            const Temp* e1 = munchExp(conditionLeftExpression);
            const Temp* e2 = munchExp(conditionRightExpression);
            emit(new CISCOperation("CMP %0 %1", std::move(TempList({e1, e2})), std::move(TempList())));
        }
        switch (jumpType) {
            case CJump::EQ:
                emit(new CISCOperation("JE %l", std::move(TempList()), std::move(TempList()), std::move(LabelList({trueLabel}))));
                break;
            case CJump::LT:
                emit(new CISCOperation("JL %l", std::move(TempList()), std::move(TempList()), std::move(LabelList({trueLabel}))));
                break;
            case CJump::NEQ:
                emit(new CISCOperation("JNE %l", std::move(TempList()), std::move(TempList()), std::move(LabelList({trueLabel}))));
                break;
            default:
                break;
        }
    }

    void Muncher::munchLabelStm(const Label* labelName) {
        emit(new LabelInstruction(labelName));
    }

}

