%skeleton "lalr1.cc"    
%require "2.4.1"
%defines
%define parser_class_name { AutoGenParser }
%code requires {
#include <string>
#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#define _SVAL_DELETE(p) { delete (String*)p; }
#define _SVAL_DELETE_StringList(p) { delete (StringList*)p; }

/* IAS_DFT_FACTORY<String>::Free(p) */
namespace IAS{
namespace Lang{
namespace Script{
namespace Parser{
class Parser; 
}}}}

}
%parse-param { ::IAS::Lang::Script::Parser::Parser& myParser }
%lex-param   { ::IAS::Lang::Script::Parser::Parser& myParser }
%locations
%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = new std::string("waisted");
};
%debug
%error-verbose
// Symbols.
%union
{
  ::IAS::String                                  *sval;
  ::IAS::StringList                              *pStringList;
  
  ::IAS::Lang::Model::ProgramNode                *pProgramNode;
  ::IAS::Lang::Model::Stmt::StatementNode        *pStatementNode;
  
  ::IAS::Lang::Model::Dec::ParametersNode        *pParametersNode;
  ::IAS::Lang::Model::Dec::DeclarationNode       *pDeclarationNode;
  ::IAS::Lang::Model::Dec::QualifiedNameNode     *pQualifiedNameNode;
  
  ::IAS::Lang::Model::Stmt::StatementsListNode   *pStatementsListNode;
  ::IAS::Lang::Model::Stmt::LeftSideNode         *pLeftSideNode;
  
  ::IAS::Lang::Model::Stmt::CatchListNode        *pCatchListNode;
  ::IAS::Lang::Model::Stmt::CatchNode            *pCatchNode;
  
  ::IAS::Lang::Model::Expr::ExprListNode         *pExprListNode;
  
  ::IAS::Lang::Model::Expr::LogicalExprNode      *pLogicalExprNode;
  ::IAS::Lang::Model::Expr::ExprNode             *pExprNode;
  
  ::IAS::Lang::Model::Expr::XPath::XPathAccessNode  *pXPathAccessNode;
  
  ::IAS::Lang::Model::Expr::XPath::XPathNode     *pXPathNode;
  
  ::IAS::Lang::Model::Dec::TypeInfoNode          *pTypeInfo;
  ::IAS::Lang::Model::Dec::TypeDefinitionNode    *pTypeDefinitionNode;
  ::IAS::Lang::Model::Dec::NamespaceDeclarationNode    *pNamespaceDeclarationNode;
  
};

%code {
#include "Parser.h"
#include "Lexer.h"
#include "yylex_function.h"

using namespace IAS;
using namespace Lang;
using namespace Model;
using namespace Script;
using namespace Parser;

}

/***************************************************************************************/

//%token        END           0
 
%token  T_NONE
%token  T_EOF				0	"end of file"
%token	T_IMPORT				"IMPORT"

%token	T_PROGRAM				"PROGRAM"
%token	T_BEGIN					"BEGIN"
%token	T_END                   "END"

%token	T_DEFINE                "DEFINE"
%token	T_EXTENSION             "EXTENSION"
%token	T_NAMESPACE             "NAMESPACE"

%token	T_CALL                  "CALL"

%token	T_SORT                  "SORT"
%token	T_MERGE                 "MERGE"
%token	T_USING                 "USING"
%token	T_INDEX                 "INDEX"

%token	T_FOR                   "FOR"
%token	T_TO                    "TO"
%token	T_STEP                  "STEP"

%token	T_WHILE                 "WHILE"
%token	T_DO	                "DO"

%token	T_IF                    "IF"
%token	T_THEN                  "THEN"
%token	T_ELSE                  "ELSE"

%token	T_RETURN                "RETURN"
%token	T_THROW                 "THROW"
%token	T_TRY                   "TRY"
%token	T_CATCH                 "CATCH"
%token	T_WITH                  "WITH"
%token	T_AS                    "AS"
%token	T_OF                    "OF"
%token	T_ARRAY                 "ARRAY"
%token	T_RETURNS               "RETURNS"
%token	T_VAR                   "VAR"

