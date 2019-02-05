#include "literal.h"
#include "variable.h"
#include <cassert>
#include <iostream>

literal::literal( LiteralType _literalType,
				  LiteralState _literalState,
				  bool _literalSatValue,
				  clause * _parentClause ) : literalType_ ( _literalType ),
											 literalState_ ( _literalState ),
											 isLiteralSat_ ( _literalSatValue ),
											 parentClause_ ( _parentClause )
{
#ifdef _DEBUG
	assert( _parentClause != nullptr );
#endif // _DEBUG

	//myClauses_.push_back( _parentClause );
}

literal::~literal()
{
}

LiteralType literal::getLiteralType() const
{
	return this->literalType_;
}

void literal::setLiteralType( LiteralType _literalType )
{
	this->literalType_ = _literalType;
}

LiteralState literal::getLiteralState() const
{
	return this->literalState_;
}

void literal::setLiteralState( LiteralState _literalState )
{
	this->literalState_ = _literalState;
}

bool literal::getLiteralSatValue() const
{
	return this->isLiteralSat_;
}

void literal::setLiteralSatValue(bool _literalSatValue)
{
	this->isLiteralSat_ = _literalSatValue;
}

//void literal::addClause( clause * _parentClause )
//{
//	this->myClauses_.push_back( _parentClause );
//}

//variable * literal::getParentVariable() const
//{
//	return this->myParentVariable_;
//}
//
//void literal::setParentVariable(variable & _variable)
//{
//	this->myParentVariable_ = &_variable;
//}

bool literal::evaluateLiteral( variable const * _parentVariable )
{
//	if (this->myParentVariable_ != nullptr)
//	{
//		bool variableValue = this->myParentVariable_->getVariableValue();
//
//		if (this->literalType_ == LiteralFormType::LFT_POS)
//		{
//			this->isLiteralSat_ = variableValue;
//		}
//		else if (this->literalType_ == LiteralFormType::LFT_COMPL)
//		{
//			this->isLiteralSat_ = !variableValue;
//		}
//		else if (this->literalType_ == LiteralFormType::LFT_TRUE)
//		{
//			this->isLiteralSat_ = true;
//		}
//		else if (this->literalType_ == LiteralFormType::LFT_FALSE)
//		{
//			this->isLiteralSat_ = false;
//		}
//	}
//	else
//	{
//#ifdef _DEBUG
//		std::cerr << "\nError: Variable for this literal not allocated";
//#endif // _DEBUG
//	}

	if ( this->literalState_ == LiteralState::LS_DYNAMIC )
	{
		// Literal is to be evaluated for a variable
		bool variableLogicValue = _parentVariable->getVariableLogicValue();

		if (this->literalType_ == LiteralType::LT_POS)
		{
			this->isLiteralSat_ = variableLogicValue;
		}
		else if (this->literalType_ == LiteralType::LT_COMPL)
		{
			this->isLiteralSat_ = !variableLogicValue;
		}
	}
	else if ( this->literalState_ == LiteralState::LS_STATIC || 
			  this->literalState_ == LiteralState::LS_PURE )
	{
		// Literal has a static(implied) logical value and will not be evaluated for any variable
		if ( this->literalType_ == LiteralType::LT_POS || 
			 this->literalType_ == LiteralType::LT_TRUE )
		{
			this->isLiteralSat_ = true;
		}
		else if ( this->literalType_ == LiteralType::LT_COMPL || 
				  this->literalType_ == LiteralType::LT_FALSE )
		{
			this->isLiteralSat_ = false;
		}
	}
	else if ( this->literalState_ == LiteralState::LS_UNKNOWN )
	{
#ifdef _DEBUG
		std::cerr << "Cannot evaluate literal as its state is unknown!" << "\n";
#endif // _DEBUG
	}

	return this->isLiteralSat_;
}