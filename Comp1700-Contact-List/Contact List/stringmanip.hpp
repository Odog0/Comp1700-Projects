#pragma once
/* String manipulation functions.
 *
 *
 * trim() - creates new string by trimming unnecessary whitespace
 * Usage:
 *     string clean = trim(s);
 *
 *
 * uppercase() - creates new string by converting letters to uppercase
 * Usage:
 *     string uc = uppercase(s);
 *
 *
 * lowercase() - creates new string by converting letters to lowercase
 * Usage:
 *     string lc = lowercase(s);
 */
#include <string>

std::string trim(std::string s);

std::string uppercase(std::string s);

std::string lowercase(std::string s);