%token	T_AND                   "AND"
%token	T_OR                    "OR"
%token	T_NOT                   "NOT"

%token	T_OPEN_PAR              "("
%token	T_CLOSE_PAR             ")"


%token	T_NEW                   "NEW"
%token	T_SIZEOF                "SIZEOF"
%token	T_COPYOF                "COPYOF"
%token	T_DETACH                "DETACH"
%token	T_CREATE				"CREATE"
%token	T_DELETE				"DELETE"

%token  T_EXTERNAL              "EXTERNAL"

%token	T_TYPE					"TYPE"
%token	T_TYPENS				"TYPENS"
%token	T_ISSET					"ISSET"
%token	T_ISNULL				"ISNULL"
%token	T_ISTYPE				"ISTYPE"
%token	T_ISINSTANCE			"ISINSTANCE"

%token	T_STRLEN				"STRLEN"
	
%token	T_OPEN_SQUARE           "["
%token	T_CLOSE_SQUARE          "]"

%token	T_DOUBLE_OPEN_SQUARE           "[["
%token	T_DOUBLE_CLOSE_SQUARE          "]]"

%token	T_PLUS             "+"
%token	T_MINUS            "-"

%token	T_ASTERISK           "*"
%token	T_SLASH              "/"
%token	T_PERCENT            "%"

%token	T_COMMA                 ","
%token	T_COLON                 ":"
%token	T_DOUBLECOLON           "::"
%token	T_DOT                   "."
%token	T_SEMICOLON             ";"

%token	T_EQ                    "=="
%token	T_GREATER               "<"
%token	T_GREATER_EQ            "<="
%token	T_LESS                  ">"
%token	T_LESS_EQ               ">="
%token	T_DIFF                  "<>"

%token	T_ASSIGN                "= (assignment)"
%token	T_CONDASSIGN            "?= (assignment)"
%token	T_QMARK                 "?"

%token	<sval>			T_SYMBOL
%token	<sval>			T_STRING
%token	<sval>          T_INTEGER
%token	<sval>          T_FLOAT
%token	<sval>          T_BOOLEAN
%token	<sval>          T_NULL

%type <pProgramNode>            program
%type <pParametersNode>         parametersList
%type <pParametersNode>         parametersListPar
%type <pStatementNode>          statement
%type <pStatementNode>          assignment
%type <pStatementNode>          condassign
%type <pStatementNode>          merge
%type <pStatementNode>          forLoop
%type <pStatementNode>          whileLoop
%type <pStatementNode>          with
%type <pStatementNode>          ifThenElse
%type <pStatementNode>          call
%type <pStatementNode>          external
%type <pStatementNode>          create
%type <pStatementNode>          delete
%type <pStatementNode>          sort
%type <pStatementNode>          index
%type <pStatementNode>          return
%type <pStatementNode>          throw
%type <pStatementNode>          tryCatch
%type <pCatchListNode>          catchList
%type <pCatchNode>              catch
%type <pDeclarationNode>        declaration
%type <pDeclarationNode>        programResult
%type <pExprListNode>           exprListPar
%type <pExprListNode>           exprList
%type <pExprNode>               expr
%type <pExprNode>               exprTerm
%type <pExprNode>               exprPrimary
%type <pExprNode>               exprPrimaryOrXPath
%type <pExprNode>               exprFactor
%type <pLogicalExprNode>        relationalOper
%type <pLogicalExprNode>        logicalExprFactor
%type <pLogicalExprNode>        logicalExprPrimary
%type <pLogicalExprNode>        logicalExprTerm
%type <pLogicalExprNode>        logicalExpr
%type <pLeftSideNode>           lvalue
%type <pStatementsListNode>     statementsList
%type <pXPathNode>     			xpath
%type <pXPathAccessNode>  		xpathAccess
%type <pStatementsListNode>     statementsListBeginEnd
%type <pQualifiedNameNode>      qname
%type <pStringList>             externalParameters
%type <pStringList>             externalParametersPar
%type <pTypeInfo>               baseType
%type <pTypeDefinitionNode>     typeDefinition
%type <pTypeDefinitionNode>     typeDefinitionPropertiesEnclosed
%type <pTypeDefinitionNode>     typeDefinitionProperties
%type <pDeclarationNode>        property
%type <pNamespaceDeclarationNode>  namespaceDeclaration
/***************************************************************************************/

