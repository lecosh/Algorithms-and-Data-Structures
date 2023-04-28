#define _CRT_SECURE_NO_WARNINGS
#define _OPEN_SYS_ITOA_EXT
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <math.h>

#define MAX_SIZE 2500
#define MAX_NUMBER_SIZE 25

enum STATES {
	INCORRECT_STRING,
	CORRECT_STRING
};

struct node{
	char operation;
	struct node* next_ptr;
};


char top(struct node** top_ptr);

void push(struct node** top_ptr, const char sign);

void pop(struct node** top_ptr);

int priority(const char sign);

void reverse_polish_notation(char* input);

void calculate(char* input);

int copy_number_to_output(char* src, char* dst);

void copy_sign_to_output(const char operation, char* dst);

void delete_braces(struct node** top_ptr, char* dst);

void move_higher_operations(struct node** top_ptr, char* dst, const char sign);

void move_others_operations(struct node** top_ptr, char* dst);

int check_input(char*);

int find(const char);

char* get_dynamic_array(const int);

char* delete_spaces(char*);

char* sum(char*, char*);

char* get_number_from_string(char*, int);

BOOL hasPoint(char*);

void ftoa(double n, char* out);

void modify_otput(char*, char*, const int, const int, char*);

char* substraction(char*, char*);

char* division(char*, char*);

char* mod(char*, char*);

char* power(char*, char*);

char* multiply(char*, char*);

void reverse(char*);

void execute_operation(const char, char*, int);

char* add_number_for_minus(char*);

int main(int argc, char* argv[]) {
	char* input = get_dynamic_array(MAX_SIZE);
	if (argc == 1) {
		printf("Enter an arithmetic expression:\n>> ");
		if (scanf("%[^\n]%*c", input) == 0) {
			printf("Scanf error");
			exit(EXIT_FAILURE);
		}
		input = delete_spaces(input);
		if (!check_input(input)){
			printf("Error input\n");
			exit(EXIT_FAILURE);
		}
		else {
			reverse_polish_notation(input);
		}

	}
	else if (argc == 2) {
		printf("%s - argv\n", argv[1]);
		if (!check_input(argv[1])) {
			
			printf("Error input\n");
			exit(EXIT_FAILURE);
		}
		reverse_polish_notation(argv[1]);

	}
	else if (argc > 2) {
		printf("Error input\n");
	}
	
}

char* add_number_for_minus(char* input) {
	char* buffer = get_dynamic_array(strlen(input) + 100);
	for (int i = 0; i < strlen(input); i++) {
		if (input[i] == '-' && input[i + 1] == '(') {
			if ( (i >= 1 && !isdigit(input[i - 1]) && input[i - 1] != ')' ) || i < 1) {
				strcpy(&buffer[strlen(buffer)], "(-1)*");
			}
			else {
				strncpy(&buffer[strlen(buffer)], &input[i], 1);
			}
		}
		else {
			strncpy(&buffer[strlen(buffer)], &input[i], 1);
		}
	}

	return buffer;
}


int priority(const char sign) {
	switch (sign){
	case '*':
		return 3;
	case '/':
		return 3;
	case '%':
		return 3;
	case '-':
		return 2;
	case '+':
		return 2;
	case '(':
		return 1;
	case '^':
		return 4;
	}
	return EXIT_SUCCESS;
}

void reverse_polish_notation(char* input) {
	char* output_string = get_dynamic_array(MAX_SIZE * 2);
	input = add_number_for_minus(input);
	struct node* newStack = NULL;
	const int size = strlen(input);
	for (int i = 0; i < size; i++) {
		if (input[i] == '(') {
			if (input[i + 1] == '-') {
				strcpy(&output_string[strlen(output_string)], "-");
				i += copy_number_to_output(&input[i + 2], output_string) + 2;
			}
			else {
				push(&newStack, input[i]);
			}
		}
		else if (input[i] == ')') {
			delete_braces(&newStack, output_string);
			//input++;
		}
		else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^' || input[i] == '%') {
			if (priority(top(&newStack)) < priority(input[i])) {
				push(&newStack, input[i]);
			}
			else {
				move_higher_operations(&newStack, output_string, input[i]);
				push(&newStack, input[i]);
			}
		}
		else if (isdigit(input[i])) {
			i += copy_number_to_output(&input[i], output_string) - 1;
		}
	}
	move_others_operations(&newStack, output_string);
	calculate(output_string);
}

