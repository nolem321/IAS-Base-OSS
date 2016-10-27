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
            case 71: // T_SYMBOL

#line 228 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:599
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 371 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:599
        break;

      case 72: // T_STRING

#line 228 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:599
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 378 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:599
        break;

      case 73: // T_INTEGER

#line 228 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:599
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 385 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:599
        break;

      case 74: // T_FLOAT

#line 228 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:599
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 392 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:599
        break;

      case 75: // T_BOOLEAN

#line 228 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:599
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 399 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:599
        break;

      case 76: // T_NULL

#line 228 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:599
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
#line 236 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { myParser.addTypeDefinition((yystack_[0].value.pTypeDefinitionNode)); }
#line 657 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 6:
#line 237 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    {
    (yystack_[0].value.pProgramNode)->setSourceLocation(myParser.getLexer()->getCachedLocation()); 
	myParser.addProgram((yystack_[0].value.pProgramNode)); 
}
#line 666 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 7:
#line 243 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    {  myParser.open((yystack_[1].value.pQualifiedNameNode)->getQualifiedName()); 
           	 IAS_DFT_FACTORY<Dec::QualifiedNameNode>::Free((yystack_[1].value.pQualifiedNameNode)); 
           	 }
#line 674 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 8:
#line 248 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode);
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[5].value.sval)); _SVAL_DELETE((yystack_[5].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[3].value.sval)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 682 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 9:
#line 253 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode);
				  (yylhs.value.pTypeDefinitionNode)->setBaseTypeNode((yystack_[2].value.pTypeInfo));
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[8].value.sval)); _SVAL_DELETE((yystack_[8].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[6].value.sval)); _SVAL_DELETE((yystack_[6].value.sval)); }
#line 691 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 10:
#line 259 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create(); 				  
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[3].value.sval)); _SVAL_DELETE((yystack_[3].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[1].value.sval)); _SVAL_DELETE((yystack_[1].value.sval)); }
#line 699 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 11:
#line 264 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create(); 
				  (yylhs.value.pTypeDefinitionNode)->setBaseTypeNode((yystack_[1].value.pTypeInfo));
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[7].value.sval)); _SVAL_DELETE((yystack_[7].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[5].value.sval)); _SVAL_DELETE((yystack_[5].value.sval)); }
#line 708 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 12:
#line 271 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeInfo) = IAS_DFT_FACTORY<Dec::TypeInfoNode>::Create(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 714 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 13:
#line 274 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeInfo) = IAS_DFT_FACTORY<Dec::TypeInfoNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval));  _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 720 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 14:
#line 276 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode); }
#line 726 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 15:
#line 277 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create();  }
#line 732 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 16:
#line 279 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[2].value.pTypeDefinitionNode); (yylhs.value.pTypeDefinitionNode)->addDeclaration((yystack_[1].value.pDeclarationNode)); }
#line 738 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 17:
#line 280 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create();}
#line 744 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 18:
#line 282 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 750 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 19:
#line 283 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); 
												                _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 757 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 20:
#line 285 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[0].value.sval)); 
												 (yylhs.value.pDeclarationNode)->setIsArray(true); 
												 _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 765 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 21:
