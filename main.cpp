#include "Header.h"

Multiplication_matrix Galois_Field_NB::multiplication_matrix(size_of_field);
int main() {
	Galois_Field_NB::calculation_of_multiplication_matrix();
	Galois_Field_NB a("15795109c9b0e4f4f2f6ef8b1cbadc4adadaefcafff", 0); // 43
	Galois_Field_NB b("0edf130b2a5bf30a816c4131bcdb4523caef5480134", 0); // 43
	Galois_Field_NB c("16cdef39cbdb4523caef5480134edf130b2a5bf30a8", 0); // 43 * 4 = 172
	
	std::cout << (a + b).return_polynomial_as_hex_string() << "\n\n"; // +
	std::cout << (a * b).return_polynomial_as_hex_string() << "\n\n"; // +
	std::cout << (a.square_polynomial()).return_polynomial_as_hex_string() << "\n\n"; // +
	std::cout << (a.polynomimal_to_power(c)).return_polynomial_as_hex_string() << "\n\n"; // +
}