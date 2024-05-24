#include "Header.h"

Galois_Field_NB Galois_Field_NB::convert_line_to_array_of_polynomial_coefficients(const std::string& line_with_coefficients, bool if_line_binary) {
	if (if_line_binary == 1) {
		std::string binary_line_with_each_coefficients = line_with_coefficients;
		unsigned int line_with_coefficients_length = binary_line_with_each_coefficients.length();
		if (line_with_coefficients_length > size_of_field)
			throw std::exception("Unsupported length. Entered line is too big!"); // or maybe good idea in this case make each coefficients = 0
		while (line_with_coefficients_length < size_of_field) {
			binary_line_with_each_coefficients = '0' + binary_line_with_each_coefficients; // if some coefficients didn't entered, set them 0
			line_with_coefficients_length++;
		}
		unsigned int current_index = 0;
		while (current_index < line_with_coefficients_length) { // checking is symbols in string are 0 or 1
			if (binary_line_with_each_coefficients[current_index] != '1' && binary_line_with_each_coefficients[current_index] != '0')
				throw std::exception("Unsupported symbol in line!");
			current_index++;
		}
		return Galois_Field_NB(std::bitset<size_of_field>(binary_line_with_each_coefficients));
	}
	else {
		std::string binary_line_with_each_coefficients;
		unsigned int line_with_coefficients_length = line_with_coefficients.length();
		unsigned int current_index = 0;
		while (current_index < line_with_coefficients_length) {
			int current_hex_symbol_to_int = 0;
			if (line_with_coefficients[current_index] >= '0' && line_with_coefficients[current_index] <= '9') // numbers 0...9
				current_hex_symbol_to_int = line_with_coefficients[current_index] - '0'; // numbers 0...9
			else if (line_with_coefficients[current_index] >= 'a' && line_with_coefficients[current_index] <= 'f') // letters a...f
				current_hex_symbol_to_int = line_with_coefficients[current_index] - 'a' + 10;
			else
				throw std::exception("Unsupported symbol in line!");
			for (int index = 3; index >= 0; index--) //convert hex value to binary; f == 1111 (most possible 4 bit)
				binary_line_with_each_coefficients += ((current_hex_symbol_to_int & (1 << index)) ? '1' : '0'); //check each bit of binary_code_of_hex_letter from most significant to least significant
			current_index++;
		}
		//int index_of_first_significant_digit = binary_line_with_each_coefficients.find_last_not_of('0');
		//if (index_of_first_significant_digit != -1)  //deleting extra nulls from begin. if they exict
		//	binary_line_with_each_coefficients.erase(binary_line_with_each_coefficients.begin(), binary_line_with_each_coefficients.begin() + index_of_first_significant_digit);
		unsigned int binary_line_with_each_coefficients_length = binary_line_with_each_coefficients.length();
		if (binary_line_with_each_coefficients_length > size_of_field)
			throw std::exception("Unsupported length. Entered line is too big!"); // or maybe good idea in this case make each coefficients = 0
		while (binary_line_with_each_coefficients_length < size_of_field) {
			binary_line_with_each_coefficients = '0' + binary_line_with_each_coefficients; // if some coefficients didn't entered, set them 0
			binary_line_with_each_coefficients_length++;
		}
		return Galois_Field_NB(std::bitset<size_of_field>(binary_line_with_each_coefficients));
	}
}

Galois_Field_NB::Galois_Field_NB(const std::string& line_with_coefficients, bool if_line_binary) {
	*this = convert_line_to_array_of_polynomial_coefficients(line_with_coefficients, if_line_binary);
}

std::string Galois_Field_NB::return_polynomial_as_hex_string() const {
	std::string polynomial_as_hex_string;
	unsigned int current_index_of_bit = 0;
	while (current_index_of_bit < size_of_field) {
		int current_hex_symbol_in_int = 0;
		unsigned int current_index_in_four_bit_subsequence = 0;
		while (current_index_in_four_bit_subsequence < 4 && (current_index_of_bit + current_index_in_four_bit_subsequence) < size_of_field) { // while we are inside the number
			if (array_of_coefficients_of_polynomial.test(current_index_of_bit + current_index_in_four_bit_subsequence)) // check, if under consideration position of binary string setted to 1
				current_hex_symbol_in_int = (current_hex_symbol_in_int | (1 << current_index_in_four_bit_subsequence)); // increasing current value, if bit was equal to 1
			current_index_in_four_bit_subsequence++;
		}
		char current_hex_digit;
		if (current_hex_symbol_in_int >= 0 && current_hex_symbol_in_int <= 9)
			current_hex_digit = (char)current_hex_symbol_in_int + '0'; // 1...9
		else
			current_hex_digit = (char)current_hex_symbol_in_int + 'a' - 10; // a...f
		polynomial_as_hex_string = current_hex_digit + polynomial_as_hex_string;
		current_index_of_bit += 4; // 4 bit == 1 hex digit
	}
	long int index_of_first_significant_digit = polynomial_as_hex_string.find_first_not_of('0'); // index, before which delete 0
	if (index_of_first_significant_digit != -1) // if not empty string
		polynomial_as_hex_string.erase(polynomial_as_hex_string.begin(), polynomial_as_hex_string.begin() + index_of_first_significant_digit);
	else
		polynomial_as_hex_string = "0";
	return polynomial_as_hex_string;
}

std::string Galois_Field_NB::return_polynomial_as_binary_string() const {
	std::string polynomial_as_binary_string;
	int current_position = size_of_field - 1;
	while (current_position >= 0) {
		polynomial_as_binary_string += (array_of_coefficients_of_polynomial.test(current_position) ? '1' : '0');
		current_position--; // using inline in bitset function test(), which return 1, if bit in current_position set to 1
	}
	return polynomial_as_binary_string;
}


