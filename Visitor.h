
class ASTProgram;
class ASTExpression;
class ASTDeclaration;
class ASTNormalDeclaration;
class ASTArrayDeclaration;
class ASTStatement;
class ASTAssignmentStatement;
class ASTBinaryExpression;
class ASTLocation;
class ASTVarLocation;
class ASTArrayLocation;
class ASTIntegerLiteralExpression;
class ASTBooleanLiteralExpression;

class Visitor {
public:
    virtual void visit(ASTProgram *) = 0;
    // virtual void visit(ASTDeclaration *) = 0;
    virtual void visit(ASTNormalDeclaration *) = 0;
    virtual void visit(ASTArrayDeclaration *) = 0;
    virtual void visit(ASTAssignmentStatement *) = 0;
    // virtual void visit(ASTExpression *) = 0;
    virtual void visit(ASTBinaryExpression *) = 0;
    // virtual void visit(ASTLocation *) = 0;
    virtual void visit(ASTVarLocation *) = 0;
    virtual void visit(ASTArrayLocation *) = 0;
    virtual void visit(ASTIntegerLiteralExpression *) = 0;
    virtual void visit(ASTBooleanLiteralExpression *) = 0;
};
