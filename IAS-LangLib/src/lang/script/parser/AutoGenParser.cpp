// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:399

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "AutoGenParser.hpp"

// User implementation prologue.

#line 51 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:407
// Unqualified %code blocks.
#line 63 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:408

#include "Parser.h"
#include "Lexer.h"
#include "yylex_function.h"

using namespace IAS;
using namespace Lang;
using namespace Model;
using namespace Script;
using namespace Parser;


#line 66 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:408


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 152 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:474

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   AutoGenParser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
   AutoGenParser :: AutoGenParser  (::IAS::Lang::Script::Parser::Parser& myParser_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      myParser (myParser_yyarg)
  {}

   AutoGenParser ::~ AutoGenParser  ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
   AutoGenParser ::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
   AutoGenParser ::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
   AutoGenParser ::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
   AutoGenParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
   AutoGenParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
   AutoGenParser ::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
   AutoGenParser ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
   AutoGenParser ::by_type::by_type ()
     : type (empty)
  {}

  inline
   AutoGenParser ::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
   AutoGenParser ::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
   AutoGenParser ::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
   AutoGenParser ::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
   AutoGenParser ::by_state::by_state ()
    : state (empty)
  {}

  inline
   AutoGenParser ::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
   AutoGenParser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
   AutoGenParser ::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
   AutoGenParser ::symbol_number_type
   AutoGenParser ::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
   AutoGenParser ::stack_symbol_type::stack_symbol_type ()
  {}


  inline
   AutoGenParser ::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
   AutoGenParser ::stack_symbol_type&
   AutoGenParser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
   AutoGenParser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 69: // T_SYMBOL

#line 224 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:599
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 371 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:599
        break;

      case 70: // T_STRING

#line 224 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:599
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 378 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:599
        break;

      case 71: // T_INTEGER

#line 224 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:599
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 385 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:599
        break;

      case 72: // T_FLOAT

#line 224 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:599
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 392 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:599
        break;

      case 73: // T_BOOLEAN

#line 224 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:599
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 399 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:599
        break;

      case 74: // T_NULL

#line 224 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:599
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 406 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:599
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
   AutoGenParser ::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
   AutoGenParser ::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
   AutoGenParser ::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
   AutoGenParser ::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   AutoGenParser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   AutoGenParser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   AutoGenParser ::debug_level_type
   AutoGenParser ::debug_level () const
  {
    return yydebug_;
  }

  void
   AutoGenParser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline  AutoGenParser ::state_type
   AutoGenParser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
   AutoGenParser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
   AutoGenParser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   AutoGenParser ::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 24 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:725
{
  // Initialize the initial location.
  yyla.location.begin.filename = yyla.location.end.filename = new std::string("waisted");
}

#line 543 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:725

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, myParser));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 5:
#line 232 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { myParser.addTypeDefinition((yystack_[0].value.pTypeDefinitionNode)); }
#line 657 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 6:
#line 233 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    {
    (yystack_[0].value.pProgramNode)->setSourceLocation(myParser.getLexer()->getCachedLocation()); 
	myParser.addProgram((yystack_[0].value.pProgramNode)); 
}
#line 666 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 7:
#line 239 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    {  myParser.open((yystack_[1].value.pQualifiedNameNode)->getQualifiedName()); 
           	 IAS_DFT_FACTORY<Dec::QualifiedNameNode>::Free((yystack_[1].value.pQualifiedNameNode)); 
           	 }
#line 674 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 8:
#line 244 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode);
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[5].value.sval)); _SVAL_DELETE((yystack_[5].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[3].value.sval)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 682 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 9:
#line 249 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode);
				  (yylhs.value.pTypeDefinitionNode)->setBaseTypeNode((yystack_[2].value.pTypeInfo));
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[8].value.sval)); _SVAL_DELETE((yystack_[8].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[6].value.sval)); _SVAL_DELETE((yystack_[6].value.sval)); }
#line 691 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 10:
#line 255 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create(); 				  
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[3].value.sval)); _SVAL_DELETE((yystack_[3].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[1].value.sval)); _SVAL_DELETE((yystack_[1].value.sval)); }
#line 699 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 11:
#line 260 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create(); 
				  (yylhs.value.pTypeDefinitionNode)->setBaseTypeNode((yystack_[1].value.pTypeInfo));
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[7].value.sval)); _SVAL_DELETE((yystack_[7].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[5].value.sval)); _SVAL_DELETE((yystack_[5].value.sval)); }
#line 708 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 12:
#line 267 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeInfo) = IAS_DFT_FACTORY<Dec::TypeInfoNode>::Create(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 714 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 13:
#line 270 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeInfo) = IAS_DFT_FACTORY<Dec::TypeInfoNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval));  _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 720 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 14:
#line 272 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode); }
#line 726 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 15:
#line 273 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create();  }
#line 732 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 16:
#line 275 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[2].value.pTypeDefinitionNode); (yylhs.value.pTypeDefinitionNode)->addDeclaration((yystack_[1].value.pDeclarationNode)); }
#line 738 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 17:
#line 276 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create();}
#line 744 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 18:
#line 278 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 750 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 19:
#line 279 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); 
												                _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 757 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 20:
