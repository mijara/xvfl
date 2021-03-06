#ifndef VFL_STATEMENTAST_HPP
#define VFL_STATEMENTAST_HPP

#include <string>

#include "NodeAST.hpp"
#include "ExpressionAST.hpp"

class BlockAST;
class StatementAST;
class Type;

typedef std::vector<std::shared_ptr<StatementAST>> StatementList;

class StatementAST : public NodeAST
{
public:
    virtual llvm::Value * accept(Demux * demux) override
    {
        return nullptr;
    }
};


/**
 * A for statement requires a variable, which will be declared in the outter scope,
 * an initial value for that variable, a continue condition, an increment, which
 * can be blank (defaulted to 1), and an execution block.
 */
class ForAST : public StatementAST
{
    std::string variable;
    std::shared_ptr<ExpressionAST> initial;
    std::shared_ptr<ExpressionAST> condition;
    std::shared_ptr<ExpressionAST> increment;
    std::shared_ptr<BlockAST> block;

public:
    ForAST(std::string variable, std::shared_ptr<ExpressionAST> initial,
           std::shared_ptr<ExpressionAST> condition,
           std::shared_ptr<ExpressionAST> increment,
           std::shared_ptr<BlockAST> block) :
            variable (variable), initial(initial), condition(condition),
            increment(increment), block(block)
    {}

    std::string getVariable()
    {
        return variable;
    }

    std::shared_ptr<ExpressionAST> getInitial()
    {
        return initial;
    }

    std::shared_ptr<ExpressionAST> getCondition()
    {
        return condition;
    }

    std::shared_ptr<ExpressionAST> getIncrement()
    {
        return increment;
    }

    std::shared_ptr<BlockAST> getBlock()
    {
        return block;
    }

    virtual llvm::Value * accept(Demux * demux) override;
};


/**
 * A variable declaration must have a name and expression or a type, the final
 * variable type is taken from the expression if the type is not explicitly
 * defined, if the type is defined, then the final type is that one, and the
 * expression is casted if there's one.
 */
class VarDeclAST : public StatementAST
{
    std::string name;
    std::shared_ptr<Type> type;
    std::shared_ptr<ExpressionAST> expression;

public:
    VarDeclAST(std::string name, std::shared_ptr<Type> type,
            std::shared_ptr<ExpressionAST> expression = nullptr) :
            name(name), type(type), expression(expression)
    {}

    const std::string & getName() const
    {
        return name;
    }

    std::shared_ptr<Type> getType()
    {
        return type;
    }

    std::shared_ptr<ExpressionAST> getExpression()
    {
        return expression;
    }

    virtual llvm::Value * accept(Demux * demux) override;
};


/**
 * An expression statement is an expression that is not enclosed inside
 * a statement, the most common case is a function call.
 */
class ExpressionStatementAST : public StatementAST
{
    std::shared_ptr<ExpressionAST> expression;

public:
    ExpressionStatementAST(std::shared_ptr<ExpressionAST> expression) :
            expression(expression)
    {}

    std::shared_ptr<ExpressionAST> getExpression() const
    {
        return expression;
    }

    virtual llvm::Value * accept(Demux * demux) override;
};


class AssignmentAST : public StatementAST
{
    std::shared_ptr<ExpressionAST> left;
    std::shared_ptr<ExpressionAST> right;

public:
    AssignmentAST(std::shared_ptr<ExpressionAST> left, std::shared_ptr<ExpressionAST> right) :
            left(left), right(right)
    {}

    const std::shared_ptr<ExpressionAST> & getLeft() const
    {
        return left;
    }

    const std::shared_ptr<ExpressionAST> & getRight() const
    {
        return right;
    }

    virtual llvm::Value * accept(Demux * demux) override;
};


class ReturnAST : public StatementAST
{
    std::shared_ptr<ExpressionAST> expression;

public:
    ReturnAST(std::shared_ptr<ExpressionAST> expression = nullptr) :
            expression(expression)
    {}

    std::shared_ptr<ExpressionAST> getExpression()
    {
        return expression;
    }

    virtual llvm::Value * accept(Demux * demux) override;
};


class IfAST : public StatementAST
{
    std::shared_ptr<ExpressionAST> condition;
    std::shared_ptr<BlockAST> thenBlock;
    std::shared_ptr<BlockAST> elseBlock;

public:
    IfAST(std::shared_ptr<ExpressionAST> condition,
          std::shared_ptr<BlockAST> thenBlock,
          std::shared_ptr<BlockAST> elseBlock) :
            condition(condition), thenBlock(thenBlock), elseBlock(elseBlock)
    {}

    std::shared_ptr<ExpressionAST> getCondition()
    {
        return condition;
    }

    std::shared_ptr<BlockAST> getThenBlock()
    {
        return thenBlock;
    }

    std::shared_ptr<BlockAST> getElseBlock()
    {
        return elseBlock;
    }

    virtual llvm::Value * accept(Demux * demux) override;
};


class PrintAST : public StatementAST
{
    std::shared_ptr<ExpressionAST> expression;

public:
    PrintAST(std::shared_ptr<ExpressionAST> expression) :
            expression(expression)
    {}

    std::shared_ptr<ExpressionAST> getExpression()
    {
        return expression;
    }

    virtual llvm::Value * accept(Demux * demux) override;
};


class BreakAST : public StatementAST
{
public:
    BreakAST() {}

    virtual llvm::Value * accept(Demux * demux) override;
};



#endif //VFL_STATEMENTAST_HPP
