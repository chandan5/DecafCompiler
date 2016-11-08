#include <vector>
#include <string>
#include <iostream>
#include "Visitor.h"

using namespace std;

class ASTNode;
class ASTProgram;
class ASTExpression;
class ASTFieldDeclaration;
class ASTStatement;
class ASTAssignmentStatement;
class ASTBinaryExpression;
class ASTLiteralExpression;
class ASTIntegerLiteralExpression;
class ASTBooleanLiteralExpression;
class ASTCharLiteralExpression;
class ASTLocation;
class ASTVarLocation;
class ASTArrayLocation;
class ASTIdentifier;
class ASTNormalIdentifier;
class ASTArrayIdentifier;
class ASTMethodDeclaration;
class ASTBlockStatement;
class ASTParam;
class ASTVarDeclaration;
class ASTMethodCall;
class ASTCalloutArg;

enum AssignOp {
    equal,
    plus_equal,
    minus_equal
};

enum DataType {
    int_type,
    bool_type,
    void_type
};

enum BinOp {
    plus_op,
    sub_op,
    multiply_op,
    divide_op,
    modulo_op,
    lessthan_op,
    greaterthan_op,
    lessequal_op,
    greaterequal_op,
    notequal_op,
    equalequal_op,
    and_op,
    or_op
};

enum UnOp {
    minus_op,
    not_op
};

union NODE {
    int ival;
    char *sval;
    char cval;
    ASTProgram *program;
    vector<ASTFieldDeclaration *> * field_decls;
    ASTFieldDeclaration * field_decl;
    vector<ASTVarDeclaration *> * var_decls;
    ASTVarDeclaration * var_decl;
    vector<ASTMethodDeclaration *> * method_decls;
    ASTMethodDeclaration * method_decl;
    vector<ASTStatement *> * statements;
    ASTStatement * statement;
    ASTBlockStatement * block;
    ASTParam * param;
    vector<ASTParam *> * params;
    vector<ASTNormalIdentifier *> * identifiers;
    vector<ASTIdentifier *> * identifier_opt_arrs;
    ASTIdentifier * identifier_opt_arr;
    vector<ASTExpression *> * exprs;
    ASTExpression * expr;
    ASTMethodCall * method_call;
    ASTLiteralExpression * literal;
    vector<ASTCalloutArg *> * callout_args;
    ASTCalloutArg * callout_arg;
    ASTLocation * location;
    DataType type;
    AssignOp assign_op;
};
typedef union NODE YYSTYPE;


class ASTNode {
public:
    ASTNode() {}
    ~ASTNode() {}
    static string stringFromDataType(DataType d) {
        switch (d) {
            case DataType::int_type:
                return "integer";
            case DataType::bool_type:
                return "boolean";
            case DataType::void_type:
                return "void";
        }
    }
    virtual void * accept(Visitor *v) = 0;
};

class ASTProgram : public ASTNode {
    std::vector<ASTFieldDeclaration *> * field_decls;
    std::vector<ASTMethodDeclaration *> * method_decls;
public:
    ASTProgram(std::vector<ASTFieldDeclaration *> *field_decls, std::vector<ASTMethodDeclaration *> * method_decls) {
        this->field_decls = field_decls;
        this->method_decls = method_decls;
    }
    ~ASTProgram();
    std::vector<ASTFieldDeclaration *> * getASTFieldDeclarations() {
        return this->field_decls;
    }
    std::vector<ASTMethodDeclaration *> * getASTMethodDeclarations() {
        return this->method_decls;
    }
    void * accept(Visitor *v) {
        v->visit(this);
    }
};


