#include <iostream>
#include <string>
#include <bitset>
#include <chrono> // for tracking time 
#include <functional> // for tracking time
#include <vector> // for tracking time


double MeasureTime(std::function<void()> operation, unsigned int amount_of_measurements);
const int size_of_matrix = 173;
using Multiplication_matrix = std::vector<std::bitset<size_of_matrix>>;
unsigned int two_in_degree_by_modulo_p(unsigned int degree, unsigned int modulo_p);

struct Galois_Field_NB {
private:
	static const int size_of_field = 173;
	std::bitset<size_of_field> array_of_coefficients_of_polynomial;
	static Multiplication_matrix multiplication_matrix;
public:
	Galois_Field_NB() : array_of_coefficients_of_polynomial{ 0 } {}; // default constructor, coefficients of polynomial is 0 
	Galois_Field_NB(const std::bitset<size_of_field>& entered_coefficients) : array_of_coefficients_of_polynomial(entered_coefficients) {};
	Galois_Field_NB(const std::string& line_of_coefficients, bool if_binary_string_or_hex); // binary = 1, hex = 0
	static Galois_Field_NB convert_line_to_array_of_polynomial_coefficients(const std::string&, bool if_binary_string_or_hex); // binary = 1, hex = 0
	friend std::ostream& operator<<(std::ostream&, const Galois_Field_NB&); // output polynomial as polynomial
	std::string return_polynomial_as_hex_string() const;
	std::string return_polynomial_as_binary_string() const;
	unsigned int trace();
	Galois_Field_NB square_polynomial();
	Galois_Field_NB operator+(const Galois_Field_NB&);
	Galois_Field_NB operator*(const Galois_Field_NB&);
	bool operator==(const Galois_Field_NB&);
	bool operator!=(const Galois_Field_NB&);
	Galois_Field_NB cyclic_shift_right_coefficients_of_polynomial(unsigned int number_of_position_to_shift);

	Galois_Field_NB polynomimal_to_power(const Galois_Field_NB& degree);
	Galois_Field_NB inverse_element();
	static void calculation_of_multiplication_matrix();
};