void calculate(char* input) {
	int i = 0;
	BOOL calcFlag = FALSE;
	while (i < (int)strlen(input)) {
		if (input[i] == '+' && !calcFlag) {
			execute_operation('+', input, i);
			calcFlag = TRUE;
		}
		if (input[i] == '-' && input[i + 1] == ' ' && !calcFlag) {
			execute_operation('-', input, i);
			calcFlag = TRUE;
		}

		if (input[i] == '*' && !calcFlag) {
			execute_operation('*', input, i);
			calcFlag = TRUE;
		}

		if (input[i] == '/' && !calcFlag) {
			execute_operation('/', input, i);
			calcFlag = TRUE;
		}

		if (input[i] == '%' && !calcFlag) {
			execute_operation('%', input, i);
			calcFlag = TRUE;
		}

		if (input[i] == '^' && !calcFlag) {
			execute_operation('^', input, i);
			calcFlag = TRUE;
		}
		i++;
		if (calcFlag) {
			i = 0;
			calcFlag = FALSE;
		}
		
	}
	printf("%s", input);
}

void execute_operation(const char operation, char* input, int index) {
	int j = index;
	j -= 2;
	char* a = get_number_from_string(input, j);
	j -= strlen(a);
	char* b = get_number_from_string(input, j - 1);
	j -= strlen(b);
	char* buffer = get_dynamic_array(MAX_SIZE);
	switch (operation)
	{
	case '+': {
		modify_otput(input, buffer, index, j, sum(a, b));
		break;
	}
	case '-': {
		modify_otput(input, buffer, index, j, substraction(b, a));
		break;
	}
	case '*': {
		modify_otput(input, buffer, index, j, multiply(b, a));
		break;
	}
	case '/': {
		modify_otput(input, buffer, index, j, division(b, a));
		break;
	}
	case '%': {
		modify_otput(input, buffer, index, j, mod(b, a));
		break;
	}
	case '^': {
		modify_otput(input, buffer, index, j, power(b, a));
		break;
	}
	default:
		break;
	}
}

void modify_otput(char* input, char* buffer, const int index, const int index_start, char* value) {
	strncpy(buffer, input, index_start);
	strncpy(&buffer[strlen(buffer)], value, strlen(value));
	strncpy(&buffer[strlen(buffer)], &input[index + 1], strlen(input) - index);
	memset(input, 0x00, sizeof(char) * strlen(input));
	strcat(input, buffer);
	free(buffer);
}

BOOL hasPoint(char* number) {
	int size = strlen(number);
	for (int i = 0; i < size; i++) {
		if (number[i] == '.') {
			return TRUE;
		}
	}
	return FALSE;
}

char* sum(char* a, char* b) {
	long long int aI = 0;
	long long int bI = 0;
	double aF = 0.0;
	double bF = 0.0;
	double resultF = 0.0;
	long long int resultI = 0;
	char* res = get_dynamic_array(MAX_NUMBER_SIZE);
	if (hasPoint(a)) {
		aF = atof(a);
	}
	else {
		aI = atol(a);
	}
	if (hasPoint(b)) {
		bF = atof(b);
	}
	else {
		bI = atol(b);
	}
	if (strlen(a) >= 19 || strlen(b) >= 19) {
		char* ptr;
		unsigned long long int aL = strtoull(a, &ptr, 10);
		unsigned long long int bL = strtoull(b, &ptr, 10);
		unsigned long long int resl = aL + bL;
		_ui64toa(resl, res, 10);
		return res;
	}
	if (hasPoint(a) && hasPoint(b)) {
		resultF = aF + bF;
		ftoa(resultF, res);
		return res;
	}
	else if (hasPoint(a) && !hasPoint(b)) {
		resultF = aF + (double)bI;
		ftoa(resultF, res);
		return res;
	}
	else if (!hasPoint(a) && hasPoint(b)) {
		resultF = (double)aI + bF;
		ftoa(resultF, res);
		return res;
	}
	else {
		resultI = aI + bI;	
		_i64toa(resultI, res, 10);
		return res;
	}
	
}

