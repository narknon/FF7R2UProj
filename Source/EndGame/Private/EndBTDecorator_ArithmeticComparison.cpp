#include "EndBTDecorator_ArithmeticComparison.h"

UEndBTDecorator_ArithmeticComparison::UEndBTDecorator_ArithmeticComparison() {
    this->ValueTypeA = EBTDecorator_ArithmeticComparisonSource::Blackboard;
    this->bUseBlackboardA = true;
    this->bUsePropertyOrFunctionA = false;
    this->bUseLiteralA = false;
    this->LiteralValueA = 0.00f;
    this->Operator = EEndAiMathCmp::Equal;
    this->ValueTypeB = EBTDecorator_ArithmeticComparisonSource::LiteralValue;
    this->bUseBlackboardB = false;
    this->bUsePropertyOrFunctionB = false;
    this->bUseLiteralB = true;
    this->LiteralValueB = 0.00f;
}


