//  Arithemetic Expression Evaluator
// 10627130 資工二甲 林冠良 & 10627131 資工二甲 李峻瑋
// CodeBlocks 17.12
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std ;
#define MAX 80

struct postfixPtr {
    int num = -1 ;
    char ch = '\0' ;
    postfixPtr * next;
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

postfixPtr* InfixToPostfix( char * infix, char * postfix ) {
    char stack[MAX] = {'\0'} ;
    int i = 0 ;
    int j = 0 ;
    int top = 0 ;
    int num = 0, temp = 0;
    char tempnum[MAX]  = {'\0'} ;
    // int numStack[MAX] = {0} ;
    
    postfixPtr* Postfix = NULL ;
    postfixPtr* head = NULL;
    Postfix = new postfixPtr;
    head = Postfix ;
    
    for ( i = 0, j = 0, top = 0 ; infix[i] != '\0' ; i++ ) switch( infix[i] ) {
        case '(' :
            stack[++top] = infix[i] ; // save it to the stack
            break ;
        case '+' : case '-' : case '*' : case '/' :
            // cout << stack[top] << " " << infix[i] << endl ;
            while ( Priority( stack[top] ) >= Priority( infix[i]) ) { // check the priority
                // cout << "while in" << endl ;
                //postfix[j++] = stack[top--] ;
                Postfix -> ch = stack[top] ;
                //cout << Postfix -> ch << endl ;
                Postfix -> next = new postfixPtr ;
                Postfix = Postfix -> next ;
                top -- ;
            } // while()
            stack[++top] = infix[i] ; // save to stack
            // cout << stack[top] << endl ;
            break ;
        case ')' :
            while ( stack[top] != '(' ) {
                // cout << "while in" << endl ;
                // postfix[j++] = stack[top--] ; // get the previous bracket and output to postfix array
                Postfix -> ch = stack[top] ;
                //cout << Postfix -> ch << endl ;
                Postfix -> next = new postfixPtr ;
                Postfix = Postfix -> next ;
                top -- ;
            } // while()
            top -- ; // minus the top
            break ;
        default : // numbers
            if( infix[i] >= '0' && infix[i] <= '9' ) {
                tempnum[temp] = infix[i];
                temp++;
            } // if
            
            if( infix[i+1] < '0' || infix[i+1] > '9' ) {
                num = atoi(tempnum);
                // cout << num << endl;
                Postfix -> num = num ;
                Postfix -> next = new postfixPtr;
                Postfix = Postfix -> next;
                for( int n = 0; n < temp; n++ ) tempnum[n] = '\0';
                temp = 0 ;
            }  // else// if it's a number, output to postfix array
    } // check and save to postfix
    // cout << top << endl ;
    
    while ( top > 0 ) {
        //cout << stack[top] ;
        //postfix[j++] = stack[top--] ;
        Postfix -> ch = stack[top] ;
        // cout << Postfix -> ch << endl ;
        Postfix -> next = new postfixPtr ;
        Postfix = Postfix -> next ;
        top -- ;
    } // get the last stack
    
    Postfix -> next = NULL ;
    Postfix = head ;
    
    while( Postfix -> next != NULL ) {
        if ( Postfix -> num != -1 ) cout << Postfix -> num << ", " ;
        if ( Postfix -> ch != '\0' ) cout << Postfix -> ch << ", " ;
        //cout << Postfix->num << " " << Postfix->ch << endl ;
        Postfix = Postfix -> next ;
    } // while
    
    Postfix = head ;
    return Postfix ;
} // change the infix expression to postfix expression

double Evaluate( char * infix ) {
    char postfix[MAX]= {'\0'} ;
    //char operand[2] = {'\0'} ;
    double stack[MAX] = {0.0} ;
    postfixPtr* calPointer = NULL ;
    
    calPointer = InfixToPostfix( infix, postfix ) ; // change infix 2 postfix
    
    int top = 0 ;
    while ( calPointer -> next != NULL ) {
        if ( calPointer->ch != '\0' ) { // operand situation
            stack[top-1] = Calculate( calPointer->ch, stack[top-1], stack[top] ) ;
            top -- ;
        } // calculate
        else if ( calPointer->num != -1 ) { // number situation
            // operand[0] = char(calPointer->num) ;
            // cout << static_cast<double>(calPointer->num) << endl ;
            stack[++top] = static_cast<double>(calPointer->num) ;
        } // save number into stack
        calPointer = calPointer->next ;
    } // check if it's a operand or number and calculate
    
    /* for ( top = 0, i = 0 ; postfix[i] != '\0' ; i++ ) switch( postfix[i] ) {
        case '+': case '-' : case '*' : case '/' :
            stack[top-1] = Calculate( postfix[i], stack[top - 1], stack[top] ) ;
            top -- ;
            break ;
        default:
            operand[0] = postfix[i] ;
            stack[++top] = atof(operand) ;
    } // check if it's a operand or number and calculate */
    
    // cout << stack[top] << endl ;
    return stack[top];
} // evaluate the postfix one by one

bool LegalExpressionOrNot( char * infix ) {
    int leftBracket = 0;
    int rightBracket = 0;
    
    for ( int i = 0; infix[i] != '\0'; i++ ) {
        if( infix[i] != '+' && infix[i] != '-' && infix[i] != '*' &&
           infix[i] != '/' && infix[i] != '(' && infix[i] != ')' && ( infix[i] < '0' || infix[i] > '9' )  ) {
            cout << "Error 1: " << infix[i] << " is not a legitimate character." << endl;
            return false;
        } // if
        
        if( infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' )  {
            if( infix[i+1] == '\0' || infix[i+1] == '+' || infix[i+1] == '-' || infix[i+1] == '*' || infix[i+1
                                                                                                           ] == '/' ) {
                cout << "Error 3: there is one extra operator." << endl;
                return false;
            } // if
        } // if
        
        if( infix[i] == '(' )  {
            if( infix[i+1] == '+' || infix[i+1] == '-' || infix[i+1] == '*' || infix[i+1] == '/' ) {
                cout << "Error 3: there is one extra operator." << endl;
                return false;
            } // if
        } // if
        
        if( infix[i] == ')' )  {
            if( infix[i+1] >= '0' && infix[i+1] <= '9' ) {
                cout << "Error 3: there is one extra operand." << endl;
                return false;
            } // if
        } // if
        
        if( infix[i] == '(' )  {
            if( infix[i-1] >= '0' && infix[i-1] <= '9' ) {
                cout << "Error 3: there is one extra operand." << endl;
                return false;
            } // if
        } // if
        
        if( infix[i] == '/' )  {
            if( infix[i+1] == '0' ) {
                cout << "Error 4: Divisor can't not be 0." << endl;
                return false;
            } // if
        } // if
        
        if( infix[i] == '(' ) leftBracket++;
        if( infix[i] == ')' ) rightBracket++;
        
    } // for
    
    if( leftBracket > rightBracket ) {
        cout<< "Error 2: there is one extra open parenthesis." << endl;
        return false;
    } // if
    
    else if( rightBracket > leftBracket ){
        cout<< "Error 2: there is one extra close parenthesis." << endl;
        return false;
    } // if
    
    cout<< "It is a legitimate infix expression" << endl;
    return true;
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
        cout << "**********************************************" << endl ;
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
                
                i = 0;
                
                
                if ( LegalExpressionOrNot( infix ) ) {
                    cout << "The value of the expression is :" << Evaluate( infix ) << endl << endl ; // print the value out
                } // if()
                else
                    cout << "Illegal expression!" << endl ; // wrong message
                do {
                    cout << "Would you like to try again?(Y/N)" << endl ;
                    scanf( "%c", &continueChar );
                    scanf( "%c", &line );
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
