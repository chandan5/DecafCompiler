#include "AST.h"
// #include "Visitor.h"
#include <iostream>
#include <cstdio>

using namespace std;

class PrintVisitor : public Visitor {
    ASTProgram * astRoot;
    int tabs;
public:
    PrintVisitor(ASTProgram * astRoot) {
        this->astRoot = astRoot;
        tabs = 0;
    }
    void print() {
        this->visit(astRoot);
    }
    void printTabs() {
        for(int i=0; i<tabs; i++) {
            cout << "\t";
        }
    }
    void visit(ASTProgram * node) {
        cout << "<program>" << endl;
        int count_field_decls = 0;
        this->tabs++;
        this->printTabs();
        if(node->getASTFieldDeclarations() != NULL) {
            count_field_decls = node->getASTFieldDeclarations()->size();
        }
        cout << "<field_declarations count=\"" << count_field_decls << "\">" << endl;
        this->tabs++;
        if(count_field_decls)
        for(auto it : *(node->getASTFieldDeclarations())) {
            this->printTabs();
            it->accept(this);
        }
        this->tabs--;
        this->printTabs();
        cout << "</field_declarations>" << endl;
        int count_method_decls = 0;
        if(node->getASTMethodDeclarations() != NULL) {
            count_method_decls = node->getASTMethodDeclarations()->size();
        }
        this->printTabs();
        cout << "<method_declarations count=\"" << count_method_decls << "\">" << endl;
        this->tabs++;
        if(count_method_decls)
        for(auto it : *(node->getASTMethodDeclarations())) {
            this->printTabs();
            it->accept(this);
        }
        this->tabs--;
        this->printTabs();
        cout << "</method_declarations>" << endl;
        this->tabs--;
        this->printTabs();
        cout << "</program>" << endl;
    }

    void visit(ASTFieldDeclaration * node) {
        cout << "<field_declaration " << "type=\"" << node->getDataType() << "\">" << endl;
        this->tabs++;
        for(auto it : *(node->getIdentifiers())) {
            this->printTabs();
            it->accept(this);
        }
        this->tabs--;
        this->printTabs();
        cout << "</field_declaration>" << endl;
    }
    void visit(ASTVarDeclaration * node) {
        cout << "<var_declaration " << "type=\"" << node->getDataType() << "\">" << endl;
        this->tabs++;
        for(auto it : *(node->getIdentifiers())) {
            this->printTabs();
            it->accept(this);
        }
        this->tabs--;
        this->printTabs();
        cout << "</var_declaration>" << endl;
    }

    void visit(ASTNormalIdentifier * node) {
        cout << "<declaration name=\"" << node->getId() << "\" />" << endl;
        // cout << "<declaration name=\"" << node->getId() << "\" type=\"" << node->getDataType() << "\" />" << endl;
    }
    void visit(ASTArrayIdentifier * node) {
        cout << "<declaration name=\"" << node->getId() << "\" size=\"" << node->getSize() << "\" />"<< endl;
        // cout << "<declaration name=\"" << node->getId() << "\" type=\"" << node->getDataType() << "\" size=\"" << node->getSize() << "\" />"<< endl;
    }
    void visit(ASTMethodDeclaration * node) {
        cout << "<method_declaration name=\"" << node->getId() << "\" type=\"" << node->getDataType() << "\" >" << endl;
        this->tabs++;
        // TODO shift count in AST.h
        int count_params = 0;
        if(node->getParams() != NULL) {
            count_params = node->getParams()->size();
        }
        this->printTabs();
        cout << "<params count=\"" << count_params <<  "\" >" << endl;
        this->tabs++;
        if(count_params)
        for(auto it : *(node->getParams())) {
            this->printTabs();
            it->accept(this);
        }
        this->tabs--;
        this->printTabs();
        cout << "</params>" << endl;
        this->printTabs();
        node->getBlock()->accept(this);
        this->tabs--;
        this->printTabs();
        cout << "</method_declaration>" << endl;
    }
    void visit(ASTParam * node) {
        cout << "<param name=\"" << node->getId() << "\" type=\"" << node->getDataType() << "\" >" << endl;
    }
    void visit(ASTIntegerLiteralExpression * node) {
        cout << "<integer value=\"" << node->getVal() << "\" />" << endl;
    }
    void visit(ASTCharLiteralExpression * node) {
        cout << "<char value=\"" << node->getVal() << "\" />" << endl;
    }
    void visit(ASTBooleanLiteralExpression * node) {
        if(node->getVal() == true) {
            cout << "<boolean value=\"true\" />" << endl;
        }
        else {
            cout << "<boolean value=\"false\" />" << endl;
        }
    }
    void visit(ASTBlockStatement * node) {
        cout << "<block>" << endl;
        this->tabs++;
        // TODO shift count in AST.h
        int count_decls = 0;
        if(node->getASTVarDeclarations() != NULL) {
            count_decls = node->getASTVarDeclarations()->size();
        }
        this->printTabs();
        cout << "<declarations count=\"" << count_decls <<  "\" >" << endl;
        this->tabs++;
        if(count_decls)
        for(auto it : *(node->getASTVarDeclarations())) {
            this->printTabs();
            it->accept(this);
        }
        this->tabs--;
        this->printTabs();
        cout << "</declarations>" << endl;

        int count_stmts = 0;
        if(node->getASTStatements() != NULL) {
            count_stmts = node->getASTStatements()->size();
        }
        this->printTabs();
        cout << "<statements count=\"" << count_stmts <<  "\" >" << endl;
        this->tabs++;
        if(count_stmts)
        for(auto it : *(node->getASTStatements())) {
            this->printTabs();
            it->accept(this);
        }
        this->tabs--;
        this->printTabs();
        cout << "</statements>" << endl;

        this->tabs--;
        this->printTabs();
        cout << "</block>" << endl;
    }