#line 281 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[0].value.sval)); 
												 (yylhs.value.pDeclarationNode)->setIsArray(true); 
												 _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 765 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 21:
#line 284 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[6].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); 
																  (yylhs.value.pDeclarationNode)->setIsArray(true); 
												                  _SVAL_DELETE((yystack_[6].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 773 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 22:
#line 290 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<StandardProgramNode>::Create((yystack_[3].value.pQualifiedNameNode),(yystack_[1].value.pStatementsListNode),(yystack_[2].value.pParametersNode)); }
#line 779 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 23:
#line 293 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<StandardProgramNode>::Create((yystack_[4].value.pQualifiedNameNode),(yystack_[1].value.pStatementsListNode),(yystack_[3].value.pParametersNode),(yystack_[2].value.pDeclarationNode)); }
#line 785 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 24:
#line 296 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<ExternalProgramNode>::Create((yystack_[5].value.pQualifiedNameNode),*(yystack_[2].value.sval),(yystack_[4].value.pParametersNode),*(yystack_[1].value.pStringList)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[1].value.pStringList));}
#line 791 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 25:
#line 299 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<ExternalProgramNode>::Create((yystack_[6].value.pQualifiedNameNode),*(yystack_[2].value.sval),(yystack_[5].value.pParametersNode),(yystack_[4].value.pDeclarationNode),*(yystack_[1].value.pStringList)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[1].value.pStringList));}
#line 797 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 26:
#line 301 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 803 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 27:
#line 302 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 809 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 28:
#line 303 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[0].value.sval));  (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 815 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 29:
#line 304 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval));  (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 821 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 30:
#line 306 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pParametersNode) = (yystack_[1].value.pParametersNode); }
#line 827 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 31:
#line 307 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pParametersNode) = IAS_DFT_FACTORY<Dec::ParametersNode>::Create();  }
#line 833 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 32:
#line 309 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pParametersNode) = (yystack_[2].value.pParametersNode); (yylhs.value.pParametersNode)->addDeclaration((yystack_[0].value.pDeclarationNode)); }
#line 839 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 33:
#line 310 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pParametersNode) = IAS_DFT_FACTORY<Dec::ParametersNode>::Create(); (yylhs.value.pParametersNode)->addDeclaration((yystack_[0].value.pDeclarationNode)); }
#line 845 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 34:
#line 312 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementsListNode) = (yystack_[1].value.pStatementsListNode); }
#line 851 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 35:
#line 314 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { 
(yylhs.value.pStatementsListNode) = (yystack_[2].value.pStatementsListNode); 
(yystack_[1].value.pStatementNode)->setSourceLocation(myParser.getLexer()->getCachedLocation());
(yylhs.value.pStatementsListNode)->addStatement((yystack_[1].value.pStatementNode));
 }
#line 861 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 36:
#line 319 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementsListNode) = (yystack_[2].value.pStatementsListNode); (yylhs.value.pStatementsListNode)->addDeclaration((yystack_[1].value.pDeclarationNode)); }
#line 867 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 37:
#line 320 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementsListNode) = IAS_DFT_FACTORY<Stmt::StatementsListNode>::Create(); }
#line 873 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 38:
#line 322 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 879 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 39:
#line 323 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 885 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 40:
#line 325 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[0].value.sval));     (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[4].value.sval));  _SVAL_DELETE((yystack_[0].value.sval)); }
#line 891 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 41:
#line 327 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[6].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[6].value.sval));  _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 897 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 42:
#line 330 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementsListNode); }
#line 903 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 43:
#line 331 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 909 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 44:
#line 332 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 915 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 45:
#line 333 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 921 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 46:
#line 334 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 927 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 47:
#line 335 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 933 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 48:
#line 336 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 939 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 49:
#line 337 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 945 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 50:
#line 338 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 951 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 51:
#line 339 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 957 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 52:
#line 340 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 963 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 53:
#line 341 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 969 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 54:
#line 342 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 975 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 55:
#line 343 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 981 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 56:
#line 345 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::AssignmentNode>::Create((yystack_[2].value.pLeftSideNode),(yystack_[0].value.pExprNode)); }
#line 987 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 57:
#line 346 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::MergeNode>::Create((yystack_[2].value.pLeftSideNode),(yystack_[0].value.pExprNode)); }
#line 993 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 58:
#line 348 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLeftSideNode) = IAS_DFT_FACTORY<Stmt::LeftSideNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 999 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 59:
#line 355 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1005 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 60:
#line 356 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::AdditionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1011 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 61:
#line 357 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::SubtractionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1017 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 62:
#line 359 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1023 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 63:
#line 360 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::MultiplyNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1029 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 64:
#line 361 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::DivisionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1035 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 65:
#line 362 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ModuloNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1041 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 66:
#line 364 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1047 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 67:
#line 366 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1053 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 68:
#line 367 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::XPath::XPathExprNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1059 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 69:
#line 369 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = (yystack_[1].value.pExprNode); }
#line 1065 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 70:
#line 370 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_INTEGER,*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1071 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 71:
#line 371 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_FLOAT,*(yystack_[0].value.sval));   _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1077 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 72:
#line 372 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_STRING,*(yystack_[0].value.sval));  _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1083 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 73:
#line 373 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_BOOLEAN,*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1089 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 74:
#line 374 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_NULL,*(yystack_[0].value.sval));    _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1095 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 75:
#line 376 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstructorNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1101 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 76:
#line 378 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstructorNode>::Create(*(yystack_[3].value.sval),*(yystack_[1].value.sval), (yystack_[0].value.pStatementsListNode)); _SVAL_DELETE((yystack_[3].value.sval)); _SVAL_DELETE((yystack_[1].value.sval)); }
#line 1107 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 77:
#line 381 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::CastNode>::Create((yystack_[3].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1113 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 78:
#line 383 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::FunCallNode>::Create((yystack_[1].value.pQualifiedNameNode), (yystack_[0].value.pExprListNode)); }
#line 1119 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 79:
#line 384 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::CopyOfNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1125 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 80:
#line 385 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::DetachNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1131 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 81:
#line 386 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::NegativeNode>::Create((yystack_[0].value.pExprNode)); }
#line 1137 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 82:
#line 387 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::SizeOfNode>::Create((yystack_[1].value.pXPathAccessNode));}
#line 1143 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 83:
#line 388 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::GetTypeNode>::Create((yystack_[1].value.pExprNode));}
#line 1149 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 84:
#line 389 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::GetTypeNSNode>::Create((yystack_[1].value.pExprNode));}
#line 1155 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 85:
#line 390 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::StrLenNode>::Create((yystack_[1].value.pExprNode));}
#line 1161 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 86:
#line 392 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1167 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 87:
#line 394 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalDiffNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1173 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 88:
#line 395 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqGtNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1179 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 89:
#line 396 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqLessNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1185 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 90:
#line 397 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalGtNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1191 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 91:
#line 398 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalLessNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1197 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 92:
#line 401 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalIsTypeNode>::Create((yystack_[4].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1203 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 93:
#line 404 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalIsInstanceNode>::Create((yystack_[4].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1209 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 94:
#line 406 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1215 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 95:
#line 407 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = (yystack_[1].value.pLogicalExprNode); }
#line 1221 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 96:
#line 408 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalNotNode>::Create((yystack_[0].value.pLogicalExprNode)); }
#line 1227 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 97:
#line 409 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::IsSetNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1233 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 98:
#line 410 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::IsNullNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1239 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 99:
#line 412 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1245 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 100:
#line 413 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalAndNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pLogicalExprNode)); }
#line 1251 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 101:
#line 415 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1257 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 102:
#line 416 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalOrNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pLogicalExprNode)); }
#line 1263 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 103:
#line 418 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1269 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 104:
#line 421 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pXPathAccessNode) = IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::Create(
								IAS_DFT_FACTORY<Expr::XPath::XPathVariableAccessNode>::Create(
										(*((yystack_[0].value.pXPathNode)->getElements().begin()))->getName()),(yystack_[0].value.pXPathNode));}