char* substraction(char* a, char* b) {
	long long int aI = 0;
	long long int bI = 0;
	double aF = 0.0;
	double bF = 0.0;
	double resultF = 0.0;
	long long int resultI = 0;
	char* res = get_dynamic_array(MAX_NUMBER_SIZE);
	if (hasPoint(a)) {
		aF = atof(a);
	}
	else {
		aI = atol(a);
	}
	if (hasPoint(b)) {
		bF = atof(b);
	}
	else {
		bI = atol(b);
	}
	if (strlen(a) >= 19 || strlen(b) >= 19) {
		char* ptr;
		unsigned long long int aL = strtoull(a, &ptr, 10);
		unsigned long long int bL = strtoull(b, &ptr, 10);
		unsigned long long int resl = aL - bL;
		_ui64toa(resl, res, 10);
		return res;
	}
	if (hasPoint(a) && hasPoint(b)) {
		resultF = aF - bF;
		ftoa(resultF, res);
		return res;
	}
	else if (hasPoint(a) && !hasPoint(b)) {
		resultF = aF - (double)bI;
		ftoa(resultF, res);
		return res;
	}
	else if (!hasPoint(a) && hasPoint(b)) {
		resultF = (double)aI - bF;
		ftoa(resultF, res);
		return res;
	}
	else {
		resultI = aI - bI;
		_i64toa(resultI, res, 10);
		return res;
	}
}

char* division(char* a, char* b) {
	long long int aI = 0;
	long long int bI = 0;
	double aF = 0.0;
	double bF = 0.0;
	double resultF = 0.0;
	long long int resultI = 0;
	
	char* res = get_dynamic_array(MAX_NUMBER_SIZE);
	if (hasPoint(a)) {
		aF = atof(a);
	}
	else {
		aI = atol(a);
	}
	if (hasPoint(b)) {
		bF = atof(b);
	}
	else {
		bI = atol(b);
	}
	if (hasPoint(a) && hasPoint(b)) {
		if (bF == 0.0) {
			printf("Division by zero. Error");
			exit(EXIT_FAILURE);
		}
		resultF = aF / bF;
		ftoa(resultF, res);
		return res;
	}
	else if (hasPoint(a) && !hasPoint(b)) {
		if (bI == 0) {
			printf("Division by zero. Error");
			exit(EXIT_FAILURE);
		}
		resultF = aF / (double)bI;
		ftoa(resultF, res);
		return res;
	}
	else if (!hasPoint(a) && hasPoint(b)) {
		if (bF == 0.0) {
			printf("Division by zero. Error");
			exit(EXIT_FAILURE);
		}
		resultF = (double)aI / bF;
		ftoa(resultF, res);
		return res;
	}
	else {
		if (bI == 0) {
			printf("Division by zero. Error");
			exit(EXIT_FAILURE);
		}
		resultI = aI / bI;
		_i64toa(resultI, res, 10);
		return res;
	}
}

char* mod(char* a, char* b) {
	long long int aI = 0;
	long long int bI = 0;
	long long int resultI = 0;
	char* res = get_dynamic_array(MAX_NUMBER_SIZE);
	aI = atol(a);
	bI = atol(b);
	if (bI == 0) {
		printf("Division by zero. Error.");
		exit(EXIT_SUCCESS);
	}
	resultI = aI % bI;
	_i64toa(resultI, res, 10);
	return res;
}

char* power(char* a, char* b) {
	double aI = 0.0;
	double bI = 0.0;
	double resultI = 0.0;
	char* res = get_dynamic_array(MAX_NUMBER_SIZE);
	aI = atof(a);
	bI = atof(b);
	resultI = pow(aI, bI);
	ftoa(resultI, res);
	return res;
}

char* multiply(char* a, char* b) {
	long long int aI = 0;
	long long int bI = 0;
	double aF = 0.0;
	double bF = 0.0;
	double resultF = 0.0;
	long long int resultI = 0;
	char* res = get_dynamic_array(MAX_NUMBER_SIZE);
	if (hasPoint(a)) {
		aF = atof(a);
	}
	else {
		aI = atol(a);
	}
	if (hasPoint(b)) {
		bF = atof(b);
	}
	else {
		bI = atol(b);
	}
	if (hasPoint(a) && hasPoint(b)) {
		resultF = aF * bF;
		ftoa(resultF, res);
		return res;
	}
	else if (hasPoint(a) && !hasPoint(b)) {
		resultF = aF * (double)bI;
		ftoa(resultF, res);
		return res;
	}
	else if (!hasPoint(a) && hasPoint(b)) {
		resultF = (double)aI * bF;
		ftoa(resultF, res);
		return res;
	}
	else {
		resultI = aI * bI;
		_i64toa(resultI, res, 10);
		return res;
	}
}

