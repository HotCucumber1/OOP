#pragma once
#include "Computable.h"
#include <memory>

class Function : public Computable
{
public:
	void SetValue(std::shared_ptr<Computable> value);
	void SetExpression(
		std::shared_ptr<Computable> arg1,
		std::shared_ptr<Computable> arg2,
		char operation
	);
	double GetValue() const override;

private:
	std::shared_ptr<Computable> m_value = nullptr;
	std::shared_ptr<Computable> m_arg1 = nullptr;
	std::shared_ptr<Computable> m_arg2 = nullptr;
	char m_operation = '.';
};
