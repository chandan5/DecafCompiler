#include <vector>
#include <string>
#include "Visitor.h"

using namespace std;

class ASTNode;
class ASTProgram;
class ASTExpression;
class ASTDeclaration;
class ASTNormalDeclaration;
class ASTArrayDeclaration;
class ASTStatement;
class ASTAssignmentStatement;
class ASTBinaryExpression;
class ASTLiteralExpression;
class ASTIntegerLiteralExpression;
class ASTBooleanLiteralExpression;
class ASTLocation;
class ASTVarLocation;
class ASTArrayLocation;


enum DataType {
    int_type,
    bool_type
};

enum BinOp {
    plus_op,
    minus_op,
    multiply_op,
    divide_op,
    modulo_op
};

union NODE {
    int ival;
    char *sval;
    char cval;
    ASTProgram *program;
    vector<ASTDeclaration *> * declarations;
    ASTDeclaration * declaration;
    vector<ASTStatement *> * statements;
    ASTStatement * statement;
    ASTExpression * expression;
    ASTLiteralExpression * literal;
    ASTLocation * location;
    DataType type;
};
typedef union NODE YYSTYPE;


class ASTNode {
public:
    ASTNode() {}
    ~ASTNode() {}
    virtual void accept(Visitor *v) = 0;
};

class ASTProgram : public ASTNode {
    std::vector<ASTDeclaration *> * dcls;
    std::vector<ASTStatement *> * stmts;
public:
    ASTProgram(std::vector<ASTDeclaration *> *dcls, std::vector<ASTStatement *> * stmts) {
        this->dcls = dcls;
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
    ~ASTProgram();
    std::vector<ASTDeclaration *> * getASTDeclarations() {
        return this->dcls;
    }
    std::vector<ASTStatement *> * getASTStatements() {
        return this->stmts;
    }
    void accept(Visitor *v) {
        v->visit(this);
    }
};


class ASTDeclaration : public ASTNode {
public:
    ASTDeclaration(){}
    ~ASTDeclaration(){}
    static string stringFromDataType(DataType d) {
        switch (d) {
            case DataType::int_type:
                return "integer";
            case DataType::bool_type:
                return "boolean";
        }
    }

    virtual void accept(Visitor *v) = 0;
};

class ASTNormalDeclaration : public ASTDeclaration {
    DataType type;
    string id;
public:
    ASTNormalDeclaration(DataType type, string id) {
        this->type = type;
        this->id = id;
    }
    ~ASTNormalDeclaration(){}
    string getId() {
        return this->id;
    }
    string getDataType() {
        return ASTDeclaration::stringFromDataType(this->type);
    }
    void accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTArrayDeclaration : public ASTDeclaration {
    DataType type;
    string id;
    int size;
public:
    ASTArrayDeclaration(DataType type, string id, int size) {
        this->type = type;
        this->id = id;
        this->size = size;
    }
    string getId() {
        return this->id;
    }
    string getDataType() {
        return ASTDeclaration::stringFromDataType(this->type);
    }
    int getSize() {
        return this->size;
    }
    ~ASTArrayDeclaration(){}
    void accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTStatement : public ASTNode {
public:
    ASTStatement() {}
    ~ASTStatement() {}
    void accept(Visitor *v) = 0;
};

class ASTAssignmentStatement : public ASTStatement {
    ASTLocation * location;
    ASTExpression * expr;
public:
    ASTAssignmentStatement(ASTLocation * location, ASTExpression * expr) {
        this->location = location;
        this->expr = expr;
    }
    ~ASTAssignmentStatement();
    ASTLocation * getASTlocation() {
        return this->location;
    }
    ASTExpression * getASTExpression() {
        return this->expr;
    }
    void accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTExpression : public ASTNode {
public:
    ASTExpression(){}
    ~ASTExpression(){}
    void accept(Visitor *v) = 0;
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
                return "Addition";
            case BinOp::minus_op:
                return "Subtraction";
            case BinOp::multiply_op:
                return "Multiplication";
            case BinOp::divide_op:
                return "Division";
            case BinOp::modulo_op:
                return "Modulus";
        }
    }
    ~ASTBinaryExpression() {}
    void accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTLocation : public ASTExpression {
public:
    ASTLocation() {}
    ~ASTLocation() {}
    void accept(Visitor *v) = 0;
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
    void accept(Visitor *v) {
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
    void accept(Visitor *v) {
        v->visit(this);
    }
};

class ASTLiteralExpression : public ASTExpression {
public:
    ASTLiteralExpression(){}
    ~ASTLiteralExpression(){}
    void accept(Visitor *v) = 0;
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
    void accept(Visitor *v) {
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
    void accept(Visitor *v) {
        v->visit(this);
    }
};
