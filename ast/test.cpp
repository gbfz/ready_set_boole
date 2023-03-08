#include "ASTree.hpp"
#include <unistd.h>

bool eval_formula(const std::string& formula)
{
	std::optional<ast::tree> maybeTree = ast::generateTree(formula);
	if (!maybeTree)
	{
		std::cerr << "Invalid formula: " << formula << '\n';
		return {};
	}
	printTree(*maybeTree);
	return maybeTree->exec();
}

#include <iomanip>

void test(const std::string& formula, std::optional<bool> expected = std::nullopt)
{
	using namespace std;
	auto maybeRoot = ast::generateTree(formula);
	if (!maybeRoot)
	{
		cerr << "Invalid formula " << quoted(formula) << '\n';
		return;
	}
	bool r = eval_formula(formula);
	if (expected && r != *expected)
	{
		cerr << "Invalid exectution of " << quoted(formula) << '\n';
		cerr << "expected: " << *expected << '\n';
		cerr << "actual  : " << r << "\n\n";
		return;
	}
	cout << quoted(formula) << " ok, exec -> " << boolalpha << r << "\n\n";
}

int main()
{
	// test("10&", false);
	// test("10=", false);
	// test("1011||=", true);
	// test("0!1^", false);
	// test("1!0|", false);
	// test("1!0!|", true);
	// test("1!0!0&|", false);
	// test("10!^0&", false);
	// test("1!!01!1!||^!1=");//, true);
	// test("1!!0|1!1!|^!1=");//, true);
	// test("1!!00!1!||&1|1|1=0!!^");//, true);
	// test("1!!00!1!||&1|1|1=0!!^11||");//, true);
	test("AB^C^D&A=B>");
	// test("1!!1^!", true);
	// test("aboba");
	// test("01||");
}