#line 288 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[6].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); 
																  (yylhs.value.pDeclarationNode)->setIsArray(true); 
												                  _SVAL_DELETE((yystack_[6].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 773 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 22:
#line 294 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<StandardProgramNode>::Create((yystack_[3].value.pQualifiedNameNode),(yystack_[1].value.pStatementsListNode),(yystack_[2].value.pParametersNode)); }
#line 779 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 23:
#line 297 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<StandardProgramNode>::Create((yystack_[4].value.pQualifiedNameNode),(yystack_[1].value.pStatementsListNode),(yystack_[3].value.pParametersNode),(yystack_[2].value.pDeclarationNode)); }
#line 785 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 24:
#line 300 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<ExternalProgramNode>::Create((yystack_[5].value.pQualifiedNameNode),*(yystack_[2].value.sval),(yystack_[4].value.pParametersNode),*(yystack_[1].value.pStringList)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[1].value.pStringList));}
#line 791 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 25:
#line 303 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<ExternalProgramNode>::Create((yystack_[6].value.pQualifiedNameNode),*(yystack_[2].value.sval),(yystack_[5].value.pParametersNode),(yystack_[4].value.pDeclarationNode),*(yystack_[1].value.pStringList)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[1].value.pStringList));}
#line 797 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 26:
#line 305 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 803 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 27:
#line 306 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 809 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 28:
#line 307 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[0].value.sval));  (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 815 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 29:
#line 308 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval));  (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 821 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 30:
#line 310 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pParametersNode) = (yystack_[1].value.pParametersNode); }
#line 827 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 31:
#line 311 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pParametersNode) = IAS_DFT_FACTORY<Dec::ParametersNode>::Create();  }
#line 833 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 32:
#line 313 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pParametersNode) = (yystack_[2].value.pParametersNode); (yylhs.value.pParametersNode)->addDeclaration((yystack_[0].value.pDeclarationNode)); }
#line 839 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 33:
#line 314 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pParametersNode) = IAS_DFT_FACTORY<Dec::ParametersNode>::Create(); (yylhs.value.pParametersNode)->addDeclaration((yystack_[0].value.pDeclarationNode)); }
#line 845 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 34:
#line 316 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementsListNode) = (yystack_[1].value.pStatementsListNode); }
#line 851 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 35:
#line 318 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { 
(yylhs.value.pStatementsListNode) = (yystack_[2].value.pStatementsListNode); 
(yystack_[1].value.pStatementNode)->setSourceLocation(myParser.getLexer()->getCachedLocation());
(yylhs.value.pStatementsListNode)->addStatement((yystack_[1].value.pStatementNode));
 }
#line 861 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 36:
#line 323 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementsListNode) = (yystack_[2].value.pStatementsListNode); (yylhs.value.pStatementsListNode)->addDeclaration((yystack_[1].value.pDeclarationNode)); }
#line 867 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 37:
#line 324 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementsListNode) = IAS_DFT_FACTORY<Stmt::StatementsListNode>::Create(); }
#line 873 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 38:
#line 326 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 879 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 39:
#line 327 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 885 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 40:
#line 329 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[0].value.sval));     (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[4].value.sval));  _SVAL_DELETE((yystack_[0].value.sval)); }
#line 891 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 41:
#line 331 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[6].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[6].value.sval));  _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 897 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 42:
#line 334 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementsListNode); }
#line 903 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 43:
#line 335 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 909 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 44:
#line 336 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 915 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 45:
#line 337 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 921 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 46:
#line 338 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 927 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 47:
#line 339 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 933 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 48:
#line 340 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 939 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 49:
#line 341 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 945 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 50:
#line 342 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 951 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 51:
#line 343 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 957 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 52:
#line 344 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 963 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 53:
#line 345 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 969 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 54:
#line 346 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 975 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 55:
#line 347 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 981 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 56:
#line 348 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 987 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 57:
#line 349 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 993 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 58:
#line 351 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::AssignmentNode>::Create((yystack_[2].value.pLeftSideNode),(yystack_[0].value.pExprNode)); }
#line 999 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 59:
#line 352 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ConditionalAssignmentNode>::Create((yystack_[2].value.pLeftSideNode),(yystack_[0].value.pXPathAccessNode)); }
#line 1005 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 60:
#line 353 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::MergeNode>::Create((yystack_[2].value.pLeftSideNode),(yystack_[0].value.pExprNode)); }
#line 1011 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 61:
#line 355 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLeftSideNode) = IAS_DFT_FACTORY<Stmt::LeftSideNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1017 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 62:
#line 362 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1023 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 63:
#line 363 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::AdditionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1029 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 64:
#line 364 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::SubtractionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1035 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 65:
#line 366 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1041 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 66:
#line 367 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::MultiplyNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1047 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 67:
#line 368 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::DivisionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1053 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 68:
#line 369 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ModuloNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1059 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 69:
#line 371 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1065 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 70:
#line 373 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1071 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 71:
#line 374 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::XPath::XPathExprNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1077 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 72:
#line 376 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = (yystack_[1].value.pExprNode); }
#line 1083 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 73:
#line 377 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_INTEGER,*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1089 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 74:
#line 378 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_FLOAT,*(yystack_[0].value.sval));   _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1095 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 75:
#line 379 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_STRING,*(yystack_[0].value.sval));  _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1101 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 76:
#line 380 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_BOOLEAN,*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1107 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 77:
#line 381 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_NULL,*(yystack_[0].value.sval));    _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1113 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 78:
#line 383 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstructorNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1119 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 79:
#line 385 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstructorNode>::Create(*(yystack_[3].value.sval),*(yystack_[1].value.sval), (yystack_[0].value.pStatementsListNode)); _SVAL_DELETE((yystack_[3].value.sval)); _SVAL_DELETE((yystack_[1].value.sval)); }
#line 1125 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 80:
#line 388 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::CastNode>::Create((yystack_[3].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1131 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 81:
#line 390 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::FunCallNode>::Create((yystack_[1].value.pQualifiedNameNode), (yystack_[0].value.pExprListNode)); }
#line 1137 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 82:
#line 391 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::CopyOfNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1143 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 83:
#line 392 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::DetachNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1149 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 84:
#line 393 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::NegativeNode>::Create((yystack_[0].value.pExprNode)); }
#line 1155 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 85:
#line 394 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::SizeOfNode>::Create((yystack_[1].value.pXPathAccessNode));}
#line 1161 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 86:
#line 395 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::GetTypeNode>::Create((yystack_[1].value.pExprNode));}
#line 1167 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 87:
#line 396 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::GetTypeNSNode>::Create((yystack_[1].value.pExprNode));}
#line 1173 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 88:
#line 397 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::StrLenNode>::Create((yystack_[1].value.pExprNode));}
#line 1179 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 89:
#line 399 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1185 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 90:
#line 401 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalDiffNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1191 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 91:
#line 402 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqGtNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1197 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 92:
#line 403 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqLessNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1203 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 93:
#line 404 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalGtNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1209 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 94:
#line 405 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalLessNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1215 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 95:
#line 408 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalIsTypeNode>::Create((yystack_[4].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1221 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 96:
#line 411 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalIsInstanceNode>::Create((yystack_[4].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1227 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 97:
#line 413 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1233 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 98:
#line 414 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = (yystack_[1].value.pLogicalExprNode); }
#line 1239 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 99:
#line 415 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalNotNode>::Create((yystack_[0].value.pLogicalExprNode)); }
#line 1245 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 100:
#line 416 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::IsSetNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1251 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 101:
#line 417 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::IsNullNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1257 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 102:
#line 419 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1263 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 103:
#line 420 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalAndNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pLogicalExprNode)); }
#line 1269 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 104:
#line 422 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1275 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 105:
#line 423 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalOrNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pLogicalExprNode)); }
#line 1281 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 106:
#line 425 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1287 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 107:
#line 428 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pXPathAccessNode) = IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::Create(
								IAS_DFT_FACTORY<Expr::XPath::XPathVariableAccessNode>::Create(
										(*((yystack_[0].value.pXPathNode)->getElements().begin()))->getName()),(yystack_[0].value.pXPathNode));}
