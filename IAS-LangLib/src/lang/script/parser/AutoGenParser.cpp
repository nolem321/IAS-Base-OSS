// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

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

#line 37 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "AutoGenParser.hpp"

// User implementation prologue.

#line 51 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 65 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:413

#include "Parser.h"
#include "Lexer.h"
#include "yylex_function.h"

using namespace IAS;
using namespace Lang;
using namespace Model;
using namespace Script;
using namespace Parser;


#line 66 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:413


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
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 152 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:479

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
    clear ();
  }

  template <typename Base>
  inline
  void
   AutoGenParser ::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
   AutoGenParser ::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
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
    : type (empty_symbol)
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
   AutoGenParser ::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
   AutoGenParser ::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
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
    : state (empty_state)
  {}

  inline
   AutoGenParser ::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
   AutoGenParser ::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
   AutoGenParser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
   AutoGenParser ::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
   AutoGenParser ::symbol_number_type
   AutoGenParser ::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
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
    that.type = empty_symbol;
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
            case 72: // T_SYMBOL

#line 231 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:614
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 405 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:614
        break;

      case 73: // T_STRING

#line 231 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:614
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 412 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:614
        break;

      case 74: // T_INTEGER

#line 231 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:614
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 419 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:614
        break;

      case 75: // T_FLOAT

#line 231 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:614
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 426 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:614
        break;

      case 76: // T_BOOLEAN

#line 231 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:614
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 433 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:614
        break;

      case 77: // T_NULL

#line 231 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:614
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 440 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:614
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
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
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
    #line 26 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:741
{
  // Initialize the initial location.
  yyla.location.begin.filename = yyla.location.end.filename = new std::string("waisted");
}

#line 578 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:741

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
    if (yyla.empty ())
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
#line 239 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { myParser.addTypeDefinition((yystack_[0].value.pTypeDefinitionNode)); }
#line 688 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 240 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    {
    (yystack_[0].value.pProgramNode)->setSourceLocation(myParser.getLexer()->getCachedLocation()); 
	myParser.addProgram((yystack_[0].value.pProgramNode)); 
}
#line 697 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 246 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    {  myParser.open((yystack_[1].value.pQualifiedNameNode)->getQualifiedName()); 
           	 IAS_DFT_FACTORY<Dec::QualifiedNameNode>::Free((yystack_[1].value.pQualifiedNameNode)); 
           	 }
