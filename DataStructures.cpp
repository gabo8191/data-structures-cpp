#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

struct Node
{
    char data;
    Node *next;
};

class LinkedList
{
private:
    Node *head;

public:
    LinkedList() : head(nullptr) {}

    void insert(char data)
    {
        Node *newNode = new Node{data, nullptr};
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    bool isEmpty() const
    {
        return !head;
    }

    char remove()
    {
        if (isEmpty())
        {
            return '\0';
        }

        char data = head->data;
        Node *temp = head;
        head = head->next;
        delete temp;

        return data;
    }
};

bool evaluateParentheses(const string &expression)
{
    stack<pair<char, int>> stack; // Pair to store the symbol and its position
    const unordered_map<char, char> parentheses = {{')', '('}, {']', '['}, {'}', '{'}};

    for (int i = 0; i < expression.size(); ++i)
    {
        char c = expression[i];
        if (parentheses.count(c) > 0)
        {
            if (stack.empty() || stack.top().first != parentheses.at(c))
            {
                cout << "La expresion ingresada tiene un parentesis de cierre '" << c << "' sin su correspondiente parentesis de apertura en la posicion " << i + 1 << "." << endl;
                return false;
            }
            stack.pop();
        }
        else if (c == '(' || c == '[' || c == '{')
        {
            stack.push({c, i + 1}); // Store the symbol and its position
        }
    }

    if (!stack.empty())
    {
        cout << "La expresion ingresada tiene un parentesis de apertura '" << stack.top().first << "' sin su correspondiente parentesis de cierre en la posicion " << stack.top().second << "." << endl;
        return false;
    }

    cout << "La expresion ingresada tiene la cantidad correcta de parentesis." << endl;
    return true;
}

string convertToPostfix(const string &expression)
{
    string postfix;
    stack<char> stack;
    const unordered_map<char, int> precedence = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

    for (char c : expression)
    {
        if (isdigit(c))
        {
            postfix += c;
        }
        else if (c == '(')
        {
            stack.push(c);
        }
        else if (c == ')')
        {
            while (!stack.empty() && stack.top() != '(')
            {
                postfix += stack.top();
                stack.pop();
            }
            stack.pop();
        }
        else if (precedence.count(c) > 0)
        {
            while (!stack.empty() && stack.top() != '(' && precedence.at(stack.top()) >= precedence.at(c))
            {
                postfix += stack.top();
                stack.pop();
            }
            stack.push(c);
        }
    }

    while (!stack.empty())
    {
        postfix += stack.top();
        stack.pop();
    }

    return postfix;
}

int evaluatePostfixExpression(const string &expression)
{
    stack<int> stack;

    for (char c : expression)
    {
        if (isdigit(c))
        {
            stack.push(c - '0');
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            if (stack.size() < 2)
            {
                return 0; // Invalid expression
            }

            int operand2 = stack.top();
            stack.pop();
            int operand1 = stack.top();
            stack.pop();

            int result;
            switch (c)
            {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            }

            stack.push(result);
        }
    }

    return stack.size() == 1 ? stack.top() : 0; // Invalid expression
}

int main()
{
    int option;
    string expression;
    int result = 0; // Declare result outside the switch statement

    do
    {
        cout << "1. Evaluar parentesis" << endl;
        cout << "2. Evaluar expresion aritmetica" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> option;

        if (cin.fail()) // Check for invalid input
        {
            cin.clear();           // Clear the error flag
            cin.ignore(100, '\n'); // Ignore the rest of the input buffer
            cout << "Opcion invalida. Ingrese un numero valido." << endl;
            continue;
        }

        switch (option)
        {
        case 1:
            cout << "Ingrese la expresion: ";
            cin >> expression;
            evaluateParentheses(expression);
            break;
        case 2:
            cout << "Ingrese la expresion: ";
            cin.ignore(); // Clear newline character from the buffer
            getline(cin, expression);
            cout << "Expresion en notacion postfija: " << convertToPostfix(expression) << endl;
            result = evaluatePostfixExpression(convertToPostfix(expression));
            if (result != 0)
            {
                cout << "El resultado es: " << result << endl;
            }
            else
            {
                cout << "Expresion aritmetica invalida" << endl;
            }
            break;
        case 3:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion invalida. Ingrese un numero entre 1 y 3." << endl;
            break;
        }

        cout << endl;
    } while (option != 3);

    return 0;
}