#include "nstring.h"

void print_joined()
{
    std::vector<std::string> v = {"foo", "bar", "baz"};
    std::string s = absl::StrJoin(v, "-");
    std::cout << "Joined string: " << s << "\n";
}