%destructor { std::cout<<"D:"<<*$$<<"\n"; _SVAL_DELETE($$); } <sval>

%%
%start globals;

globals : | globals global

global: import
global: typeDefinition { myParser.addTypeDefinition($1); }
global: program {
    $1->setSourceLocation(myParser.getLexer()->getCachedLocation()); 
	myParser.addProgram($1); 
};

global : namespaceDeclaration {
  myParser.addNamespaceDeclaration($1);
}

import : T_IMPORT qname T_SEMICOLON 
           {  myParser.open($2->getQualifiedName()); 
           	 IAS_DFT_FACTORY<Dec::QualifiedNameNode>::Free($2); 
           	 }; 

typeDefinition : T_DEFINE T_SYMBOL T_COLON T_STRING T_AS typeDefinitionPropertiesEnclosed T_SEMICOLON 
				{ $$ = $6;
				  $$->setName(*$2); _SVAL_DELETE($2); 
				  $$->setNamespace(*$4); _SVAL_DELETE($4); };
	
typeDefinition : T_DEFINE T_SYMBOL T_COLON T_STRING T_AS T_EXTENSION T_OF baseType typeDefinitionPropertiesEnclosed T_SEMICOLON 
				{ $$ = $9;
				  $$->setBaseTypeNode($8);
				  $$->setName(*$2); _SVAL_DELETE($2); 
				  $$->setNamespace(*$4); _SVAL_DELETE($4); };

typeDefinition : T_DEFINE T_SYMBOL T_COLON T_STRING T_SEMICOLON 
				{ $$ = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create(); 				  
				  $$->setName(*$2); _SVAL_DELETE($2); 
				  $$->setNamespace(*$4); _SVAL_DELETE($4); };
				  
typeDefinition : T_DEFINE T_SYMBOL T_COLON T_STRING T_AS T_EXTENSION T_OF baseType T_SEMICOLON 
				{ $$ = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create(); 
				  $$->setBaseTypeNode($8);
				  $$->setName(*$2); _SVAL_DELETE($2); 
				  $$->setNamespace(*$4); _SVAL_DELETE($4); };


baseType: T_SYMBOL  
		{ $$ = IAS_DFT_FACTORY<Dec::TypeInfoNode>::Create(*$1); _SVAL_DELETE($1);};
		
baseType: T_SYMBOL T_COLON T_STRING 
		{ $$ = IAS_DFT_FACTORY<Dec::TypeInfoNode>::Create(*$1,*$3);  _SVAL_DELETE($1); _SVAL_DELETE($3);};
		
typeDefinitionPropertiesEnclosed: T_BEGIN typeDefinitionProperties T_END { $$ = $2; }
				|  T_BEGIN T_END { $$ = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create();  }

typeDefinitionProperties: typeDefinitionProperties  property T_SEMICOLON { $$ = $1; $$->addDeclaration($2); }
 		        |   { $$ = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create();};
 		        
property : T_SYMBOL T_AS T_SYMBOL { $$ = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*$1,*$3); _SVAL_DELETE($1); _SVAL_DELETE($3); }
property : T_SYMBOL T_AS T_SYMBOL T_COLON T_STRING { $$ = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*$1,*$3,*$5); 
												                _SVAL_DELETE($1); _SVAL_DELETE($3); _SVAL_DELETE($5);}
property : T_SYMBOL T_AS T_ARRAY T_OF T_SYMBOL { $$ = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*$1,*$5); 
												 $$->setIsArray(true); 
												 _SVAL_DELETE($1); _SVAL_DELETE($5); }												 
