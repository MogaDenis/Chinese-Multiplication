#include <stdio.h>

void swap_integers(int *var1, int *var2)
{
	// Interchange two integer values
	int aux = *var1;
	*var1 = *var2;
	*var2 = aux;
}

void decompose_digits(int initial_num, int digits[], int *length)
{
	// Save the digits of the given number inside an integer array
	*length = 0;
	while(initial_num != 0)
	{
		digits[(*length)++] = initial_num % 10;
		initial_num /= 10;
	}
}

void print_2d_array(int matrix[][20], int n, int m)
{
	// Print a 2d array with n rows and m columns
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

int check_length(int var1, int var2)
{
	// Delete digits of both numbers until at least one of them becomes 0.
	while(var1 != 0 && var2 != 0)
	{
		var1 /= 10;
		var2 /= 10;
	}

	// If one of them is not 0, then the initial numbers had different numbers of digits.
	if(var1 != var2)
		return 0;

	// Else, their numbers of digits were equal.
	return 1;
}

int main()
{

	// NB! It is mandatory for the two numbers to have the same number of digits.
	int num1, num2;

	// Read the two numbers to multiply
	printf("\nPlease enter two numbers to multiply.\n");
	scanf("%d", &num1);
	scanf("%d", &num2);

	// Check if the user inputed two values with different numbers of digits.
	// If that is the case, request a new input until they enter two integers with the same number of digits.
	while(!check_length(num1, num2))
	{
		printf("\nInvalid input! The two numbers must have the same number of digits!\n");
		printf("\nPlease enter two numbers to multiply.\n");
		scanf("%d", &num1);
		scanf("%d", &num2);
	}

	// This 2d array will store the number of intersection points of the lines used in the chinese multiplication
	int grid[20][20];

	// In this variables we will store the digits of the given numbers and the number of digits of each.
	int digits_of_num1[10], digits_of_num2[10];
	int length1 = 0, length2 = 0;

	// Make sure that the first number is the largest one(will surely have the most digits).
	if(num1 < num2)
		swap_integers(&num1, &num2);

	// Extract the digits of the two numbers and store them into two arrays.
	decompose_digits(num1, digits_of_num1, &length1);
	decompose_digits(num2, digits_of_num2, &length2);

	// "Draw" horizontal lines on the grid.
	for(int i = 0; i < length1; i++)
	{
		for(int j = 0; j < length1; j++)
			grid[i][j] = digits_of_num1[length1 - i - 1];
	}

	// Display the grid with the horizontal lines.
	printf("\nThis grid represents the number of lines corresponding to each digit of the first term:\n");
	print_2d_array(grid, length1, length1);	

	// We skip the drawing step and we just obtain the number of intersection points by multiplying the digits of number 2 with the number of corresponding horizontal lines.
	for(int i = 0; i < length2; i++)
	{
		for(int j = 0; j < length1; j++)
			grid[j][length1 - 1 - i] *= digits_of_num2[i];
	}

	// What we have now is practically the drawing where the number of dots is represented on the grid.
	printf("\nThis grid represents the number of points obtained after the intersections of all the corresponding lines:\n");
	print_2d_array(grid, length1, length1);	

	// We now have to compute the digits of the product of the two given numbers.
	// The carry is just the transport obtained during the iterative process of multiplications.
	int digits_of_result[20], length_result = 0, carry = 0;

	// Calculate some digits by adding the values on the diagonals parallel to the secondary diagonal which are on its right, including itself.
	for(int i = length1 - 1; i >= 0; i--)
	{
		int sum = 0;
		for(int j = length1 - 1; j >= i; j--)
			sum += grid[length1 - 1 - j + i][j];
		digits_of_result[length_result++] = (sum + carry) % 10;
		carry = (sum + carry) / 10;
	}

	// Calculate the rest of the digits by adding the values on the diagonals parallel to the secondary diagonal which are on its left, excluding itself.
	for(int j = length1 - 2; j >= 0; j--)
	{
		int sum = 0;
		for(int i = 0; i <= j; i++)
		{
			sum += grid[i][j - i];
		}
		digits_of_result[length_result++] = (sum + carry) % 10;
		carry = (sum + carry) / 10;
	}

	int result = 0;

	// If the carry is not 0, then we have a transport digit outside the area of representation of length (2*n - 1), where n is the number of digits of the two numbers.
	if(carry != 0)
		digits_of_result[length_result++] = carry;

	// Compute the result from the obatained digits.
	for(int i = length_result - 1; i >= 0; i--)
		result = result * 10 + digits_of_result[i];

	printf("\nThe result of the chinese multiplication is: %d\n", result);
	
	return 0;
}