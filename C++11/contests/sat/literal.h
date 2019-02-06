#pragma once
#include <vector>

// Type of Form of variable represented by a Literal
enum LiteralType
{
	LT_POS,		// represents true form x of a variable x
	LT_COMPL,	// represents complementary form !x of a variable x
	LT_FALSE,	// represents boolean logic 0(false) form 
	LT_TRUE		// represents boolean logic 1(true) form
};

// State of literal
enum LiteralState
{
	LS_STATIC,		// A literal state is static or implied if it is permanently assigned a value (say due to unit propogation)
	LS_PURE,		// A literal state is pure(special state of static or implied) , if its variable is pure
	LS_DYNAMIC,		// A literal state is dynamic if its assignable logic value 0 or 1
	LS_UNKNOWN		// A literal state is unknown if it is not in any of remaining states(default)
};

// forward declarations
class variable;
class clause;

// A literal represents true or complemented form of a boolean variable
class literal
{
	// literal can represent various forms of a boolean variable:
	// - true form(1)
	// - false form (-1)
	// - forced logic 0 (0)
	// - forced logic 1 (any other integer)
	LiteralType literalType_;

	// State of literal: pure, implied, assigned, unassigned (default)
	LiteralState literalState_;

	// A literal representing 
	// - true form x of variable x is satisfied, if its variable x is assigned true
	// - complementary form !x of variable x is satisfied, if its variable x is assigned false
	// - forced logic 0, is always unsatisfied
	// - forced logic 1, is always satisfied
	bool isLiteralSat_;

	// Every literal has a parent variable. 
	//variable* myParentVariable_;

	//// A literal may be shared by multiple clauses
	//std::vector< clause* > myClauses_;
	
	// Every literal has one parent clause
	clause* parentClause_;

public:
	literal( LiteralType _literalType,
			 LiteralState _literalState,
			 bool _literalSatValue,
			 clause * _parentClause );

	~literal();

	LiteralType getLiteralType() const;

	LiteralState getLiteralState() const;
	void setLiteralState( LiteralState _literalState );

	bool getLiteralSatValue() const;

	//void addClause( clause* _parentClause );

	//variable* getParentVariable() const;
	//void setParentVariable(variable & _variable);

	bool evaluateLiteral( variable const * _parentVariable );
};
