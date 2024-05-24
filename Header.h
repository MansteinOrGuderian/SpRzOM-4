#include <iostream>
#include <string>
#include <bitset>
#include <chrono> // for tracking time 
#include <functional> // for tracking time
#include <vector> // for tracking time


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
	//friend std::ostream& operator<<(std::ostream&, const Galois_Field_NB&); // output polynomial as polynomial
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
	
	//static void calculation_of_multiplication_matrix() {
	//	int modulo_p = 2 * size_of_field + 1;
	//	int current_row = 0;
	//	while (current_row < size_of_field) {
	//		int current_column = 0;
	//		while (current_column < size_of_field) {
	//			int two_in_degree_of_rows = two_in_degree_by_modulo_p(current_row, modulo_p);
	//			int two_in_degree_of_columns = two_in_degree_by_modulo_p(current_column, modulo_p);
	//			if ((two_in_degree_of_rows + two_in_degree_of_columns) % modulo_p == 1 || (two_in_degree_of_rows + two_in_degree_of_columns + modulo_p) % modulo_p == 1 || ((modulo_p - two_in_degree_of_rows) + two_in_degree_of_columns) % modulo_p == 1 || ((modulo_p - two_in_degree_of_rows) - two_in_degree_of_columns + modulo_p) % modulo_p == 1)
	//				multiplication_matrix[size_of_field - current_row - 1][size_of_field - current_column - 1] = 1;
	//			current_column++;
	//		}
	//		current_row++;
	//	}
	//}
	static void calculation_of_multiplication_matrix();
};
