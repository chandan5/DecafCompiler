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
        int count_decls = 0;
        this->tabs++;
        this->printTabs();
        if(node->getASTDeclarations() != NULL) {
            count_decls = node->getASTDeclarations()->size();
        }
        cout << "<declarations count=\"" << count_decls << "\">" << endl;
        this->tabs++;
        if(count_decls)
        for(auto it : *(node->getASTDeclarations())) {
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
        cout << "<statements count=\"" << count_stmts << "\">" << endl;
        this->tabs++;
        if(count_stmts)
        for(auto it : *(node->getASTStatements())) {
            if(it == NULL)
                cout << "Whoa!!! NULL" << endl;
            this->printTabs();
            it->accept(this);
        }
        this->tabs--;
        this->printTabs();
        cout << "</statements>" << endl;
        this->tabs--;
        this->printTabs();
        cout << "</program>" << endl;
    }
    void visit(ASTNormalDeclaration * node) {
        cout << "<declaration name=\"" << node->getId() << "\" type=\"" << node->getDataType() << "\" />" << endl;
    }
    void visit(ASTArrayDeclaration * node) {
        cout << "<declaration name=\"" << node->getId() << "\" type=\"" << node->getDataType() << "\" size=\"" << node->getSize() << "\" />"<< endl;
    }
    void visit(ASTIntegerLiteralExpression * node) {
        cout << "<integer value=\"" << node->getVal() << "\" />" << endl;
    }
    void visit(ASTBooleanLiteralExpression * node) {
        if(node->getVal() == true) {
            cout << "<boolean value=\"true\" />" << endl;
        }
        else {
            cout << "<boolean value=\"false\" />" << endl;
        }
    }
    void visit(ASTAssignmentStatement * node) {
        cout << "<assignment>" << endl;
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

};
