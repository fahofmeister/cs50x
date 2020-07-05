#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // This program asks the user name and greets him
    string name = get_string("What's your name?\n");
    printf("hello, %s\n", name);
}