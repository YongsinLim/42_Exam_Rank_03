/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_solution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yolim <yolim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 19:37:17 by yolim             #+#    #+#             */
/*   Updated: 2026/03/16 21:12:04 by yolim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
* EXERCISE: FT_SCANF

* DESCRIPTION:
* Implement a simplified version of scanf that handles only %s, %d, and %c.

* KEY CONCEPTS:
* 1. ARGUMENT VARIABLES: va_list, va_start, va_arg, va_end
* 2. FORMAT PARSING: Analyze formatted strings character by character
* 3. FILE READING: fgetc(), ungetc() for flow control
* 4. CONVERSIONS: Convert strings to numbers, handle whitespace

* SUPPORTED FORMATS:
* - %s: string (up to the first whitespace character)
* - %d: decimal integer (signed optional)
* - %c: single character
*/

#include <stdarg.h> // for va_start, va_arg, va_copy, va_end
#include <stdio.h> // for fgetc, ungetc, ferror, feof
#include <ctype.h> // for isspace, isdigit,

/*
fgetc :
Read character by character
Return Value: Returns the character read as an unsigned char converted to an int.
                If the end-of-file is reached or an error occurs, it returns EOF.

ungetc(int char, FILE *stream) :
takes a single character and put it back onto an input stream.
char: specifies the int promotion of the character to be put back.
        The value is internally converted to an unsigned char when put back.
Return Value: On success, returns the character ch. On failure, EOF is returned without changing the stream.

ferror :
check errors in files during file operations
return value : If the file has error, returns a non-zero value. Otherwise, returns 0.
*/

/*
Important Notes !!!!!
scan_char
scan_int
scan_string
match_conv

above function all need to declare parameter : va_list *ap
inside those function :
va_arg(*ap, int *)
must have * for ap

*/

// Function to skip whitespace in the stream
int match_space(FILE *f)
{
    // Read the first character from the stream.
    int ch = fgetc(f);
    // Check if EOF was caused by a real error (not just end of input)
    if (ch == EOF && ferror(f))
        return -1;

    while (ch != EOF)
    {
        // If ch is not a space, put it back with ungetc and break — the non-space char is preserved for the next read.
        if (!isspace(ch))
        {
            ungetc(ch, f);
            break ;
        }
        // If ch is a space, discard it and read the next char with fgetc.
        ch = fgetc(f);
    }
    // After the loop, check if any read inside the loop caused an error.
    if (ferror(f))
        return -1;
    // All whitespace was consumed successfully.
    return (1);
}

// Function to check a specific character
int match_char(FILE *f, char c)
{
/*
- It reads one character with fgetc(f) into ch.
- If ch == c, it returns 1 (match success).
- If it does not match and ch != EOF, it pushes that character back with ungetc(ch, f) so later parsing can read it again.
- Then it returns -1 (match failure).
So this function is used for literal format characters in scanf-style parsing: consume only if it matches, otherwise do not lose input.
*/
    int ch = fgetc(f);
    if (ch == c)
        return 1;
    if (ch != EOF)
        ungetc(ch, f);
    return -1;
}

// Function to read a character (%c)
int scan_char(FILE *f, va_list *ap)
{
    /*
    * %c CONVERSION:
    * - Read exactly one character
    * - declare char ptr using va_arg
    * - Do not skip whitespace
    * - Store in the provided pointer
    */

    int ch = fgetc(f);
    // It gets the destination pointer from variable arguments.
    char *cp = va_arg(*ap, char *);
    // If reading fails (EOF), it returns -1 to signal conversion failure.
    if (ch == EOF)
        return -1;
    // Otherwise, it stores the character into *cp and returns 1 for success.
    *cp = (char)ch;
    return 1;
    // unlike %d or %s, %c does not skip whitespace, so space/newline can be valid input characters.
}

// Function to read an integer (%d)
int scan_int(FILE *f, va_list *ap)
{
    /*
    * %d CONVERSION:
    * - declare int ptr using va_arg
    * - Skip leading whitespace
    * - Read optional sign (+/-)
    * - Check 1st ch is number
    * - Read digits and construct the number
    * - Return the last non-digit character to the stream
    * - Check count whether run
    * - If count run, assign number into int ptr
    */

    int sign = 1;
    int value = 0;

    int ch = fgetc(f);
    // It gets the output pointer from variadic arguments
    int *ip = va_arg(*ap, int *);
    int count = 0;

    if (ch == EOF)
        return -1;

    // It skips leading whitespace.
    while (isspace(ch))
        ch = fgetc(f);

    // It checks optional sign (+ or -), adjust sign value
    if (ch == '-')
    {
        sign = -1;
        ch = fgetc(f);
    }
    else if (ch == '+')
        ch = fgetc(f);

    // Verify the first character is a digit
    if (!isdigit(ch))
    {
        ungetc(ch, f);
        return -1;
    }

    // Read digits and build the number
    while (isdigit(ch))
    {
        value = value * 10 + (ch - '0');
        count++;
        ch = fgetc(f);
    }

    // Return last non-digit character
    if (ch != EOF)
        ungetc(ch, f);

    if (count == 0)
        return -1;

    // It stores the final number in *ip as value * sign
    *ip = value * sign;
    return 1;
}