#line 1295 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 108:
#line 432 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pXPathAccessNode) = IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::Create(
						IAS_DFT_FACTORY<Expr::XPath::XPathExprAccessNode>::Create((yystack_[2].value.pExprNode)),(yystack_[0].value.pXPathNode)); }
#line 1302 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 109:
#line 435 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pXPathNode) = (yystack_[2].value.pXPathNode); (yylhs.value.pXPathNode)->addSingleElement(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1308 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 110:
#line 437 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pXPathNode) = (yystack_[5].value.pXPathNode); (yylhs.value.pXPathNode)->addMultiElement(*(yystack_[3].value.sval),(yystack_[1].value.pExprNode)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 1314 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 111:
#line 439 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pXPathNode) = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); (yylhs.value.pXPathNode)->addSingleElement(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1320 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 112:
#line 441 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pXPathNode) = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); (yylhs.value.pXPathNode)->addMultiElement(*(yystack_[3].value.sval),(yystack_[1].value.pExprNode)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 1326 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 113:
#line 444 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WithNode>::Create("",(yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pStatementNode)); }
#line 1332 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 114:
#line 445 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WithNode>::Create(*(yystack_[4].value.sval),(yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pStatementNode)); _SVAL_DELETE((yystack_[4].value.sval)); }
#line 1338 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 115:
#line 447 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WhileLoopNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pStatementNode)); }
#line 1344 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 116:
#line 450 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ForLoopNode>::Create((yystack_[6].value.pXPathAccessNode),(yystack_[0].value.pStatementNode),(yystack_[4].value.pExprNode),(yystack_[2].value.pExprNode)); }
#line 1350 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 117:
#line 453 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ForLoopNode>::Create((yystack_[8].value.pXPathAccessNode),(yystack_[0].value.pStatementNode),(yystack_[6].value.pExprNode),(yystack_[4].value.pExprNode),(yystack_[2].value.pExprNode)); }
#line 1356 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 118:
#line 455 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::IfThenElseNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pStatementNode)); }
#line 1362 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 119:
#line 458 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::IfThenElseNode>::Create((yystack_[4].value.pLogicalExprNode),(yystack_[2].value.pStatementNode),(yystack_[0].value.pStatementNode)); }
#line 1368 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 120:
#line 460 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CallNode>::Create((yystack_[1].value.pQualifiedNameNode),(yystack_[0].value.pExprListNode)); }
#line 1374 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 121:
#line 462 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CallNode>::Create((yystack_[1].value.pQualifiedNameNode),(yystack_[0].value.pExprListNode)); }
#line 1380 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 122:
#line 463 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CreateNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1386 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 123:
#line 464 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CreateNode>::Create((yystack_[1].value.pXPathAccessNode),(yystack_[0].value.pStatementsListNode)); }
#line 1392 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 124:
#line 465 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::DeleteNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1398 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 125:
#line 467 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ReturnNode>::Create(); }
#line 1404 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 126:
#line 468 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ReturnNode>::Create((yystack_[0].value.pExprNode)); }
#line 1410 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 127:
#line 471 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ThrowNode>::Create((yystack_[0].value.pExprNode)); }
#line 1416 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 128:
#line 473 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::SortNode>::Create((yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pQualifiedNameNode)); }
#line 1422 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 129:
#line 475 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::TryCatchNode>::Create((yystack_[1].value.pStatementsListNode),(yystack_[0].value.pCatchListNode));  }
#line 1428 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 130:
#line 476 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pCatchListNode) = (yystack_[1].value.pCatchListNode); (yylhs.value.pCatchListNode)->addCatchNode((yystack_[0].value.pCatchNode));           }
#line 1434 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 131:
#line 477 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pCatchListNode) = IAS_DFT_FACTORY<Stmt::CatchListNode>::Create(); (yylhs.value.pCatchListNode)->addCatchNode((yystack_[0].value.pCatchNode)); }
#line 1440 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 132:
#line 480 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pCatchNode) = IAS_DFT_FACTORY<Stmt::CatchNode>::Create((yystack_[2].value.pDeclarationNode),(yystack_[0].value.pStatementsListNode)); }
#line 1446 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 133:
#line 482 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprListNode) = IAS_DFT_FACTORY<Expr::ExprListNode>::Create(); }
#line 1452 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 134:
#line 483 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprListNode)=(yystack_[1].value.pExprListNode); }
#line 1458 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 135:
#line 485 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprListNode)=(yystack_[2].value.pExprListNode); (yylhs.value.pExprListNode)->addExprNode((yystack_[0].value.pExprNode)); }
#line 1464 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 136:
#line 486 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pExprListNode) = IAS_DFT_FACTORY<Expr::ExprListNode>::Create();  (yylhs.value.pExprListNode)->addExprNode((yystack_[0].value.pExprNode)); }
#line 1470 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 137:
#line 488 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStringList) = new StringList; }
#line 1476 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 138:
#line 489 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStringList)=(yystack_[1].value.pStringList); }
#line 1482 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 139:
#line 491 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStringList)=(yystack_[2].value.pStringList); (yylhs.value.pStringList)->push_back(*(yystack_[0].value.sval)); }
#line 1488 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 140:
#line 492 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pStringList) = new StringList;  (yylhs.value.pStringList)->push_back(*(yystack_[0].value.sval)); }
#line 1494 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 141:
#line 495 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pQualifiedNameNode)= IAS_DFT_FACTORY<Dec::QualifiedNameNode>::Create(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1500 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;

  case 142:
