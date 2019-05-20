//////////////////////////////////////////////////////////////////////
//
//    CodeGenListener - Walk the parser tree to do
//                             the generation of code
//
//    Copyright (C) 2018  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#include "CodeGenListener.h"

#include "antlr4-runtime.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/code.h"

#include <cstddef>    // std::size_t

// uncomment the following line to enable debugging messages with DEBUG*
// #define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;


// Constructor
CodeGenListener::CodeGenListener(TypesMgr       & Types,
				 SymTable       & Symbols,
				 TreeDecoration & Decorations,
				 code           & Code) :
  Types{Types},
  Symbols{Symbols},
  Decorations{Decorations},
  Code{Code} {
}

void CodeGenListener::enterProgram(AslParser::ProgramContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
}
void CodeGenListener::exitProgram(AslParser::ProgramContext *ctx) {
  Symbols.popScope();
  DEBUG_EXIT();
}

void CodeGenListener::enterFunction(AslParser::FunctionContext *ctx) {
  DEBUG_ENTER();
  subroutine subr(ctx->ID()->getText());
  if (ctx->ID()->getText() != "main")
    subr.add_param("_result");
  Code.add_subroutine(subr);
  SymTable::ScopeId sc = getScopeDecor(ctx);
  TypesMgr::TypeId t = getTypeDecor(ctx);
  Symbols.setCurrentFunctionTy(Types.getFuncReturnType(t));
  Symbols.pushThisScope(sc);
  codeCounters.reset();
}
void CodeGenListener::exitFunction(AslParser::FunctionContext *ctx) {
  subroutine & subrRef = Code.get_last_subroutine();
  instructionList code = getCodeDecor(ctx->statements());
  code = code || instruction::RETURN();
  subrRef.set_instructions(code);
  Symbols.popScope();
  DEBUG_EXIT();
}