#line 1277 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 105:
#line 425 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pXPathAccessNode) = IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::Create(
						IAS_DFT_FACTORY<Expr::XPath::XPathExprAccessNode>::Create((yystack_[2].value.pExprNode)),(yystack_[0].value.pXPathNode)); }
#line 1284 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 106:
#line 428 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pXPathNode) = (yystack_[2].value.pXPathNode); (yylhs.value.pXPathNode)->addSingleElement(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1290 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 107:
#line 430 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pXPathNode) = (yystack_[5].value.pXPathNode); (yylhs.value.pXPathNode)->addMultiElement(*(yystack_[3].value.sval),(yystack_[1].value.pExprNode)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 1296 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 108:
#line 432 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pXPathNode) = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); (yylhs.value.pXPathNode)->addSingleElement(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1302 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 109:
#line 434 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pXPathNode) = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); (yylhs.value.pXPathNode)->addMultiElement(*(yystack_[3].value.sval),(yystack_[1].value.pExprNode)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 1308 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 110:
#line 437 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WithNode>::Create("",(yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pStatementNode)); }
#line 1314 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 111:
#line 438 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WithNode>::Create(*(yystack_[4].value.sval),(yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pStatementNode)); _SVAL_DELETE((yystack_[4].value.sval)); }
#line 1320 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 112:
#line 440 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WhileLoopNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pStatementNode)); }
#line 1326 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 113:
#line 443 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ForLoopNode>::Create((yystack_[6].value.pXPathAccessNode),(yystack_[0].value.pStatementNode),(yystack_[4].value.pExprNode),(yystack_[2].value.pExprNode)); }
#line 1332 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 114:
#line 446 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ForLoopNode>::Create((yystack_[8].value.pXPathAccessNode),(yystack_[0].value.pStatementNode),(yystack_[6].value.pExprNode),(yystack_[4].value.pExprNode),(yystack_[2].value.pExprNode)); }
#line 1338 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 115:
#line 448 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::IfThenElseNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pStatementNode)); }
#line 1344 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 116:
#line 451 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::IfThenElseNode>::Create((yystack_[4].value.pLogicalExprNode),(yystack_[2].value.pStatementNode),(yystack_[0].value.pStatementNode)); }
#line 1350 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 117:
#line 453 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CallNode>::Create((yystack_[1].value.pQualifiedNameNode),(yystack_[0].value.pExprListNode)); }
#line 1356 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 118:
#line 455 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CallNode>::Create((yystack_[1].value.pQualifiedNameNode),(yystack_[0].value.pExprListNode)); }
#line 1362 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 119:
#line 456 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::DeleteNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1368 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 120:
#line 458 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ReturnNode>::Create(); }
#line 1374 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 121:
#line 459 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ReturnNode>::Create((yystack_[0].value.pExprNode)); }
#line 1380 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 122:
#line 462 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ThrowNode>::Create((yystack_[0].value.pExprNode)); }
#line 1386 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 123:
#line 464 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::SortNode>::Create((yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pQualifiedNameNode)); }
#line 1392 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 124:
#line 466 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::TryCatchNode>::Create((yystack_[1].value.pStatementsListNode),(yystack_[0].value.pCatchListNode));  }
#line 1398 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 125:
#line 467 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pCatchListNode) = (yystack_[1].value.pCatchListNode); (yylhs.value.pCatchListNode)->addCatchNode((yystack_[0].value.pCatchNode));           }
#line 1404 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 126:
#line 468 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pCatchListNode) = IAS_DFT_FACTORY<Stmt::CatchListNode>::Create(); (yylhs.value.pCatchListNode)->addCatchNode((yystack_[0].value.pCatchNode)); }
#line 1410 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 127:
#line 471 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pCatchNode) = IAS_DFT_FACTORY<Stmt::CatchNode>::Create((yystack_[2].value.pDeclarationNode),(yystack_[0].value.pStatementsListNode)); }
#line 1416 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 128:
#line 473 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprListNode) = IAS_DFT_FACTORY<Expr::ExprListNode>::Create(); }
#line 1422 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 129:
#line 474 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprListNode)=(yystack_[1].value.pExprListNode); }
#line 1428 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 130:
#line 476 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprListNode)=(yystack_[2].value.pExprListNode); (yylhs.value.pExprListNode)->addExprNode((yystack_[0].value.pExprNode)); }
#line 1434 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 131:
#line 477 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprListNode) = IAS_DFT_FACTORY<Expr::ExprListNode>::Create();  (yylhs.value.pExprListNode)->addExprNode((yystack_[0].value.pExprNode)); }
#line 1440 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 132:
#line 479 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStringList) = new StringList; }
#line 1446 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 133:
#line 480 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStringList)=(yystack_[1].value.pStringList); }
#line 1452 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 134:
#line 482 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStringList)=(yystack_[2].value.pStringList); (yylhs.value.pStringList)->push_back(*(yystack_[0].value.sval)); }
#line 1458 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 135:
#line 483 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStringList) = new StringList;  (yylhs.value.pStringList)->push_back(*(yystack_[0].value.sval)); }
#line 1464 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 136:
#line 486 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pQualifiedNameNode)= IAS_DFT_FACTORY<Dec::QualifiedNameNode>::Create(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1470 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 137:
#line 487 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pQualifiedNameNode)=(yystack_[2].value.pQualifiedNameNode); (yylhs.value.pQualifiedNameNode)->addNextSymbol(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1476 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;


