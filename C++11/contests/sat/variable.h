#pragma once

// Variable State
enum VariableState
{
	VS_UNASSIGN,	// Unassigned boolean variable (default)
	VS_ASSIGN,		// Assigned boolean variable
	VS_PURE,		// A variable is pure(static), if it has same form of literal representation in all the clauses
	VS_STATIC		// Variable value remains static
};

class variable
{
	// A variable has only two possible values: either true or false
	bool logicValue_;

	// Variable State
	VariableState variableState_;

public:

	// Default variable logic value is 0 and state of a variable is unassigned
	variable( bool _logicValue = false
			, VariableState _variableState = VariableState::VS_UNASSIGN );

	~variable();

	bool getVariableLogicValue() const;
	void setVariableLogicValue( bool _value );

	VariableState getVariableState() const;
	void setVariableState( VariableState _variableState );

	void evaluateVariableLogicValue();
};