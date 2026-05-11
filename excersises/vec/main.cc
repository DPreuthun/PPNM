#include <iostream>

#include "vec.h"

int main() {

    vec a(1,2,3);
    vec b(4,5,6);

    std::cout << "===== VECTORS =====\n\n";

    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n\n";

    std::cout << "===== OPERATIONS =====\n\n";

    vec c = a + b;
    vec d = a - b;

    std::cout << "a + b = " << c << "\n";
    std::cout << "a - b = " << d << "\n";

    std::cout << "2*a = " << 2*a << "\n";

    std::cout << "\n";

    std::cout << "===== PRODUCTS =====\n\n";

    std::cout
        << "a dot b = "
        << a.dot(b)
        << "\n";

    std::cout
        << "a cross b = "
        << a.cross(b)
        << "\n\n";

    std::cout << "===== NORMS =====\n\n";

    std::cout
        << "|a| = "
        << a.norm()
        << "\n";

    std::cout
        << "|b| = "
        << b.norm()
        << "\n\n";

    std::cout << "===== APPROX =====\n\n";

    vec e(1.0000000001,
          2.0000000001,
          3.0000000001);

    std::cout
        << "approx(a,e) = "
        << (approx(a,e)
            ? "true"
            : "false")
        << "\n";

    return 0;
}