void ftoa(double n, char* out) {
	BOOL minusFlag = FALSE;
	int beforePoint = (int)n;
	if (n < 0 && beforePoint >= 0) {
		minusFlag = TRUE;
	}
	double afterPoint, i;
	if (minusFlag) {
		strcat(out, "-");
	}
	_itoa(beforePoint, &out[strlen(out)], 10);
	strcat(out, ".");
	afterPoint = modf(n, &i);
	int decpnt, sign;
	char* strAfterPoint = NULL;
	strAfterPoint = _fcvt(afterPoint, 5, &decpnt, &sign);
	if (strAfterPoint != NULL) {
		strcat(out, strAfterPoint);
	}
	
}

char* get_number_from_string(char* string, int index) {
	char* number = get_dynamic_array(MAX_NUMBER_SIZE);
	int j = 0;
	while (string[index] != ' ' && index >= 0) {
		number[j] = string[index];
		index--;
		j++;
	}
	reverse(number);
	return number;
}

void reverse(char* string) {
	const int size = strlen(string);
	for (int i = 0; i < size / 2; i++) {
		char temp = string[i];
		string[i] = string[size - i - 1];
		string[size - i - 1] = temp;
	}
}

void delete_braces(struct node** top_ptr, char* dst) {
	while (top(top_ptr) != '(') {
		copy_sign_to_output(top(top_ptr), dst);
		pop(top_ptr);
	}
	pop(top_ptr);
}

void move_higher_operations(struct node** top_ptr, char* dst, const char sign) {
	while (priority(top(top_ptr)) >= priority(sign)) {
		if (top(top_ptr) != '\0' && top(top_ptr) != '(') {
			copy_sign_to_output(top(top_ptr), dst);
			pop(top_ptr);
		}
		else {
			break;
		}
	}
}

void move_others_operations(struct node** top_ptr, char* dst) {
	while (*top_ptr != NULL) {
		copy_sign_to_output(top(top_ptr), dst);
		pop(top_ptr);
	}
}

void copy_sign_to_output(const char operation, char* dst) {
	dst[strlen(dst)] = operation;
	dst[strlen(dst)] = ' ';
}

int copy_number_to_output(char* src, char* dst) {
	int i = 0;
	while (isdigit(*src) || *src == '.') {
		dst[strlen(dst)] = *src;
		src++;
		i++;
	}
	dst[strlen(dst)] = ' ';
	return i;
}

void push(struct node** top_ptr, const char sign) {
	struct node* temp = NULL;
	temp = (struct node*)malloc(sizeof(struct node));

	if (temp != NULL)
	{
		memset(temp, 0x00, sizeof(struct node));
		temp->operation = sign;
		temp->next_ptr = *top_ptr;
		*top_ptr = temp;
	}
}

void pop(struct node** top_ptr){
	struct node* temp = NULL;

	if (*top_ptr == NULL)
	{
		exit(EXIT_SUCCESS);
	}

	temp = *top_ptr;
	*top_ptr = (*top_ptr)->next_ptr;

	free(temp);
}

char top(struct node** top_ptr) {
	if (*top_ptr == NULL) {
		return 0x00;
	}
	return (*top_ptr)->operation;
}

int find(const char symbol) {
	const char correct_symbols[] = { '+', '-', '*', '^', '/', '%', '(', ')', '.', '\0' };
	int correct_symbols_size = strlen(correct_symbols);
	for (int i = 0; i < correct_symbols_size; i++) {
		if (correct_symbols[i] == symbol || isdigit(symbol)) {
			return CORRECT_STRING;
		}
	}
	return INCORRECT_STRING;
}

