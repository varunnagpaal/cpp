#include "cnf.h"
#include "clause.h"
#include "literal.h"
#include "variable.h"
#include <cassert>
#include <algorithm>
#include <iostream>
#include <thread>

cnf::cnf() : isSat_( false )
{
}

cnf::~cnf()
{
}

void cnf::appendClause( clause & _clause )
{
	clauses_.push_back( &_clause );
}

void cnf::appendVariable( variable & _variable )
{
	variables_.push_back( &_variable);
}

bool cnf::optimizePureVariableLiterals()
{
	// If a variable has same literal form (either positive or complement) 
	// across all clauses, then the variable and its identical literal form 
	// are said to be pure
	for( auto varidx = 0; varidx < this->variables_.size(); ++varidx )
	{
		auto isVarPure = true;
		auto clIdx = 0;
		LiteralType firstClauseLitType = LiteralType::LT_FALSE;

		for ( auto cl : this->clauses_ )
		{
			auto lts = cl->getLiterals();
			literal* currLit = lts[varidx];
			auto currLitType = currLit->getLiteralType();

			if( clIdx == 0 )
			{
				firstClauseLitType = currLitType;
			}
			else
			{
				if( currLitType != firstClauseLitType )
				{
					isVarPure = false;
					break;
				}
			}
		
			++clIdx;
		}

		if( isVarPure )
		{
			// Set state of variable and all its literals with identical form across clauses as pure
			// Note: we donot need to set logic value of a pure variable as its literals store this value
			this->variables_[varidx]->setVariableState( VariableState::VS_PURE );
			for ( auto cl : this->clauses_ )
			{
				auto lts = cl->getLiterals();
				literal* currLit = lts[varidx];

				// The pure literal is made static so that it always evaluates to true
				currLit->setLiteralState( LiteralState::LS_PURE );

				// A pure literal is evaluated without a variable
				currLit->evaluateLiteral( nullptr );
			}

			// Save index of pure variable iff if it is literal of type POS, COMPL or TRUE
			if( firstClauseLitType == LiteralType::LT_COMPL || 
				firstClauseLitType == LiteralType::LT_POS ||
				firstClauseLitType == LiteralType::LT_TRUE )
			{
				this->idxPureVariables_.push_back( varidx );
			}
		}
	}

	return !( idxPureVariables_.empty() ) ;
}

