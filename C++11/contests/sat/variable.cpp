#include "variable.h"

variable::variable( bool _logicValue,
					VariableState _variableState ) : logicValue_ ( _logicValue ),
													 variableState_ ( _variableState )
{
}

variable::~variable()
{
}

bool variable::getVariableLogicValue() const
{
	return this->logicValue_;
}

void variable::setVariableLogicValue(bool _logicValue)
{
	this->logicValue_ = _logicValue;
}

VariableState variable::getVariableState() const
{
	return this->variableState_;
}

void variable::setVariableState(VariableState _variableState)
{
	this->variableState_ = _variableState;
}

void variable::evaluateVariableLogicValue()
{
	if( this->variableState_ == VariableState::VS_STATIC || 
		this->variableState_ == VariableState::VS_PURE )
	{
	}
	else if ( this->variableState_ == VariableState::VS_ASSIGN ||
			  this->variableState_ == VariableState::VS_PURE)
	{

	}
}