#line 1480 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
   AutoGenParser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
   AutoGenParser ::yysyntax_error_ (state_type yystate, symbol_number_type yytoken) const
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short int  AutoGenParser ::yypact_ninf_ = -176;

  const short int  AutoGenParser ::yytable_ninf_ = -137;

  const short int
   AutoGenParser ::yypact_[] =
  {
    -176,   136,  -176,   -54,   -54,   -42,  -176,  -176,  -176,  -176,
    -176,    92,    13,   -23,    30,  -176,    11,    27,   -39,  -176,
      34,  -176,    55,  -176,  -176,    -9,    38,    22,    74,    12,
      90,  -176,   108,   282,   114,    87,   117,    91,   101,  -176,
      75,  -176,    -8,  -176,  -176,   362,   362,     6,     6,   362,
     362,   161,   402,   362,   105,   135,   141,   142,   362,   -54,
     148,   149,   150,   442,    35,  -176,  -176,  -176,  -176,  -176,
    -176,   132,   133,  -176,  -176,    -5,   137,  -176,   138,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
      48,   131,   134,   -12,   145,   117,  -176,   195,   175,   153,
     185,   158,   204,    48,   151,     6,     6,   183,   192,    67,
      36,    72,  -176,   137,  -176,  -176,   188,   196,   210,  -176,
     211,  -176,  -176,   205,    47,   215,   198,   208,   178,   362,
     362,   362,  -176,    48,   362,   362,   362,  -176,   362,  -176,
    -176,   362,   362,   168,   169,   152,   179,   182,  -176,  -176,
    -176,    56,  -176,   180,  -176,    -4,   174,  -176,   176,   177,
     -54,  -176,   362,  -176,    57,   212,   362,   362,   214,   217,
     362,   362,   362,   362,   362,   362,   362,   362,   362,   362,
     362,     6,     6,   322,   322,   219,   205,  -176,   362,   322,
    -176,   174,   186,   221,   222,   223,  -176,   224,   225,   226,
     199,  -176,  -176,   213,   138,   216,  -176,  -176,    59,   197,
    -176,   206,  -176,  -176,   228,   218,   207,     5,   220,  -176,
     187,   254,  -176,   238,   239,   174,   174,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,   256,   108,  -176,   263,  -176,   246,   161,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,   362,  -176,   362,  -176,  -176,
      -7,  -176,   230,  -176,   234,   232,   362,  -176,  -176,   247,
     248,   322,   249,   322,  -176,  -176,   235,  -176,   259,   233,
    -176,  -176,  -176,   140,  -176,  -176,  -176,   161,  -176,  -176,
     229,   237,   362,   322,  -176,   251,  -176,   292,  -176,   241,
     322,  -176,  -176
  };

  const unsigned char
   AutoGenParser ::yydefact_[] =
  {
       2,     0,     1,     0,     0,     0,     3,     4,     5,     6,
     136,     0,     0,     0,     0,     7,     0,     0,     0,   137,
       0,    31,     0,    33,    37,     0,     0,     0,     0,     0,
       0,    30,     0,     0,     0,    26,     0,     0,     0,    22,
       0,    10,     0,    32,    34,     0,     0,     0,     0,   120,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   108,    72,    70,    71,    73,    74,
      42,     0,     0,    43,    44,     0,     0,    58,   104,    47,
      46,    45,    48,    49,    50,    51,    52,    54,    53,    55,
       0,     0,     0,     0,     0,     0,    23,    17,     0,     0,
       0,    38,     0,     0,     0,     0,     0,     0,     0,     0,
      59,    62,    66,    67,    94,    99,   101,   103,     0,    68,
       0,   121,   122,     0,   108,     0,     0,    66,     0,     0,
       0,     0,   119,     0,     0,     0,     0,    81,     0,    36,
      35,     0,     0,     0,     0,     0,   117,    28,    27,   132,
     135,     0,    24,     0,    15,     0,     0,     8,     0,     0,
       0,    78,     0,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   124,   126,     0,     0,
      69,     0,     0,     0,     0,     0,   118,     0,     0,     0,
       0,    57,    56,   108,   105,   106,   128,   131,     0,     0,
     133,     0,    25,    14,     0,     0,    12,     0,    40,    39,
     123,     0,    95,     0,     0,     0,     0,    86,    90,    88,
      91,    89,    87,    60,    61,    63,    64,    65,   100,   102,
     112,   115,     0,   125,     0,   110,     0,    75,    82,    79,
      80,    83,    84,    85,   109,     0,   129,     0,    29,   134,
       0,    16,     0,    11,     0,     0,     0,    97,    98,     0,
       0,     0,     0,     0,    77,    76,     0,   130,     0,    18,
      13,     9,    41,     0,    92,    93,   116,     0,   111,   107,
       0,     0,     0,     0,   127,    20,    19,     0,   113,     0,
       0,    21,   114
  };

  const short int
   AutoGenParser ::yypgoto_[] =
  {
    -176,  -176,  -176,  -176,  -176,  -172,    95,  -176,  -176,  -176,
    -176,  -176,  -176,   -15,  -176,   -27,  -175,  -176,  -176,  -176,
      37,   -11,   -30,   -35,   -29,  -176,   209,   146,   155,   -38,
     -20,   172,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,   130,   -66,  -176,   243,  -176,    -3
  };

  const short int
   AutoGenParser ::yydefgoto_[] =
  {
      -1,     1,     6,     7,     8,   217,    99,   155,   215,     9,
      27,    17,    22,    70,    33,    23,    72,    73,    74,    75,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   186,   187,   146,   208,    94,   151,   103
  };

  const short int
   AutoGenParser ::yytable_[] =
  {
      11,    12,    28,   213,    76,    43,    71,   141,   240,   241,
     120,    97,    38,    77,   245,    10,    76,    76,   127,   246,
      34,   100,   278,    76,   149,   102,   104,    13,    24,    76,
      90,    29,   125,    24,   137,    18,   123,   161,   132,    40,
     105,   106,    20,    54,    55,    56,    57,    21,    16,    60,
      61,   107,   108,   269,   270,    62,   133,    25,   150,    63,
      35,   101,   279,   142,    37,   214,   263,   196,   165,    26,
    -136,   127,    14,    41,   188,    64,    65,    66,    67,    68,
      69,    97,  -136,   145,    98,   138,   121,   122,   176,   177,
     126,    31,   210,   190,  -136,   256,   286,   138,   288,    19,
      76,    76,    76,    30,   168,   169,  -136,    14,    36,   193,
     194,   195,    32,   211,   168,   169,   257,    42,   298,   170,
     171,   172,   173,   174,   175,   302,   178,   179,   180,   170,
     171,   172,   173,   174,   175,    39,     2,    76,    76,    20,
       3,     4,    91,   164,     5,    92,   223,   224,   235,   236,
     237,    14,    93,    15,    76,    76,   292,   220,   293,    76,
      76,    95,    96,    77,    77,   233,   234,    24,   244,    77,
     129,   197,   198,   199,   128,   200,   130,   131,   201,   202,
      90,    90,   207,   134,   135,   136,    90,    53,   206,    54,
      55,    56,    57,   139,   140,    60,    61,   143,   144,   221,
     147,    62,   154,   156,   148,    63,   152,   227,   228,   229,
     230,   231,   232,   158,   157,   272,   159,   160,   166,   162,
     181,    64,    65,    66,    67,    68,    69,   167,   183,   182,
     185,   184,   275,   189,   190,   191,   192,   203,   205,   -78,
     209,   212,    76,   216,    76,   218,    14,   219,   222,   225,
     254,    77,   226,    77,   242,   260,   247,   248,   249,   250,
     251,   252,   253,   138,    76,   262,   255,   258,    90,   266,
      90,    76,   294,    77,   267,   268,   259,   271,   265,   261,
      77,   273,   274,   284,   285,   287,   289,   290,    24,    44,
      90,   291,   276,    45,   277,   281,    46,    90,   295,    47,
     280,    48,   282,   283,    49,    50,    51,   296,    52,   299,
     300,   301,   264,    20,   163,   204,   243,    53,     0,    54,
      55,    56,    57,    58,    59,    60,    61,   238,    24,   297,
       0,    62,     0,    45,     0,    63,    46,   239,   153,    47,
       0,    48,     0,     0,    49,    50,    51,     0,    52,     0,
       0,    64,    65,    66,    67,    68,    69,    53,     0,    54,
      55,    56,    57,    58,    59,    60,    61,     0,     0,     0,
       0,    62,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,    65,    66,    67,    68,    69,    53,     0,    54,
      55,    56,    57,     0,     0,    60,    61,     0,     0,     0,
       0,    62,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,    65,    66,    67,    68,    69,    53,     0,    54,
      55,    56,    57,     0,     0,    60,    61,     0,     0,     0,
       0,    62,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   124,    65,    66,    67,    68,    69,    53,     0,    54,
      55,    56,    57,     0,     0,    60,    61,     0,     0,     0,
       0,    62,     0,     0,     0,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    10,    65,    66,    67,    68,    69
  };

  const short int
   AutoGenParser ::yycheck_[] =
  {
       3,     4,    17,     7,    33,    32,    33,    12,   183,   184,
      48,     6,    27,    33,   189,    69,    45,    46,    53,   191,
      29,    29,    29,    52,    36,    45,    46,    69,     6,    58,
      33,    70,    52,     6,    63,    58,    51,   103,    58,    27,
      34,    35,    31,    37,    38,    39,    40,    36,    35,    43,
      44,    45,    46,   225,   226,    49,    59,    30,    70,    53,
      69,    69,    69,    68,    42,    69,    61,   133,   106,    42,
      35,   106,    59,    61,    27,    69,    70,    71,    72,    73,
      74,     6,    35,    35,     9,    50,    49,    50,    52,    53,
      53,    36,    36,    36,    59,    36,   271,    50,   273,    69,
     129,   130,   131,    69,    47,    48,    59,    59,    70,   129,
     130,   131,    57,    57,    47,    48,    57,    27,   293,    62,
      63,    64,    65,    66,    67,   300,    54,    55,    56,    62,
      63,    64,    65,    66,    67,    61,     0,   166,   167,    31,
       4,     5,    28,   106,     8,    58,   166,   167,   178,   179,
     180,    59,    35,    61,   183,   184,    16,   160,    18,   188,
     189,    70,    61,   183,   184,   176,   177,     6,   188,   189,
      35,   134,   135,   136,    69,   138,    35,    35,   141,   142,
     183,   184,   145,    35,    35,    35,   189,    35,    36,    37,
      38,    39,    40,    61,    61,    43,    44,    60,    60,   162,
      69,    49,     7,    28,    70,    53,    61,   170,   171,   172,
     173,   174,   175,    28,    61,   242,    58,    13,    35,    68,
      32,    69,    70,    71,    72,    73,    74,    35,    18,    33,
      25,    20,   247,    18,    36,    27,    58,    69,    69,    60,
      58,    61,   271,    69,   273,    69,    59,    70,    36,    35,
      51,   271,    35,   273,    35,    27,    70,    36,    36,    36,
      36,    36,    36,    50,   293,    58,    50,    70,   271,    15,
     273,   300,   287,   293,    36,    36,    70,    21,    58,    61,
     300,    18,    36,    36,    36,    36,    51,    28,     6,     7,
     293,    58,   255,    11,   257,    61,    14,   300,    69,    17,
      70,    19,    70,   266,    22,    23,    24,    70,    26,    58,
      18,    70,   217,    31,   105,   143,   186,    35,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,   181,     6,   292,
      -1,    49,    -1,    11,    -1,    53,    14,   182,    95,    17,
      -1,    19,    -1,    -1,    22,    23,    24,    -1,    26,    -1,
      -1,    69,    70,    71,    72,    73,    74,    35,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    70,    71,    72,    73,    74,    35,    -1,    37,
      38,    39,    40,    -1,    -1,    43,    44,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    70,    71,    72,    73,    74,    35,    -1,    37,
      38,    39,    40,    -1,    -1,    43,    44,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    70,    71,    72,    73,    74,    35,    -1,    37,
      38,    39,    40,    -1,    -1,    43,    44,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    70,    71,    72,    73,    74
  };

  const unsigned char
   AutoGenParser ::yystos_[] =
  {
       0,    76,     0,     4,     5,     8,    77,    78,    79,    84,
      69,   124,   124,    69,    59,    61,    35,    86,    58,    69,
      31,    36,    87,    90,     6,    30,    42,    85,    88,    70,
      69,    36,    57,    89,    29,    69,    70,    42,    88,    61,
      27,    61,    27,    90,     7,    11,    14,    17,    19,    22,
      23,    24,    26,    35,    37,    38,    39,    40,    41,    42,
      43,    44,    49,    53,    69,    70,    71,    72,    73,    74,
      88,    90,    91,    92,    93,    94,    99,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     124,    28,    58,    35,   122,    70,    61,     6,     9,    81,
      29,    69,   105,   124,   105,    34,    35,    45,    46,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     104,    95,    95,    88,    69,   105,    95,    98,    69,    35,
      35,    35,   105,   124,    35,    35,    35,    99,    50,    61,
      61,    12,    68,    60,    60,    35,   120,    69,    70,    36,
      70,   123,    61,   122,     7,    82,    28,    61,    28,    58,
      13,   120,    68,   101,    95,   104,    35,    35,    47,    48,
      62,    63,    64,    65,    66,    67,    52,    53,    54,    55,
      56,    32,    33,    18,    20,    25,   118,   119,    27,    18,
      36,    27,    58,   105,   105,   105,   120,    95,    95,    95,
      95,    95,    95,    69,   106,    69,    36,    95,   121,    58,
      36,    57,    61,     7,    69,    83,    69,    80,    69,    70,
     124,    95,    36,   105,   105,    35,    35,    95,    95,    95,
      95,    95,    95,    96,    96,    97,    97,    97,   102,   103,
      91,    91,    35,   119,   105,    91,    80,    70,    36,    36,
      36,    36,    36,    36,    51,    50,    36,    57,    70,    70,
      27,    61,    58,    61,    81,    58,    15,    36,    36,    80,
      80,    21,    90,    18,    36,    88,    95,    95,    29,    69,
      70,    61,    70,    95,    36,    36,    91,    36,    91,    51,
      28,    58,    16,    18,    88,    69,    70,    95,    91,    58,
      18,    70,    91
  };

  const unsigned char
   AutoGenParser ::yyr1_[] =
  {
       0,    75,    76,    76,    77,    77,    77,    78,    79,    79,
      79,    79,    80,    80,    81,    81,    82,    82,    83,    83,
      83,    83,    84,    84,    84,    84,    85,    85,    85,    85,
      86,    86,    87,    87,    88,    89,    89,    89,    90,    90,
      90,    90,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    92,    93,    94,    95,
      96,    96,    96,    97,    97,    97,    97,    98,    98,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,   100,   100,   100,   100,
     100,   100,   100,   100,   101,   101,   101,   101,   101,   102,
     102,   103,   103,   104,   105,   105,   106,   106,   106,   106,
     107,   107,   108,   109,   109,   110,   110,   111,   112,   113,
     114,   114,   115,   116,   117,   118,   118,   119,   120,   120,
     121,   121,   122,   122,   123,   123,   124,   124
  };

  const unsigned char
   AutoGenParser ::yyr2_[] =
  {
       0,     2,     0,     2,     1,     1,     1,     3,     7,    10,
       5,     9,     1,     3,     3,     2,     3,     0,     3,     5,
       5,     7,     5,     6,     7,     8,     2,     4,     4,     6,
       3,     2,     3,     1,     3,     3,     3,     0,     4,     6,
       6,     8,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     1,     1,
       3,     3,     1,     3,     3,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     4,     5,     5,     2,     4,
       4,     2,     4,     4,     4,     4,     3,     3,     3,     3,
       3,     3,     5,     5,     1,     3,     2,     4,     4,     1,
       3,     1,     3,     1,     1,     3,     3,     6,     1,     4,
       4,     6,     4,     8,    10,     4,     6,     2,     3,     2,
       1,     2,     2,     4,     3,     2,     1,     5,     2,     3,
       3,     1,     2,     3,     3,     1,     1,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  AutoGenParser ::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "T_NONE", "\"IMPORT\"",
  "\"PROGRAM\"", "\"BEGIN\"", "\"END\"", "\"DEFINE\"", "\"EXTENSION\"",
  "\"CALL\"", "\"SORT\"", "\"MERGE\"", "\"USING\"", "\"FOR\"", "\"TO\"",
  "\"STEP\"", "\"WHILE\"", "\"DO\"", "\"IF\"", "\"THEN\"", "\"ELSE\"",
  "\"RETURN\"", "\"THROW\"", "\"TRY\"", "\"CATCH\"", "\"WITH\"", "\"AS\"",
  "\"OF\"", "\"ARRAY\"", "\"RETURNS\"", "\"VAR\"", "\"AND\"", "\"OR\"",
  "\"NOT\"", "\"(\"", "\")\"", "\"NEW\"", "\"SIZEOF\"", "\"COPYOF\"",
  "\"DETACH\"", "\"DELETE\"", "\"EXTERNAL\"", "\"TYPE\"", "\"TYPENS\"",
  "\"ISSET\"", "\"ISNULL\"", "\"ISTYPE\"", "\"ISINSTANCE\"", "\"STRLEN\"",
  "\"[\"", "\"]\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"%\"", "\",\"",
  "\":\"", "\"::\"", "\".\"", "\";\"", "\"==\"", "\"<\"", "\"<=\"",
  "\">\"", "\">=\"", "\"<>\"", "\"= (assignment)\"", "T_SYMBOL",
  "T_STRING", "T_INTEGER", "T_FLOAT", "T_BOOLEAN", "T_NULL", "$accept",
  "globals", "global", "import", "typeDefinition", "baseType",
  "typeDefinitionPropertiesEnclosed", "typeDefinitionProperties",
  "property", "program", "programResult", "parametersListPar",
  "parametersList", "statementsListBeginEnd", "statementsList",
  "declaration", "statement", "assignment", "merge", "lvalue", "expr",
  "exprTerm", "exprFactor", "exprPrimaryOrXPath", "exprPrimary",
  "relationalOper", "logicalExprPrimary", "logicalExprFactor",
  "logicalExprTerm", "logicalExpr", "xpathAccess", "xpath", "with",
  "whileLoop", "forLoop", "ifThenElse", "call", "external", "delete",
  "return", "throw", "sort", "tryCatch", "catchList", "catch",
  "exprListPar", "exprList", "externalParametersPar", "externalParameters",
  "qname", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
   AutoGenParser ::yyrline_[] =
  {
       0,   229,   229,   229,   231,   232,   233,   238,   243,   248,
     254,   259,   266,   269,   272,   273,   275,   276,   278,   279,
     281,   284,   289,   292,   295,   298,   301,   302,   303,   304,
     306,   307,   309,   310,   312,   314,   319,   320,   322,   323,
     324,   326,   330,   331,   332,   333,   334,   335,   336,   337,
     338,   339,   340,   341,   342,   343,   345,   346,   348,   355,
     356,   357,   359,   360,   361,   362,   364,   366,   367,   369,
     370,   371,   372,   373,   374,   376,   377,   380,   383,   384,
     385,   386,   387,   388,   389,   390,   392,   394,   395,   396,
     397,   398,   400,   403,   406,   407,   408,   409,   410,   412,
     413,   415,   416,   418,   421,   424,   428,   429,   432,   433,
     437,   438,   440,   442,   445,   448,   450,   453,   455,   456,
     458,   459,   462,   464,   466,   467,   468,   470,   473,   474,
     476,   477,   479,   480,   482,   483,   486,   487
  };

  // Print the state stack on the debug stream.
  void
   AutoGenParser ::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
   AutoGenParser ::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
   AutoGenParser ::token_number_type
   AutoGenParser ::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
    };
    const unsigned int user_token_number_max_ = 329;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 2158 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:1155
#line 489 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:1156



void yy::AutoGenParser::error (const location_type& l,
                               const std::string& m)
{
  myParser.onAutoGenParserError(l, m);
}

