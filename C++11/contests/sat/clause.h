#pragma once
#include <vector>

// forward declarations
class literal;
class variable;

// State of a Clause
enum ClauseState
{
	CS_UNSAT,	// unsatisfied clause i.e. all literals are assigned 0
	CS_SAT,		// satisfied i.e. atleast one literal is assigned 1
	CS_UNIT,	// unit clause i.e. it has only one literal and other literals are implied 0. a unit literal is unit propogated to make it satisfied
	CS_EMPTY,	// empty clause i.e. it has no literals i.e. all literals are implied 0. Empty clause results in CNF being UNSAT
	CS_UNRES	// unresolved clause state (default)
};

// A clause is OR or Disjunction of k-literals
class clause
{
	// list of k-literals, k <= n boolean variables
	std::vector< literal* > literals;

	// State of clause: unsatisfied, satisfied, unit, empty, unresolved (default)
	ClauseState clauseState_;

public:
	clause( ClauseState _clauseState = ClauseState::CS_UNRES ); // default state of clause is unresolved
	~clause();

	void appendLiteral( literal & _literal );
	std::vector< literal* > getLiterals() const;

	// returns true if unit propogation was done for the clause. otherwise returns false
	bool optimizeUnitPropagate();

	//// returns true if atleast one optimization is done. otherwise false
	//bool optimizeClause();

	// returns true if satisfied, false otherwise
	bool evaluateClause( std::vector<variable*> const & _variables );
};