#line 705 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 251 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode);
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[5].value.sval)); _SVAL_DELETE((yystack_[5].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[3].value.sval)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 713 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 256 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode);
				  (yylhs.value.pTypeDefinitionNode)->setBaseTypeNode((yystack_[2].value.pTypeInfo));
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[8].value.sval)); _SVAL_DELETE((yystack_[8].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[6].value.sval)); _SVAL_DELETE((yystack_[6].value.sval)); }
#line 722 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 262 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create(); 				  
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[3].value.sval)); _SVAL_DELETE((yystack_[3].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[1].value.sval)); _SVAL_DELETE((yystack_[1].value.sval)); }
#line 730 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 267 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create(); 
				  (yylhs.value.pTypeDefinitionNode)->setBaseTypeNode((yystack_[1].value.pTypeInfo));
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[7].value.sval)); _SVAL_DELETE((yystack_[7].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[5].value.sval)); _SVAL_DELETE((yystack_[5].value.sval)); }
#line 739 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 274 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeInfo) = IAS_DFT_FACTORY<Dec::TypeInfoNode>::Create(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 745 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 277 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeInfo) = IAS_DFT_FACTORY<Dec::TypeInfoNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval));  _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 751 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 279 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode); }
#line 757 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 280 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create();  }
#line 763 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 282 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[2].value.pTypeDefinitionNode); (yylhs.value.pTypeDefinitionNode)->addDeclaration((yystack_[1].value.pDeclarationNode)); }
#line 769 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 283 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create();}
#line 775 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 285 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 781 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 286 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); 
												                _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 788 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 288 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[0].value.sval)); 
												 (yylhs.value.pDeclarationNode)->setIsArray(true); 
												 _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 796 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 291 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[6].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); 
																  (yylhs.value.pDeclarationNode)->setIsArray(true); 
												                  _SVAL_DELETE((yystack_[6].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 804 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 297 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<StandardProgramNode>::Create((yystack_[3].value.pQualifiedNameNode),(yystack_[1].value.pStatementsListNode),(yystack_[2].value.pParametersNode)); }
#line 810 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 300 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<StandardProgramNode>::Create((yystack_[4].value.pQualifiedNameNode),(yystack_[1].value.pStatementsListNode),(yystack_[3].value.pParametersNode),(yystack_[2].value.pDeclarationNode)); }
#line 816 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 303 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<ExternalProgramNode>::Create((yystack_[5].value.pQualifiedNameNode),*(yystack_[2].value.sval),(yystack_[4].value.pParametersNode),*(yystack_[1].value.pStringList)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE_StringList((yystack_[1].value.pStringList));}
#line 822 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 306 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<ExternalProgramNode>::Create((yystack_[6].value.pQualifiedNameNode),*(yystack_[2].value.sval),(yystack_[5].value.pParametersNode),(yystack_[4].value.pDeclarationNode),*(yystack_[1].value.pStringList)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE_StringList((yystack_[1].value.pStringList));}
#line 828 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 308 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 834 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 309 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 840 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 310 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[0].value.sval));  (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 846 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 311 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval));  (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 852 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 313 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pParametersNode) = (yystack_[1].value.pParametersNode); }
#line 858 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 314 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pParametersNode) = IAS_DFT_FACTORY<Dec::ParametersNode>::Create();  }
#line 864 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 316 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pParametersNode) = (yystack_[2].value.pParametersNode); (yylhs.value.pParametersNode)->addDeclaration((yystack_[0].value.pDeclarationNode)); }
#line 870 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 317 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pParametersNode) = IAS_DFT_FACTORY<Dec::ParametersNode>::Create(); (yylhs.value.pParametersNode)->addDeclaration((yystack_[0].value.pDeclarationNode)); }
#line 876 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 319 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementsListNode) = (yystack_[1].value.pStatementsListNode); }
#line 882 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 321 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { 
(yylhs.value.pStatementsListNode) = (yystack_[2].value.pStatementsListNode); 
(yystack_[1].value.pStatementNode)->setSourceLocation(myParser.getLexer()->getCachedLocation());
(yylhs.value.pStatementsListNode)->addStatement((yystack_[1].value.pStatementNode));
 }