class ASTMethodDeclaration : public ASTNode {
    DataType type;
    string id;
    vector<ASTParam *> * params;
    ASTBlockStatement * block;
public:
    ASTMethodDeclaration(DataType type, string id, vector<ASTParam *> * params, ASTBlockStatement * block) {
        this->type = type;
        this->id = id;
        this->params = params;
        this->block = block;
    }
    string getDataType() {
        return ASTNode::stringFromDataType(this->type);
    }
    string getId() {
        return this->id;
    }
    vector<ASTParam *> * getParams() {
        return this->params;
    }
    ASTBlockStatement * getBlock() {
        return this->block;
    }
    ~ASTMethodDeclaration() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTMethodCall : public ASTNode {
public:
    ASTMethodCall() {}
    ~ASTMethodCall() {}
    virtual void * accept(Visitor *v) = 0;
};

class ASTSimpleMethodCall : public ASTMethodCall {
    string id;
    vector<ASTExpression *> * exprs;
public:
    ASTSimpleMethodCall(string id, vector<ASTExpression *> * exprs) {
        this->id = id;
        this->exprs = exprs;
    }
    string getId() {
        return this->id;
    }
    vector<ASTExpression *> * getExpressions() {
        return this->exprs;
    }
    ~ASTSimpleMethodCall() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTCalloutMethodCall : public ASTMethodCall {
    string id;
    vector<ASTCalloutArg *> * callout_args;
public:
    ASTCalloutMethodCall(string id, vector<ASTCalloutArg *> * callout_args) {
        this->id = id;
        this->callout_args = callout_args;
    }
    string getId() {
        return this->id;
    }
    vector<ASTCalloutArg *> * getCalloutArgs() {
        return this->callout_args;
    }
    ~ASTCalloutMethodCall() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTStatement : public ASTNode {
public:
    ASTStatement() {}
    ~ASTStatement() {}
    void * accept(Visitor *v) = 0;
};

class ASTBlockStatement : public ASTStatement {
    std::vector<ASTVarDeclaration *> * var_decls;
    std::vector<ASTStatement *> * stmts;
public:
    ASTBlockStatement(vector<ASTVarDeclaration *> * var_decls, vector<ASTStatement *> * stmts) {
        this->var_decls = var_decls;
        std::vector<ASTStatement *> * s = new std::vector<ASTStatement *>();
        if(stmts == NULL)
            this->stmts = stmts;
        else {
            for(auto it : *stmts) {
                if(it != NULL)
                    s->push_back(it);
            }
            this->stmts = s;
        }
    }
    ~ASTBlockStatement() {}
    std::vector<ASTVarDeclaration *> * getASTVarDeclarations() {
        return this->var_decls;
    }
    std::vector<ASTStatement *> * getASTStatements() {
        return this->stmts;
    }
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTCalloutArg : public ASTNode {
public:
    ASTCalloutArg() {}
    ~ASTCalloutArg() {}
    virtual void * accept(Visitor *v) = 0;
};

class ASTExpressionCalloutArg : public ASTCalloutArg {
    ASTExpression * expr;
public:
    ASTExpressionCalloutArg(ASTExpression * expr) {
        this->expr = expr;
    }
    ASTExpression * getExpression() {
        return this->expr;
    }
    ~ASTExpressionCalloutArg() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTStringCalloutArg : public ASTCalloutArg {
    string val;
public:
    ASTStringCalloutArg(string val) {
        this->val = val;
    }
    ~ASTStringCalloutArg() {}
    string getVal() {
        return this->val;
    }
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTParam : public ASTNode {
    DataType type;
    string id;
public:
    ASTParam(DataType type, string id) {
        this->type = type;
        this->id = id;
    }
    string getId() {
        return this->id;
    }
    string getDataType() {
        return ASTNode::stringFromDataType(this->type);
    }
    ~ASTParam() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTFieldDeclaration : public ASTNode {
    DataType type;
    vector<ASTIdentifier *> * identifiers;
public:
    ASTFieldDeclaration(DataType type, vector<ASTIdentifier *> * identifiers){
        this->type = type;
        this->identifiers = identifiers;
    }
    ~ASTFieldDeclaration(){}
    string getDataType() {
        return ASTNode::stringFromDataType(this->type);
    }
    vector<ASTIdentifier *> * getIdentifiers() {
        return this->identifiers;
    }
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTIdentifier :public ASTNode {
public:
    ASTIdentifier() {}
    ~ASTIdentifier() {}
    virtual void * accept(Visitor *v) = 0;
};

class ASTNormalIdentifier : public ASTIdentifier {
    string id;
public:
    ASTNormalIdentifier(string id) {
        this->id = id;
    }
    ~ASTNormalIdentifier(){}
    string getId() {
        return this->id;
    }
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTArrayIdentifier  : public ASTIdentifier {
    string id;
    int size;
public:
    ASTArrayIdentifier(string id, int size) {
        this->id = id;
        this->size = size;
    }
    string getId() {
        return this->id;
    }
    int getSize() {
        return this->size;
    }
    ~ASTArrayIdentifier(){}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};



class ASTAssignmentStatement : public ASTStatement {
    ASTLocation * location;
    ASTExpression * expr;
    AssignOp op;
public:
    ASTAssignmentStatement(ASTLocation * location, ASTExpression * expr, AssignOp op) {
        this->location = location;
        this->expr = expr;
        this->op = op;
    }
    ~ASTAssignmentStatement();
    ASTLocation * getASTlocation() {
        return this->location;
    }
    ASTExpression * getASTExpression() {
        return this->expr;
    }
    string getAssignOp() {
        switch (this->op) {
            case AssignOp::equal:
                return "equal";
            case AssignOp::plus_equal:
                return "plus_equal";
            case AssignOp::minus_equal:
                return "minus_equal";
        }
    }
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTIfStatement : public ASTStatement {
    ASTExpression * expr;
    ASTBlockStatement * ifBlock;
    ASTBlockStatement * elseBlock;
public:
    ASTIfStatement(ASTExpression * expr, ASTBlockStatement * ifBlock, ASTBlockStatement * elseBlock) {
        this->expr = expr;
        this->ifBlock = ifBlock;
        this->elseBlock = elseBlock;
    }
    ASTExpression * getExpression() {
        return this->expr;
    }
    ASTBlockStatement * getIfBlock() {
        return this->ifBlock;
    }
    ASTBlockStatement * getElseBlock() {
        return this->elseBlock;
    }
    ~ASTIfStatement() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTForStatement : public ASTStatement {
    string id;
    ASTExpression * init_val;
    ASTExpression * end_val;
    ASTBlockStatement * block;
public:
    ASTForStatement(string id, ASTExpression * init_val, ASTExpression * end_val, ASTBlockStatement * block) {
        this->id = id;
        this->init_val = init_val;
        this->end_val = end_val;
        this->block = block;
    }
    ~ASTForStatement() {}
    string getId() {
        return this->id;
    }
    ASTExpression * getInitVal() {
        return this->init_val;
    }
    ASTExpression * getEndVal() {
        return this->end_val;
    }
    ASTBlockStatement * getBlock() {
        return this->block;
    }
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTReturnStatement : public ASTStatement {
public:
    ASTExpression * expr;
    ASTReturnStatement(ASTExpression * expr) {
        this->expr = expr;
    }
    ~ASTReturnStatement() {}
    ASTExpression * getExpression() {
        return this->expr;
    }
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTBreakStatement : public ASTStatement {
public:
    ASTBreakStatement() {}
    ~ASTBreakStatement() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTContinueStatement : public ASTStatement {
public:
    ASTContinueStatement() {}
    ~ASTContinueStatement() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTExpression : public ASTNode {
public:
    ASTExpression(){}
    ~ASTExpression(){}
    void * accept(Visitor *v) = 0;
};

class ASTBinaryExpression : public ASTExpression {
    ASTExpression * left;
    ASTExpression * right;
    BinOp op;
public:
    ASTBinaryExpression(ASTExpression * left, ASTExpression * right, BinOp op) {
        this->left = left;
        this->right = right;
        this->op = op;
    }
    ASTExpression * getLeftExpression() {
        return this->left;
    }
    ASTExpression * getRightExpression() {
        return this->right;
    }
    string getBinOp() {
        switch (this->op) {
            case BinOp::plus_op:
                return "addition";
            case BinOp::sub_op:
                return "subtraction";
            case BinOp::multiply_op:
                return "multiplication";
            case BinOp::divide_op:
                return "division";
            case BinOp::modulo_op:
                return "modulus";
            case BinOp::lessthan_op:
                return "less_than";
            case BinOp::greaterthan_op:
                return "greater_than";
            case BinOp::lessequal_op:
                return "less_equal";
            case BinOp::greaterequal_op:
                return "greater_equal";
            case BinOp::notequal_op:
                return "is_not_equal";
            case BinOp::equalequal_op:
                return "is_equal";
            case BinOp::and_op:
                return "and";
            case BinOp::or_op:
                return "or";
        }
    }
    ~ASTBinaryExpression() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTUnaryExpression : public ASTExpression {
    ASTExpression * expr;
    UnOp op;
public:
    ASTUnaryExpression(ASTExpression * expr, UnOp op) {
        this->expr = expr;
        this->op = op;
    }
    ASTExpression * getExpression() {
        return this->expr;
    }
    string getUnOp() {
        switch (this->op) {
            case UnOp::minus_op:
                return "minus";
            case UnOp::not_op:
                return "not";
        }
    }
    ~ASTUnaryExpression() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTMethodCallExpression : public ASTMethodCall, public ASTExpression {
    ASTMethodCall * method_call;
public:
    ASTMethodCallExpression(ASTMethodCall * method_call) {
        this->method_call = method_call;
    }
    ASTMethodCall * getASTMethodCall() {
        return this->method_call;
    }
    ~ASTMethodCallExpression() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};


class ASTMethodCallStatement : public ASTMethodCall, public ASTStatement {
    ASTMethodCall * method_call;
public:
    ASTMethodCallStatement(ASTMethodCall * method_call) {
        this->method_call = method_call;
    }
    ASTMethodCall * getASTMethodCall() {
        return this->method_call;
    }
    ~ASTMethodCallStatement() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};


class ASTVarDeclaration : public ASTNode {
    DataType type;
    vector<ASTNormalIdentifier *> * identifiers;
public:
    ASTVarDeclaration(DataType type, vector<ASTNormalIdentifier *> * identifiers) {
        this->type = type;
        this->identifiers = identifiers;
    }
    ~ASTVarDeclaration() {}
    vector<ASTNormalIdentifier *> * getIdentifiers() {
        return this->identifiers;
    }
    string getDataType() {
        return ASTNode::stringFromDataType(type);
    }
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTLocation : public ASTExpression {
public:
    ASTLocation() {}
    ~ASTLocation() {}
    void * accept(Visitor *v) = 0;
    virtual string getId() = 0;
};

class ASTVarLocation : public ASTLocation {
    string id;
public:
    ASTVarLocation(string id) {
        this->id = id;
    }
    string getId() {
        return this->id;
    }
    ~ASTVarLocation() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTArrayLocation : public ASTLocation {
    string id;
    ASTExpression * expr;
public:
    ASTArrayLocation(string id, ASTExpression * expr) {
        this->id = id;
        this->expr = expr;
    }
    string getId() {
        return this->id;
    }
    ASTExpression * getASTExpression() {
        return this->expr;
    }
    ~ASTArrayLocation() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTLiteralExpression : public ASTExpression {
public:
    ASTLiteralExpression(){}
    ~ASTLiteralExpression(){}
    void * accept(Visitor *v) = 0;
};

class ASTIntegerLiteralExpression : public ASTLiteralExpression {
    int val;
public:
    ASTIntegerLiteralExpression(int val) {
        this->val = val;
    }
    int getVal() {
        return this->val;
    }
    ~ASTIntegerLiteralExpression() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTCharLiteralExpression : public ASTLiteralExpression {
    char val;
public:
    ASTCharLiteralExpression(char val) {
        this->val = val;
    }
    char getVal() {
        return this->val;
    }
    ~ASTCharLiteralExpression() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTBooleanLiteralExpression : public ASTLiteralExpression {
    bool val;
public:
    ASTBooleanLiteralExpression(bool val) {
        this->val = val;
    }
    bool getVal() {
        return this->val;
    }
    ~ASTBooleanLiteralExpression() {}
    void * accept(Visitor *v) {
        v->visit(this);
    }
};