property : T_SYMBOL T_AS T_ARRAY T_OF T_SYMBOL T_COLON T_STRING { $$ = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*$1,*$5,*$7); 
																  $$->setIsArray(true); 
												                  _SVAL_DELETE($1); _SVAL_DELETE($5); _SVAL_DELETE($7);}

namespaceDeclaration : T_NAMESPACE T_STRING T_AS T_STRING T_SEMICOLON 
				{ $$ = IAS_DFT_FACTORY<Dec::NamespaceDeclarationNode>::Create(*$2,*$4); 
					_SVAL_DELETE($2); _SVAL_DELETE($4); };	        
           
program : T_PROGRAM qname parametersListPar statementsListBeginEnd T_SEMICOLON 
			{ $$ = IAS_DFT_FACTORY<StandardProgramNode>::Create($2,$4,$3); };

program : T_PROGRAM qname parametersListPar programResult statementsListBeginEnd T_SEMICOLON 
			{ $$ = IAS_DFT_FACTORY<StandardProgramNode>::Create($2,$5,$3,$4); };

program : T_PROGRAM qname parametersListPar T_EXTERNAL T_STRING externalParametersPar T_SEMICOLON 
			{ $$ = IAS_DFT_FACTORY<ExternalProgramNode>::Create($2,*$5,$3,*$6); _SVAL_DELETE($5); _SVAL_DELETE_StringList($6);};

program : T_PROGRAM qname parametersListPar programResult T_EXTERNAL T_STRING externalParametersPar T_SEMICOLON 
			{ $$ = IAS_DFT_FACTORY<ExternalProgramNode>::Create($2,*$6,$3,$4,*$7); _SVAL_DELETE($6); _SVAL_DELETE_StringList($7);};

programResult : T_RETURNS T_SYMBOL { $$ = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*$2); _SVAL_DELETE($2); }
programResult : T_RETURNS T_SYMBOL T_COLON T_STRING { $$ = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*$2,*$4); _SVAL_DELETE($2); _SVAL_DELETE($4);}
programResult : T_RETURNS T_ARRAY T_OF T_SYMBOL { $$ = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*$4);  $$->setIsArray(true); _SVAL_DELETE($4); }
programResult : T_RETURNS T_ARRAY T_OF T_SYMBOL T_COLON T_STRING { $$ = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*$4,*$6);  $$->setIsArray(true); _SVAL_DELETE($4); _SVAL_DELETE($6);}

parametersListPar: T_OPEN_PAR parametersList T_CLOSE_PAR { $$ = $2; }
				|  T_OPEN_PAR T_CLOSE_PAR { $$ = IAS_DFT_FACTORY<Dec::ParametersNode>::Create();  }
				   
parametersList: parametersList T_COMMA declaration  { $$ = $1; $$->addDeclaration($3); }
		      |  declaration  { $$ = IAS_DFT_FACTORY<Dec::ParametersNode>::Create(); $$->addDeclaration($1); };
	
statementsListBeginEnd: T_BEGIN statementsList T_END{ $$ = $2; }

statementsList: statementsList statement T_SEMICOLON { 
$$ = $1; 
$2->setSourceLocation(myParser.getLexer()->getCachedLocation());
$$->addStatement($2);
 }
statementsList: statementsList declaration T_SEMICOLON { $$ = $1; $$->addDeclaration($2); }
           | /* Nothing.  */             { $$ = IAS_DFT_FACTORY<Stmt::StatementsListNode>::Create(); };

declaration : T_VAR T_SYMBOL T_AS T_SYMBOL { $$ = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*$2,*$4); _SVAL_DELETE($2); _SVAL_DELETE($4); }
declaration : T_VAR T_SYMBOL T_AS T_SYMBOL T_COLON T_STRING { $$ = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*$2,*$4,*$6); _SVAL_DELETE($2); _SVAL_DELETE($4); _SVAL_DELETE($6);}
declaration : T_VAR T_SYMBOL T_AS T_ARRAY T_OF T_SYMBOL 
		{ $$ = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*$2,*$6);     $$->setIsArray(true); _SVAL_DELETE($2);  _SVAL_DELETE($6); }
