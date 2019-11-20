#include <bits/stdc++.h>
using namespace std;

// operator sequence function

int precedence(char op)
{
    if(op == '+'||op == '-')
        return 1;
    if(op == '*'||op == '/')
        return 2;
    if(op == '^')
        return 3;
    return 0;
}

//calculation function

double operation(double a, double b, char op)
{
    switch(op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a,b);

    }
}

double evaluate(string tokens)
{
    int i;

    stack <double> values;     // value store korar jonno

    stack <char> ops;       // operator store korar jonno

    for(i = 0; i < tokens.length(); i++)
    {

        if(tokens[i] == ' ')
            continue;

        else if(tokens[i] == '(')
        {
            ops.push(tokens[i]);
        }

        else if((tokens[i]>=48 && tokens[i]<=57) || tokens[i]==46)
        {
            double val = 0.0;
            int j=0,d=0,e=0;

            while(i < tokens.length() &&
                    (tokens[i]>=48 && tokens[i]<=57) || tokens[i]==46)
            {
                if(tokens[i]==46){
                    d=1;
                    i++;
                    continue;
                }

                else {
                    if(d==1)e++;
                    val = (val*10) + (tokens[i]-'0');
                }
                i++;
                j++;
            }
            double r=pow(10,e);
            double res=(val*1)/(r*1);

            //cout<<fixed<<setprecision(2)<<res<<endl;

            values.push(res);
            i--;
            //cout<<i<<endl;

        }

        else if(tokens[i] == ')')
        {
            while(!ops.empty() && ops.top() != '(')
            {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(operation(val1, val2, op));
            }

            // pop opening brace.
            if(!ops.empty())
                ops.pop();
        }

        else
        {
            while(!ops.empty() && precedence(ops.top())
                    >= precedence(tokens[i]))
            {
                double val2 = values.top();
                values.pop();

                double val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(operation(val1, val2, op));
            }

            ops.push(tokens[i]);

        }
    }

    while(!ops.empty())
    {
        double val2 = values.top();
        values.pop();

        double val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();


        values.push(operation(val1, val2, op));
    }

    return values.top();         // shesh porjonto je value ta thakbe setai result
}

int main()
{
    string str;
    cin>>str;

    //cout<<str.size();

    double result=evaluate(str);
    //cout<<fixed()<<setprecision<<result<<endl;

    printf("%f\n",result);
    return 0;
}
