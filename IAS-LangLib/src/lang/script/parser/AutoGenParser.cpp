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
#line 66 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:413

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
            case 76: // T_SYMBOL

#line 239 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:614
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 405 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:614
        break;

      case 77: // T_STRING

#line 239 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:614
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 412 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:614
        break;

      case 78: // T_INTEGER

#line 239 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:614
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 419 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:614
        break;

      case 79: // T_FLOAT

#line 239 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:614
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 426 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:614
        break;

      case 80: // T_BOOLEAN

#line 239 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:614
        { std::cout<<"D:"<<*(yysym.value.sval)<<"\n"; _SVAL_DELETE((yysym.value.sval)); }
#line 433 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:614
        break;

      case 81: // T_NULL

#line 239 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:614
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
#line 247 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { myParser.addTypeDefinition((yystack_[0].value.pTypeDefinitionNode)); }
#line 688 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 248 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    {
    (yystack_[0].value.pProgramNode)->setSourceLocation(myParser.getLexer()->getCachedLocation()); 
	myParser.addProgram((yystack_[0].value.pProgramNode)); 
}
#line 697 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 253 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    {
  myParser.addNamespaceDeclaration((yystack_[0].value.pNamespaceDeclarationNode));
}
#line 705 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 258 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    {  myParser.open((yystack_[1].value.pQualifiedNameNode)->getQualifiedName()); 
           	 IAS_DFT_FACTORY<Dec::QualifiedNameNode>::Free((yystack_[1].value.pQualifiedNameNode)); 
           	 }
#line 713 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 263 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode);
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[5].value.sval)); _SVAL_DELETE((yystack_[5].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[3].value.sval)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 721 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 268 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode);
				  (yylhs.value.pTypeDefinitionNode)->setBaseTypeNode((yystack_[2].value.pTypeInfo));
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[8].value.sval)); _SVAL_DELETE((yystack_[8].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[6].value.sval)); _SVAL_DELETE((yystack_[6].value.sval)); }
#line 730 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 274 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create(); 				  
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[3].value.sval)); _SVAL_DELETE((yystack_[3].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[1].value.sval)); _SVAL_DELETE((yystack_[1].value.sval)); }
#line 738 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 279 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create(); 
				  (yylhs.value.pTypeDefinitionNode)->setBaseTypeNode((yystack_[1].value.pTypeInfo));
				  (yylhs.value.pTypeDefinitionNode)->setName(*(yystack_[7].value.sval)); _SVAL_DELETE((yystack_[7].value.sval)); 
				  (yylhs.value.pTypeDefinitionNode)->setNamespace(*(yystack_[5].value.sval)); _SVAL_DELETE((yystack_[5].value.sval)); }
#line 747 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 286 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeInfo) = IAS_DFT_FACTORY<Dec::TypeInfoNode>::Create(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 753 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 289 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeInfo) = IAS_DFT_FACTORY<Dec::TypeInfoNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval));  _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 759 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 291 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[1].value.pTypeDefinitionNode); }
#line 765 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 292 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create();  }
#line 771 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 294 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = (yystack_[2].value.pTypeDefinitionNode); (yylhs.value.pTypeDefinitionNode)->addDeclaration((yystack_[1].value.pDeclarationNode)); }
#line 777 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 295 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pTypeDefinitionNode) = IAS_DFT_FACTORY<Dec::TypeDefinitionNode>::Create();}
#line 783 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 297 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 789 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 298 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); 
												                _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 796 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 300 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[0].value.sval)); 
												 (yylhs.value.pDeclarationNode)->setIsArray(true); 
												 _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 804 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 303 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[6].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); 
																  (yylhs.value.pDeclarationNode)->setIsArray(true); 
												                  _SVAL_DELETE((yystack_[6].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 812 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 308 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pNamespaceDeclarationNode) = IAS_DFT_FACTORY<Dec::NamespaceDeclarationNode>::Create(*(yystack_[3].value.sval),*(yystack_[1].value.sval)); 
					_SVAL_DELETE((yystack_[3].value.sval)); _SVAL_DELETE((yystack_[1].value.sval)); }
