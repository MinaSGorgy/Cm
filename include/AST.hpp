#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include "../include/context.hpp"
using namespace std;

class Node {
    public:
        virtual ~Node() { }
        virtual void generateCode(Context &context) = 0;
};

class NExpression: public Node {
    public:
        virtual ~NExpression() { }
        virtual void generateCode(Context &context) = 0;
};

class NStatement: public Node {
    public:
        virtual ~NStatement() { }
        virtual void generateCode(Context &context) = 0;
};

class NBlock: public Node {
    public:
        vector<NStatement*> statements;

        NBlock(NStatement *statement): statements(vector<NStatement*>{statement}) { }
        virtual ~NBlock();
        virtual void generateCode(Context &context);
};

class NConstant: public NExpression {
    public:
        const int value;

        NConstant(const int& value): value(value) { }
        virtual void generateCode(Context &context);
};

class NIdentifier: public NExpression {
    public:
        const int index;

        NIdentifier(const int& index): index(index) { }
        virtual void generateCode(Context &context);
};

class NBinaryOperation: public NExpression {
    public:
        string *operation;
        NExpression *lhs, *rhs;

        NBinaryOperation(string *operation, NExpression *lhs, NExpression *rhs):
            operation(operation), lhs(lhs), rhs(rhs) { }
        virtual void generateCode(Context &context);
        virtual ~NBinaryOperation();
};

class NAssignment: public NExpression {
    public:
        NIdentifier *id;
        NExpression *rhs;

        NAssignment(NIdentifier *id, NExpression *rhs): id(id), rhs(rhs) { }
        virtual void generateCode(Context &context);
        virtual ~NAssignment();
};

class NExpressionStatement: public NStatement {
    public:
        NExpression *expression;

        NExpressionStatement(NExpression *expression): expression(expression) { }
        virtual void generateCode(Context &context);
        virtual ~NExpressionStatement();
};

class NControlFlowStatement: public NStatement {
    public:
        NExpression *expression;
        NBlock *block;

        NControlFlowStatement(NExpression *expression, NBlock *block): expression(expression),
            block(block) { }
        virtual void generateCode(Context &context) = 0;
        virtual ~NControlFlowStatement();
};

class NWhileStatement: public NControlFlowStatement {
    public:
        NWhileStatement(NExpression *expression, NBlock *block):
            NControlFlowStatement(expression, block) { }
        virtual void generateCode(Context &context);
};

class NIfStatement: public NControlFlowStatement {
    public:
        NBlock *elseBlock;

        NIfStatement(NExpression *expression, NBlock *block, NBlock *elseBlock):
            NControlFlowStatement(expression, block), elseBlock(elseBlock) { }
        NIfStatement(NExpression *expression, NBlock *block):
            NIfStatement(expression, block, NULL) { }
        virtual void generateCode(Context &context);
        virtual ~NIfStatement();
};

extern int sym[26];

#endif /* AST_H */