bool cnf::findAlwaysUnsatClauses()
{
	auto idx = 0;
	for( auto cl: this->clauses_ )
	{
		// Check if all of its literals are of FALSE type
		bool found = true;
		auto lits = cl->getLiterals();
		for( auto lit: lits )
		{
			if( lit->getLiteralType() != LiteralType::LT_FALSE )
			{
				found = false;
				break;
			}
		}

		if ( found ) 
		{
			this->idxAlwaysUnsatClauses_.push_back( idx );
		}
		++idx;
	}

	if ( idxAlwaysUnsatClauses_.empty() )
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool cnf::optimizeUnitPropagateClauses()
{
	auto idx = 0;
	for ( auto currClause : this->clauses_ )
	{
		auto optimized = currClause->optimizeUnitPropagate();

		if ( optimized )
		{
			this->idxUnitClauses_.push_back( idx );
		}

		++idx;
	}
	return !( this->idxUnitClauses_.empty() );
}

void cnf::getUnitClauseLiteralInfo( clause const * _unitClause, 
									uint16_t & _idxUnitClauseLiteral,
									LiteralType & _litType )
{
	// For this unit clause, get the literal type and 
	// index of lone POS or COMPL type literal
	for ( auto lit : _unitClause->getLiterals() )
	{
		_litType = lit->getLiteralType();

		if ( ( _litType == LiteralType::LT_POS ||
			   _litType == LiteralType::LT_COMPL ) &&
			   ( lit->getLiteralState() == LiteralState::LS_STATIC || 
			     lit->getLiteralState() == LiteralState::LS_PURE ) )
		{
			break;
		}
		++_idxUnitClauseLiteral;
	}
}

bool cnf::findComplUnitClauses()
{
	bool found = false;

	if( this->idxUnitClauses_.empty() ) return false;

	for( auto i = 0; i < this->idxUnitClauses_.size()-1 ; ++i )
	{
		auto idxFirstUnitClause = this->idxUnitClauses_[i];
		auto firstUnitClause = this->clauses_[idxFirstUnitClause];

		// For this unit clause, get the literal type and 
		// index of lone POS or COMPL type literal
		uint16_t idxFirstUnitClauseLiteral = 0;
		LiteralType firstLiteralType;
		getUnitClauseLiteralInfo( firstUnitClause, idxFirstUnitClauseLiteral, firstLiteralType );

		// Look at subsequent unit clauses and see if its complementary to 
		// the first unit clause (they should have same form for same variable)
		for( auto j = i+1; j < this->idxUnitClauses_.size(); ++j )
		{
			auto idxNextUnitClause = this->idxUnitClauses_[j];
			auto nextUnitClause = this->clauses_[idxNextUnitClause];

			// For this unit clause, get the literal type and 
			// index of lone POS or COMPL type literal
			uint16_t idxNexUnitClausetLiteral = 0;
			LiteralType nextLiteralType;
			getUnitClauseLiteralInfo( nextUnitClause, idxNexUnitClausetLiteral, nextLiteralType );

			// Check if the current pair of unit clauses is complementary
			if( idxFirstUnitClauseLiteral == idxNexUnitClausetLiteral &&
				firstLiteralType != nextLiteralType )
			{
				found = true;
				break;
			}
		}
	
		// Stop as soon as first pair of complimentary unit literals is found
		if (found) break;
	}

	return found;
}

void cnf::evaluateClauses( unsigned int _begin, unsigned int _end, unsigned int _threadId )
{
	bool isSat = true;
	for ( unsigned int i = _begin; i < _end; ++i )
	{
		isSat = isSat && this->clauses_[i]->evaluateClause( this->variables_ );
	}
	this->perThreadSatResults_[_threadId] = this->perThreadSatResults_[_threadId] && isSat;
}

static void parallel_for( unsigned int _threadCnt, 
						  unsigned int _cntElements, 
						  std::function<void ( unsigned int _begin, unsigned int _end, unsigned int _threadId )> _functor,
						  bool _isMultiThreaded = true )
{
	auto elemsPerThread = _cntElements / _threadCnt;
	auto remElems = _cntElements % _threadCnt;

	std::vector<std::thread> workerThreads( _threadCnt );

	if ( _isMultiThreaded )
	{
		// Launch worker threads with assigned elements per thread
		for( unsigned int i = 0; i < _threadCnt; ++i )
		{
			auto begin = i * elemsPerThread;
			workerThreads[i] = std::thread( _functor, begin, begin + elemsPerThread, i );
		}
	}
	else
	{
		for( unsigned  int i = 0; i < _threadCnt; ++i )
		{
			auto begin = i * elemsPerThread;
			_functor( begin, begin + elemsPerThread, i );
		}
	}

	// The remaining elements are processed by current thread
	// and merged with results of thread id 0
	auto begin = _threadCnt * elemsPerThread;
	_functor( begin, begin + remElems, 0 );

	if( _isMultiThreaded )
	{
		// Join threads (waiting for all threads to finish)
		for( auto & workerThread : workerThreads )
		{
			workerThread.join();
		}
	}
}

bool cnf::findFirstSatVariableAssignment( std::string & _firstSatVariableAssignment )
{
	unsigned int threadCnt = std::thread::hardware_concurrency();
	for ( unsigned int i = 0; i < threadCnt; ++i )
	{
		perThreadSatResults_.push_back( true );
	}

	std::vector<bool> variableLogicCombination( this->variables_.size(), true );

	for ( auto varidx = 0; varidx < variables_.size(); ++varidx )
	{
		std::cout << "Variable Id: " << varidx << "\n";
		do
		{
			this->isSat_ = true;

#ifdef _DEBUG
			std::cout << "(";
			for (auto boolval : variableLogicCombination)
			{
				std::cout << boolval << ",";
			}
			std::cout << ")\n";
#endif // _DEBUG		

			// Assign generated logic vector to variables
			auto idx = 0;
			for( auto var: this->variables_ )
			{
				var->setVariableLogicValue( variableLogicCombination[idx] );
				
				if( var->getVariableState() == VariableState::VS_UNASSIGN )
				{
					var->setVariableState ( VariableState::VS_ASSIGN );
				}
				++idx;
			}

			// Evaluate AND of all clauses for the variable assignment in parallel
			parallel_for( threadCnt,
						  static_cast<unsigned int>( this->clauses_.size() ), 
						  [this]( unsigned int begin, unsigned int end, unsigned int threadIdx ){ this->evaluateClauses( begin, end, threadIdx ); } );

			// Merge sat results from all threads
			for( auto thIsSat: this->perThreadSatResults_ )
				this->isSat_ = this->isSat_ && thIsSat;
			
			//// Sequential is very slow
			//for ( auto cl : this->clauses_ )
			//{
			//	this->isSat_ = this->isSat_ && cl->evaluateClause( this->variables_ );
			//}

			// Check if this variable assignment satisfies the CNF expression
			if ( this->isSat_ )
			{
				// The Satisfying Variable Assignment is found
				_firstSatVariableAssignment += "(";
				for ( auto varLogicValue : variableLogicCombination )
				{
					_firstSatVariableAssignment += ( varLogicValue ? "1":"0" );
					_firstSatVariableAssignment += ",";
				}
				_firstSatVariableAssignment += ")";
			}

			if ( !_firstSatVariableAssignment.empty() )
				break;

			// Generate next possible permutations for given logic vector
		}while( std::next_permutation( variableLogicCombination.begin(), variableLogicCombination.end() ) );

		if ( !_firstSatVariableAssignment.empty() )
			break;

		// We keep the logic vector sorted (all false to all true) 
		// so that all of the next possible permutations can be generated.
		// To do this, we set the (N-varidx)th element in logic vector to true
		// As a result, every iteration logic true is shifted from LSB to MSB 
		variableLogicCombination[varidx] = false;
	}

	// Note: The final permutation (all variables true) is generated 
	// but not evaluated in above loop. So we separately evaluate it below
	if ( _firstSatVariableAssignment.empty() )
	{

#ifdef _DEBUG
		std::cout << "(";
		for (auto boolval : variableLogicCombination)
		{
			std::cout << boolval << ",";
		}
		std::cout << ")\n";
#endif // _DEBUG

		// Assign generated logic vector to variables
		auto idx = 0;
		for ( auto var : this->variables_ )
		{
			var->setVariableLogicValue( variableLogicCombination[idx] );
			++idx;
		}

		// Evaluate AND of all clauses for the variable assignment
		for ( auto cl : this->clauses_ )
		{
			this->isSat_ = this->isSat_ && cl->evaluateClause( this->variables_ );
		}

		// Check if this variable assignment satisfies the CNF expression
		if ( this->isSat_ )
		{
			// The Satisfying Variable Assignment is found
			_firstSatVariableAssignment += "(";
			for ( auto varLogicValue : variableLogicCombination )
			{
				_firstSatVariableAssignment += varLogicValue;
				_firstSatVariableAssignment += ",";
			}
			_firstSatVariableAssignment += ")";
		}
	}

	return this->isSat_;
}

bool cnf::optimizeCnfExpression()
{
	bool couldOptimize = false;

	// 1: Pure Variable(literal) optimization 
	bool foundPureVarLit = this->optimizePureVariableLiterals();
	couldOptimize = couldOptimize || foundPureVarLit;

	// 2: Optimize clauses individually (unit propogation)
	auto idx = 0;
	bool couldUnitPropagate = this->optimizeUnitPropagateClauses();
	couldOptimize = couldOptimize || couldUnitPropagate;

	return couldOptimize;
}

// Evaluates CNF expression and returns the first satisfying variable assignment
bool cnf::evaluateSatisfiability( std::string & _firstSatVariableAssignment )
{
	if( this->clauses_.size() == 1 )
	{
		// CNF expression is satisified trivially if it has just one non-empty clause
		this->isSat_ = findFirstSatVariableAssignment( _firstSatVariableAssignment );
	}
	else if( this->clauses_.size() > 1 )
	{
		if ( this->findAlwaysUnsatClauses() )
		{
			// Trivially unsatisifed if it has atleast one clause with all static FALSE type literals
			this->isSat_ = false;

			// The CNF expression is always unsatisfied for this no matter 
			// what logic value combination are assigned to variables
			_firstSatVariableAssignment += "(";
			for( auto var: this->variables_ )
			{
				_firstSatVariableAssignment += "-,";
			}
			_firstSatVariableAssignment += ")";
		}
		else if ( findComplUnitClauses() )
		{
			// Trivially unsatisifed if CNF has atleast one pair of 
			// complementary unit clauses i.e. there is a unit clause 
			// which has for lone variable x the literal x i.e in true form, 
			// and there is another unit clause which has for same lone 
			// variable x the literal !x i.e. in compl form
			this->isSat_ = false;

			// The CNF expression is always unsatisfied for this no matter 
			// what logic value combination are assigned to variables
			_firstSatVariableAssignment += "(";
			for (auto var : this->variables_)
			{
				_firstSatVariableAssignment += "-,";
			}
			_firstSatVariableAssignment += ")";

		}
		else if( !this->idxPureVariables_.empty() )
		{
			// Trivially satisfied if it has atleast one pure 
			// variable (literal) of type POS, COMPL and true
			auto idxLastPureVar = 0;
			auto firstClauseLits = this->clauses_[0]->getLiterals();

			// Begin the variable assignment
			_firstSatVariableAssignment += "(";

			// Fill satisfying logic values for pure variables 
			// and dont cares for non-pure variables
			for( auto idxCurrPureVar : this->idxPureVariables_  )
			{
#ifdef _DEBUG
				assert( this->variables_[idxCurrPureVar]->getVariableState() == VariableState::VS_PURE );
				assert( firstClauseLits[idxCurrPureVar]->getLiteralState() == LiteralState::LS_PURE );
#endif // _DEBUG
				// Fill any dont cares for non-pure variables before current pure variable
				for( auto i = idxLastPureVar; i < idxCurrPureVar; ++i )
				{
					// dont care
					_firstSatVariableAssignment += "-,";
				}

				// Fill logic value that satisfies the current pure variable
				auto pureLitLogicSatValue = firstClauseLits[idxCurrPureVar]->getLiteralSatValue();
				if ( pureLitLogicSatValue == true )
				{
					_firstSatVariableAssignment += "1,";
				}
				else
				{
					_firstSatVariableAssignment += "0,";
				}

				idxLastPureVar = idxCurrPureVar + 1;
			}

			// Fill any dont cares after last pure variable
			for ( auto i = idxLastPureVar; i < this->variables_.size(); ++i )
			{
				_firstSatVariableAssignment += "-,";
			}

			// End the variable assignment
			_firstSatVariableAssignment += ")";

			this->isSat_ = true;
		}
		else
		{
			// Find first satisfiable variable assignment
			this->isSat_ = findFirstSatVariableAssignment( _firstSatVariableAssignment );
		}
	}

	return this->isSat_;
}