declaration : T_VAR T_SYMBOL T_AS T_ARRAY T_OF T_SYMBOL T_COLON T_STRING 
        { $$ = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*$2,*$6,*$8); $$->setIsArray(true); _SVAL_DELETE($2);  _SVAL_DELETE($6); _SVAL_DELETE($8);}


statement: statementsListBeginEnd        { $$ =$1; } ;
statement: assignment                    { $$ =$1; } ;
statement: condassign                    { $$ =$1; } ;
statement: merge                         { $$ =$1; } ;
statement: forLoop                       { $$ =$1; } ;
statement: whileLoop                     { $$ =$1; } ;
statement: with                          { $$ =$1; } ;
statement: ifThenElse                    { $$ =$1; } ;
statement: index                         { $$ =$1; } ;
statement: call                          { $$ =$1; } ;
statement: external                      { $$ =$1; } ;
statement: create                        { $$ =$1; } ;
statement: delete                        { $$ =$1; } ;
statement: return                        { $$ =$1; } ;
statement: sort                          { $$ =$1; } ;
statement: throw                         { $$ =$1; } ;
statement: tryCatch                      { $$ =$1; } ;

assignment: lvalue T_ASSIGN expr  { $$ = IAS_DFT_FACTORY<Stmt::AssignmentNode>::Create($1,$3); } ;
condassign: lvalue T_CONDASSIGN xpathAccess  { $$ = IAS_DFT_FACTORY<Stmt::ConditionalAssignmentNode>::Create($1,$3); } ;
merge:      lvalue T_MERGE  expr  { $$ = IAS_DFT_FACTORY<Stmt::MergeNode>::Create($1,$3); } ;

lvalue : xpathAccess { $$ = IAS_DFT_FACTORY<Stmt::LeftSideNode>::Create($1); } ; 

%left T_PLUS T_MINUS;
%left T_ASTERISK T_SLASH T_PERCENT;
%left T_AND T_OR ;


expr:      exprTerm  { $$ = $1; };
exprTerm:  exprTerm T_PLUS   exprTerm { $$ = IAS_DFT_FACTORY<Expr::AdditionNode>::Create($1,$3); };
exprTerm:  exprTerm T_MINUS  exprTerm { $$ = IAS_DFT_FACTORY<Expr::SubtractionNode>::Create($1,$3); };

exprTerm:    exprFactor { $$ = $1; } ;
exprFactor:  exprFactor T_ASTERISK exprFactor { $$ = IAS_DFT_FACTORY<Expr::MultiplyNode>::Create($1,$3); };
exprFactor:  exprFactor T_SLASH    exprFactor { $$ = IAS_DFT_FACTORY<Expr::DivisionNode>::Create($1,$3); };
exprFactor:  exprFactor T_PERCENT  exprFactor { $$ = IAS_DFT_FACTORY<Expr::ModuloNode>::Create($1,$3); };

exprFactor: exprPrimaryOrXPath { $$ = $1; } ;

exprPrimaryOrXPath :  exprPrimary    { $$ = $1; } 
exprPrimaryOrXPath :  xpathAccess    { $$ = IAS_DFT_FACTORY<Expr::XPath::XPathExprNode>::Create($1); };
					  
exprPrimary: T_OPEN_PAR expr T_CLOSE_PAR { $$ = $2; } ;
exprPrimary: T_INTEGER  { $$ = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_INTEGER,*$1); _SVAL_DELETE($1); } ;
exprPrimary: T_FLOAT    { $$ = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_FLOAT,*$1);   _SVAL_DELETE($1); } ;
exprPrimary: T_STRING   { $$ = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_STRING,*$1);  _SVAL_DELETE($1); } ;
exprPrimary: T_BOOLEAN  { $$ = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_BOOLEAN,*$1); _SVAL_DELETE($1); } ;
exprPrimary: T_NULL     { $$ = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_NULL,*$1);    _SVAL_DELETE($1); } ;

