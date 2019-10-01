#pragma once
#include <vector>
#include "literal.h"

// forward declarations
class clause;
class variable;

// Conjunction Normal Form (CNF) or SOP form 
// is a Conjunction or AND of m-Clauses
class cnf
{
	// list of m-clauses
	std::vector< clause* > clauses_;

	// list of n-boolean variables
	std::vector< variable* > variables_;

	// CNF formulae is satisifed if there exists 
	// atleast one truth assignment that makes it
	// evaluate to true
	bool isSat_;

	// Indexes of pure variable (literals) of type 
	// POS, COMPL and TRUE
	std::vector<uint16_t> idxPureVariables_;

	// Indexes of clauses which are always unsat 
	// these are clause with all FALSE type literals
	std::vector<uint16_t> idxAlwaysUnsatClauses_;

	// Indexes of clauses which are unit clauses
	std::vector<uint16_t> idxUnitClauses_;

	std::vector<bool> perThreadSatResults_;

	// Finds pure variables(literals) for the cnf expression, 
	// Optimizes them and stores indexes of found pure 
	// variables (literals) of type POS, COMP and TRUE
	bool optimizePureVariableLiterals();

	// Finds clauses which have all FALSE type literals.
	// Such a clauseis always. Returns true if atleast 
	// one such always unsat clause is found. false otherwise
	bool findAlwaysUnsatClauses();

	// Unit propogates clauses. returns true iff atleast 
	// one clause was found to be a unit clause. false otherwise
	bool optimizeUnitPropagateClauses();

	// Find info of lone POS or COMPL literal for a unit clause
	void getUnitClauseLiteralInfo( clause const * _unitClause, 
								   uint16_t & _idxUnitClauseLiteral,
								   LiteralType & _litType );

	// Finds if the CNF expression has atleast 
	// one pair of complementary unit clauses
	bool findComplUnitClauses();

	void evaluateClauses( unsigned int _begin, unsigned int _end, unsigned int _threadId = 0 );

	// Finds first combination of boolean logic variables which satisfies the CNF Expression
	// Returns true and satisfying variable assignment string if satisfying assignment found
	// Returns false and dont-care variable assignment string if satisfying assignment not found
	bool findFirstSatVariableAssignment( std::string & _firstSatVariableAssignment );

public:
	cnf();
	~cnf();

	void appendClause( clause & _clause );
	void appendVariable( variable & _variable );

	std::vector<clause*> getClauses() const;
	std::vector<variable*> getVariables() const;

	// returns true if cnf expression was optimized. otherwise false
	bool optimizeCnfExpression();

	// Evaluates CNF expression and returns the first satisfying variable assignment
	bool evaluateSatisfiability( std::string & _firstSatVariableAssignment );
};