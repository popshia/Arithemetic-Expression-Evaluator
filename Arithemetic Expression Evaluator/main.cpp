// Arithemetic Expression Evaluator

// CodeBlocks 17.12
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std ;
#define MAX 80

struct postfixPtr {
  char ch ;
  postfixPtr * next ;
} ;

int Priority( char oPerator ) {
    switch( oPerator ) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default:            return 0;
    } // switch between operators
} // determine the operator's priority

double Calculate( char oPerator, double num1, double num2 ) {
    switch( oPerator ) {
        case '+' : return num1 + num2 ;
        case '-' : return num1 - num2 ;
        case '*' : return num1 * num2 ;
        case '/' : return num1 / num2 ;
        default : return 0 ;
    } // switch between operators
} // calculate the numbers

void InfixToPostfix( char * infix, char * postfix ) {
    char stack[MAX] = {'\0'} ;
    int i = 0 ;
    int j = 0 ;
    int top = 0 ;

    for ( i = 0, j = 0, top = 0 ; infix[i] != '\0' ; i++ ) switch( infix[i] ) {
        case '(' :
            stack[++top] = infix[i] ; // save it to the stack
            break ;
        case '+' : case '-' : case '*' : case '/' :
            while ( Priority( stack[top] ) >= Priority( infix[i]) ) postfix[j++] = stack[top--] ; // check the priority
            stack[++top] = infix[i] ; // save to stack
            break ;
        case ')' :
            while ( stack[top] != '(' ) postfix[j++] = stack[top--] ; // get the previous bracket and output to postfix array
            top -- ; // minus the top
            break ;
        default : // numbers
            postfix[j++] = infix[i] ; // if it's a number, output to postfix array
    } // check and save to postfix

    while ( top > 0 ) postfix[j++] = stack[top--] ; // get the last stack
    postfixPtr * Postfix = NULL ;
    postfixPtr * head = NULL ;
    Postfix = new postfixPtr ;
    head = Postfix ;

    for ( int k = 0 ; postfix[k] != '\0' ; k++ ) {
        Postfix -> ch = postfix[k] ;
        Postfix -> next = new postfixPtr ;
        Postfix = Postfix -> next ;
    } // for()

    Postfix -> next = NULL ;
    Postfix = head ;
    while ( Postfix -> next != NULL ) {
        cout << Postfix -> ch << " , " ;
        Postfix = Postfix -> next ;
    } // while()

    cout << endl ;

} // change the infix expression to postfix expression

double Evaluate( char * infix ) {
    char postfix[MAX]= {'\0'} ;
    char operand[2] = {'\0'} ;
    double stack[MAX] = {0.0} ;

    InfixToPostfix( infix, postfix ) ; // change infix 2 postfix

    int top = 0 ;
    int i = 0 ;
    for ( top = 0, i = 0 ; postfix[i] != '\0' ; i++ ) switch( postfix[i] ) {
            case '+': case '-' : case '*' : case '/' :
                stack[top - 1] = Calculate( postfix[i], stack[top - 1], stack[top] ) ;
                top -- ;
                break ;
            default:
                operand[0] = postfix[i] ;
                stack[++top] = atof(operand) ;
    } // check if it's a operand or number and calculate

    return stack[top];
} // evaluate the postfix one by one