exprPrimary: T_NEW T_SYMBOL T_COLON T_STRING { $$ = IAS_DFT_FACTORY<Expr::ConstructorNode>::Create(*$2,*$4); _SVAL_DELETE($2); _SVAL_DELETE($4); } ;
exprPrimary: T_NEW T_SYMBOL T_COLON T_STRING statementsListBeginEnd 
	{ $$ = IAS_DFT_FACTORY<Expr::ConstructorNode>::Create(*$2,*$4, $5); _SVAL_DELETE($2); _SVAL_DELETE($4); } ;

exprPrimary: T_OPEN_PAR exprPrimaryOrXPath T_AS baseType T_CLOSE_PAR
		{ $$ = IAS_DFT_FACTORY<Expr::CastNode>::Create($2,$4); };

exprPrimary: T_OPEN_PAR xpathAccess T_OR exprPrimaryOrXPath T_CLOSE_PAR
		{ $$ = IAS_DFT_FACTORY<Expr::XPathOrValueNode>::Create($2,$4); };

exprPrimary: T_OPEN_PAR logicalExpr T_QMARK exprPrimaryOrXPath T_COLON exprPrimaryOrXPath T_CLOSE_PAR
		{ $$ = IAS_DFT_FACTORY<Expr::CondValueNode>::Create($2,$4,$6); };
 
exprPrimary:  qname exprListPar                    { $$ = IAS_DFT_FACTORY<Expr::FunCallNode>::Create($1, $2); };
exprPrimary:  T_COPYOF T_OPEN_PAR xpathAccess T_CLOSE_PAR { $$ = IAS_DFT_FACTORY<Expr::CopyOfNode>::Create($3); };
exprPrimary:  T_DETACH T_OPEN_PAR xpathAccess T_CLOSE_PAR { $$ = IAS_DFT_FACTORY<Expr::DetachNode>::Create($3); };
exprPrimary:  T_MINUS exprPrimary                  { $$ = IAS_DFT_FACTORY<Expr::NegativeNode>::Create($2); };
exprPrimary:  T_SIZEOF T_OPEN_PAR xpathAccess T_CLOSE_PAR { $$ = IAS_DFT_FACTORY<Expr::SizeOfNode>::Create($3);}
exprPrimary:  T_TYPE   T_OPEN_PAR expr T_CLOSE_PAR { $$ = IAS_DFT_FACTORY<Expr::GetTypeNode>::Create($3);}
exprPrimary:  T_TYPENS T_OPEN_PAR expr T_CLOSE_PAR { $$ = IAS_DFT_FACTORY<Expr::GetTypeNSNode>::Create($3);}
exprPrimary:  T_STRLEN T_OPEN_PAR expr T_CLOSE_PAR { $$ = IAS_DFT_FACTORY<Expr::StrLenNode>::Create($3);}

relationalOper: expr T_EQ expr { $$ = IAS_DFT_FACTORY<Expr::RelationalEqNode>::Create($1,$3); }; 

relationalOper: expr T_DIFF expr       { $$ = IAS_DFT_FACTORY<Expr::RelationalDiffNode>::Create($1,$3); };
relationalOper: expr T_GREATER_EQ expr { $$ = IAS_DFT_FACTORY<Expr::RelationalEqGtNode>::Create($1,$3); }; 
relationalOper: expr T_LESS_EQ expr    { $$ = IAS_DFT_FACTORY<Expr::RelationalEqLessNode>::Create($1,$3); }; 
relationalOper: expr T_GREATER expr    { $$ = IAS_DFT_FACTORY<Expr::RelationalGtNode>::Create($1,$3); }; 
relationalOper: expr T_LESS expr       { $$ = IAS_DFT_FACTORY<Expr::RelationalLessNode>::Create($1,$3); }; 

relationalOper: expr T_ISTYPE T_OPEN_PAR baseType T_CLOSE_PAR 
		{ $$ = IAS_DFT_FACTORY<Expr::RelationalIsTypeNode>::Create($1,$4); };

relationalOper: expr T_ISINSTANCE T_OPEN_PAR baseType T_CLOSE_PAR 
		{ $$ = IAS_DFT_FACTORY<Expr::RelationalIsInstanceNode>::Create($1,$4); };
			   		
