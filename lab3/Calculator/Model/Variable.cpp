#include "Variable.h"


void Variable::SetValue(double value)
{
	m_value = value;
}

void Variable::SetValue(const Variable& value)
{
	m_value = value.GetValue();
}

double Variable::GetValue() const
{
	return m_value;
}