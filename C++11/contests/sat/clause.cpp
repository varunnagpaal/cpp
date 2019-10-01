#include "clause.h"
#include "literal.h"
#include "variable.h"

clause::clause( ClauseState _clauseState ) : clauseState_( _clauseState )
{
}

clause::~clause()
{
}

void clause::appendLiteral( literal & _literal )
{
	this->literals.push_back( &_literal );
}

std::vector<literal*> clause::getLiterals() const
{
	return this->literals;
}

// returns true if unit propogation was done. otherwise returns false
bool clause::optimizeUnitPropagate()
{
	// If a clause has only one literal in positive or complement form, 
	// its called a unit clause. We can unit propogate a unit clause 
	// i.e. hold the value of the lone positive/compliment literal of the clause
	// to a static value which will always satisfy the unit clause
	bool isUnitPropogated = false;
	uint16_t cntPosOrComplLiterals = 0;
	literal* lastValidLiteral = nullptr;
	
	for( auto currentLit : this->literals )
	{
		auto currentLitType = currentLit->getLiteralType();
		if ( currentLitType == LiteralType::LT_POS || 
			 currentLitType == LiteralType::LT_COMPL )
		{
			++cntPosOrComplLiterals;
			if ( cntPosOrComplLiterals == 1 )
				lastValidLiteral = currentLit;
			else if ( cntPosOrComplLiterals > 1 )
				break;
		}
	}

	if( cntPosOrComplLiterals == 1 )
	{
		//  Propogate static value to the literal which will always make it satisfied
		if( lastValidLiteral->getLiteralState() != LiteralState::LS_PURE )
		{
			lastValidLiteral->setLiteralState( LiteralState::LS_STATIC );
		}

		// A static literal is evaluated without a variable
		lastValidLiteral->evaluateLiteral( nullptr );

		// Set state of clause to unit clause
		this->clauseState_ = ClauseState::CS_UNIT;

		isUnitPropogated = true;
	}

	//if ( literals.size() == 1 )
	//{
	//	LiteralType literalType = literals[0]->getLiteralType();
	//	variable *parentVariable = literals[0]->getParentVariable();

	//	//  Propogate static value to variable which will make literal always satisfied
	//	if ( ( literalType == LiteralType::LT_POS ) || ( literalType == LiteralType::LT_TRUE ) )
	//	{
	//		parentVariable->setVariableLogicValue(true);
	//	}
	//	else if ( ( literalType == LiteralType::LT_COMPL ) || ( literalType == LiteralType::LT_FALSE ) )
	//	{
	//		parentVariable->setVariableLogicValue(false);
	//	}

	//	// Change state of variable to static (implied)
	//	parentVariable->setVariableState( VariableState::VS_STATIC );

	//	// propogate the static variable value to the literal
	//	literals[0]->evaluateLiteralValue();

	//	// Change state of literal to implied
	//	literals[0]->setLiteralState(LiteralState::LS_STATIC);

	//	// Set state of clause to unit clause
	//	this->clauseState_ = ClauseState::CS_UNIT;

	//	isPropogated = true;
	//}

	return isUnitPropogated;
}

//bool clause::optimizeClause()
//{
//	bool isOptimized = false;
//
//	isOptimized = unitPropogate();
//	return isOptimized;
//}

//bool clause::evaluateClause( variable const* _parentVariable )
//{
//	bool isClauseSat = false;
//
//	for(  auto lit: this->getLiterals() )
//	{
//		isClauseSat |= lit->evaluateLiteralValue( _parentVariable );
//	}
//
//	return isClauseSat;
//}

bool clause::evaluateClause( std::vector<variable*> const & _variables )
{
	bool isClauseSat = false;

	for(  auto idx = 0; idx < _variables.size(); ++idx )
	{
		isClauseSat = isClauseSat || this->literals[idx]->evaluateLiteral( _variables[idx] );
	}

	return isClauseSat;
}