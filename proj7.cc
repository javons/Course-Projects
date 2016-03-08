/**********************************************************************
 *
 * Project 7: Strings, the Hard Way
 *
 * This program will first make letters that user enters capital, then
 * add a separator to two strings and lastly test out what user enters
 * whether a palindrome or not.
 *
 * Author: Tianmao Jiang 
 * Date: August 26 2015
 *
 **********************************************************************/

#include <iostream>
using namespace std;

// return a char pointer to what the user enters
const char* get_c_string();
// function that will return the length of a c-string
int strlen(const char* s);
// return a boolean value depends on the letter is lower case or not
bool islower(char c);
// function to change the lower case letters to upper case ones
void toupper(char* s);
// function that copys the c-string
char* strdup(const char* s);
// function that will put a separator between two strings
char* cat_dot(const char *s1, const char* s2, const char* sep=".");
// return a boolean value that reflects if it's a palindrome
bool is_palindrome(const char* s);


int main()
{
    // transform all letters to upper case
    cout << "toupper/strdup test:\n";
    cout << "Enter a mixed-case string: ";
    const char* s = get_c_string();
    cout << "The original string is \"" << s << "\"\n";
    char *s1 = strdup(s);
    toupper(s1);
    cout << "Translated to upper case: \"" << s1 << "\"\n";

    // cat_dot test
    cout << "\ncat_dot test\n";
    char str1[] = "bonjour";
    char str2[] = "olam";
    // use default separator
    cout << "cat_dot(\"" << str1 << "\", \"" << str2 << "\") is \""
	 << cat_dot(str1, str2) << "\"\n";
    // use new separator
    char newsep[] = "#!?"; 
    cout << "cat_dot(\"" << str1 << "\", \"" << str2 << "\", \"" 
	 << newsep << "\") is \""
	 << cat_dot(str1, str2, newsep) << "\"\n";
    
    // palindrome test
    cout << "\nPalindrome test:\n";
    cout << "Enter palindrome candidates (one per line).\n"
	"End-of-file (control-D) terminates input (and program).\n";
    while (true) {
	const char* pal_cand = get_c_string();
	if (!cin)
	    break;
	cout << "\"" << pal_cand << "\" is " ;
	if (!is_palindrome(pal_cand)) cout << "not ";
	cout << "a palindrome.\n";
    }
}

// returns the length of a C-string 
int strlen(const char *s)
{
    int len = 0;
    while (s[len] != 0) len++;
    return len;
}

// foolproof way to get a C-string from input
// not exactly in the spirit of C :-)
// suffers from a memory leak
const char* get_c_string()
{
    string str;
    getline(cin, str);
    const char* s = str.c_str();         // memory leak!
    return s;
}

bool islower(char c)
{
    // lower a to z is the range of low case letters
    return (c >= 'a' && c <= 'z');  
}

char toupper(char c)
{
    if (islower(c))
	// the ascii number addition to make the lower case upper
	return (c - 'a' + 'A');  
    else
	return c;
}

void toupper(char* s)
{
    // examine letters one by one and make them upper case
    for (int i = 0; i != strlen(s); ++i){
	char x = s[i];         
	s[i] = toupper(x);
    }
}

char* strdup(const char* s)
{
    char* x = new char(strlen(s));
    for (int i = 0; i <= strlen(s); ++i){
	x[i] = s[i];      // copy the string by copying each index
    }
    return x;
}

char* cat_dot(const char* s1, const char* s2, const char* sep)
{
    int len = strlen(s1) + strlen(s2) + strlen(sep);
    char* result = new char[len+1];
    // copy the s1 part into result
    for (int i = 0; i <= strlen(s1); ++i)
	result[i] = s1[i];
    // copy the sep part into result
    int mid = strlen(s1);
    for (int i = 0; i <= strlen(sep); ++i)
	result[mid+i] = sep[i];
    // copy the s2 part into result
    int last = strlen(s1) + strlen(sep);
    for (int i = 0; i <= strlen(s2); ++i)
	result[last+i] = s2[i];
    
    return result;
}

char* reverse(const char* s)
{
    int  n = strlen(s);
    char *s1 = new char[n + 1];
    char *s2 = (s1 + n - 1);
    s1[n] = 0;
    while (*s) {
	*s2-- = *s++;     // copy the s backwards into s2 which 
	                  // the front part is s1
    }
    return s1;     
}

bool equal(const char* s1, const char* s2)
{
    // string length not equal
    if (strlen(s1) != strlen(s2))
	return false;
    for (int i = 0; i < strlen(s1); i++)
	// string index not equal
	if (s1[i] != s2[i])
	    return false;
    return true;
}

bool is_palindrome(const char* s)
{
    char *p = reverse(s);
    // compare reverse version and original version
    if (equal(p,s))
	return true;
    else
	return false;
}