void CodeGenListener::enterDeclarations(AslParser::DeclarationsContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitDeclarations(AslParser::DeclarationsContext *ctx) {
  DEBUG_EXIT();
}

void CodeGenListener::enterReturnStmt(AslParser::ReturnStmtContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitReturnStmt(AslParser::ReturnStmtContext *ctx) {
  instructionList code;
  if (ctx->expr()) {
    TypesMgr::TypeId te = getTypeDecor(ctx->expr());
    TypesMgr::TypeId tr = Symbols.getCurrentFunctionTy();
    std::string addr = getAddrDecor(ctx->expr());
    code = getCodeDecor(ctx->expr());
    if (Types.isFloatTy(tr) and (not Types.isFloatTy(te))) {
      code = code || instruction::FLOAT("_result", addr);
    } else {
      code = code || instruction::LOAD("_result", addr);
    }
  }
  code = code || instruction::RETURN();
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterParameter(AslParser::ParameterContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitParameter(AslParser::ParameterContext *ctx) {
  subroutine & subrRef = Code.get_last_subroutine();
  subrRef.add_param(ctx->ID()->getText());
  DEBUG_EXIT();
}

void CodeGenListener::enterParenthesis(AslParser::ParenthesisContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitParenthesis(AslParser::ParenthesisContext *ctx) {
  putAddrDecor(ctx, getAddrDecor(ctx->expr()));
  putCodeDecor(ctx, getCodeDecor(ctx->expr()));
  DEBUG_EXIT();
}

void CodeGenListener::enterVariable_decl(AslParser::Variable_declContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitVariable_decl(AslParser::Variable_declContext *ctx) {
  subroutine & subrRef = Code.get_last_subroutine();
  TypesMgr::TypeId t1 = getTypeDecor(ctx->data());
  std::size_t size = Types.getSizeOfType(t1);
  for(unsigned int i = 0; i < ctx->ID().size(); ++i)
    subrRef.add_var(ctx->ID(i)->getText(), size);
  DEBUG_EXIT();
}

void CodeGenListener::enterType(AslParser::TypeContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitType(AslParser::TypeContext *ctx) {
  DEBUG_EXIT();
}

void CodeGenListener::enterStatements(AslParser::StatementsContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitStatements(AslParser::StatementsContext *ctx) {
  instructionList code;
  for (auto stCtx : ctx->statement()) {
    code = code || getCodeDecor(stCtx);
  }
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterAssignStmt(AslParser::AssignStmtContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitAssignStmt(AslParser::AssignStmtContext *ctx) {
  instructionList  code;
  std::string     addr2 = getAddrDecor(ctx->expr());
  instructionList code2 = getCodeDecor(ctx->expr());
  if (ctx->left_expr()->ident()) {
    std::string     addr1 = getAddrDecor(ctx->left_expr()->ident());
    instructionList code1 = getCodeDecor(ctx->left_expr()->ident());
    code = code1 || code2 || instruction::LOAD(addr1, addr2);
  } else {
    std::string     addr1 = getAddrDecor(ctx->left_expr()->arrayid()->ident());
    instructionList code1 = getCodeDecor(ctx->left_expr()->arrayid()->ident());
    std::string name = ctx->left_expr()->arrayid()->ident()->ID()->getText();
    instructionList code3 = getCodeDecor(ctx->left_expr()->arrayid()->expr());
    std::string     addr3 = getAddrDecor(ctx->left_expr()->arrayid()->expr());
    code = code1 || code3 || code2 || instruction::XLOAD(addr1, addr3, addr2);
  }
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterIfStmt(AslParser::IfStmtContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitIfStmt(AslParser::IfStmtContext *ctx) {
  instructionList   code;
  std::string      addr1 = getAddrDecor(ctx->expr());
  instructionList  code1 = getCodeDecor(ctx->expr());
  instructionList  code2 = getCodeDecor(ctx->statements());
  std::string      label = codeCounters.newLabelIF();
  std::string labelEndIf = "endif"+label;
  if (ctx->elseStmt()) {
    std::string labelElse = "else"+label;
    instructionList code3 = getCodeDecor(ctx->elseStmt()->statements());
    code = code1 || instruction::FJUMP(addr1, labelElse) || code2 ||
           instruction::UJUMP(labelEndIf) || instruction::LABEL(labelElse) ||
           code3 || instruction::LABEL(labelEndIf);
  } else {
    code = code1 || instruction::FJUMP(addr1, labelEndIf) ||
           code2 || instruction::LABEL(labelEndIf);
  }
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterWhileStmt(AslParser::WhileStmtContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitWhileStmt(AslParser::WhileStmtContext *ctx) {
  instructionList   code;
  std::string      addr1 = getAddrDecor(ctx->expr());
  instructionList  code1 = getCodeDecor(ctx->expr());
  instructionList  code2 = getCodeDecor(ctx->statements());
  std::string      label = codeCounters.newLabelWHILE();
  std::string labelEndWhile = "endwhile"+label;
  std::string labelWhile = "while"+label;
  code = instruction::LABEL(labelWhile) || code1 || instruction::FJUMP(addr1, labelEndWhile) ||
         code2 || instruction::UJUMP(labelWhile) || instruction::LABEL(labelEndWhile);
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterProcCall(AslParser::ProcCallContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitProcCall(AslParser::ProcCallContext *ctx) {
  instructionList code;
  // std::string name = ctx->ident()->ID()->getSymbol()->getText();
  code = instruction::PUSH();
  if (ctx->exprs()) {
    std::vector<TypesMgr::TypeId> Params = Types.getFuncParamsTypes(getTypeDecor(ctx->ident())); 
    for (size_t i = 0; i < ctx->exprs()->expr().size(); ++i) {
      std::string addr = getAddrDecor(ctx->exprs()->expr(i));
      instructionList code1 = getCodeDecor(ctx->exprs()->expr(i));
      TypesMgr::TypeId tp = getTypeDecor(ctx->exprs()->expr(i));
      if (Types.isArrayTy(tp)) {
        std::string temp = "%"+codeCounters.newTEMP();
        code1 = code1 || instruction::ALOAD(temp, addr);
        addr = temp;
      }
      else if (Types.isFloatTy(Params[i]) and (not Types.isFloatTy(tp))) {
        std::string temp = "%"+codeCounters.newTEMP();
        code1 = code1 || instruction::FLOAT(temp, addr);
        addr = temp;
      }
      code = code || code1 || instruction::PUSH(addr);
    }
  }
  std::string name = ctx->ident()->getText();
  code = code || instruction::CALL(name);
  if (ctx->exprs()) {
    for (size_t i = 0; i < ctx->exprs()->expr().size(); ++i) {
      code = code  || instruction::POP();
    }
  }
  code = code || instruction::POP();
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterFuncid(AslParser::FuncidContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitFuncid(AslParser::FuncidContext *ctx) {
  instructionList code;
  // std::string name = ctx->ident()->ID()->getSymbol()->getText();
  code = instruction::PUSH();
  if (ctx->exprs()) {
    std::vector<TypesMgr::TypeId> Params = Types.getFuncParamsTypes(getTypeDecor(ctx->ident())); 
    for (size_t i = 0; i < ctx->exprs()->expr().size(); ++i) {
      std::string addr = getAddrDecor(ctx->exprs()->expr(i));
      instructionList code1 = getCodeDecor(ctx->exprs()->expr(i));
      TypesMgr::TypeId tp = getTypeDecor(ctx->exprs()->expr(i));
      if (Types.isArrayTy(tp)) {
        std::string temp = "%"+codeCounters.newTEMP();
        code1 = code1 || instruction::ALOAD(temp, addr);
        addr = temp;
      }
      else if (Types.isFloatTy(Params[i]) and (not Types.isFloatTy(tp))) {
        std::string temp = "%"+codeCounters.newTEMP();
        code1 = code1 || instruction::FLOAT(temp, addr);
        addr = temp;
      }
      code = code || code1 || instruction::PUSH(addr);
    }
  }
  std::string name = ctx->ident()->getText();
  code = code || instruction::CALL(name);
  if (ctx->exprs()) {
    for (size_t i = 0; i < ctx->exprs()->expr().size(); ++i) {
      code = code  || instruction::POP();
    }
  }
  std::string label = codeCounters.newTEMP();
  std::string labelTemp = "%"+label;
  code = code || instruction::POP(labelTemp);
  putAddrDecor(ctx,labelTemp);
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterReadStmt(AslParser::ReadStmtContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitReadStmt(AslParser::ReadStmtContext *ctx) {
  instructionList  code;
  TypesMgr::TypeId tid1;
  std::string     addr1;
  instructionList code1;
  if (ctx->left_expr()->ident()) {
    tid1 = getTypeDecor(ctx->left_expr()->ident());
    addr1 = getAddrDecor(ctx->left_expr()->ident());
    code1 = getCodeDecor(ctx->left_expr()->ident());
  } else {
    tid1 = getTypeDecor(ctx->left_expr()->arrayid());
    addr1 = "%"+codeCounters.newTEMP();
    code1 = getCodeDecor(ctx->left_expr()->arrayid()->expr());
  }
  if (Types.isFloatTy(tid1)) {
    code = code1 || instruction::READF(addr1);
  } else if (Types.isCharacterTy(tid1)) {
    code = code1 || instruction::READC(addr1);
  } else {
    code = code1 || instruction::READI(addr1);
  }
  if (ctx->left_expr()->arrayid()) {
    std::string addr2 = getAddrDecor(ctx->left_expr()->arrayid()->ident());
    std::string addr3 = getAddrDecor(ctx->left_expr()->arrayid()->expr());
    code = code || instruction::XLOAD(addr2, addr3, addr1);
  }
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterWriteExpr(AslParser::WriteExprContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitWriteExpr(AslParser::WriteExprContext *ctx) {
  instructionList code;
  std::string     addr1 = getAddrDecor(ctx->expr());
  instructionList code1 = getCodeDecor(ctx->expr());
  TypesMgr::TypeId tid1 = getTypeDecor(ctx->expr());
  if (Types.isFloatTy(tid1)) {
    code = code1 || instruction::WRITEF(addr1);
  } else if (Types.isCharacterTy(tid1)) {
    code = code1 || instruction::WRITEC(addr1);
  } else {
    code = code1 || instruction::WRITEI(addr1);
  }
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterWriteString(AslParser::WriteStringContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitWriteString(AslParser::WriteStringContext *ctx) {
  instructionList code;
  std::string s = ctx->STRING()->getText();
  std::string temp = "%"+codeCounters.newTEMP();
  int i = 1;
  while (i < int(s.size())-1) {
    if (s[i] != '\\') {
      code = code ||
	     instruction::CHLOAD(temp, s.substr(i,1)) ||
	     instruction::WRITEC(temp);
      i += 1;
    }
    else {
      assert(i < int(s.size())-2);
      if (s[i+1] == 'n') {
        code = code || instruction::WRITELN();
        i += 2;
      }
      else if (s[i+1] == 't' or s[i+1] == '"' or s[i+1] == '\\') {
        code = code ||
               instruction::CHLOAD(temp, s.substr(i,2)) ||
	       instruction::WRITEC(temp);
        i += 2;
      }
      else {
        code = code ||
               instruction::CHLOAD(temp, s.substr(i,1)) ||
	       instruction::WRITEC(temp);
        i += 1;
      }
    }
  }
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterLeft_expr(AslParser::Left_exprContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitLeft_expr(AslParser::Left_exprContext *ctx) {
  DEBUG_ENTER();
}

void CodeGenListener::enterIdentExpr(AslParser::IdentExprContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitIdentExpr(AslParser::IdentExprContext *ctx) {
  putAddrDecor(ctx, getAddrDecor(ctx->ident()));
  putCodeDecor(ctx, getCodeDecor(ctx->ident()));
  DEBUG_ENTER();
}

void CodeGenListener::enterArrayExpr(AslParser::ArrayExprContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitArrayExpr(AslParser::ArrayExprContext *ctx) {
  std::string label = codeCounters.newTEMP();
  std::string labelTemp = "%"+label;
  std::string addr1 = getAddrDecor(ctx->arrayid()->ident());
  instructionList code1 =  getCodeDecor(ctx->arrayid()->ident());
  std::string addr2 = getAddrDecor(ctx->arrayid()->expr());
  instructionList code2 = getCodeDecor(ctx->arrayid()->expr());
  instructionList code = code1 || code2 || instruction::LOADX(labelTemp, addr1, addr2);
  putCodeDecor(ctx, code);
  putAddrDecor(ctx, labelTemp);
  DEBUG_ENTER();
}

void CodeGenListener::enterArithmetic(AslParser::ArithmeticContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitArithmetic(AslParser::ArithmeticContext *ctx) {
  std::string     addr1 = getAddrDecor(ctx->expr(0));
  instructionList code1 = getCodeDecor(ctx->expr(0));
  std::string     addr2 = getAddrDecor(ctx->expr(1));
  instructionList code2 = getCodeDecor(ctx->expr(1));
  instructionList code  = code1 || code2;
  std::string temp = "%"+codeCounters.newTEMP();
  TypesMgr::TypeId tp = getTypeDecor(ctx);
  if (Types.isFloatTy(tp)) {
    TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
    TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
    if (not Types.isFloatTy(t1)) {
      std::string temp1 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp1,addr1);
      addr1 = temp1;
    }
    if (not Types.isFloatTy(t2)) {
      std::string temp2 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp2,addr2);
      addr2 = temp2;
    }
    if (ctx->MUL()) {
      code = code || instruction::FMUL(temp, addr1, addr2);
    } else if (ctx->DIV()) {
      code = code || instruction::FDIV(temp, addr1, addr2);
    } else if (ctx->PLUS()) {
      code = code || instruction::FADD(temp, addr1, addr2);
    } else { // MINUS
      code = code || instruction::FSUB(temp, addr1, addr2);
    }
  } else {
    if (ctx->MUL()) {
      code = code || instruction::MUL(temp, addr1, addr2);
    } else if (ctx->DIV()) {
      code = code || instruction::DIV(temp, addr1, addr2);
    } else if (ctx->MOD()) {
      code = code || instruction::DIV(temp, addr1, addr2) || instruction::MUL(temp, addr2, temp) || instruction::SUB(temp, addr1, temp);
    } else if (ctx->PLUS()) {
      code = code || instruction::ADD(temp, addr1, addr2);
    } else { // MINUS
      code = code || instruction::SUB(temp, addr1, addr2);
    }
  }
  putAddrDecor(ctx, temp);
  putOffsetDecor(ctx, "");
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterLogical(AslParser::LogicalContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitLogical(AslParser::LogicalContext *ctx) {
  std::string     addr1 = getAddrDecor(ctx->expr(0));
  instructionList code1 = getCodeDecor(ctx->expr(0));
  std::string     addr2 = getAddrDecor(ctx->expr(1));
  instructionList code2 = getCodeDecor(ctx->expr(1));
  instructionList code  = code1 || code2;
  std::string temp = "%"+codeCounters.newTEMP();
  if (ctx->AND()) {
    code = code || instruction::AND(temp, addr1, addr2);
  } else {
    code = code || instruction::OR(temp, addr1, addr2);
  }
  putAddrDecor(ctx, temp);
  putOffsetDecor(ctx, "");
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterUnary(AslParser::UnaryContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitUnary(AslParser::UnaryContext *ctx) {
  std::string     addr1 = getAddrDecor(ctx->expr());
  instructionList code1 = getCodeDecor(ctx->expr());
  instructionList code  = code1;
  std::string temp = addr1;
  if (not ctx->PLUS()) {
    temp = "%"+codeCounters.newTEMP();
    if (ctx->NOT()) {
      code = code || instruction::NOT(temp, addr1);
    } else {
      TypesMgr::TypeId tp = getTypeDecor(ctx->expr());
      if (Types.isFloatTy(tp)) {
        code = code || instruction::FNEG(temp, addr1);
      } else {
        code = code || instruction::NEG(temp, addr1);
      }
    }
  }
  putAddrDecor(ctx, temp);
  putOffsetDecor(ctx, "");
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterRelational(AslParser::RelationalContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitRelational(AslParser::RelationalContext *ctx) {
  std::string     addr1 = getAddrDecor(ctx->expr(0));
  instructionList code1 = getCodeDecor(ctx->expr(0));
  std::string     addr2 = getAddrDecor(ctx->expr(1));
  instructionList code2 = getCodeDecor(ctx->expr(1));
  instructionList code  = code1 || code2;
  std::string temp = "%"+codeCounters.newTEMP();
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  if (Types.isFloatTy(t1) or Types.isFloatTy(t2)) {
    if (not Types.isFloatTy(t1)) {
      std::string temp1 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp1,addr1);
      addr1 = temp1;
    }
    if (not Types.isFloatTy(t2)) {
      std::string temp2 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp2,addr2);
      addr2 = temp2;
    }
    if (ctx->EQUAL()) {
      code = code || instruction::FEQ(temp, addr1, addr2);
    } else if (ctx->NEQUAL()) {
      code = code || instruction::FEQ(temp, addr1, addr2) || instruction::NOT(temp, temp);
    } else if (ctx->LT()) {
      code = code || instruction::FLT(temp, addr1, addr2);
    } else if (ctx->GT()) {
      code = code || instruction::FLT(temp, addr2, addr1);
    } else if (ctx->LE()) {
      code = code || instruction::FLE(temp, addr1, addr2);
    } else { // GE
      code = code || instruction::FLE(temp, addr2, addr1);
    }
  } else {
    if (ctx->EQUAL()) {
      code = code || instruction::EQ(temp, addr1, addr2);
    } else if (ctx->NEQUAL()) {
      code = code || instruction::EQ(temp, addr1, addr2) || instruction::NOT(temp, temp);
    } else if (ctx->LT()) {
      code = code || instruction::LT(temp, addr1, addr2);
    } else if (ctx->GT()) {
      code = code || instruction::LT(temp, addr2, addr1);
    } else if (ctx->LE()) {
      code = code || instruction::LE(temp, addr1, addr2);
    } else { // GE
      code = code || instruction::LE(temp, addr2, addr1);
    }
  }
  putAddrDecor(ctx, temp);
  putOffsetDecor(ctx, "");
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterValue(AslParser::ValueContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitValue(AslParser::ValueContext *ctx) {
  instructionList code;
  std::string temp = "%"+codeCounters.newTEMP();
  if (ctx->INTVAL()) {
    code = instruction::ILOAD(temp, ctx->getText());
  } else if (ctx->CHARVAL()) {
    int mida = (int)ctx->getText().size();
    assert(mida > 2);
    code = instruction::CHLOAD(temp, ctx->getText().substr(1,mida-2));
  } else if (ctx->FLOATVAL()) {
    code = instruction::FLOAD(temp, ctx->getText());
  } else if (ctx->TRUE()) {
    code = instruction::ILOAD(temp, "1");
  } else {
    code = instruction::ILOAD(temp, "0");
  }
  putAddrDecor(ctx, temp);
  putOffsetDecor(ctx, "");
  putCodeDecor(ctx, code);
  DEBUG_EXIT();
}

void CodeGenListener::enterIdent(AslParser::IdentContext *ctx) {
  DEBUG_ENTER();
}
void CodeGenListener::exitIdent(AslParser::IdentContext *ctx) {
  std::string name = ctx->ID()->getText();
  putOffsetDecor(ctx, "");
  instructionList code;
  if (Types.isArrayTy(getTypeDecor(ctx)) and Symbols.isParameterClass(name)) {
    std::string temp = "%"+codeCounters.newTEMP();
    code = instruction::LOAD(temp, name);
    name = temp;
  }
  putCodeDecor(ctx, code);
  putAddrDecor(ctx, name);
  DEBUG_EXIT();
}

// void CodeGenListener::enterEveryRule(antlr4::ParserRuleContext *ctx) {
//   DEBUG_ENTER();
// }
// void CodeGenListener::exitEveryRule(antlr4::ParserRuleContext *ctx) {
//   DEBUG_EXIT();
// }
// void CodeGenListener::visitTerminal(antlr4::tree::TerminalNode *node) {
//   DEBUG(">>> visit " << node->getSymbol()->getLine() << ":" << node->getSymbol()->getCharPositionInLine() << " CodeGen TerminalNode");
// }
// void CodeGenListener::visitErrorNode(antlr4::tree::ErrorNode *node) {
// }


// Getters for the necessary tree node atributes:
//   Scope, Type, Addr, Offset and Code
SymTable::ScopeId CodeGenListener::getScopeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getScope(ctx);
}
TypesMgr::TypeId CodeGenListener::getTypeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getType(ctx);
}
std::string CodeGenListener::getAddrDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getAddr(ctx);
}
std::string  CodeGenListener::getOffsetDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getOffset(ctx);
}
instructionList CodeGenListener::getCodeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getCode(ctx);
}

// Setters for the necessary tree node attributes:
//   Addr, Offset and Code
void CodeGenListener::putAddrDecor(antlr4::ParserRuleContext *ctx, const std::string & a) {
  Decorations.putAddr(ctx, a);
}
void CodeGenListener::putOffsetDecor(antlr4::ParserRuleContext *ctx, const std::string & o) {
  Decorations.putOffset(ctx, o);
}
void CodeGenListener::putCodeDecor(antlr4::ParserRuleContext *ctx, const instructionList & c) {
  Decorations.putCode(ctx, c);
}