#line 892 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 326 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementsListNode) = (yystack_[2].value.pStatementsListNode); (yylhs.value.pStatementsListNode)->addDeclaration((yystack_[1].value.pDeclarationNode)); }
#line 898 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 327 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementsListNode) = IAS_DFT_FACTORY<Stmt::StatementsListNode>::Create(); }
#line 904 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 329 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 910 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 330 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 916 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 332 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[0].value.sval));     (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[4].value.sval));  _SVAL_DELETE((yystack_[0].value.sval)); }
#line 922 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 334 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[6].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[6].value.sval));  _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 928 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 337 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementsListNode); }
#line 934 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 338 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 940 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 339 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 946 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 340 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 952 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 341 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 958 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 342 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 964 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 343 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 970 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 344 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 976 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 345 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 982 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 346 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 988 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 347 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 994 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 348 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1000 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 349 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1006 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 350 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1012 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 351 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1018 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 352 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1024 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 354 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::AssignmentNode>::Create((yystack_[2].value.pLeftSideNode),(yystack_[0].value.pExprNode)); }
#line 1030 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 355 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ConditionalAssignmentNode>::Create((yystack_[2].value.pLeftSideNode),(yystack_[0].value.pXPathAccessNode)); }
#line 1036 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 356 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::MergeNode>::Create((yystack_[2].value.pLeftSideNode),(yystack_[0].value.pExprNode)); }
#line 1042 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 358 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLeftSideNode) = IAS_DFT_FACTORY<Stmt::LeftSideNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1048 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 365 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1054 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 366 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::AdditionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1060 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 367 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::SubtractionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1066 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 369 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1072 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 370 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::MultiplyNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1078 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 371 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::DivisionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1084 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 372 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ModuloNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1090 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 374 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1096 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 376 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1102 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 377 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::XPath::XPathExprNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1108 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 379 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = (yystack_[1].value.pExprNode); }
#line 1114 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 380 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_INTEGER,*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1120 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 381 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_FLOAT,*(yystack_[0].value.sval));   _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1126 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 382 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_STRING,*(yystack_[0].value.sval));  _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1132 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 383 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_BOOLEAN,*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1138 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 384 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_NULL,*(yystack_[0].value.sval));    _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1144 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 386 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstructorNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1150 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 388 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstructorNode>::Create(*(yystack_[3].value.sval),*(yystack_[1].value.sval), (yystack_[0].value.pStatementsListNode)); _SVAL_DELETE((yystack_[3].value.sval)); _SVAL_DELETE((yystack_[1].value.sval)); }
#line 1156 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 391 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::CastNode>::Create((yystack_[3].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1162 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 394 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::XPathOrValueNode>::Create((yystack_[3].value.pXPathAccessNode),(yystack_[1].value.pExprNode)); }
#line 1168 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 397 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::CondValueNode>::Create((yystack_[5].value.pLogicalExprNode),(yystack_[3].value.pExprNode),(yystack_[1].value.pExprNode)); }
#line 1174 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 399 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::FunCallNode>::Create((yystack_[1].value.pQualifiedNameNode), (yystack_[0].value.pExprListNode)); }
#line 1180 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 400 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::CopyOfNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1186 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 401 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::DetachNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1192 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 402 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::NegativeNode>::Create((yystack_[0].value.pExprNode)); }
#line 1198 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 403 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::SizeOfNode>::Create((yystack_[1].value.pXPathAccessNode));}
#line 1204 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 404 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::GetTypeNode>::Create((yystack_[1].value.pExprNode));}
#line 1210 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 405 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::GetTypeNSNode>::Create((yystack_[1].value.pExprNode));}
#line 1216 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 406 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::StrLenNode>::Create((yystack_[1].value.pExprNode));}
#line 1222 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 408 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1228 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 410 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalDiffNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1234 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 411 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqGtNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1240 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 412 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqLessNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1246 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 413 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalGtNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1252 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 414 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalLessNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1258 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 417 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalIsTypeNode>::Create((yystack_[4].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1264 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 420 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalIsInstanceNode>::Create((yystack_[4].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1270 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 422 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1276 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 423 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = (yystack_[1].value.pLogicalExprNode); }
#line 1282 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 424 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalNotNode>::Create((yystack_[0].value.pLogicalExprNode)); }
#line 1288 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 425 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::IsSetNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1294 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 426 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::IsNullNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1300 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 428 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1306 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 429 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalAndNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pLogicalExprNode)); }
#line 1312 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 431 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1318 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 432 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalOrNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pLogicalExprNode)); }
#line 1324 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 434 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1330 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 437 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pXPathAccessNode) = IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::Create(
								IAS_DFT_FACTORY<Expr::XPath::XPathVariableAccessNode>::Create(
										(*((yystack_[0].value.pXPathNode)->getElements().begin()))->getName()),(yystack_[0].value.pXPathNode));}
#line 1338 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 441 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pXPathAccessNode) = IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::Create(
						IAS_DFT_FACTORY<Expr::XPath::XPathExprAccessNode>::Create((yystack_[2].value.pExprNode)),(yystack_[0].value.pXPathNode)); }