logicalExprPrimary : relationalOper { $$ = $1; };
logicalExprPrimary : T_OPEN_PAR logicalExpr T_CLOSE_PAR{ $$ = $2; };
logicalExprPrimary : T_NOT logicalExprPrimary { $$ = IAS_DFT_FACTORY<Expr::LogicalNotNode>::Create($2); };
logicalExprPrimary : T_ISSET  T_OPEN_PAR xpathAccess T_CLOSE_PAR { $$ = IAS_DFT_FACTORY<Expr::IsSetNode>::Create($3); };
logicalExprPrimary : T_ISNULL T_OPEN_PAR xpathAccess T_CLOSE_PAR { $$ = IAS_DFT_FACTORY<Expr::IsNullNode>::Create($3); };

logicalExprFactor :  logicalExprPrimary { $$ = $1; };
logicalExprFactor :  logicalExprFactor T_AND logicalExprFactor { $$ = IAS_DFT_FACTORY<Expr::LogicalAndNode>::Create($1,$3); };

logicalExprTerm :  logicalExprFactor { $$ = $1; };
logicalExprTerm :  logicalExprTerm T_OR logicalExprTerm { $$ = IAS_DFT_FACTORY<Expr::LogicalOrNode>::Create($1,$3); };

logicalExpr :  logicalExprTerm { $$ = $1; };

//TODO resolve conflicting recursion 
xpathAccess : xpath { $$ = IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::Create(
								IAS_DFT_FACTORY<Expr::XPath::XPathVariableAccessNode>::Create(
										(*($1->getElements().begin()))->getName()),$1);} ;													
xpathAccess : exprPrimary T_DOT xpath 
			{ $$ = IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::Create(
						IAS_DFT_FACTORY<Expr::XPath::XPathExprAccessNode>::Create($1),$3); } ;

xpath: xpath T_DOT T_SYMBOL              { $$ = $1; $$->addSingleElement(*$3); _SVAL_DELETE($3); }
xpath: xpath T_DOT T_SYMBOL T_OPEN_SQUARE
                     expr  T_CLOSE_SQUARE{ $$ = $1; $$->addMultiElement(*$3,$5); _SVAL_DELETE($3); }

xpath: xpath T_DOT T_SYMBOL T_DOUBLE_OPEN_SQUARE
                     expr  T_DOUBLE_CLOSE_SQUARE{ $$ = $1; $$->addHashIndexElement(*$3,$5); _SVAL_DELETE($3); }
                     
xpath: T_SYMBOL { $$ = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); $$->addSingleElement(*$1); _SVAL_DELETE($1); }
xpath: T_SYMBOL T_OPEN_SQUARE
         expr  T_CLOSE_SQUARE{ $$ = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); $$->addMultiElement(*$1,$3); _SVAL_DELETE($1); }
                     
xpath: T_SYMBOL T_DOUBLE_OPEN_SQUARE
                     expr  T_DOUBLE_CLOSE_SQUARE{ $$ = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); $$->addHashIndexElement(*$1,$3); _SVAL_DELETE($1); }
           
with : T_WITH xpathAccess T_DO statement     { $$ = IAS_DFT_FACTORY<Stmt::WithNode>::Create("",$2,$4); } ;
with : T_WITH T_SYMBOL T_AS xpathAccess T_DO statement     { $$ = IAS_DFT_FACTORY<Stmt::WithNode>::Create(*$2,$4,$6); _SVAL_DELETE($2); } ;

whileLoop : T_WHILE logicalExpr T_DO statement   { $$ = IAS_DFT_FACTORY<Stmt::WhileLoopNode>::Create($2,$4); } ;

forLoop : T_FOR xpathAccess T_ASSIGN expr T_TO expr T_DO statement   
				{ $$ = IAS_DFT_FACTORY<Stmt::ForLoopNode>::Create($2,$8,$4,$6); } ;

forLoop : T_FOR xpathAccess T_ASSIGN expr T_TO expr T_STEP expr T_DO statement   
			  { $$ = IAS_DFT_FACTORY<Stmt::ForLoopNode>::Create($2,$10,$4,$6,$8); } ;
			  