#line 496 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:847
    { (yylhs.value.pQualifiedNameNode)=(yystack_[2].value.pQualifiedNameNode); (yylhs.value.pQualifiedNameNode)->addNextSymbol(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1506 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
    break;


#line 1510 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:847
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


  const short int  AutoGenParser ::yypact_ninf_ = -166;

  const short int  AutoGenParser ::yytable_ninf_ = -142;

  const short int
   AutoGenParser ::yypact_[] =
  {
    -166,   114,  -166,   -51,   -51,   -34,  -166,  -166,  -166,  -166,
    -166,   -14,    21,   -26,   -28,  -166,    11,    19,     5,  -166,
       9,  -166,    -4,  -166,  -166,   -16,    13,    10,    28,   -12,
      71,  -166,    72,   288,    84,    57,    82,    55,    66,  -166,
      35,  -166,   -11,  -166,  -166,   415,   415,   331,   331,   415,
     415,   130,   457,   415,    70,   102,   110,   111,   415,   415,
     -51,   115,   116,   117,   499,    31,  -166,  -166,  -166,  -166,
    -166,  -166,    81,    87,  -166,  -166,  -166,    -1,    93,  -166,
      94,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,    24,    88,    86,    -5,    98,    82,  -166,
     154,   135,   104,   139,   109,   166,    24,   112,   331,   331,
     145,   147,   224,    53,    32,  -166,    93,  -166,  -166,   151,
     155,   169,  -166,   164,  -166,  -166,   165,    51,   171,   156,
     174,   134,   415,   415,   415,   130,  -166,    24,   415,   415,
     415,  -166,   415,  -166,  -166,   415,   415,   415,   125,   127,
     373,   142,   148,  -166,  -166,  -166,    43,  -166,   144,  -166,
       1,   133,  -166,   138,   140,   -51,  -166,   415,  -166,   108,
     175,   415,   415,   184,   185,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   331,   331,   191,   191,
     186,   165,  -166,   415,   191,  -166,   133,   152,   187,   189,
     201,  -166,  -166,   202,   204,   206,   192,  -166,  -166,  -166,
     195,    94,   196,  -166,  -166,    47,   176,  -166,   177,  -166,
    -166,   216,   188,   193,     8,   198,  -166,   199,   236,  -166,
     219,   222,   133,   133,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,   239,    72,
    -166,   243,  -166,   232,   130,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,   415,  -166,   415,  -166,  -166,   -10,  -166,   197,
    -166,   208,   209,   415,  -166,  -166,   235,   238,   191,   242,
     191,  -166,  -166,   228,  -166,   254,   226,  -166,  -166,  -166,
      79,  -166,  -166,  -166,   130,  -166,  -166,   225,   221,   415,
     191,  -166,   241,  -166,   280,  -166,   229,   191,  -166,  -166
  };

  const unsigned char
   AutoGenParser ::yydefact_[] =
  {
       2,     0,     1,     0,     0,     0,     3,     4,     5,     6,
     141,     0,     0,     0,     0,     7,     0,     0,     0,   142,
       0,    31,     0,    33,    37,     0,     0,     0,     0,     0,
       0,    30,     0,     0,     0,    26,     0,     0,     0,    22,
       0,    10,     0,    32,    34,     0,     0,     0,     0,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   111,    75,    73,    74,    76,
      77,    42,     0,     0,    43,    44,    45,     0,     0,    61,
     107,    48,    47,    46,    49,    50,    51,    52,    53,    54,
      56,    55,    57,     0,     0,     0,     0,     0,     0,    23,
      17,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,    62,    65,    69,    70,    97,   102,   104,
     106,     0,    71,     0,   126,   127,     0,   111,     0,     0,
      69,     0,     0,     0,     0,   122,   124,     0,     0,     0,
       0,    84,     0,    36,    35,     0,     0,     0,     0,     0,
       0,   120,    28,    27,   137,   140,     0,    24,     0,    15,
       0,     0,     8,     0,     0,     0,    81,     0,    99,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   129,   131,     0,     0,    72,     0,     0,     0,     0,
       0,   123,   121,     0,     0,     0,     0,    60,    58,    59,
     111,   108,   109,   133,   136,     0,     0,   138,     0,    25,
      14,     0,     0,    12,     0,    40,    39,   128,     0,    98,
       0,     0,     0,     0,    89,    93,    91,    94,    92,    90,
      63,    64,    66,    67,    68,   103,   105,   115,   118,     0,
     130,     0,   113,     0,    78,    85,    82,    83,    86,    87,
      88,   112,     0,   134,     0,    29,   139,     0,    16,     0,
      11,     0,     0,     0,   100,   101,     0,     0,     0,     0,
       0,    80,    79,     0,   135,     0,    18,    13,     9,    41,
       0,    95,    96,   119,     0,   114,   110,     0,     0,     0,
       0,   132,    20,    19,     0,   116,     0,     0,    21,   117
  };

  const short int
   AutoGenParser ::yypgoto_[] =
  {
    -166,  -166,  -166,  -166,  -166,  -158,    85,  -166,  -166,  -166,
    -166,  -166,  -166,   -15,  -166,   -27,  -165,  -166,  -166,  -166,
    -166,   -46,  -155,   -59,   -36,   -24,  -166,   200,   129,   131,
     -38,     6,   168,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,  -166,  -166,  -166,   126,   -61,  -166,   205,
    -166,    -3
  };

  const short int
   AutoGenParser ::yydefgoto_[] =
  {
      -1,     1,     6,     7,     8,   224,   102,   160,   222,     9,
      27,    17,    22,    71,    33,    23,    73,    74,    75,    76,
      77,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,   191,   192,   151,   215,    97,
     156,   106
  };

  const short int
   AutoGenParser ::yytable_[] =
  {
      11,    12,    28,   124,   125,    43,    72,   129,   220,    78,
     123,   145,    38,    34,   100,    40,    24,   130,   103,   285,
      10,    78,    78,   247,   248,    24,   240,   241,    78,   252,
      93,   154,    31,    18,    78,    78,   126,    13,   253,    79,
     141,   100,    20,    19,   101,   166,    14,    21,    15,    25,
      41,   105,   107,    37,    32,    35,    16,   137,   128,   150,
     104,   286,    26,   169,   135,   136,  -141,   155,   146,   147,
     270,   170,   221,   130,   276,   277,   202,    29,   193,   217,
      30,    14,   142,   263,    14,    36,  -141,   183,   184,   185,
      39,  -141,   203,   204,   205,   299,   206,   300,    42,   207,
     208,   218,   142,    20,   214,   264,   181,   182,    78,    78,
      78,  -141,    94,   293,     2,   295,    95,    96,     3,     4,
     201,   228,     5,    78,   242,   243,   244,    98,    99,   234,
     235,   236,   237,   238,   239,   305,    24,   132,   198,   199,
     200,   131,   309,   143,   195,   133,   134,    78,    78,   144,
     138,   139,   140,   209,   148,   149,   173,   174,   153,   152,
     157,   159,   227,   161,    78,    78,   162,   163,   164,    78,
      78,   175,   176,   177,   178,   179,   180,   230,   231,   165,
     171,   167,   172,   186,   189,    93,    93,   188,   187,   194,
     190,    93,   195,   197,    79,    79,   210,    24,   212,   251,
      79,   196,    45,   -81,   223,    46,   219,   216,    47,   225,
      48,   229,   226,    49,    50,    51,   283,    52,   284,   232,
     233,   249,   279,   255,   254,   256,    53,   290,    54,    55,
      56,    57,    58,    59,    60,    61,    62,   257,   258,   282,
     259,    63,   260,   267,   261,    64,   142,   262,   265,   266,
     268,   273,   269,   304,    78,   274,    78,   272,   275,    14,
     278,   280,    65,    66,    67,    68,    69,    70,   281,   287,
     288,   291,   173,   174,   292,    93,    78,    93,   294,   301,
     296,   289,   297,    78,    79,   298,    79,   175,   176,   177,
     178,   179,   180,   303,    24,    44,   302,    93,   307,    45,
     306,   308,    46,   158,    93,    47,    79,    48,   168,   271,
      49,    50,    51,    79,    52,   245,   211,   250,   246,    20,
       0,     0,     0,    53,     0,    54,    55,    56,    57,    58,
      59,    60,    61,    62,     0,     0,     0,     0,    63,     0,
       0,     0,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    65,
      66,    67,    68,    69,    70,   108,   109,     0,    54,    55,
      56,    57,     0,     0,     0,    61,    62,   110,   111,     0,
       0,    63,     0,     0,     0,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,    66,    67,    68,    69,    70,    53,   213,
      54,    55,    56,    57,     0,     0,     0,    61,    62,     0,
       0,     0,     0,    63,     0,     0,     0,    64,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    65,    66,    67,    68,    69,    70,
      53,     0,    54,    55,    56,    57,     0,     0,     0,    61,
      62,     0,     0,     0,     0,    63,     0,     0,     0,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    65,    66,    67,    68,
      69,    70,    53,     0,    54,    55,    56,    57,     0,     0,
       0,    61,    62,     0,     0,     0,     0,    63,     0,     0,
       0,    64,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   127,    66,
      67,    68,    69,    70,    53,     0,    54,    55,    56,    57,
       0,     0,     0,    61,    62,     0,     0,     0,     0,    63,
       0,     0,     0,    64,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      10,    66,    67,    68,    69,    70
  };

  const short int
   AutoGenParser ::yycheck_[] =
  {
       3,     4,    17,    49,    50,    32,    33,    53,     7,    33,
      48,    12,    27,    29,     6,    27,     6,    53,    29,    29,
      71,    45,    46,   188,   189,     6,   181,   182,    52,   194,
      33,    36,    36,    59,    58,    59,    51,    71,   196,    33,
      64,     6,    31,    71,     9,   106,    60,    36,    62,    30,
      62,    45,    46,    43,    58,    71,    35,    60,    52,    35,
      71,    71,    43,   109,    58,    59,    35,    72,    69,    70,
      62,   109,    71,   109,   232,   233,   137,    72,    27,    36,
      71,    60,    51,    36,    60,    72,    35,    55,    56,    57,
      62,    60,   138,   139,   140,    16,   142,    18,    27,   145,
     146,    58,    51,    31,   150,    58,    53,    54,   132,   133,
     134,    60,    28,   278,     0,   280,    59,    35,     4,     5,
     135,   167,     8,   147,   183,   184,   185,    72,    62,   175,
     176,   177,   178,   179,   180,   300,     6,    35,   132,   133,
     134,    71,   307,    62,    36,    35,    35,   171,   172,    62,
      35,    35,    35,   147,    61,    61,    48,    49,    72,    71,
      62,     7,   165,    28,   188,   189,    62,    28,    59,   193,
     194,    63,    64,    65,    66,    67,    68,   171,   172,    13,
      35,    69,    35,    32,    20,   188,   189,    18,    33,    18,
      25,   194,    36,    59,   188,   189,    71,     6,    71,   193,
     194,    27,    11,    61,    71,    14,    62,    59,    17,    71,
      19,    36,    72,    22,    23,    24,   262,    26,   264,    35,
      35,    35,   249,    36,    72,    36,    35,   273,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    36,    36,   254,
      36,    50,    36,    27,    52,    54,    51,    51,    72,    72,
      62,    15,    59,   299,   278,    36,   280,    59,    36,    60,
      21,    18,    71,    72,    73,    74,    75,    76,    36,    72,
      62,    36,    48,    49,    36,   278,   300,   280,    36,   294,
      52,    72,    28,   307,   278,    59,   280,    63,    64,    65,
      66,    67,    68,    72,     6,     7,    71,   300,    18,    11,
      59,    72,    14,    98,   307,    17,   300,    19,   108,   224,
      22,    23,    24,   307,    26,   186,   148,   191,   187,    31,
      -1,    -1,    -1,    35,    -1,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    76,    34,    35,    -1,    37,    38,
      39,    40,    -1,    -1,    -1,    44,    45,    46,    47,    -1,
      -1,    50,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    44,    45,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      35,    -1,    37,    38,    39,    40,    -1,    -1,    -1,    44,
      45,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    35,    -1,    37,    38,    39,    40,    -1,    -1,
      -1,    44,    45,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    76,    35,    -1,    37,    38,    39,    40,
      -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76
  };

  const unsigned char
   AutoGenParser ::yystos_[] =
  {
       0,    78,     0,     4,     5,     8,    79,    80,    81,    86,
      71,   128,   128,    71,    60,    62,    35,    88,    59,    71,
      31,    36,    89,    92,     6,    30,    43,    87,    90,    72,
      71,    36,    58,    91,    29,    71,    72,    43,    90,    62,
      27,    62,    27,    92,     7,    11,    14,    17,    19,    22,
      23,    24,    26,    35,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    50,    54,    71,    72,    73,    74,    75,
      76,    90,    92,    93,    94,    95,    96,    97,   102,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   128,    28,    59,    35,   126,    72,    62,
       6,     9,    83,    29,    71,   108,   128,   108,    34,    35,
      46,    47,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   107,    98,    98,    90,    71,   108,    98,
     101,    71,    35,    35,    35,   108,   108,   128,    35,    35,
      35,   102,    51,    62,    62,    12,    69,    70,    61,    61,
      35,   124,    71,    72,    36,    72,   127,    62,   126,     7,
      84,    28,    62,    28,    59,    13,   124,    69,   104,    98,
     107,    35,    35,    48,    49,    63,    64,    65,    66,    67,
      68,    53,    54,    55,    56,    57,    32,    33,    18,    20,
      25,   122,   123,    27,    18,    36,    27,    59,   108,   108,
     108,    90,   124,    98,    98,    98,    98,    98,    98,   108,
      71,   109,    71,    36,    98,   125,    59,    36,    58,    62,
       7,    71,    85,    71,    82,    71,    72,   128,    98,    36,
     108,   108,    35,    35,    98,    98,    98,    98,    98,    98,
      99,    99,   100,   100,   100,   105,   106,    93,    93,    35,
     123,   108,    93,    82,    72,    36,    36,    36,    36,    36,
      36,    52,    51,    36,    58,    72,    72,    27,    62,    59,
      62,    83,    59,    15,    36,    36,    82,    82,    21,    92,
      18,    36,    90,    98,    98,    29,    71,    72,    62,    72,
      98,    36,    36,    93,    36,    93,    52,    28,    59,    16,
      18,    90,    71,    72,    98,    93,    59,    18,    72,    93
  };

  const unsigned char
   AutoGenParser ::yyr1_[] =
  {
       0,    77,    78,    78,    79,    79,    79,    80,    81,    81,
      81,    81,    82,    82,    83,    83,    84,    84,    85,    85,
      85,    85,    86,    86,    86,    86,    87,    87,    87,    87,
      88,    88,    89,    89,    90,    91,    91,    91,    92,    92,
      92,    92,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    94,    95,
      96,    97,    98,    99,    99,    99,   100,   100,   100,   100,
     101,   101,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   103,
     103,   103,   103,   103,   103,   103,   103,   104,   104,   104,
     104,   104,   105,   105,   106,   106,   107,   108,   108,   109,
     109,   109,   109,   110,   110,   111,   112,   112,   113,   113,
     114,   115,   116,   116,   117,   118,   118,   119,   120,   121,
     122,   122,   123,   124,   124,   125,   125,   126,   126,   127,
     127,   128,   128
  };

  const unsigned char
   AutoGenParser ::yyr2_[] =
  {
       0,     2,     0,     2,     1,     1,     1,     3,     7,    10,
       5,     9,     1,     3,     3,     2,     3,     0,     3,     5,
       5,     7,     5,     6,     7,     8,     2,     4,     4,     6,
       3,     2,     3,     1,     3,     3,     3,     0,     4,     6,
       6,     8,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     1,     1,     3,     3,     1,     3,     3,     3,     1,
       1,     1,     3,     1,     1,     1,     1,     1,     4,     5,
       5,     2,     4,     4,     2,     4,     4,     4,     4,     3,
       3,     3,     3,     3,     3,     5,     5,     1,     3,     2,
       4,     4,     1,     3,     1,     3,     1,     1,     3,     3,
       6,     1,     4,     4,     6,     4,     8,    10,     4,     6,
       2,     3,     2,     3,     2,     1,     2,     2,     4,     3,
       2,     1,     5,     2,     3,     3,     1,     2,     3,     3,
       1,     1,     3
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
  "\"DETACH\"", "\"CREATE\"", "\"DELETE\"", "\"EXTERNAL\"", "\"TYPE\"",
  "\"TYPENS\"", "\"ISSET\"", "\"ISNULL\"", "\"ISTYPE\"", "\"ISINSTANCE\"",
  "\"STRLEN\"", "\"[\"", "\"]\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"",
  "\"%\"", "\",\"", "\":\"", "\"::\"", "\".\"", "\";\"", "\"==\"", "\"<\"",
  "\"<=\"", "\">\"", "\">=\"", "\"<>\"", "\"= (assignment)\"",
  "\"?= (assignment)\"", "T_SYMBOL", "T_STRING", "T_INTEGER", "T_FLOAT",
  "T_BOOLEAN", "T_NULL", "$accept", "globals", "global", "import",
  "typeDefinition", "baseType", "typeDefinitionPropertiesEnclosed",
  "typeDefinitionProperties", "property", "program", "programResult",
  "parametersListPar", "parametersList", "statementsListBeginEnd",
  "statementsList", "declaration", "statement", "assignment", "condassign",
  "merge", "lvalue", "expr", "exprTerm", "exprFactor",
  "exprPrimaryOrXPath", "exprPrimary", "relationalOper",
  "logicalExprPrimary", "logicalExprFactor", "logicalExprTerm",
  "logicalExpr", "xpathAccess", "xpath", "with", "whileLoop", "forLoop",
  "ifThenElse", "call", "external", "create", "delete", "return", "throw",
  "sort", "tryCatch", "catchList", "catch", "exprListPar", "exprList",
  "externalParametersPar", "externalParameters", "qname", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
   AutoGenParser ::yyrline_[] =
  {
       0,   233,   233,   233,   235,   236,   237,   242,   247,   252,
     258,   263,   270,   273,   276,   277,   279,   280,   282,   283,
     285,   288,   293,   296,   299,   302,   305,   306,   307,   308,
     310,   311,   313,   314,   316,   318,   323,   324,   326,   327,
     328,   330,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   351,   352,
     353,   355,   362,   363,   364,   366,   367,   368,   369,   371,
     373,   374,   376,   377,   378,   379,   380,   381,   383,   384,
     387,   390,   391,   392,   393,   394,   395,   396,   397,   399,
     401,   402,   403,   404,   405,   407,   410,   413,   414,   415,
     416,   417,   419,   420,   422,   423,   425,   428,   431,   435,
     436,   439,   440,   444,   445,   447,   449,   452,   455,   457,
     460,   462,   463,   464,   465,   467,   468,   471,   473,   475,
     476,   477,   479,   482,   483,   485,   486,   488,   489,   491,
     492,   495,   496
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76
    };
    const unsigned int user_token_number_max_ = 331;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 2206 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:1155
#line 498 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:1156



void yy::AutoGenParser::error (const location_type& l,
                               const std::string& m)
{
  myParser.onAutoGenParserError(l, m);
}

