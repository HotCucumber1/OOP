#pragma once
#include "Computable.h"
#include <cmath>

class Variable : public Computable
{
public:
	void SetValue(double value);
	void SetValue(const Variable& value);
	double GetValue() const override;

private:
	double m_value = std::nan("");
};