ifThenElse: T_IF logicalExpr T_THEN statement   { $$ = IAS_DFT_FACTORY<Stmt::IfThenElseNode>::Create($2,$4); } ;

ifThenElse: T_IF logicalExpr T_THEN statement T_ELSE statement
										 { $$ = IAS_DFT_FACTORY<Stmt::IfThenElseNode>::Create($2,$4,$6); } ;

call : qname exprListPar { $$ = IAS_DFT_FACTORY<Stmt::CallNode>::Create($1,$2); };

external : T_EXTERNAL qname exprListPar { $$ = IAS_DFT_FACTORY<Stmt::CallNode>::Create($2,$3); };
create :   T_CREATE	  xpathAccess  { $$ = IAS_DFT_FACTORY<Stmt::CreateNode>::Create($2); }
create :   T_CREATE	  xpathAccess statementsListBeginEnd { $$ = IAS_DFT_FACTORY<Stmt::CreateNode>::Create($2,$3); }
delete :   T_DELETE	  xpathAccess  { $$ = IAS_DFT_FACTORY<Stmt::DeleteNode>::Create($2); }

return: T_RETURN { $$ = IAS_DFT_FACTORY<Stmt::ReturnNode>::Create(); } ;
return: T_RETURN expr  { $$ = IAS_DFT_FACTORY<Stmt::ReturnNode>::Create($2); } ;

//throw: T_THROW       { $$ = IAS_DFT_FACTORY<Stmt::ThrowNode>::Create(); } ;
throw: T_THROW expr  { $$ = IAS_DFT_FACTORY<Stmt::ThrowNode>::Create($2); } ;

sort: T_SORT xpathAccess T_USING qname { $$ = IAS_DFT_FACTORY<Stmt::SortNode>::Create($2,$4); } ;

index: T_INDEX xpathAccess T_USING xpathAccess { $$ = IAS_DFT_FACTORY<Stmt::IndexNode>::Create($2,$4);};

tryCatch: T_TRY statementsListBeginEnd catchList { $$ = IAS_DFT_FACTORY<Stmt::TryCatchNode>::Create($2,$3);  }
catchList: catchList catch              { $$ = $1; $$->addCatchNode($2);           }
		   | catch                      { $$ = IAS_DFT_FACTORY<Stmt::CatchListNode>::Create(); $$->addCatchNode($1); }
		    
catch : T_CATCH T_OPEN_PAR declaration T_CLOSE_PAR statementsListBeginEnd
			{ $$ = IAS_DFT_FACTORY<Stmt::CatchNode>::Create($3,$5); }

exprListPar : T_OPEN_PAR T_CLOSE_PAR { $$ = IAS_DFT_FACTORY<Expr::ExprListNode>::Create(); }
	       | T_OPEN_PAR exprList T_CLOSE_PAR{ $$=$2; } 
	       
exprList : exprList T_COMMA expr  { $$=$1; $$->addExprNode($3); };
		| expr    { $$ = IAS_DFT_FACTORY<Expr::ExprListNode>::Create();  $$->addExprNode($1); };

externalParametersPar : T_OPEN_PAR T_CLOSE_PAR { $$ = new StringList;}
		| T_OPEN_PAR externalParameters T_CLOSE_PAR{ $$=$2; }  

externalParameters : externalParameters T_COMMA T_STRING  { $$=$1; $$->push_back(*$3); _SVAL_DELETE($3);};
		| T_STRING    { $$ = new StringList; $$->push_back(*$1); _SVAL_DELETE($1); };

		
qname : T_SYMBOL { $$= IAS_DFT_FACTORY<Dec::QualifiedNameNode>::Create(*$1); _SVAL_DELETE($1); }
qname : qname T_DOUBLECOLON T_SYMBOL { $$=$1; $$->addNextSymbol(*$3); _SVAL_DELETE($3); }

%%


void yy::AutoGenParser::error (const location_type& l,
                               const std::string& m)
{
  myParser.onAutoGenParserError(l, m);
}