#line 1345 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 444 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pXPathNode) = (yystack_[2].value.pXPathNode); (yylhs.value.pXPathNode)->addSingleElement(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1351 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 446 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pXPathNode) = (yystack_[5].value.pXPathNode); (yylhs.value.pXPathNode)->addMultiElement(*(yystack_[3].value.sval),(yystack_[1].value.pExprNode)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 1357 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 448 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pXPathNode) = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); (yylhs.value.pXPathNode)->addSingleElement(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1363 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 450 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pXPathNode) = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); (yylhs.value.pXPathNode)->addMultiElement(*(yystack_[3].value.sval),(yystack_[1].value.pExprNode)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 1369 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 453 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WithNode>::Create("",(yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pStatementNode)); }
#line 1375 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 454 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WithNode>::Create(*(yystack_[4].value.sval),(yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pStatementNode)); _SVAL_DELETE((yystack_[4].value.sval)); }
#line 1381 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 456 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WhileLoopNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pStatementNode)); }
#line 1387 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 459 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ForLoopNode>::Create((yystack_[6].value.pXPathAccessNode),(yystack_[0].value.pStatementNode),(yystack_[4].value.pExprNode),(yystack_[2].value.pExprNode)); }
#line 1393 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 462 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ForLoopNode>::Create((yystack_[8].value.pXPathAccessNode),(yystack_[0].value.pStatementNode),(yystack_[6].value.pExprNode),(yystack_[4].value.pExprNode),(yystack_[2].value.pExprNode)); }
#line 1399 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 464 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::IfThenElseNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pStatementNode)); }
#line 1405 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 467 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::IfThenElseNode>::Create((yystack_[4].value.pLogicalExprNode),(yystack_[2].value.pStatementNode),(yystack_[0].value.pStatementNode)); }
#line 1411 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 469 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CallNode>::Create((yystack_[1].value.pQualifiedNameNode),(yystack_[0].value.pExprListNode)); }
#line 1417 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 471 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CallNode>::Create((yystack_[1].value.pQualifiedNameNode),(yystack_[0].value.pExprListNode)); }
#line 1423 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 472 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CreateNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1429 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 473 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CreateNode>::Create((yystack_[1].value.pXPathAccessNode),(yystack_[0].value.pStatementsListNode)); }
#line 1435 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 474 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::DeleteNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1441 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 476 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ReturnNode>::Create(); }
#line 1447 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 477 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ReturnNode>::Create((yystack_[0].value.pExprNode)); }
#line 1453 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 480 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ThrowNode>::Create((yystack_[0].value.pExprNode)); }
#line 1459 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 482 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::SortNode>::Create((yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pQualifiedNameNode)); }
#line 1465 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 484 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::TryCatchNode>::Create((yystack_[1].value.pStatementsListNode),(yystack_[0].value.pCatchListNode));  }
#line 1471 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 485 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pCatchListNode) = (yystack_[1].value.pCatchListNode); (yylhs.value.pCatchListNode)->addCatchNode((yystack_[0].value.pCatchNode));           }
#line 1477 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 486 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pCatchListNode) = IAS_DFT_FACTORY<Stmt::CatchListNode>::Create(); (yylhs.value.pCatchListNode)->addCatchNode((yystack_[0].value.pCatchNode)); }
#line 1483 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 489 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pCatchNode) = IAS_DFT_FACTORY<Stmt::CatchNode>::Create((yystack_[2].value.pDeclarationNode),(yystack_[0].value.pStatementsListNode)); }
#line 1489 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 491 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprListNode) = IAS_DFT_FACTORY<Expr::ExprListNode>::Create(); }
#line 1495 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 492 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprListNode)=(yystack_[1].value.pExprListNode); }
#line 1501 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 494 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprListNode)=(yystack_[2].value.pExprListNode); (yylhs.value.pExprListNode)->addExprNode((yystack_[0].value.pExprNode)); }
#line 1507 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 495 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprListNode) = IAS_DFT_FACTORY<Expr::ExprListNode>::Create();  (yylhs.value.pExprListNode)->addExprNode((yystack_[0].value.pExprNode)); }
#line 1513 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 497 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStringList) = new StringList;}
#line 1519 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 498 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStringList)=(yystack_[1].value.pStringList); }
#line 1525 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 500 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStringList)=(yystack_[2].value.pStringList); (yylhs.value.pStringList)->push_back(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 1531 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 501 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStringList) = new StringList; (yylhs.value.pStringList)->push_back(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1537 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 504 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pQualifiedNameNode)= IAS_DFT_FACTORY<Dec::QualifiedNameNode>::Create(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1543 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 505 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pQualifiedNameNode)=(yystack_[2].value.pQualifiedNameNode); (yylhs.value.pQualifiedNameNode)->addNextSymbol(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1549 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;


