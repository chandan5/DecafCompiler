// #include "AST.h"
#include <iostream>
#include <cstdio>

#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/PassManager.h>
#include <llvm/Pass.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/Analysis/Verifier.h>

using namespace llvm;
using namespace std;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static Module * TheModule;
static map<string, Value *> NamedValues;

Value *LogErrorV(const char *Str) {
  cout << Str << endl;
  return nullptr;
}

class CodeGenVisitor : public Visitor {
    ASTProgram * astRoot;
    Module * module;
    Function * mainFunction;
public:
    CodeGenVisitor(ASTProgram * astRoot) {
        module = new Module("program", getGlobalContext());
        module->setTargetTriple("x86_64-pc-linux-gnu");
        this->astRoot = astRoot;
        FunctionType *ftype = FunctionType::get(Type::getVoidTy(getGlobalContext()), false); // type,argsornot
        mainFunction = Function::Create(ftype, GlobalValue::ExternalLinkage, "main", module);
    }

    void generateCode() {
        BasicBlock *block = BasicBlock::Create(getGlobalContext(), "entry", mainFunction, 0);// 0 is used for nullptr because no parent block of the entry block
        this->visit(astRoot);
        ReturnInst::Create(getGlobalContext(), block);
        verifyModule(*module, PrintMessageAction);
        PassManager PM;
        PM.add(createPrintModulePass(&outs()));
        PM.run(*module);
    }

    Value * ErrorHandler(const char * error) {
        cerr << error << endl;
        exit(0);
    }

    void * visit(ASTProgram * node) {
        if(node->getASTFieldDeclarations() != NULL) {
            for(auto it : *(node->getASTFieldDeclarations())) {
                it->accept(this);
            }
        }
        Function * iterator = NULL;
        Function * userMain = NULL;
        if(node->getASTMethodDeclarations() != NULL) {
            for(auto it : *(node->getASTMethodDeclarations())) {
                if (module->getFunction(it->getId()) && it->getId() != "main") {
                    return ErrorHandler("Multiple Function Declaration");
                }
                if (it->getId() == "main" && userMain) {
                    return ErrorHandler("Multiple Main Declaration");
                }
                iterator = static_cast<Function *>(it->accept(this));
                if (it->getId() == "main" && !userMain) {
                    userMain = iterator;
                }
                if (it->getId() == "main" && it->getParams()) {
                    return ErrorHandler("Main has no arguments");
                }
            }
        }
        if (!userMain) {
            return ErrorHandler("No Main Found");
        }
        else {
            // return CallInst::Create(userMain, "", symbolTable.topBlock());
        }
        return NULL;
    }

    void * visit(ASTFieldDeclaration * node) {
        for(auto it : *(node->getIdentifiers())) {
            it->accept(this);
        }
        return NULL;
    }

    void * visit(ASTVarDeclaration * node) {
        for(auto it : *(node->getIdentifiers())) {
            it->accept(this);
        }
        return NULL;
    }

    void * visit(ASTNormalIdentifier * node) {
        cout << "<declaration name=\"" << node->getId() << "\" />" << endl;
        // cout << "<declaration name=\"" << node->getId() << "\" type=\"" << node->getDataType() << "\" />" << endl;
    }
    void * visit(ASTArrayIdentifier * node) {
        cout << "<declaration name=\"" << node->getId() << "\" size=\"" << node->getSize() << "\" />"<< endl;
        // cout << "<declaration name=\"" << node->getId() << "\" type=\"" << node->getDataType() << "\" size=\"" << node->getSize() << "\" />"<< endl;
    }
    void * visit(ASTMethodDeclaration * node) {
        cout << "<method_declaration name=\"" << node->getId() << "\" type=\"" << node->getDataType() << "\" >" << endl;

        // TODO shift count in AST.h
        int count_params = 0;
        if(node->getParams() != NULL) {
            count_params = node->getParams()->size();
        }

        cout << "<params count=\"" << count_params <<  "\" >" << endl;

        if(count_params)
        for(auto it : *(node->getParams())) {

            it->accept(this);
        }


        cout << "</params>" << endl;

        node->getBlock()->accept(this);


        cout << "</method_declaration>" << endl;
    }
    void * visit(ASTParam * node) {
        cout << "<param name=\"" << node->getId() << "\" type=\"" << node->getDataType() << "\" >" << endl;
    }
    void * visit(ASTIntegerLiteralExpression * node) {
        cout << "<integer value=\"" << node->getVal() << "\" />" << endl;
        return ConstantInt::get(Type::getInt64Ty(getGlobalContext()), node->getVal(), true);
    }
    void * visit(ASTCharLiteralExpression * node) {
        cout << "<char value=\"" << node->getVal() << "\" />" << endl;
        return ConstantInt::get(Type::getInt64Ty(getGlobalContext()), node->getVal(), true);
    }
    void * visit(ASTBooleanLiteralExpression * node) {
        if(node->getVal() == true)
            cout << "<boolean value=\"true\" />" << endl;
        else
            cout << "<boolean value=\"false\" />" << endl;

        return ConstantInt::get(llvm::Type::getInt64Ty(llvm::getGlobalContext()), node->getVal(), true);
    }
    void * visit(ASTBlockStatement * node) {
        cout << "<block>" << endl;

        // TODO shift count in AST.h
        int count_decls = 0;
        if(node->getASTVarDeclarations() != NULL) {
            count_decls = node->getASTVarDeclarations()->size();
        }

        cout << "<declarations count=\"" << count_decls <<  "\" >" << endl;

        if(count_decls)
        for(auto it : *(node->getASTVarDeclarations())) {

            it->accept(this);
        }


        cout << "</declarations>" << endl;

        int count_stmts = 0;
        if(node->getASTStatements() != NULL) {
            count_stmts = node->getASTStatements()->size();
        }

        cout << "<statements count=\"" << count_stmts <<  "\" >" << endl;

        if(count_stmts)
        for(auto it : *(node->getASTStatements())) {

            it->accept(this);
        }


        cout << "</statements>" << endl;



        cout << "</block>" << endl;
    }

