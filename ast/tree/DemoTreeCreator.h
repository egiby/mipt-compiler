#include <ast/tree/Program.h>

namespace NSyntaxTree {
    inline void CreateDemoTree(Program &program) {
        int value = 5;
        IntegerLiteralExpression *integerLiteralExp = new IntegerLiteralExpression(value);
        PrintlnStatement *printLnStatement = new PrintlnStatement(integerLiteralExp);
        MainClass *mainClass = new MainClass("nameId", "mainClassArgsId", printLnStatement);

        program.mainClass = std::unique_ptr<MainClass>(mainClass);
        program.classes = nullptr;
    }
}