//std::ostream& operator<< (std::ostream& out, const Galois_Field_NB& Data) { // check later if is changed to reverse order 
//	out << "Polynomial is:\t"; // << Data.array_of_coefficients_of_polynomial;
//	int degree = Data.size_of_field - 1;
//	int index_of_coefficient = Data.size_of_field - 1;
//	while (degree >= 0) {
//		out << Data.array_of_coefficients_of_polynomial[index_of_coefficient] << " * x^" << degree << (degree != 0 ? " + " : "\n\n");
//		degree--; index_of_coefficient--;
//	}
//	return out;
//}

Galois_Field_NB Galois_Field_NB::operator+(const Galois_Field_NB& Right_polynomial) {
	Galois_Field_NB result_of_summing = this->array_of_coefficients_of_polynomial ^ Right_polynomial.array_of_coefficients_of_polynomial; // ^ is XOR == + mod 2
	return result_of_summing;
}

unsigned int Galois_Field_NB::trace() {
	unsigned int trace = (this->array_of_coefficients_of_polynomial.count()) % 2; // trace in F_2 can be 0 or 1
	return trace; // in Field F_p with Normal Basis trace of element is just sum of its components by modulo p
}

Galois_Field_NB Galois_Field_NB::square_polynomial() {
	Galois_Field_NB square_polynomial = *this; // cyclic right shift
	square_polynomial = ((square_polynomial.array_of_coefficients_of_polynomial >> 1) | (square_polynomial.array_of_coefficients_of_polynomial << (size_of_field - 1)));
	return square_polynomial; // shift right "vector" left, and bitwise OR with right "vector", shifted on (size_of_field - 1) -> In summary squaring is cyclic shift right
}


int mod_pow2(int exponent, int mod) {
	int result = 1;
	for (int i = 0; i < exponent; ++i) {
		result = (result << 1) % mod;
	}
	return result;
}

std::vector<std::bitset<173>> Galois_Field_NB::calculation_of_multiplication_matrix() {

}

Galois_Field_NB Galois_Field_NB::polynomimal_to_power(const Galois_Field_NB& degree) { // degree is number
	Galois_Field_NB polynomial_to_power = *this;
	Galois_Field_NB result_of_getting_to_power("1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 0); // neutral element by multiplication is 1, 1 in NB is (1, 1, ... 1, 1) 173 times == 1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
	unsigned int current_index = 0; 
	while (current_index < size_of_field) {
		if (degree.array_of_coefficients_of_polynomial.test(current_index) == 1)
			result_of_getting_to_power = polynomial_to_power * result_of_getting_to_power;
		polynomial_to_power = polynomial_to_power.square_polynomial();
		current_index++;
	}
	return result_of_getting_to_power;
}

bool Galois_Field_NB::operator==(const Galois_Field_NB& Right_polynomial) {
	return (this->array_of_coefficients_of_polynomial == Right_polynomial.array_of_coefficients_of_polynomial);
}

bool Galois_Field_NB::operator!=(const Galois_Field_NB& Right_polynomial) {
	return !(*this == Right_polynomial);
}

Galois_Field_NB Galois_Field_NB::cyclic_shift_right_coefficients_of_polynomial(unsigned int number_of_position_to_shift) {
	Galois_Field_NB result_of_shifting = *this;
	result_of_shifting = ((result_of_shifting.array_of_coefficients_of_polynomial >> number_of_position_to_shift) | (result_of_shifting.array_of_coefficients_of_polynomial << (size_of_field - number_of_position_to_shift)));
	return result_of_shifting;
}


Galois_Field_NB Galois_Field_NB::operator*(const Galois_Field_NB& Right_polynomial) { // (u <<< i) * L * (v <<< i)^T
	std::vector<std::bitset<size_of_field>> multiplication_matrix = calculation_of_multiplication_matrix();
	Galois_Field_NB result_of_multiplication; 
	unsigned int current_index = 0;
	while (current_index < size_of_field) {
		Galois_Field_NB left_temp_polynomial, right_temp_polynomial, left_mult_on_multiplication_matrix;
		left_temp_polynomial.array_of_coefficients_of_polynomial = ((this->array_of_coefficients_of_polynomial << current_index) | (this->array_of_coefficients_of_polynomial >> (size_of_field - current_index)));
		unsigned int current_row = 0;
		while (current_row < size_of_field){ // u * L
			if (left_temp_polynomial.array_of_coefficients_of_polynomial.test(current_row) == 1) {
				unsigned int current_column = 0;
				while (current_column < size_of_field) {
					if (multiplication_matrix[current_row].test(current_column) == 1) // if bit 1 was in u and in L matrix -> in  u * L also set 1
						left_mult_on_multiplication_matrix.array_of_coefficients_of_polynomial.flip(current_column);
					current_column++;
				}
			}
			current_row++;
		}
		right_temp_polynomial.array_of_coefficients_of_polynomial = ((Right_polynomial.array_of_coefficients_of_polynomial << current_index) | (Right_polynomial.array_of_coefficients_of_polynomial >> (size_of_field - current_index)));
		unsigned int current_row = 0;  
		while (current_row < size_of_field) {
			if (left_mult_on_multiplication_matrix.array_of_coefficients_of_polynomial[current_row] == 1 && right_temp_polynomial.array_of_coefficients_of_polynomial[current_row] == 1)
				result_of_multiplication.array_of_coefficients_of_polynomial.flip(current_row);
			current_row++;
		}
		current_index++;
	}
	return result_of_multiplication;
}