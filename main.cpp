#include "Header.h"

Multiplication_matrix Galois_Field_NB::multiplication_matrix(size_of_field);
int main() {
	Galois_Field_NB::calculation_of_multiplication_matrix();
	Galois_Field_NB a("15795109c9b0e4f4f2f6ef8b1cbadc4adadaefcafff", 0); // 43
	Galois_Field_NB b("0edf130b2a5bf30a816c4131bcdb4523caef5480134", 0); // 43
	Galois_Field_NB c("16cdef39cbdb4523caef5480134edf130b2a5bf30a8", 0); // 43 * 4 = 172
	
	//std::cout << "Checking the properties:\n";
	//std::cout << "First property:\t\t(a+b)*c = a*c + b*c\n";
	//Galois_Field_NB a_sum_b = a + b;
	//Galois_Field_NB a_sum_b_mult_c = a_sum_b * c;
	//Galois_Field_NB a_mult_c = a * c;
	//Galois_Field_NB b_mult_c = b * c;
	//Galois_Field_NB a_mult_c_sum_b_mult_c = a_mult_c + b_mult_c;
	//std::cout << a_sum_b_mult_c.return_polynomial_as_hex_string() << "\n\n";
	//std::cout << a_mult_c_sum_b_mult_c.return_polynomial_as_hex_string() << "\n\n";

	//std::cout << "Second property:\ta^(2^(m-1)) = 1\n";
	//std::bitset <173> degree = std::bitset<173>().set(); // all bits are 1 (max possible value)
	//Galois_Field_NB polynimial_degree(degree);
	//std:: cout << (a.polynomimal_to_power(polynimial_degree)).return_polynomial_as_hex_string();

	std::cout << "SUM:\t" << (a + b).return_polynomial_as_hex_string() << "\n\n";
	std::cout << "Multiply:\t" << (a * b).return_polynomial_as_hex_string() << "\n\n";
	std::cout << "Square:\t" << (a.square_polynomial()).return_polynomial_as_hex_string() << "\n\n";
	std::cout << "Trace:\t" << a.trace() << "\n\n";
	std::cout << "Inverse to a:\t" << (a.inverse_element().return_polynomial_as_hex_string()) << "\n\n";
	std::cout << "Degree:\t" << (a.polynomimal_to_power(c)).return_polynomial_as_hex_string() << "\n\n";

}