#line 819 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 312 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<StandardProgramNode>::Create((yystack_[3].value.pQualifiedNameNode),(yystack_[1].value.pStatementsListNode),(yystack_[2].value.pParametersNode)); }
#line 825 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 315 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<StandardProgramNode>::Create((yystack_[4].value.pQualifiedNameNode),(yystack_[1].value.pStatementsListNode),(yystack_[3].value.pParametersNode),(yystack_[2].value.pDeclarationNode)); }
#line 831 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 318 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<ExternalProgramNode>::Create((yystack_[5].value.pQualifiedNameNode),*(yystack_[2].value.sval),(yystack_[4].value.pParametersNode),*(yystack_[1].value.pStringList)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE_StringList((yystack_[1].value.pStringList));}
#line 837 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 321 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pProgramNode) = IAS_DFT_FACTORY<ExternalProgramNode>::Create((yystack_[6].value.pQualifiedNameNode),*(yystack_[2].value.sval),(yystack_[5].value.pParametersNode),(yystack_[4].value.pDeclarationNode),*(yystack_[1].value.pStringList)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE_StringList((yystack_[1].value.pStringList));}
#line 843 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 323 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 849 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 324 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 855 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 325 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[0].value.sval));  (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 861 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 326 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::ResultDeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval));  (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 867 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 328 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pParametersNode) = (yystack_[1].value.pParametersNode); }
#line 873 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 329 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pParametersNode) = IAS_DFT_FACTORY<Dec::ParametersNode>::Create();  }
#line 879 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 331 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pParametersNode) = (yystack_[2].value.pParametersNode); (yylhs.value.pParametersNode)->addDeclaration((yystack_[0].value.pDeclarationNode)); }
#line 885 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 332 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pParametersNode) = IAS_DFT_FACTORY<Dec::ParametersNode>::Create(); (yylhs.value.pParametersNode)->addDeclaration((yystack_[0].value.pDeclarationNode)); }
#line 891 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 334 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementsListNode) = (yystack_[1].value.pStatementsListNode); }
#line 897 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 336 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { 
(yylhs.value.pStatementsListNode) = (yystack_[2].value.pStatementsListNode); 
(yystack_[1].value.pStatementNode)->setSourceLocation(myParser.getLexer()->getCachedLocation());
(yylhs.value.pStatementsListNode)->addStatement((yystack_[1].value.pStatementNode));
 }
#line 907 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 341 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementsListNode) = (yystack_[2].value.pStatementsListNode); (yylhs.value.pStatementsListNode)->addDeclaration((yystack_[1].value.pDeclarationNode)); }
#line 913 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 342 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementsListNode) = IAS_DFT_FACTORY<Stmt::StatementsListNode>::Create(); }
#line 919 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 344 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 925 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 345 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[4].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 931 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 347 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[4].value.sval),*(yystack_[0].value.sval));     (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[4].value.sval));  _SVAL_DELETE((yystack_[0].value.sval)); }
#line 937 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 349 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pDeclarationNode) = IAS_DFT_FACTORY<Dec::DeclarationNode>::Create(*(yystack_[6].value.sval),*(yystack_[2].value.sval),*(yystack_[0].value.sval)); (yylhs.value.pDeclarationNode)->setIsArray(true); _SVAL_DELETE((yystack_[6].value.sval));  _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 943 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 352 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementsListNode); }
#line 949 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 353 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 955 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 354 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 961 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 355 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 967 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 356 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 973 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 357 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 979 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 358 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 985 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 359 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 991 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 360 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 997 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 361 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1003 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 362 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1009 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 363 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1015 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 364 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1021 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 365 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1027 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 366 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1033 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 367 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1039 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 368 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) =(yystack_[0].value.pStatementNode); }
#line 1045 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 370 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::AssignmentNode>::Create((yystack_[2].value.pLeftSideNode),(yystack_[0].value.pExprNode)); }
#line 1051 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 371 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ConditionalAssignmentNode>::Create((yystack_[2].value.pLeftSideNode),(yystack_[0].value.pXPathAccessNode)); }
#line 1057 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 372 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::MergeNode>::Create((yystack_[2].value.pLeftSideNode),(yystack_[0].value.pExprNode)); }
#line 1063 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 374 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLeftSideNode) = IAS_DFT_FACTORY<Stmt::LeftSideNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1069 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 381 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1075 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 382 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::AdditionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1081 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 383 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::SubtractionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1087 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 385 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1093 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 386 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::MultiplyNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1099 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 387 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::DivisionNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1105 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 388 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ModuloNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1111 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 390 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1117 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 392 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = (yystack_[0].value.pExprNode); }
#line 1123 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 393 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::XPath::XPathExprNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1129 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 395 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = (yystack_[1].value.pExprNode); }
#line 1135 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 396 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_INTEGER,*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1141 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 397 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_FLOAT,*(yystack_[0].value.sval));   _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1147 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 398 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_STRING,*(yystack_[0].value.sval));  _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1153 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 399 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_BOOLEAN,*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1159 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 400 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstNode>::Create(Expr::ConstNode::CN_NULL,*(yystack_[0].value.sval));    _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1165 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 402 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstructorNode>::Create(*(yystack_[2].value.sval),*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[2].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1171 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 404 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::ConstructorNode>::Create(*(yystack_[3].value.sval),*(yystack_[1].value.sval), (yystack_[0].value.pStatementsListNode)); _SVAL_DELETE((yystack_[3].value.sval)); _SVAL_DELETE((yystack_[1].value.sval)); }
#line 1177 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 407 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::CastNode>::Create((yystack_[3].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1183 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 410 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::XPathOrValueNode>::Create((yystack_[3].value.pXPathAccessNode),(yystack_[1].value.pExprNode)); }
#line 1189 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 413 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::CondValueNode>::Create((yystack_[5].value.pLogicalExprNode),(yystack_[3].value.pExprNode),(yystack_[1].value.pExprNode)); }
#line 1195 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 415 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::FunCallNode>::Create((yystack_[1].value.pQualifiedNameNode), (yystack_[0].value.pExprListNode)); }
#line 1201 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 416 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::CopyOfNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1207 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 417 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::DetachNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1213 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 418 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::NegativeNode>::Create((yystack_[0].value.pExprNode)); }
#line 1219 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 419 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::SizeOfNode>::Create((yystack_[1].value.pXPathAccessNode));}
#line 1225 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 420 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::GetTypeNode>::Create((yystack_[1].value.pExprNode));}
#line 1231 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 421 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::GetTypeNSNode>::Create((yystack_[1].value.pExprNode));}
#line 1237 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 422 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprNode) = IAS_DFT_FACTORY<Expr::StrLenNode>::Create((yystack_[1].value.pExprNode));}
#line 1243 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 424 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1249 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 426 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalDiffNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1255 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 427 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqGtNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1261 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 428 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalEqLessNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1267 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 429 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalGtNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1273 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 430 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalLessNode>::Create((yystack_[2].value.pExprNode),(yystack_[0].value.pExprNode)); }
#line 1279 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 433 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalIsTypeNode>::Create((yystack_[4].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1285 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 436 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::RelationalIsInstanceNode>::Create((yystack_[4].value.pExprNode),(yystack_[1].value.pTypeInfo)); }
#line 1291 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 438 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1297 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 439 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = (yystack_[1].value.pLogicalExprNode); }
#line 1303 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 440 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalNotNode>::Create((yystack_[0].value.pLogicalExprNode)); }
#line 1309 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 441 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::IsSetNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1315 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 442 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::IsNullNode>::Create((yystack_[1].value.pXPathAccessNode)); }
#line 1321 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 444 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1327 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 445 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalAndNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pLogicalExprNode)); }
#line 1333 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 447 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1339 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 448 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = IAS_DFT_FACTORY<Expr::LogicalOrNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pLogicalExprNode)); }
#line 1345 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 450 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pLogicalExprNode) = (yystack_[0].value.pLogicalExprNode); }
#line 1351 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 453 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pXPathAccessNode) = IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::Create(
								IAS_DFT_FACTORY<Expr::XPath::XPathVariableAccessNode>::Create(
										(*((yystack_[0].value.pXPathNode)->getElements().begin()))->getName()),(yystack_[0].value.pXPathNode));}