#line 1553 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
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
    if (!yyla.empty ())
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
        if (!yyla.empty ())
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
   AutoGenParser ::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
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
       - The only way there can be no lookahead present (in yyla) is
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
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
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

    std::string yyres;
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


  const short int  AutoGenParser ::yypact_ninf_ = -165;

  const short int  AutoGenParser ::yytable_ninf_ = -144;

  const short int
   AutoGenParser ::yypact_[] =
  {
    -165,    40,  -165,   -39,   -39,   -33,  -165,  -165,  -165,  -165,
    -165,    32,    12,   -32,   -21,  -165,    50,    11,   -20,  -165,
      16,  -165,   -12,  -165,  -165,   -14,    10,    26,    29,    -7,
      74,  -165,    89,   197,    95,    71,   102,    68,    80,  -165,
      81,  -165,   -13,  -165,  -165,   414,   414,   328,   328,   414,
     414,   137,   457,   328,    75,   110,   111,   115,   414,   414,
     -39,   116,   119,   120,   500,    49,  -165,  -165,  -165,  -165,
    -165,  -165,    96,    97,  -165,  -165,  -165,    -9,    99,  -165,
     100,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,    45,    91,    94,     6,   106,   102,  -165,
     155,   141,   112,   144,   114,   162,    45,   109,   328,   328,
     145,   146,   200,    73,    58,  -165,    99,  -165,  -165,   147,
     149,   165,  -165,   164,  -165,  -165,   160,    38,   170,   282,
     163,   118,   158,   136,   414,   414,   414,   137,  -165,    45,
     414,   414,   414,  -165,   414,  -165,  -165,   414,   414,   414,
     124,   125,   371,   139,   142,  -165,  -165,  -165,    35,  -165,
     140,  -165,     3,   133,  -165,   134,   152,   -39,  -165,   414,
    -165,     7,   414,   414,   172,   174,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   328,   328,   284,
     284,   175,   160,  -165,   414,   284,  -165,   133,   414,   414,
     154,   176,   177,   179,  -165,  -165,   181,   182,   193,   178,
    -165,  -165,  -165,   180,   100,   192,  -165,  -165,    46,   173,
    -165,   183,  -165,  -165,   223,   190,   194,     8,   195,  -165,
     198,   240,  -165,   221,   224,   133,   133,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,   254,    89,  -165,   258,  -165,   241,   219,   243,   137,
    -165,  -165,  -165,  -165,  -165,  -165,  -165,   414,  -165,   414,
    -165,  -165,    -6,  -165,   208,  -165,   226,   210,   414,  -165,
    -165,   249,   255,   284,   257,   284,  -165,   414,  -165,  -165,
     242,  -165,   268,   238,  -165,  -165,  -165,    90,  -165,  -165,
    -165,   137,  -165,   263,  -165,   228,   229,   414,   284,  -165,
    -165,   245,  -165,   291,  -165,   244,   284,  -165,  -165
  };

  const unsigned char
   AutoGenParser ::yydefact_[] =
  {
       2,     0,     1,     0,     0,     0,     3,     4,     5,     6,
     143,     0,     0,     0,     0,     7,     0,     0,     0,   144,
       0,    31,     0,    33,    37,     0,     0,     0,     0,     0,
       0,    30,     0,     0,     0,    26,     0,     0,     0,    22,
       0,    10,     0,    32,    34,     0,     0,     0,     0,   127,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   113,    75,    73,    74,    76,
      77,    42,     0,     0,    43,    44,    45,     0,     0,    61,
     109,    48,    47,    46,    49,    50,    51,    52,    53,    54,
      56,    55,    57,     0,     0,     0,     0,     0,     0,    23,
      17,     0,     0,     0,    38,     0,     0,     0,     0,     0,
       0,     0,     0,    62,    65,    69,    70,    99,   104,   106,
     108,     0,    71,     0,   128,   129,     0,   113,     0,     0,
      69,     0,    71,     0,     0,     0,     0,   124,   126,     0,
       0,     0,     0,    86,     0,    36,    35,     0,     0,     0,
       0,     0,     0,   122,    28,    27,   139,   142,     0,    24,
       0,    15,     0,     0,     8,     0,     0,     0,    83,     0,
     101,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131,   133,     0,     0,    72,     0,     0,     0,
       0,     0,     0,     0,   125,   123,     0,     0,     0,     0,
      60,    58,    59,   113,   110,   111,   135,   138,     0,     0,
     140,     0,    25,    14,     0,     0,    12,     0,    40,    39,
     130,     0,   100,     0,     0,     0,     0,    91,    95,    93,
      96,    94,    92,    63,    64,    66,    67,    68,   105,   107,
     117,   120,     0,   132,     0,   115,     0,     0,     0,    78,
      87,    84,    85,    88,    89,    90,   114,     0,   136,     0,
      29,   141,     0,    16,     0,    11,     0,     0,     0,   102,
     103,     0,     0,     0,     0,     0,    80,     0,    81,    79,
       0,   137,     0,    18,    13,     9,    41,     0,    97,    98,
     121,     0,   116,     0,   112,     0,     0,     0,     0,   134,
      82,    20,    19,     0,   118,     0,     0,    21,   119
  };

  const short int
   AutoGenParser ::yypgoto_[] =
  {
    -165,  -165,  -165,  -165,  -165,  -159,    84,  -165,  -165,  -165,
    -165,  -165,  -165,   -15,  -165,   -26,  -164,  -165,  -165,  -165,
    -165,   -45,   -54,   -68,   -42,     4,  -165,   206,   128,   148,
     -35,   -24,   166,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
    -165,  -165,  -165,  -165,  -165,  -165,   143,   -87,  -165,   234,
    -165,    -3
  };

  const short int
   AutoGenParser ::yydefgoto_[] =
  {
      -1,     1,     6,     7,     8,   227,   102,   162,   225,     9,
      27,    17,    22,    71,    33,    23,    73,    74,    75,    76,
      77,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,   192,   193,   153,   218,    97,
     158,   106
  };

  const short int
   AutoGenParser ::yytable_[] =
  {
      11,    12,    28,   147,   124,   125,    43,    72,   129,    79,
     223,   130,    38,   123,   100,    34,   103,    24,   131,   168,
      40,   105,   107,   292,    31,   250,   251,    18,   128,   132,
      93,   255,    24,    10,   137,   138,   126,    78,   256,    13,
       2,    25,   156,   232,     3,     4,    32,    16,     5,    78,
      78,    19,   205,    29,    26,    41,    78,   139,    35,   104,
     148,   149,    78,    78,   129,   194,   293,   130,   143,    37,
     275,   220,    14,  -143,   171,   224,   281,   282,   198,   157,
     152,    20,   268,    36,  -143,   132,    21,   100,    30,   144,
     101,    39,    14,   221,    15,   206,   207,   208,  -143,   209,
     144,    42,   210,   211,   269,    14,   307,   217,   308,  -143,
     201,   202,   203,   184,   185,   186,   245,   246,   247,   300,
      20,   302,   204,    94,   231,   212,   182,   183,   243,   244,
      95,   237,   238,   239,   240,   241,   242,    96,    78,    78,
      78,    98,    99,    24,   314,   134,   135,   133,   233,   234,
     136,   140,   318,    78,   141,   142,   257,   258,   145,   146,
     150,   151,   161,   154,   230,    79,    79,   155,   159,   163,
     254,    79,   165,   166,   164,   167,    78,    78,   169,   187,
     172,   173,   188,   189,   190,   191,    93,    93,   195,   198,
     197,   199,    93,    78,    78,   200,   213,   215,    78,    78,
     -83,   219,   222,    24,    44,   226,   228,   235,    45,   236,
     252,    46,   260,   261,    47,   262,    48,   263,   264,    49,
      50,    51,   290,    52,   291,   229,   284,   259,    20,   265,
     266,   144,    53,   297,    54,    55,    56,    57,    58,    59,
      60,    61,    62,   267,   289,   303,   270,    63,   174,   175,
     272,    64,   273,   274,   277,   278,   271,   279,    14,    79,
     280,    79,   313,   176,   177,   178,   179,   180,   181,    65,
      66,    67,    68,    69,    70,   283,   285,   286,   287,   288,
      93,   294,    93,   296,    79,   298,   309,    78,   295,    78,
      24,   299,    79,   301,   304,    45,   305,   306,    46,   310,
     311,    47,   312,    48,   315,    93,    49,    50,    51,   316,
      52,   276,    78,    93,   170,   248,   214,   317,   196,    53,
      78,    54,    55,    56,    57,    58,    59,    60,    61,    62,
     174,   175,   160,     0,    63,   253,   249,     0,    64,     0,
       0,     0,     0,     0,     0,   176,   177,   178,   179,   180,
     181,     0,     0,     0,     0,     0,    65,    66,    67,    68,
      69,    70,   108,   109,     0,    54,    55,    56,    57,     0,
       0,     0,    61,    62,   110,   111,     0,     0,    63,     0,
       0,     0,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      65,    66,    67,    68,    69,    70,    53,   216,    54,    55,
      56,    57,     0,     0,     0,    61,    62,     0,     0,     0,
       0,    63,     0,     0,     0,    64,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    65,    66,    67,    68,    69,    70,    53,
       0,    54,    55,    56,    57,     0,     0,     0,    61,    62,
       0,     0,     0,     0,    63,     0,     0,     0,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    65,    66,    67,    68,
      69,    70,    53,     0,    54,    55,    56,    57,     0,     0,
       0,    61,    62,     0,     0,     0,     0,    63,     0,     0,
       0,    64,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
      66,    67,    68,    69,    70,    53,     0,    54,    55,    56,
      57,     0,     0,     0,    61,    62,     0,     0,     0,     0,
      63,     0,     0,     0,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    10,    66,    67,    68,    69,    70
  };

  const short int
   AutoGenParser ::yycheck_[] =
  {
       3,     4,    17,    12,    49,    50,    32,    33,    53,    33,
       7,    53,    27,    48,     6,    29,    29,     6,    53,   106,
      27,    45,    46,    29,    36,   189,   190,    59,    52,    53,
      33,   195,     6,    72,    58,    59,    51,    33,   197,    72,
       0,    30,    36,    36,     4,     5,    58,    35,     8,    45,
      46,    72,   139,    73,    43,    62,    52,    60,    72,    72,
      69,    70,    58,    59,   109,    27,    72,   109,    64,    43,
      62,    36,    60,    35,   109,    72,   235,   236,    71,    73,
      35,    31,    36,    73,    35,   109,    36,     6,    72,    51,
       9,    62,    60,    58,    62,   140,   141,   142,    60,   144,
      51,    27,   147,   148,    58,    60,    16,   152,    18,    60,
     134,   135,   136,    55,    56,    57,   184,   185,   186,   283,
      31,   285,   137,    28,   169,   149,    53,    54,   182,   183,
      59,   176,   177,   178,   179,   180,   181,    35,   134,   135,
     136,    73,    62,     6,   308,    35,    35,    72,   172,   173,
      35,    35,   316,   149,    35,    35,   198,   199,    62,    62,
      61,    61,     7,    72,   167,   189,   190,    73,    62,    28,
     194,   195,    28,    59,    62,    13,   172,   173,    69,    32,
      35,    35,    33,    18,    20,    25,   189,   190,    18,    71,
      27,    33,   195,   189,   190,    59,    72,    72,   194,   195,
      61,    59,    62,     6,     7,    72,    72,    35,    11,    35,
      35,    14,    36,    36,    17,    36,    19,    36,    36,    22,
      23,    24,   267,    26,   269,    73,   252,    73,    31,    36,
      52,    51,    35,   278,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    51,   259,   287,    73,    50,    48,    49,
      27,    54,    62,    59,    59,    15,    73,    36,    60,   283,
      36,   285,   307,    63,    64,    65,    66,    67,    68,    72,
      73,    74,    75,    76,    77,    21,    18,    36,    59,    36,
     283,    73,   285,    73,   308,    36,   301,   283,    62,   285,
       6,    36,   316,    36,    52,    11,    28,    59,    14,    36,
      72,    17,    73,    19,    59,   308,    22,    23,    24,    18,
      26,   227,   308,   316,   108,   187,   150,    73,    36,    35,
     316,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      48,    49,    98,    -1,    50,   192,   188,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,
      68,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    34,    35,    -1,    37,    38,    39,    40,    -1,
      -1,    -1,    44,    45,    46,    47,    -1,    -1,    50,    -1,
      -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    35,    36,    37,    38,
      39,    40,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    35,
      -1,    37,    38,    39,    40,    -1,    -1,    -1,    44,    45,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    35,    -1,    37,    38,    39,    40,    -1,    -1,
      -1,    44,    45,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    35,    -1,    37,    38,    39,
      40,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77
  };

  const unsigned char
   AutoGenParser ::yystos_[] =
  {
       0,    79,     0,     4,     5,     8,    80,    81,    82,    87,
      72,   129,   129,    72,    60,    62,    35,    89,    59,    72,
      31,    36,    90,    93,     6,    30,    43,    88,    91,    73,
      72,    36,    58,    92,    29,    72,    73,    43,    91,    62,
      27,    62,    27,    93,     7,    11,    14,    17,    19,    22,
      23,    24,    26,    35,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    50,    54,    72,    73,    74,    75,    76,
      77,    91,    93,    94,    95,    96,    97,    98,   103,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   129,    28,    59,    35,   127,    73,    62,
       6,     9,    84,    29,    72,   109,   129,   109,    34,    35,
      46,    47,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   108,    99,    99,    91,    72,   109,    99,
     102,   108,   109,    72,    35,    35,    35,   109,   109,   129,
      35,    35,    35,   103,    51,    62,    62,    12,    69,    70,
      61,    61,    35,   125,    72,    73,    36,    73,   128,    62,
     127,     7,    85,    28,    62,    28,    59,    13,   125,    69,
     105,   108,    35,    35,    48,    49,    63,    64,    65,    66,
      67,    68,    53,    54,    55,    56,    57,    32,    33,    18,
      20,    25,   123,   124,    27,    18,    36,    27,    71,    33,
      59,   109,   109,   109,    91,   125,    99,    99,    99,    99,
      99,    99,   109,    72,   110,    72,    36,    99,   126,    59,
      36,    58,    62,     7,    72,    86,    72,    83,    72,    73,
     129,    99,    36,   109,   109,    35,    35,    99,    99,    99,
      99,    99,    99,   100,   100,   101,   101,   101,   106,   107,
      94,    94,    35,   124,   109,    94,    83,   102,   102,    73,
      36,    36,    36,    36,    36,    36,    52,    51,    36,    58,
      73,    73,    27,    62,    59,    62,    84,    59,    15,    36,
      36,    83,    83,    21,    93,    18,    36,    59,    36,    91,
      99,    99,    29,    72,    73,    62,    73,    99,    36,    36,
      94,    36,    94,   102,    52,    28,    59,    16,    18,    91,
      36,    72,    73,    99,    94,    59,    18,    73,    94
  };

  const unsigned char
   AutoGenParser ::yyr1_[] =
  {
       0,    78,    79,    79,    80,    80,    80,    81,    82,    82,
      82,    82,    83,    83,    84,    84,    85,    85,    86,    86,
      86,    86,    87,    87,    87,    87,    88,    88,    88,    88,
      89,    89,    90,    90,    91,    92,    92,    92,    93,    93,
      93,    93,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    95,    96,
      97,    98,    99,   100,   100,   100,   101,   101,   101,   101,
     102,   102,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   104,   104,   104,   104,   104,   104,   104,   104,   105,
     105,   105,   105,   105,   106,   106,   107,   107,   108,   109,
     109,   110,   110,   110,   110,   111,   111,   112,   113,   113,
     114,   114,   115,   116,   117,   117,   118,   119,   119,   120,
     121,   122,   123,   123,   124,   125,   125,   126,   126,   127,
     127,   128,   128,   129,   129
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
       5,     5,     7,     2,     4,     4,     2,     4,     4,     4,
       4,     3,     3,     3,     3,     3,     3,     5,     5,     1,
       3,     2,     4,     4,     1,     3,     1,     3,     1,     1,
       3,     3,     6,     1,     4,     4,     6,     4,     8,    10,
       4,     6,     2,     3,     2,     3,     2,     1,     2,     2,
       4,     3,     2,     1,     5,     2,     3,     3,     1,     2,
       3,     3,     1,     1,     3
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
  "\"?= (assignment)\"", "\"?\"", "T_SYMBOL", "T_STRING", "T_INTEGER",
  "T_FLOAT", "T_BOOLEAN", "T_NULL", "$accept", "globals", "global",
  "import", "typeDefinition", "baseType",
  "typeDefinitionPropertiesEnclosed", "typeDefinitionProperties",
  "property", "program", "programResult", "parametersListPar",
  "parametersList", "statementsListBeginEnd", "statementsList",
  "declaration", "statement", "assignment", "condassign", "merge",
  "lvalue", "expr", "exprTerm", "exprFactor", "exprPrimaryOrXPath",
  "exprPrimary", "relationalOper", "logicalExprPrimary",
  "logicalExprFactor", "logicalExprTerm", "logicalExpr", "xpathAccess",
  "xpath", "with", "whileLoop", "forLoop", "ifThenElse", "call",
  "external", "create", "delete", "return", "throw", "sort", "tryCatch",
  "catchList", "catch", "exprListPar", "exprList", "externalParametersPar",
  "externalParameters", "qname", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
   AutoGenParser ::yyrline_[] =
  {
       0,   236,   236,   236,   238,   239,   240,   245,   250,   255,
     261,   266,   273,   276,   279,   280,   282,   283,   285,   286,
     288,   291,   296,   299,   302,   305,   308,   309,   310,   311,
     313,   314,   316,   317,   319,   321,   326,   327,   329,   330,
     331,   333,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   354,   355,
     356,   358,   365,   366,   367,   369,   370,   371,   372,   374,
     376,   377,   379,   380,   381,   382,   383,   384,   386,   387,
     390,   393,   396,   399,   400,   401,   402,   403,   404,   405,
     406,   408,   410,   411,   412,   413,   414,   416,   419,   422,
     423,   424,   425,   426,   428,   429,   431,   432,   434,   437,
     440,   444,   445,   448,   449,   453,   454,   456,   458,   461,
     464,   466,   469,   471,   472,   473,   474,   476,   477,   480,
     482,   484,   485,   486,   488,   491,   492,   494,   495,   497,
     498,   500,   501,   504,   505
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
      75,    76,    77
    };
    const unsigned int user_token_number_max_ = 332;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 2253 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:1167
#line 507 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:1168



void yy::AutoGenParser::error (const location_type& l,
                               const std::string& m)
{
  myParser.onAutoGenParserError(l, m);
}