bool LegalExpressionOrNot( char * infix ) {
    int leftBracket = 0 ;
    int rightBracket = 0 ;

    for ( int i = 0 ; infix[i] != '\0' ; i++ ) {
        if ( infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' &&
             infix[i] != '(' && infix[i] != ')' && ( infix[i] < '0' || infix[i] > '9' ) ) {
          cout << "Error 1: " << infix[i] << " is not a legitimate character." << endl ;
          return false ;
        } // if

        if ( infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' )  {
           if ( infix[i+1] == '\0' || infix[i+1] == '+' || infix[i+1] == '-' || infix[i+1] == '*' || infix[i+1] == '/' ) {
              cout << "Error 3: there is one extra operator." << endl ;
              return false ;
           } // if
        } // if

        if ( infix[i] == '(' )  {
           if ( infix[i+1] == '+' || infix[i+1] == '-' || infix[i+1] == '*' || infix[i+1] == '/' ) {
              cout << "Error 3: there is one extra operator." << endl ;
              return false ;
           } // if
        } // if

        if ( infix[i] == ')' )  {
           if ( infix[i+1] >= '0' && infix[i+1] <= '9' ) {
              cout << "Error 3: there is one extra operand." << endl ;
              return false ;
           } // if
        } // if

        if ( infix[i] == '(' )  {
           if ( infix[i-1] >= '0' && infix[i-1] <= '9' ) {
              cout << "Error 3: there is one extra operand." << endl ;
              return false ;
           } // if
        } // if

        if (  infix[i] == '/' )  {
           if ( infix[i+1] == '0' ) {
              cout << "Error 4: Divisor can't not be 0." << endl ;
              return false ;
           } // if
        } // if

        if ( infix[i] == '(' ) leftBracket++ ;
        if ( infix[i] == ')' ) rightBracket++ ;

    } // for

        if ( leftBracket > rightBracket ) {
           cout << "Error 2: there is one extra open parenthesis." << endl ;
           return false ;
        } // if

        else if ( rightBracket > leftBracket ){
           cout << "Error 2: there is one extra close parenthesis." << endl ;
           return false ;
        } // if

    cout << "It is a legitimate infix expression" << endl ;
    return true ;
} // check if the expression is legal

int main() {
    char infix[MAX] = {'\0'} ;
    bool continueOrNot = false ;
    char continueChar = '\0' ;
    int command = 0 ;
    char temp = '\0';
    char line = '\0';
    int i = 0;
    do {
        cout << "**********************************************" << endl ; // welcome message
        cout << "*****  Arithemetic Expression Evaluator  *****" << endl ;
        cout << "***** 0 : Quit                           *****" << endl ;
        cout << "***** 1 : Read, analyze and calculate    *****" << endl ;
        cout << "**********************************************" << endl << endl ;
        cout << "Please enter your command:" << endl ;
        scanf( "%d", &command );
        scanf( "%c", &line );

        switch ( command ) {
            case 0 :
                cout << "Bye :(" << endl ;
                return 0 ;
            // quit case
            case 1 :
                cout << "Please enter your infix expression:" << endl ;
                while( temp != '\n' ) {
                  scanf( "%c", &temp );
                  if ( temp != ' ' && temp != '\n' ) {
                    infix[i] = temp ;
                    i++;
                  } // if
                } // while

                cout << infix << endl ;
                i = 0;

                if ( LegalExpressionOrNot( infix ) )
                    cout << "The value of the expression is :" << Evaluate( infix ) << endl << endl ; // print the value out
                else
                    cout << "Illegal expression!" << endl ; // wrong message
                do {
                    cout << "Would you like to try again?(Y/N)" << endl ;
                    scanf( "%c", &continueChar ) ;
                    scanf( "%c", &line ) ;
                    switch ( continueChar ) {
                        case 'Y' : case 'y' :
                            continueOrNot = true ;
                            break;
                        case 'N' : case 'n' :
                            continueOrNot = false ;
                            break ;
                        default:
                            cout << "Wrong command! Please try again..." << endl ;
                    } // switch between continueChar
                } while ( continueChar != 'Y' && continueChar != 'y' && continueChar != 'N' && continueChar != 'n' ) ;
                break ;
            // revert, evaluate, calculate and print
            default:
                cout << "Error command! Please try again..." << endl ;
                continueOrNot = true ;
                break ;
            // illegal input
        } // switch between commands

        temp = '\0';
        for( int j = 0; infix[j] != '\0'; j++ ) infix[j] = '\0';
    } while( continueOrNot ) ;

    cout << "Bye :(" << endl ;
} // main()
