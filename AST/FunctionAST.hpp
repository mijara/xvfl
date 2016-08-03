#ifndef VFL_FUNCTION_HPP
#define VFL_FUNCTION_HPP

#include <llvm/IR/Value.h>
#include <vector>
#include <string>
#include <memory>

#include "ExpressionAST.hpp"
#include "StatementAST.hpp"

class Demux;
class FunctionAST;
class BlockAST;
class ParameterAST;

typedef std::vector<std::shared_ptr<FunctionAST>> FunctionList;
typedef std::vector<std::shared_ptr<ParameterAST>> ParameterList;


class ParameterAST : public NodeAST
{
private:
    std::string name;
    std::shared_ptr<Type> type;

public:
    ParameterAST(const std::string & name, const std::shared_ptr<Type> & type) : name(name), type(type)
    {}

    virtual llvm::Value * accept(Demux * demux) override;
};


class FunctionAST : public NodeAST
{
    std::string name;
    std::string version;
    ParameterList parameters;
    std::shared_ptr<Type> type;
    std::shared_ptr<BlockAST> block;

public:
    FunctionAST(std::string name, ParameterList & parameters, std::shared_ptr<BlockAST> block,
                std::string version = "", std::shared_ptr<Type> type = nullptr) :
            name(name),
            version(version),
            parameters(parameters),
            type(type),
            block(block)
    {}

    static std::string virtualName(std::string name, std::string version);

    virtual llvm::Value * accept(Demux * demux) override;
};


class BlockAST : public NodeAST
{
    StatementList statements;

public:
    BlockAST()
    {}

    void addStatement(std::shared_ptr<StatementAST> statement)
    {
        statements.push_back(statement);
    }

    virtual llvm::Value * accept(Demux * demux) override;
};

#endif // VFL_FUNCTION_HPP