#line 1359 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 457 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pXPathAccessNode) = IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::Create(
						IAS_DFT_FACTORY<Expr::XPath::XPathExprAccessNode>::Create((yystack_[2].value.pExprNode)),(yystack_[0].value.pXPathNode)); }
#line 1366 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 460 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pXPathNode) = (yystack_[2].value.pXPathNode); (yylhs.value.pXPathNode)->addSingleElement(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1372 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 462 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pXPathNode) = (yystack_[5].value.pXPathNode); (yylhs.value.pXPathNode)->addMultiElement(*(yystack_[3].value.sval),(yystack_[1].value.pExprNode)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 1378 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 465 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pXPathNode) = (yystack_[5].value.pXPathNode); (yylhs.value.pXPathNode)->addHashIndexElement(*(yystack_[3].value.sval),(yystack_[1].value.pExprNode)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 1384 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 467 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pXPathNode) = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); (yylhs.value.pXPathNode)->addSingleElement(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1390 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 469 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pXPathNode) = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); (yylhs.value.pXPathNode)->addMultiElement(*(yystack_[3].value.sval),(yystack_[1].value.pExprNode)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 1396 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 472 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pXPathNode) = IAS_DFT_FACTORY<Expr::XPath::XPathNode>::Create(); (yylhs.value.pXPathNode)->addHashIndexElement(*(yystack_[3].value.sval),(yystack_[1].value.pExprNode)); _SVAL_DELETE((yystack_[3].value.sval)); }
#line 1402 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 474 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WithNode>::Create("",(yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pStatementNode)); }
#line 1408 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 475 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WithNode>::Create(*(yystack_[4].value.sval),(yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pStatementNode)); _SVAL_DELETE((yystack_[4].value.sval)); }
#line 1414 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 477 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::WhileLoopNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pStatementNode)); }
#line 1420 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 480 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ForLoopNode>::Create((yystack_[6].value.pXPathAccessNode),(yystack_[0].value.pStatementNode),(yystack_[4].value.pExprNode),(yystack_[2].value.pExprNode)); }
#line 1426 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 483 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ForLoopNode>::Create((yystack_[8].value.pXPathAccessNode),(yystack_[0].value.pStatementNode),(yystack_[6].value.pExprNode),(yystack_[4].value.pExprNode),(yystack_[2].value.pExprNode)); }
#line 1432 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 485 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::IfThenElseNode>::Create((yystack_[2].value.pLogicalExprNode),(yystack_[0].value.pStatementNode)); }
#line 1438 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 488 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::IfThenElseNode>::Create((yystack_[4].value.pLogicalExprNode),(yystack_[2].value.pStatementNode),(yystack_[0].value.pStatementNode)); }
#line 1444 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 490 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CallNode>::Create((yystack_[1].value.pQualifiedNameNode),(yystack_[0].value.pExprListNode)); }
#line 1450 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 492 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CallNode>::Create((yystack_[1].value.pQualifiedNameNode),(yystack_[0].value.pExprListNode)); }
#line 1456 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 493 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CreateNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1462 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 494 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::CreateNode>::Create((yystack_[1].value.pXPathAccessNode),(yystack_[0].value.pStatementsListNode)); }
#line 1468 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 495 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::DeleteNode>::Create((yystack_[0].value.pXPathAccessNode)); }
#line 1474 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 497 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ReturnNode>::Create(); }
#line 1480 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 498 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ReturnNode>::Create((yystack_[0].value.pExprNode)); }
#line 1486 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 501 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::ThrowNode>::Create((yystack_[0].value.pExprNode)); }
#line 1492 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 503 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::SortNode>::Create((yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pQualifiedNameNode)); }
#line 1498 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 505 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::IndexNode>::Create((yystack_[2].value.pXPathAccessNode),(yystack_[0].value.pXPathAccessNode));}
#line 1504 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 507 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStatementNode) = IAS_DFT_FACTORY<Stmt::TryCatchNode>::Create((yystack_[1].value.pStatementsListNode),(yystack_[0].value.pCatchListNode));  }
#line 1510 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 508 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pCatchListNode) = (yystack_[1].value.pCatchListNode); (yylhs.value.pCatchListNode)->addCatchNode((yystack_[0].value.pCatchNode));           }
#line 1516 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 509 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pCatchListNode) = IAS_DFT_FACTORY<Stmt::CatchListNode>::Create(); (yylhs.value.pCatchListNode)->addCatchNode((yystack_[0].value.pCatchNode)); }
#line 1522 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 512 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pCatchNode) = IAS_DFT_FACTORY<Stmt::CatchNode>::Create((yystack_[2].value.pDeclarationNode),(yystack_[0].value.pStatementsListNode)); }
#line 1528 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 514 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprListNode) = IAS_DFT_FACTORY<Expr::ExprListNode>::Create(); }
#line 1534 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 515 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprListNode)=(yystack_[1].value.pExprListNode); }
#line 1540 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 517 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprListNode)=(yystack_[2].value.pExprListNode); (yylhs.value.pExprListNode)->addExprNode((yystack_[0].value.pExprNode)); }
#line 1546 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 518 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pExprListNode) = IAS_DFT_FACTORY<Expr::ExprListNode>::Create();  (yylhs.value.pExprListNode)->addExprNode((yystack_[0].value.pExprNode)); }
#line 1552 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 520 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStringList) = new StringList;}
#line 1558 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 521 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStringList)=(yystack_[1].value.pStringList); }
#line 1564 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 523 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStringList)=(yystack_[2].value.pStringList); (yylhs.value.pStringList)->push_back(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval));}
#line 1570 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 524 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pStringList) = new StringList; (yylhs.value.pStringList)->push_back(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1576 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 527 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pQualifiedNameNode)= IAS_DFT_FACTORY<Dec::QualifiedNameNode>::Create(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1582 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 528 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:859
    { (yylhs.value.pQualifiedNameNode)=(yystack_[2].value.pQualifiedNameNode); (yylhs.value.pQualifiedNameNode)->addNextSymbol(*(yystack_[0].value.sval)); _SVAL_DELETE((yystack_[0].value.sval)); }
