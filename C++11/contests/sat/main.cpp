#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cassert>
#include "cnf.h"
#include "clause.h"
#include "literal.h"
#include "variable.h"

int parseCnfFile(int argc, char *argv[], cnf & _cnfExpression )
{
	if (argc != 2)
	{
		std::cerr << "Please specify name of file as argument" << std::endl;
		return 0;
	}

	std::string filename = argv[1];

#ifdef _DEBUG
	std::string executable = argv[0];
	std::cout << "Executable: " << executable << std::endl;
	std::cout << "Filename: " << filename << std::endl;
#endif // _DEBUG

	std::ifstream ifs;
	ifs.open( filename, std::ios::in );

	if ( !ifs.is_open() )
	{
		std::cout << "Cannot open file " << filename << std::endl;
		return 0;
	}

	bool isFirstClause = true;
	for ( std::string line; std::getline( ifs, line ); )
	{
#ifdef _DEBUG
		std::cerr << line << std::endl;
#endif
		clause *currentClause = nullptr;
		bool isNextLitCompl = false;

		for ( auto nextToken : line )
		{
			if ( nextToken == '(' )
			{
				// start a new clause
				currentClause = new clause( ClauseState::CS_UNRES );
			}
			else if ( nextToken == '0' )
			{
#ifdef _DEBUG
				assert( currentClause != nullptr );
#endif // _DEBUG

				// Start a new literal: static 0 form of x of a variable x
				bool logicalSatValue = false;
				literal *currentLiteral = new literal( LiteralType::LT_FALSE, 
													   LiteralState::LS_STATIC,
													   logicalSatValue,
													   currentClause ) ;

				// Append this literal to current clause
				currentClause->appendLiteral( *currentLiteral );

				// if this is the first clause, create a variable for the cnf expression
				if ( isFirstClause )
				{
					variable *currentVariable = new variable ( logicalSatValue, VariableState::VS_STATIC );
					_cnfExpression.appendVariable( *currentVariable );
				}
			}
			else if ( nextToken == '1' )
			{
#ifdef _DEBUG
				assert( currentClause != nullptr );
#endif // _DEBUG

				bool logicalSatValue;
				LiteralType litType;
				
				if( isNextLitCompl )
				{
					// Start a new literal: represents complementary form !x of a variable x
					logicalSatValue = false;
					litType = LiteralType::LT_COMPL;
					isNextLitCompl = false;
				}
				else
				{
					// Start a new literal: true form x of a variable x
					logicalSatValue = true;
					litType = LiteralType::LT_POS;
				}			

				literal *currentLiteral = new literal( litType,
													   LiteralState::LS_DYNAMIC,
													   logicalSatValue,
													   currentClause ) ;

				// Append this literal to current clause
				currentClause->appendLiteral( *currentLiteral );

				// if this is the first clause, create a variable for the cnf expression
				if( isFirstClause )
				{
					variable *currentVariable = new variable ( logicalSatValue, VariableState::VS_UNASSIGN );
					_cnfExpression.appendVariable( *currentVariable );
				}
			}
			else if ( nextToken == ')' )
			{
#ifdef _DEBUG
				assert( currentClause != nullptr );

				// TBU: what to do with empty clauses
				if ( currentClause->getLiterals().empty() )
				{
					std::cerr << "Empty clause!" << "\n";
				}
#endif // _DEBUG

				// End of current clause : append current clause to the cnf expression
				_cnfExpression.appendClause( *currentClause );

				// All variables added to cnf expression after reading the first clause.
				// No more variables need to be added for any subsequent clauses(literals)
				isFirstClause = false;
			}
			else if (nextToken == '-')
			{
				// Start of -1
				isNextLitCompl = true;
			}
			else if ( nextToken == ',' || nextToken == ' ' )
			{
				// do nothing. skip
			}
			else
			{
#ifdef _DEBUG
				// All other characters are invalid
				std::cerr << "Invalid token: " << nextToken << "\n";
				std::cerr << "Should be either 0, 1, -1, ',', ')', '('" << "\n";
#endif // _DEBUG
				return 0;
			}
		}
	}

	ifs.close();
	return 1;
}

int main(int argc, char *argv[])
{
	bool isSat = false;
	
	cnf cnfExpression;
	std::string firstSatVariableAssignment;

	int ret = parseCnfFile( argc, argv, cnfExpression );
	if( ret == 0 ) exit(0);

	// Optimize the CNF expression. Returns true of atleast one optimization succeeds
	bool coudOptimize = cnfExpression.optimizeCnfExpression();

	// Evaluate satisfiability for the optimized CNF expression
	isSat = cnfExpression.evaluateSatisfiability( firstSatVariableAssignment );

	if (isSat == true)
	{
		std::cout << std::string(argv[1]) << ": " << "Yes, " << firstSatVariableAssignment << "\n";
	}
	else
	{
		std::cout << std::string(argv[1]) << ": " << "No, " << firstSatVariableAssignment << "\n";
	}

	return 0;
}