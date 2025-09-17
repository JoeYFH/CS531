#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 25
#define MIN_LENGTH 0
#define INPUT_SIZE 10
#define BUFFER (MAX_LENGTH * 4)
#define STRING_SIZE (MAX_LENGTH + 1)

/*Use for testing, create file name: input.txt and output.txt. Then uncomment the //setup() */
void setup()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
}
/*
 * Check if the string has the valid size
 * compare the actual size within the range [min_length, max_length]
 */
int is_valid_size(int size, int min_length, int max_length);
/*
 * Check if the string contains invalid pre-defined characters set
 */
int is_contained_invalid_char(char illegal_chars[], int illegal_size, char s[], int size);
/*
 *  Check for duplication
 */
int is_duplicated(char s[], char inputs[INPUT_SIZE][STRING_SIZE]);
/*
 * Give a warning for invalid char
 */
void warning_invalid_char(char illegal_chars[], int index);
/*
 * Give a warning for invalid length of string
 */
void warning_invalid_size(int string_len, int min_length, int max_length);
/*
 * Give a warning for duplicated input
 */
void warning_duplicated_input();
/*
 * Sort strings with Ascending or Descending option
 */
void sort_input(char inputs[INPUT_SIZE][STRING_SIZE], char option);
/*
 * Print array of string
 */
void print_inputs(char inputs[INPUT_SIZE][STRING_SIZE]);
/*
 * Swap content of 2 strings
 */
void swap_string(char a[STRING_SIZE], char b[STRING_SIZE], char temp[STRING_SIZE]);
int main()
{
    // setup();
    char user_input[BUFFER];
    char illegal_chars[] = {'+', '$', '%', '^', '(', ')'};
    const unsigned int invalid_chars_size = sizeof(illegal_chars) / sizeof(illegal_chars[0]);
    char inputs[INPUT_SIZE][STRING_SIZE];

    int index = 0;
    printf("Enter %d characters string: ", INPUT_SIZE);
    while (index < INPUT_SIZE)
    {
        printf("Enter string %d: ", index + 1);
        putchar('\n');
        fgets(user_input, BUFFER, stdin);
        int current_len = strlen(user_input);
        user_input[--current_len] = '\0';
        if (!is_valid_size(current_len, MIN_LENGTH, MAX_LENGTH))
        {
            warning_invalid_size(current_len, MIN_LENGTH, MAX_LENGTH);
            continue;
        }
        int illegal_index = is_contained_invalid_char(illegal_chars, invalid_chars_size, user_input, current_len);
        if (illegal_index != -1)
        {
            warning_invalid_char(illegal_chars, illegal_index);
            continue;
        }
        if (is_duplicated(user_input, inputs))
        {
            warning_duplicated_input();
            continue;
        }

        strcpy(inputs[index], user_input);
        index++;
    }
    char sort_option[MAX_LENGTH];
    do
    {
        printf("Print character strings in Ascending or Descending order (A or D): ");
        fgets(sort_option, BUFFER, stdin);
        int current_len = strlen(sort_option);
        sort_option[--current_len] = '\0';
        if (current_len != 1)
            continue;
        putchar('\n');
    }
    while (sort_option[0] != 'A' && sort_option[0] != 'D');
    const char order = sort_option[0];
    sort_input(inputs, order);
    print_inputs(inputs);
    printf("String with the lowest ascii value: %s\n", (order == 'A') ? inputs[0] : inputs[INPUT_SIZE-1]);
    printf("String with the highest ascii value: %s\n", (order == 'A') ? inputs[INPUT_SIZE-1] : inputs[0]);
    return 0;
}

void swap_string(char a[STRING_SIZE], char b[STRING_SIZE], char temp[STRING_SIZE])
{
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}
void sort_input(char inputs[INPUT_SIZE][STRING_SIZE], char option)
{
    char temp[STRING_SIZE];
    for (int i = 0; i < INPUT_SIZE - 1; i++)
    {
        for (int j = 0; j < INPUT_SIZE - 1 - i; j++)
        {
            if (option == 'A')
            {
                if (strcmp(inputs[j], inputs[j+1]) > 0)
                    swap_string(inputs[j], inputs[j+1], temp);
            } else
            {
                if (strcmp(inputs[j], inputs[j+1]) < 0)
                    swap_string(inputs[j], inputs[j+1], temp);
            }
        }
    }
}

int is_contained_invalid_char(char illegal_chars[], int illegal_size, char s[], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < illegal_size; j++)
        {
            if (s[i] == illegal_chars[j])
                return j;
        }
    }
    return -1;
}

int is_valid_size(int size, int min_length, int max_length)
{
    if (!(min_length < size && size <= max_length)) return 0;
    return 1;
}

void warning_invalid_size(int string_len, int min_length, int max_length)
{
    printf("Error %d is illegal length, length must be from [%d - %d]\n", string_len, min_length, max_length);
}

void warning_invalid_char(char illegal_chars[], int index)
{
    printf("Error %c is an illegal character-please re-enter\n", illegal_chars[index]);
}

int is_duplicated(char s[], char inputs[INPUT_SIZE][STRING_SIZE])
{
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        if (strcmp(s, inputs[i]) == 0) return 1;
    }
    return 0;
}

void print_inputs(char inputs[INPUT_SIZE][STRING_SIZE])
{
    for (int i = 0; i < INPUT_SIZE; i++)
        puts(inputs[i]);
}

void warning_duplicated_input()
{
    puts("Error: duplicate string - please re-enter");
}