#ifndef STRING_UTILS_H
#define STRING_UTILS_H

/**
 * @brief Set the "str" string with the constant char 'new_str' string. The function
 * reallocate the memory to new string.
 * 
 * @param new_str previous string to set.
 * @param l new string.
 * @return char* the string setted.
 */
char *string_set(char *str, const char *new_str);

/**
 * @brief Free the string from memory.
 * 
 * @param str string to clean.
 */
void string_clean(char *str);

/**
 * @brief Concatenate "str" and "other" strings. The function reallocate
 * the memory if is necessary.
 * 
 * @param str original string.
 * @param other string to concatenate.
 * @return char* the concatenated strings.
 */
char *string_cat(char *str, const char *other);

/**
 * @brief Concatenate "str" and "number" being "number" an integer number.
 * The function reallocate the memory if is necessary.
 * 
 * @param str original string.
 * @param number integer to concatenate.
 * @return char* the concatenated string.
 */
char *string_cat_number(char *str, int number);

#endif