#line 1588 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
    break;


#line 1592 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:859
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


  const short int  AutoGenParser ::yypact_ninf_ = -180;

  const short int  AutoGenParser ::yytable_ninf_ = -150;

  const short int
   AutoGenParser ::yypact_[] =
  {
    -180,   151,  -180,   -56,   -56,   -39,    10,  -180,  -180,  -180,
    -180,  -180,  -180,    52,    15,    -7,    62,    27,  -180,    -4,
       9,    30,    35,  -180,    46,  -180,     0,  -180,  -180,   -21,
      49,    13,    61,   -15,    69,   107,  -180,   117,   328,    56,
     100,   127,    90,   102,  -180,   114,  -180,  -180,    -8,  -180,
    -180,   227,   227,   227,    53,    53,   227,   227,   163,   387,
      53,    96,   139,   143,   150,   227,   227,   -56,   152,   155,
     156,   432,    88,  -180,  -180,  -180,  -180,  -180,  -180,   113,
     122,  -180,  -180,  -180,    -2,   136,  -180,   140,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,    20,   128,   132,   -10,   146,   127,  -180,   206,   186,
     161,   187,   165,   204,    20,   215,   157,    53,    53,   194,
     196,   390,    -9,   -17,  -180,   136,  -180,  -180,   200,   201,
     220,  -180,   213,  -180,  -180,   214,    51,   222,   188,   223,
     168,   216,   190,   227,   227,   227,   163,  -180,    20,   227,
     227,   227,  -180,   227,   227,  -180,  -180,   227,   227,   227,
     185,   195,   144,   197,   207,  -180,  -180,  -180,    12,  -180,
     209,  -180,    -1,   202,  -180,   205,   199,   -56,  -180,   227,
     227,  -180,   -12,   227,   227,   235,   240,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,    53,    53,
     373,   373,   243,   214,  -180,   227,   373,  -180,   202,   227,
     227,   210,   244,   245,   246,  -180,  -180,   248,   250,   251,
     237,   253,  -180,  -180,  -180,    87,   140,    92,  -180,  -180,
      23,   219,  -180,   224,  -180,  -180,   264,   234,   239,     3,
     247,  -180,   249,  -180,   294,  -180,   274,   276,   202,   202,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,   292,   117,  -180,   296,  -180,   279,
     255,   282,   163,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,   227,   227,  -180,   227,  -180,  -180,     2,  -180,   252,
    -180,   257,   254,   227,  -180,  -180,   283,   286,   373,   287,
     373,  -180,   227,  -180,  -180,   272,   277,  -180,   298,   269,
    -180,  -180,  -180,   142,  -180,  -180,  -180,   163,  -180,   299,
    -180,  -180,   260,   265,   227,   373,  -180,  -180,   285,  -180,
     325,  -180,   278,   373,  -180,  -180
  };

  const unsigned char
   AutoGenParser ::yydefact_[] =
  {
       2,     0,     1,     0,     0,     0,     0,     3,     4,     5,
       7,     6,   149,     0,     0,     0,     0,     0,     8,     0,
       0,     0,     0,   150,     0,    33,     0,    35,    39,     0,
       0,     0,     0,     0,     0,     0,    32,     0,     0,     0,
      28,     0,     0,     0,    24,     0,    11,    23,     0,    34,
      36,     0,     0,     0,     0,     0,   132,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,    78,    76,    77,    79,    80,    44,     0,
       0,    45,    46,    47,     0,     0,    64,   112,    50,    49,
      48,    51,    53,    54,    55,    56,    57,    59,    58,    52,
      60,     0,     0,     0,     0,     0,     0,    25,    18,     0,
       0,     0,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    65,    68,    72,    73,   102,   107,   109,   111,
       0,    74,     0,   133,   134,     0,   117,     0,     0,    72,
       0,    74,     0,     0,     0,     0,   129,   131,     0,     0,
       0,     0,    89,     0,     0,    38,    37,     0,     0,     0,
       0,     0,     0,   127,    30,    29,   145,   148,     0,    26,
       0,    16,     0,     0,     9,     0,     0,     0,    86,     0,
       0,   104,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   137,   139,     0,     0,    75,     0,     0,
       0,     0,     0,     0,     0,   130,   128,     0,     0,     0,
       0,     0,    63,    61,    62,   117,   113,   114,   141,   144,
       0,     0,   146,     0,    27,    15,     0,     0,    13,     0,
      42,    41,   135,   136,     0,   103,     0,     0,     0,     0,
      94,    98,    96,    99,    97,    95,    66,    67,    69,    70,
      71,   108,   110,   122,   125,     0,   138,     0,   120,     0,
       0,     0,    81,    90,    87,    88,    91,    92,    93,   118,
     119,     0,     0,   142,     0,    31,   147,     0,    17,     0,
      12,     0,     0,     0,   105,   106,     0,     0,     0,     0,
       0,    83,     0,    84,    82,     0,     0,   143,     0,    19,
      14,    10,    43,     0,   100,   101,   126,     0,   121,     0,
     115,   116,     0,     0,     0,     0,   140,    85,    21,    20,
       0,   123,     0,     0,    22,   124
  };

  const short int
   AutoGenParser ::yypgoto_[] =
  {
    -180,  -180,  -180,  -180,  -180,  -172,   112,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,   -18,  -180,   -33,  -179,  -180,  -180,
    -180,  -180,    57,  -112,   -99,   -52,    -6,  -180,   229,   159,
     160,   -48,   -35,   198,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,   173,   -75,
    -180,   256,  -180,    -3
  };

  const short int
   AutoGenParser ::yydefgoto_[] =
  {
      -1,     1,     7,     8,     9,   239,   110,   172,   237,    10,
      11,    31,    20,    26,    78,    38,    27,    80,    81,    82,
      83,    84,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   203,   204,   163,
     230,   105,   168,   114
  };

  const short int
   AutoGenParser ::yytable_[] =
  {
      13,    14,    32,    86,    49,    79,   235,   132,   139,   108,
      39,   157,   140,    43,    45,    28,   113,   115,   116,    28,
      12,   263,   264,   111,   137,   141,   245,   268,   166,    24,
     146,   147,    85,   308,    25,   101,   269,    15,    36,   178,
     135,    29,   195,   196,   197,    85,    85,    85,   193,   194,
     232,    46,    19,    85,    30,    40,    21,   162,    42,    85,
      85,   283,    37,   209,   148,   152,   139,   167,   112,   290,
     182,   158,   159,   216,   233,   236,   296,   297,   309,    17,
     205,   256,   257,   141,    17,   284,   102,    16,  -149,   117,
     118,    22,    61,    62,    63,    64,   258,   259,   260,    68,
      69,   119,   120,    23,   153,    70,   154,    33,   212,   213,
     214,    71,    34,   133,   134,  -149,    17,   138,    18,   316,
     108,   318,    35,   109,   224,  -149,    41,    44,   215,    72,
      73,    74,    75,    76,    77,    47,    48,    85,    85,    85,
     153,   153,   154,   154,   243,   281,   331,   282,   246,   247,
      24,     2,  -149,    85,   335,     3,     4,   270,   271,     5,
     324,     6,   325,   103,   104,    86,    86,   106,   107,    28,
     267,    86,   142,    85,   242,   138,   143,    85,    85,   155,
     144,    60,   228,    61,    62,    63,    64,   145,   156,   149,
      68,    69,   150,   151,    85,    85,    70,   101,   101,    85,
      85,   160,    71,   101,   164,   161,   217,   218,   219,   165,
     220,   221,   169,   171,   222,   223,   173,   175,   177,   229,
      72,    73,    74,    75,    76,    77,   207,   174,   176,   179,
     180,   183,   299,   184,   198,   201,   199,   244,   185,   186,
     200,   202,   206,   209,   250,   251,   252,   253,   254,   255,
     319,   210,   208,   211,   304,   187,   188,   189,   190,   191,
     192,   225,   -86,    86,    60,    86,    61,    62,    63,    64,
     231,   227,   248,    68,    69,   234,   241,   249,   238,    70,
     265,   240,   273,   274,   275,    71,   276,   272,   277,   278,
      86,   279,    85,   287,    85,   101,   285,   101,    86,   326,
     288,   286,   289,    72,    73,    74,    75,    76,    77,   280,
     292,   293,   294,    17,   295,   298,   300,   301,   302,    85,
     303,   314,   101,   311,   315,   317,   320,    85,   322,   310,
     101,   312,   323,   321,    28,    50,   328,   327,   305,   306,
      51,   307,   329,    52,    53,   333,   181,    54,   332,    55,
     313,   291,    56,    57,    58,   334,    59,   261,   226,   262,
       0,    24,   170,     0,     0,    60,     0,    61,    62,    63,
      64,    65,    66,    67,    68,    69,   266,     0,     0,    28,
      70,   330,     0,     0,     0,    51,    71,     0,    52,    53,
       0,     0,    54,     0,    55,     0,     0,    56,    57,    58,
       0,    59,     0,     0,    72,    73,    74,    75,    76,    77,
      60,     0,    61,    62,    63,    64,    65,    66,    67,    68,
      69,     0,     0,     0,    60,    70,    61,    62,    63,    64,
       0,    71,     0,    68,    69,     0,     0,     0,     0,    70,
     185,   186,     0,     0,     0,    71,     0,     0,     0,    72,
      73,    74,    75,    76,    77,     0,     0,   187,   188,   189,
     190,   191,   192,   136,    73,    74,    75,    76,    77,    60,
       0,    61,    62,    63,    64,     0,     0,     0,    68,    69,
       0,     0,     0,     0,    70,     0,     0,     0,     0,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    12,    73,
      74,    75,    76,    77
  };

  const short int
   AutoGenParser ::yycheck_[] =
  {
       3,     4,    20,    38,    37,    38,     7,    55,    60,     6,
      31,    13,    60,    31,    29,     6,    51,    52,    53,     6,
      76,   200,   201,    31,    59,    60,    38,   206,    38,    33,
      65,    66,    38,    31,    38,    38,   208,    76,    38,   114,
      58,    32,    59,    60,    61,    51,    52,    53,    57,    58,
      38,    66,    37,    59,    45,    76,    63,    37,    45,    65,
      66,    38,    62,    75,    67,    71,   118,    77,    76,    66,
     118,    73,    74,   148,    62,    76,   248,   249,    76,    64,
      29,   193,   194,   118,    64,    62,    30,    77,    37,    36,
      37,    29,    39,    40,    41,    42,   195,   196,   197,    46,
      47,    48,    49,    76,    53,    52,    55,    77,   143,   144,
     145,    58,    77,    56,    57,    64,    64,    60,    66,   298,
       6,   300,    76,     9,   159,    37,    77,    66,   146,    76,
      77,    78,    79,    80,    81,    66,    29,   143,   144,   145,
      53,    53,    55,    55,   179,    53,   325,    55,   183,   184,
      33,     0,    64,   159,   333,     4,     5,   209,   210,     8,
      18,    10,    20,    63,    37,   200,   201,    77,    66,     6,
     205,   206,    76,   179,   177,   118,    37,   183,   184,    66,
      37,    37,    38,    39,    40,    41,    42,    37,    66,    37,
      46,    47,    37,    37,   200,   201,    52,   200,   201,   205,
     206,    65,    58,   206,    76,    65,   149,   150,   151,    77,
     153,   154,    66,     7,   157,   158,    30,    30,    14,   162,
      76,    77,    78,    79,    80,    81,    38,    66,    63,    14,
      73,    37,   265,    37,    34,    22,    35,   180,    50,    51,
      20,    27,    20,    75,   187,   188,   189,   190,   191,   192,
     302,    35,    29,    63,   272,    67,    68,    69,    70,    71,
      72,    76,    65,   298,    37,   300,    39,    40,    41,    42,
      63,    76,    37,    46,    47,    66,    77,    37,    76,    52,
      37,    76,    38,    38,    38,    58,    38,    77,    38,    38,
     325,    54,   298,    29,   300,   298,    77,   300,   333,   317,
      66,    77,    63,    76,    77,    78,    79,    80,    81,    56,
      63,    17,    38,    64,    38,    23,    20,    38,    63,   325,
      38,    38,   325,    66,    38,    38,    54,   333,    30,    77,
     333,    77,    63,    56,     6,     7,    76,    38,   281,   282,
      12,   284,    77,    15,    16,    20,   117,    19,    63,    21,
     293,   239,    24,    25,    26,    77,    28,   198,   160,   199,
      -1,    33,   106,    -1,    -1,    37,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    47,   203,    -1,    -1,     6,
      52,   324,    -1,    -1,    -1,    12,    58,    -1,    15,    16,
      -1,    -1,    19,    -1,    21,    -1,    -1,    24,    25,    26,
      -1,    28,    -1,    -1,    76,    77,    78,    79,    80,    81,
      37,    -1,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    -1,    -1,    -1,    37,    52,    39,    40,    41,    42,
      -1,    58,    -1,    46,    47,    -1,    -1,    -1,    -1,    52,
      50,    51,    -1,    -1,    -1,    58,    -1,    -1,    -1,    76,
      77,    78,    79,    80,    81,    -1,    -1,    67,    68,    69,
      70,    71,    72,    76,    77,    78,    79,    80,    81,    37,
      -1,    39,    40,    41,    42,    -1,    -1,    -1,    46,    47,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    81
  };

  const unsigned char
   AutoGenParser ::yystos_[] =
  {
       0,    83,     0,     4,     5,     8,    10,    84,    85,    86,
      91,    92,    76,   135,   135,    76,    77,    64,    66,    37,
      94,    63,    29,    76,    33,    38,    95,    98,     6,    32,
      45,    93,    96,    77,    77,    76,    38,    62,    97,    31,
      76,    77,    45,    96,    66,    29,    66,    66,    29,    98,
       7,    12,    15,    16,    19,    21,    24,    25,    26,    28,
      37,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      52,    58,    76,    77,    78,    79,    80,    81,    96,    98,
      99,   100,   101,   102,   103,   108,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   135,    30,    63,    37,   133,    77,    66,     6,     9,
      88,    31,    76,   114,   135,   114,   114,    36,    37,    48,
      49,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   113,   104,   104,    96,    76,   114,   104,   107,
     113,   114,    76,    37,    37,    37,   114,   114,   135,    37,
      37,    37,   108,    53,    55,    66,    66,    13,    73,    74,
      65,    65,    37,   131,    76,    77,    38,    77,   134,    66,
     133,     7,    89,    30,    66,    30,    63,    14,   131,    14,
      73,   110,   113,    37,    37,    50,    51,    67,    68,    69,
      70,    71,    72,    57,    58,    59,    60,    61,    34,    35,
      20,    22,    27,   129,   130,    29,    20,    38,    29,    75,
      35,    63,   114,   114,   114,    96,   131,   104,   104,   104,
     104,   104,   104,   104,   114,    76,   115,    76,    38,   104,
     132,    63,    38,    62,    66,     7,    76,    90,    76,    87,
      76,    77,   135,   114,   104,    38,   114,   114,    37,    37,
     104,   104,   104,   104,   104,   104,   105,   105,   106,   106,
     106,   111,   112,    99,    99,    37,   130,   114,    99,    87,
     107,   107,    77,    38,    38,    38,    38,    38,    38,    54,
      56,    53,    55,    38,    62,    77,    77,    29,    66,    63,
      66,    88,    63,    17,    38,    38,    87,    87,    23,    98,
      20,    38,    63,    38,    96,   104,   104,   104,    31,    76,
      77,    66,    77,   104,    38,    38,    99,    38,    99,   107,
      54,    56,    30,    63,    18,    20,    96,    38,    76,    77,
     104,    99,    63,    20,    77,    99
  };

  const unsigned char
   AutoGenParser ::yyr1_[] =
  {
       0,    82,    83,    83,    84,    84,    84,    84,    85,    86,
      86,    86,    86,    87,    87,    88,    88,    89,    89,    90,
      90,    90,    90,    91,    92,    92,    92,    92,    93,    93,
      93,    93,    94,    94,    95,    95,    96,    97,    97,    97,
      98,    98,    98,    98,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,   100,   101,   102,   103,   104,   105,   105,   105,   106,
     106,   106,   106,   107,   107,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   109,   109,   109,   109,   109,   109,
     109,   109,   110,   110,   110,   110,   110,   111,   111,   112,
     112,   113,   114,   114,   115,   115,   115,   115,   115,   115,
     116,   116,   117,   118,   118,   119,   119,   120,   121,   122,
     122,   123,   124,   124,   125,   126,   127,   128,   129,   129,
     130,   131,   131,   132,   132,   133,   133,   134,   134,   135,
     135
  };

  const unsigned char
   AutoGenParser ::yyr2_[] =
  {
       0,     2,     0,     2,     1,     1,     1,     1,     3,     7,
      10,     5,     9,     1,     3,     3,     2,     3,     0,     3,
       5,     5,     7,     5,     5,     6,     7,     8,     2,     4,
       4,     6,     3,     2,     3,     1,     3,     3,     3,     0,
       4,     6,     6,     8,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     1,     1,     3,     3,     1,     3,
       3,     3,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     4,     5,     5,     5,     7,     2,     4,     4,     2,
       4,     4,     4,     4,     3,     3,     3,     3,     3,     3,
       5,     5,     1,     3,     2,     4,     4,     1,     3,     1,
       3,     1,     1,     3,     3,     6,     6,     1,     4,     4,
       4,     6,     4,     8,    10,     4,     6,     2,     3,     2,
       3,     2,     1,     2,     2,     4,     4,     3,     2,     1,
       5,     2,     3,     3,     1,     2,     3,     3,     1,     1,
       3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  AutoGenParser ::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "T_NONE", "\"IMPORT\"",
  "\"PROGRAM\"", "\"BEGIN\"", "\"END\"", "\"DEFINE\"", "\"EXTENSION\"",
  "\"NAMESPACE\"", "\"CALL\"", "\"SORT\"", "\"MERGE\"", "\"USING\"",
  "\"INDEX\"", "\"FOR\"", "\"TO\"", "\"STEP\"", "\"WHILE\"", "\"DO\"",
  "\"IF\"", "\"THEN\"", "\"ELSE\"", "\"RETURN\"", "\"THROW\"", "\"TRY\"",
  "\"CATCH\"", "\"WITH\"", "\"AS\"", "\"OF\"", "\"ARRAY\"", "\"RETURNS\"",
  "\"VAR\"", "\"AND\"", "\"OR\"", "\"NOT\"", "\"(\"", "\")\"", "\"NEW\"",
  "\"SIZEOF\"", "\"COPYOF\"", "\"DETACH\"", "\"CREATE\"", "\"DELETE\"",
  "\"EXTERNAL\"", "\"TYPE\"", "\"TYPENS\"", "\"ISSET\"", "\"ISNULL\"",
  "\"ISTYPE\"", "\"ISINSTANCE\"", "\"STRLEN\"", "\"[\"", "\"]\"", "\"[[\"",
  "\"]]\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"%\"", "\",\"", "\":\"",
  "\"::\"", "\".\"", "\";\"", "\"==\"", "\"<\"", "\"<=\"", "\">\"",
  "\">=\"", "\"<>\"", "\"= (assignment)\"", "\"?= (assignment)\"", "\"?\"",
  "T_SYMBOL", "T_STRING", "T_INTEGER", "T_FLOAT", "T_BOOLEAN", "T_NULL",
  "$accept", "globals", "global", "import", "typeDefinition", "baseType",
  "typeDefinitionPropertiesEnclosed", "typeDefinitionProperties",
  "property", "namespaceDeclaration", "program", "programResult",
  "parametersListPar", "parametersList", "statementsListBeginEnd",
  "statementsList", "declaration", "statement", "assignment", "condassign",
  "merge", "lvalue", "expr", "exprTerm", "exprFactor",
  "exprPrimaryOrXPath", "exprPrimary", "relationalOper",
  "logicalExprPrimary", "logicalExprFactor", "logicalExprTerm",
  "logicalExpr", "xpathAccess", "xpath", "with", "whileLoop", "forLoop",
  "ifThenElse", "call", "external", "create", "delete", "return", "throw",
  "sort", "index", "tryCatch", "catchList", "catch", "exprListPar",
  "exprList", "externalParametersPar", "externalParameters", "qname", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
   AutoGenParser ::yyrline_[] =
  {
       0,   244,   244,   244,   246,   247,   248,   253,   257,   262,
     267,   273,   278,   285,   288,   291,   292,   294,   295,   297,
     298,   300,   303,   307,   311,   314,   317,   320,   323,   324,
     325,   326,   328,   329,   331,   332,   334,   336,   341,   342,
     344,   345,   346,   348,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   367,
     368,   370,   371,   372,   374,   381,   382,   383,   385,   386,
     387,   388,   390,   392,   393,   395,   396,   397,   398,   399,
     400,   402,   403,   406,   409,   412,   415,   416,   417,   418,
     419,   420,   421,   422,   424,   426,   427,   428,   429,   430,
     432,   435,   438,   439,   440,   441,   442,   444,   445,   447,
     448,   450,   453,   456,   460,   461,   464,   467,   468,   471,
     474,   475,   477,   479,   482,   485,   487,   490,   492,   493,
     494,   495,   497,   498,   501,   503,   505,   507,   508,   509,
     511,   514,   515,   517,   518,   520,   521,   523,   524,   527,
     528
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
      75,    76,    77,    78,    79,    80,    81
    };
    const unsigned int user_token_number_max_ = 336;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 2289 "src/lang/script/parser/AutoGenParser.cpp" // lalr1.cc:1167
#line 530 "src/lang/script/parser/AutoGenParser.yy" // lalr1.cc:1168



void yy::AutoGenParser::error (const location_type& l,
                               const std::string& m)
{
  myParser.onAutoGenParserError(l, m);
}

