//Brandon Roy
#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <exception>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

/**
 * ValueType is a data type that will only accept integers.
 * The program operates by accepting int values, we can change
 * that to floats or doubles by simply editing this line.
 */
using ValueType = int;

/**
 * Prompt's user if they require instructions.
 * @param void does not take input
 * @return if user chooses no.
 */
void provideHelpIfNecessary(void);

/**
 * Determine the value of an infix expression
 *
 * @param expr a string, supposedly representing an infix expression
 * @return the value of <code>expr</code>
 * @throw IllegalExprException if <code>expr</code> is not a legal infix
 * expression
 * @throw ZeroDivideException if <code>expr</code> involves a division
 * by zero
 */
ValueType processExpression(const string& expr);

/**
 *Takes two operands from top of operand stack and the top operator from operator stack and sends
 * those three values to the doOperation function.
 * @return takes the top value in the operand stack that was put there by the doOperation function.
 */
ValueType execute(stack<ValueType>& valStack, stack<char>& opStack);

/**
 *Takes the three values send to it from the execute function and performs the mathematical operation
 * based on what operator was sent to it.
 * @return the result of the operation to the execute function.
 */
ValueType doOperation(ValueType operand2, char operation, ValueType operand1);

/**
 *Determines the order of operation for certain operators.
 * @return the precedence int value of an operation to processExpression function.
 */
int precedence(char op);

int main(){
    provideHelpIfNecessary();

    while(true){
        cout << "Expression?";
        string expr;      // holds the supposed expression
        getline(cin, expr); //get input

        if (expr.length() == 0) //Exit Condition
            break;

        ValueType result = processExpression(expr);
        cout << "Result: " << result << endl;
    }
}

void provideHelpIfNecessary(void){
    char help = ' ';              //holds help choice
    cout << "Do you need help (Y/N): ";
    cin >> help;

    while(help != 'Y' && help != 'y' && help != 'N' && help != 'n'){    //Input Validation
        cout << "Invalid Input. Try Again (Y/N): ";
        cin >> help;
    }

    if(help == 'Y' || help == 'y'){                 //Choice is Yes
        cout << "Enter an infix expression at the prompt." << endl
             << "The program will tell you its value." << endl
             << "To stop the program, just hit \"enter\" or \"return\" at the prompt." << endl << endl;
        cin.ignore();       //Program needs this to use getline flawlessly
    }

    else        //Choice is No
        cin.ignore();       //Program needs this to use getline flawlessly
        return;
}

ValueType processExpression(const string& expr){
    string fullExpr(expr);          //string stream the string so it can be treated as an array
    stack<ValueType> valStack;      //holds operands in a stack
    stack<char> opStack;            //holds operators in a stack

    for (int i = 0; i < fullExpr.size(); i++){
        switch (fullExpr[i]){
            case '0' : valStack.push(0);
                       break;
            case '1' : valStack.push(1);
                       break;
            case '2' : valStack.push(2);
                       break;
            case '3' : valStack.push(3);
                       break;
            case '4' : valStack.push(4);
                       break;
            case '5' : valStack.push(5);
                       break;
            case '6' : valStack.push(6);
                       break;
            case '7' : valStack.push(7);
                       break;
            case '8' : valStack.push(8);
                       break;
            case '9' : valStack.push(9);
                       break;
            case '(' : opStack.push('(');
                       break;
            case '+' :
            case '-' :
            case '*' :
            case '/' :
                       if (opStack.empty())
                           opStack.push(fullExpr[i]);
                       else if (precedence(fullExpr[i]) > precedence(opStack.top()))
                           opStack.push(fullExpr[i]);
                       else{
                       while (!opStack.empty() && precedence(fullExpr[i])
                              <= precedence(opStack.top()))
                              execute(valStack, opStack);
                       opStack.push(fullExpr[i]);
                       }
                       break;
            case ')' :
                       while(opStack.top() != '('){
                            //cout << "case ( first val stack " << valStack.top() << endl;   //Debugging check
                            //cout << "case ( first opStack " << opStack.top() << endl; //Debugging check
                            execute(valStack, opStack);
                            //cout << "case ( second val stack " << valStack.top() << endl;     //Debugging check
                       }
                       opStack.pop();
                       break;
        }
    }
    while (!opStack.empty())
        execute(valStack, opStack);

    //cout << "In final return: " << endl;      //Debugging check
    return valStack.top();
}

ValueType execute(stack<ValueType>& valStack, stack<char>& opStack){//Take 2 operands and one operator
    ValueType operand2 = valStack.top();    //Operand 1
    valStack.pop();
    ValueType operand1 = valStack.top();    //Operand 2
    valStack.pop();

    char op = opStack.top();        //Operator
    opStack.pop();

    ValueType result = doOperation(operand2, op, operand1); //Send for calculation
    valStack.push(result);      //Result is pushed to top of valStack

    return valStack.top();      //Send back top of valStack
}

ValueType doOperation(ValueType operand2, char operation, ValueType operand1){
    switch(operation){      //Operator logic
        case '+' : return (operand2 + operand1);
        case '-' :
                   if(operand2 < 0)     //Contingency for negative numbers
                      return (operand1 + ((operand2) * -1));
                   return (operand1 - operand2);
        case '*' : return (operand2 * operand1);
        case '/' : return (operand1 / operand2);
    }
}

int precedence(char op){ //Order of Operations
    if(op == '*' || op == '/') return 3;
    else if(op == '+' || op == '-') return 2;
    else return 1;
}