// Function to read a string (%s)
int scan_string(FILE *f, va_list *ap)
{
    /*

    * %s CONVERSION:
    * - declare str ptr using va_arg
    * - Skip leading whitespace
    * - Read characters until a whitespace character is found
    * - Terminate the string with '\0'
    * - Return the last whitespace character to the stream
    * - Return -1 if i not run, 1 if i run
    */

    int ch = fgetc(f);
    char *sp = va_arg(*ap, char *);
    int i = 0;

    // Skip leading whitespace
    while (ch != EOF && isspace(ch))
        ch = fgetc(f);

    if (ch == EOF)
        return -1;

    // Read characters up to a space
    while (ch != EOF && !isspace(ch))
    {
        sp[i] = ch;
        i++;
        ch = fgetc(f);
    }
    sp[i] = '\0';

    // Return a space character to the stream
    if (ch != EOF)
        ungetc(ch, f);

    if (i == 0)
        return -1;
    return 1;
}

// Function to handle format conversions
int	match_conv(FILE *f, const char **format, va_list *ap)
{
    /*
    * CONVERSION DISPATCHER:
    * - Parse the conversion character
    * - Call the appropriate function
    * - Automatically handle spaces for %d and %s
    */

    if (**format == 'c')
        return scan_char(f, ap);
    else if (**format == 'd')
    {
        match_space(f); // %d skips spaces automatically
        return scan_int(f, ap);
    }
    else if (**format == 's')
    {
        match_space(f); // %s skips spaces automatically
        return scan_string(f, ap);
    }
    else if (**format == '\0')
        return -1;
    else
        return -1; // Conversion not supported
}

// Main function of scanf (no need to remember, Q will provide all the code!)
// the only thing need to change is if (match_conv(f, &format, &ap) != 1) ap must have &
int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
    /*
    * MAIN LOGIC OF SCANF:
    * - Analyze format string character by character
    * - Handle literal characters and conversions (%)
    * - Count successful conversions
    * - Stop at the first error
    */

    int nconv = 0; // Number of successful conversions

    // Verify that data is available
    int c = fgetc(f);
    if (c == EOF)
        return EOF;
    ungetc(c, f);

    while (*format)
    {
        if (*format == '%')
        {
            // Conversion found
            format++;
            if (match_conv(f, &format, &ap) != 1)
                break; // Conversion error
            else
                nconv++; // Successful conversion
        }
        else if (isspace(*format))
        {
            // Blank space in format: skip spaces in input
            if (match_space(f) == -1)
                break;
        }
        // Literal character: must match exactly
        else if (match_char(f, *format) != 1)
            break;
        format++;
    }
    // Check for file errors
    if (ferror(f))
        return EOF;
    return nconv; // Return number of successful conversions
}

// Wrapper function for standard scanf
int ft_scanf(const char *format, ...)
{
    /*
    * WRAPPER FOR VARIABLE ARGUMENTS:
    * - Initialize va_list
    * - Call the main function with stdin
    * - Clear va_list
    */

    va_list ap;

    va_start(ap, format);
    int ret = ft_vfscanf(stdin, format, ap);
    va_end(ap);
    return ret;
}

/*
* KEY POINTS FOR THE EXAM:

* 1. VARIABLE ARGUMENTS:
* - va_start(ap, last_param) to initialize
* - va_arg(ap, type) to get the next argument
* - va_end(ap) to clear

* 2. FILE FLOW CONTROL:
* - fgetc() to read a character
* - ungetc() to return a character to the stream
* - ferror() to check for errors

* 3. SPACE HANDLING:
* - %c does NOT skip whitespace
* - %d and %s DO skip whitespace
* - Spaces in format match any whitespace

* 4. RETURN VALUE:
* - Number of successful conversions
* - EOF if file error or EOF before conversions
* - Stop on first failed conversion
*/

/*
EXAMPLE USAGE:
int main(void)
{
     int x;
     char str[100];
     char c;

     // Read: number, space, string, space, character
     int converted = ft_scanf("%d %s %c", &x, str, &c);
     printf("Converted: %d\n", converted);
     printf("Number: %d, String: %s, Character: %c\n", x, str, c);
     return 0;
 }
*/