int check_input(char* input) {
	int input_size = strlen(input);
	if (input_size > 1) {
		BOOL flag = FALSE;
		for (int i = 0; i < input_size; i++) {
			if (!find(input[i])) {
				return INCORRECT_STRING;
				
			}
			if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '^' || input[i] == '/' || input[i] == '%') {
				flag = TRUE;
			}
		}
		if (!flag) {
			return INCORRECT_STRING;
			
		}
		for (int i = 0; i < input_size - 1; i++) {
			if (
				(input[i] == '+' && input[i + 1] == '+') ||
				(input[i] == '+' && input[i + 1] == '-') ||
				(input[i] == '+' && input[i + 1] == '*') ||
				(input[i] == '+' && input[i + 1] == '^') ||
				(input[i] == '+' && input[i + 1] == '/') ||
				(input[i] == '+' && input[i + 1] == '%') ||
				(input[i] == '+' && input[i + 1] == ')') ||

				(input[i] == '-' && input[i + 1] == '+') ||
				(input[i] == '-' && input[i + 1] == '-') ||
				(input[i] == '-' && input[i + 1] == '*') ||
				(input[i] == '-' && input[i + 1] == '^') ||
				(input[i] == '-' && input[i + 1] == '/') ||
				(input[i] == '-' && input[i + 1] == '%') ||
				(input[i] == '-' && input[i + 1] == ')') ||

				(input[i] == '*' && input[i + 1] == '+') ||
				(input[i] == '*' && input[i + 1] == '-') ||
				(input[i] == '*' && input[i + 1] == '*') ||
				(input[i] == '*' && input[i + 1] == '^') ||
				(input[i] == '*' && input[i + 1] == '/') ||
				(input[i] == '*' && input[i + 1] == '%') ||
				(input[i] == '*' && input[i + 1] == ')') ||

				(input[i] == '/' && input[i + 1] == '+') ||
				(input[i] == '/' && input[i + 1] == '-') ||
				(input[i] == '/' && input[i + 1] == '*') ||
				(input[i] == '/' && input[i + 1] == '^') ||
				(input[i] == '/' && input[i + 1] == '/') ||
				(input[i] == '/' && input[i + 1] == '%') ||
				(input[i] == '/' && input[i + 1] == ')') ||

				(input[i] == '%' && input[i + 1] == '+') ||
				(input[i] == '%' && input[i + 1] == '-') ||
				(input[i] == '%' && input[i + 1] == '*') ||
				(input[i] == '%' && input[i + 1] == '^') ||
				(input[i] == '%' && input[i + 1] == '/') ||
				(input[i] == '%' && input[i + 1] == '%') ||
				(input[i] == '%' && input[i + 1] == ')') ||

				(input[i] == '^' && input[i + 1] == '+') ||
				(input[i] == '^' && input[i + 1] == '-') ||
				(input[i] == '^' && input[i + 1] == '*') ||
				(input[i] == '^' && input[i + 1] == '^') ||
				(input[i] == '^' && input[i + 1] == '/') ||
				(input[i] == '^' && input[i + 1] == '%') ||
				(input[i] == '^' && input[i + 1] == ')') ||

				(input[i] == ')' && input[i + 1] == '(') ||
				(input[i] == '+' && input[i + 1] == '0') ||
				(input[i] == '-' && input[i + 1] == '0') ||
				(isdigit(input[i]) && input[i + 1] == '(')

				) {
				return INCORRECT_STRING;
			}
		}
		if (input[input_size - 1] == '*' ||
			input[input_size - 1] == '+' ||
			input[input_size - 1] == '-' ||
			input[input_size - 1] == '/' ||
			input[input_size - 1] == '%' ||
			input[input_size - 1] == '^') {

			return INCORRECT_STRING;
		}
	}
	else {
		return INCORRECT_STRING;
	}
	return CORRECT_STRING;
}

char* delete_spaces(char* input) {
	char* buffer = get_dynamic_array(MAX_SIZE);
	int size = strlen(input);
	int j = 0;
	for (int i = 0; i < size; i++) {
		if (input[i] != ' ') {
			buffer[j] = input[i];
			j++;
		}
	}
	return buffer;
}

char* get_dynamic_array(const int size) {
	char* arr = NULL;
	arr = (char*)malloc(sizeof(char) * size);
	if (arr != NULL) {
		memset(arr, 0x00, sizeof(char) * size);
		return arr;
	}
	else {
		printf("Allocate error\n");
		exit(EXIT_FAILURE);
	}
}