    void * visit(ASTAssignmentStatement * node) {
        cout << "<assignment type=\"" << node->getAssignOp() << "\"" << " >" << endl;


        cout << "<LHS name=\"" << node->getASTlocation()->getId() << "\">" << endl;
        ASTArrayLocation * arraylocation = dynamic_cast<ASTArrayLocation *>(node->getASTlocation());

        if(arraylocation) {


            arraylocation->getASTExpression()->accept(this);

        }

        cout << "</LHS>" << endl;

        cout << "<RHS>" << endl;


        node->getASTExpression()->accept(this);


        cout << "</RHS>" << endl;


        cout << "</assignment>" << endl;
    }

    void * visit(ASTIfStatement * node) {
        cout << "<if_statement>" << endl;


        node->getExpression()->accept(this);


        node->getIfBlock()->accept(this);

        if(node->getElseBlock())
        {

            node->getElseBlock()->accept(this);
        }



        cout << "</if_statement>" << endl;
    }

    void * visit(ASTForStatement * node) {
        cout << "<for_statement loop_variable=\"" << node->getId() << "\"" << " >" << endl;



        cout << "<init_val>" << endl;


        node->getInitVal()->accept(this);


        cout << "</init_val>" << endl;


        cout << "<end_val>" << endl;


        node->getEndVal()->accept(this);


        cout << "</end_val>" << endl;


        node->getBlock()->accept(this);



        cout << "</for_statement>" << endl;
    }

    void * visit(ASTReturnStatement * node) {
        cout << "<return_statement>" << endl;
        if(node->getExpression()) {


            node->getExpression()->accept(this);

        }

        cout << "</return_statement>" << endl;
    }

    void * visit(ASTUnaryExpression * node) {
        cout << "<unary_expression type=\"" << node->getUnOp() << "\">" << endl;


        node->getExpression()->accept(this);


        cout << "</unary_expression>" << endl;
    }
    void * visit(ASTBinaryExpression * node) {
        cout << "<binary_expression type=\"" << node->getBinOp() << "\">" << endl;


        node->getLeftExpression()->accept(this);

        node->getRightExpression()->accept(this);


        cout << "</binary_expression>" << endl;
    }

    void * visit(ASTBreakStatement * node) {
        cout << "<break_statement/>"<< endl;
    }

    void * visit(ASTContinueStatement * node) {
        cout << "<continue_statement/>"<< endl;
    }

    void * visit(ASTVarLocation * node) {
        cout << "<identifier name=\"" << node->getId() << "\" />"<< endl;
    }

    void * visit(ASTArrayLocation * node) {
        cout << "<identifier name=\"" << node->getId() << "\">"<< endl;


        node->getASTExpression()->accept(this);


        cout << "</identifier>" << endl;
    }

    void * visit(ASTMethodCallExpression * node) {
        node->getASTMethodCall()->accept(this);
    }

    void * visit(ASTMethodCallStatement * node) {
        node->getASTMethodCall()->accept(this);
    }

    void * visit(ASTSimpleMethodCall * node) {
        cout << "<method_call name=\"" << node->getId() << "\" >" << endl;


        int count_exprs = 0;
        if(node->getExpressions() != NULL) {
            count_exprs = node->getExpressions()->size();
        }
        cout << "<expressions count=\"" << count_exprs << "\">" << endl;

        if(count_exprs)
        for(auto it : *(node->getExpressions())) {

            it->accept(this);
        }


        cout << "</expressions>" << endl;


        cout << "</method_call>" << endl;
    }

    void * visit(ASTCalloutMethodCall * node) {
        cout << "<method_call>" << endl;


        cout << "<callout_call name=\"" << node->getId() << "\" >" << endl;

        int count_callout_args = 0;
        if(node->getCalloutArgs() != NULL) {
            count_callout_args = node->getCalloutArgs()->size();
        }

        cout << "<callout_args count=\"" << count_callout_args << "\">" << endl;

        if(count_callout_args)
        for(auto it : *(node->getCalloutArgs())) {

            it->accept(this);
        }


        cout << "</callout_args>" << endl;



        cout << "</callout_call>" << endl;


        cout << "</method_call>" << endl;
    }

    void * visit(ASTExpressionCalloutArg * node) {
        node->getExpression()->accept(this);
    }
    void * visit(ASTStringCalloutArg * node) {
        cout << "<callout_arg value=\"" << node->getVal() << "/>" << endl;
    }

};