    void visit(ASTAssignmentStatement * node) {
        cout << "<assignment type=\"" << node->getAssignOp() << "\"" << " >" << endl;
        this->tabs++;
        this->printTabs();
        cout << "<LHS name=\"" << node->getASTlocation()->getId() << "\">" << endl;
        ASTArrayLocation * arraylocation = dynamic_cast<ASTArrayLocation *>(node->getASTlocation());

        if(arraylocation) {
            this->tabs++;
            this->printTabs();
            arraylocation->getASTExpression()->accept(this);
            this->tabs--;
        }
        this->printTabs();
        cout << "</LHS>" << endl;
        this->printTabs();
        cout << "<RHS>" << endl;
        this->tabs++;
        this->printTabs();
        node->getASTExpression()->accept(this);
        this->tabs--;
        this->printTabs();
        cout << "</RHS>" << endl;
        this->tabs--;
        this->printTabs();
        cout << "</assignment>" << endl;
    }

    void visit(ASTIfStatement * node) {
        cout << "<if_statement>" << endl;
        this->tabs++;
        this->printTabs();
        node->getExpression()->accept(this);

        this->printTabs();
        node->getIfBlock()->accept(this);

        if(node->getElseBlock())
        {
            this->printTabs();
            node->getElseBlock()->accept(this);
        }

        this->tabs--;
        this->printTabs();
        cout << "</if_statement>" << endl;
    }

    void visit(ASTForStatement * node) {
        cout << "<for_statement loop_variable=\"" << node->getId() << "\"" << " >" << endl;
        this->tabs++;
        this->printTabs();

        cout << "<init_val>" << endl;
        this->tabs++;
        this->printTabs();
        node->getInitVal()->accept(this);
        this->tabs--;
        this->printTabs();
        cout << "</init_val>" << endl;

        this->printTabs();
        cout << "<end_val>" << endl;
        this->tabs++;
        this->printTabs();
        node->getEndVal()->accept(this);
        this->tabs--;
        this->printTabs();
        cout << "</end_val>" << endl;

        this->printTabs();
        node->getBlock()->accept(this);

        this->tabs--;
        this->printTabs();
        cout << "</for_statement>" << endl;
    }

    void visit(ASTReturnStatement * node) {
        cout << "<return_statement>" << endl;
        if(node->getExpression()) {
            this->tabs++;
            this->printTabs();
            node->getExpression()->accept(this);
            this->tabs--;
        }
        this->printTabs();
        cout << "</return_statement>" << endl;
    }

    void visit(ASTUnaryExpression * node) {
        cout << "<unary_expression type=\"" << node->getUnOp() << "\">" << endl;
        this->tabs++;
        this->printTabs();
        node->getExpression()->accept(this);
        this->tabs--;
        this->printTabs();
        cout << "</unary_expression>" << endl;
    }
    void visit(ASTBinaryExpression * node) {
        cout << "<binary_expression type=\"" << node->getBinOp() << "\">" << endl;
        this->tabs++;
        this->printTabs();
        node->getLeftExpression()->accept(this);
        this->printTabs();
        node->getRightExpression()->accept(this);
        this->tabs--;
        this->printTabs();
        cout << "</binary_expression>" << endl;
    }

    void visit(ASTBreakStatement * node) {
        cout << "<break_statement/>"<< endl;
    }

    void visit(ASTContinueStatement * node) {
        cout << "<continue_statement/>"<< endl;
    }

    void visit(ASTVarLocation * node) {
        cout << "<identifier name=\"" << node->getId() << "\" />"<< endl;
    }

    void visit(ASTArrayLocation * node) {
        cout << "<identifier name=\"" << node->getId() << "\">"<< endl;
        this->tabs++;
        this->printTabs();
        node->getASTExpression()->accept(this);
        this->tabs--;
        this->printTabs();
        cout << "</identifier>" << endl;
    }

    void visit(ASTSimpleMethodCall * node) {
        cout << "<method_call>" << endl;
        this->tabs++;
        this->printTabs();

        this->tabs--;
        this->printTabs();
        cout << "</method_call>" << endl;
    }

    void visit(ASTCalloutMethodCall * node) {
        cout << "<method_call>" << endl;
        this->tabs++;
        this->printTabs();
        cout << "<callout_call name=\"" << node->getId() << "\" >" << endl;
        this->tabs++;
        int count_callout_args = 0;
        if(node->getCalloutArgs() != NULL) {
            count_callout_args = node->getCalloutArgs()->size();
        }
        this->printTabs();
        cout << "<callout_args count=\"" << count_callout_args << "\">" << endl;
        this->tabs++;
        if(count_callout_args)
        for(auto it : *(node->getCalloutArgs())) {
            this->printTabs();
            it->accept(this);
        }
        this->tabs--;
        this->printTabs();
        cout << "</callout_args>" << endl;

        this->tabs--;
        this->printTabs();
        cout << "</callout_call>" << endl;
        this->tabs--;
        this->printTabs();
        cout << "</method_call>" << endl;
    }

    void visit(ASTExpressionCalloutArg * node) {
        cout << "<callout_arg>" << endl;
        this->tabs++;
        this->printTabs();
        node->getExpression()->accept(this);
        this->tabs--;
        this->printTabs();
        cout << "</callout_arg>" << endl;
    }
    void visit(ASTStringCalloutArg * node) {
        cout << "<callout_arg value=\"" << node->getVal() << "/>" << endl;
    }

};
