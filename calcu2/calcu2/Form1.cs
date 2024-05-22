using System;
using System.Collections.Generic;
using System.Globalization;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace calcu2
{
    public partial class Form1 : Form
    {
        string currentExpression;
        string previousResult = "";

        public Form1()
        {
            InitializeComponent();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            string buttonText = ((Button)sender).Text;
            if (display.Text == "0" || previousResult != "")
            {
                previousResult = "";
                display.Text = buttonText;
                currentExpression = buttonText;
            }
            else
            {
                if (!(display.Text == "0" && buttonText == "0"))
                {
                    currentExpression += buttonText;
                    display.Text += buttonText;
                }
            }
        }

        static double EvaluateExpression(string expression)
        {
            Stack<double> values = new Stack<double>();
            Stack<char> operators = new Stack<char>();
            int i = 0;

            while (i < expression.Length)
            {
                if (char.IsDigit(expression[i]) || expression[i] == '.')
                {
                    string number = "";
                    while (i < expression.Length && (char.IsDigit(expression[i]) || expression[i] == '.'))
                    {
                        number += expression[i];
                        i++;
                    }
                    values.Push(double.Parse(number, CultureInfo.InvariantCulture));
                }
                else
                {
                    while (operators.Count > 0 && GetPrecedence(operators.Peek()) >= GetPrecedence(expression[i]))
                    {
                        ApplyOperator(values, operators);
                    }
                    operators.Push(expression[i]);
                    i++;
                }
            }

            while (operators.Count > 0)
            {
                ApplyOperator(values, operators);
            }

            return values.Pop();
        }

        static int GetPrecedence(char operatorChar)
        {
            switch (operatorChar)
            {
                case '+':
                case '-':
                    return 1;
                case '*':
                case '/':
                    return 2;
                default:
                    return 0;
            }
        }

        private void button14_Click(object sender, EventArgs e)
        {
            double result = EvaluateExpression(currentExpression);
            previousResult += result;
            display.Text = result.ToString();
            currentExpression = result.ToString();
        }

        static void ApplyOperator(Stack<double> values, Stack<char> operators)
        {
            double operand2 = values.Pop();
            double operand1 = values.Pop();
            char operatorChar = operators.Pop();

            switch (operatorChar)
            {
                case '+':
                    values.Push(operand1 + operand2);
                    break;
                case '-':
                    values.Push(operand1 - operand2);
                    break;
                case '*':
                    values.Push(operand1 * operand2);
                    break;
                case '/':
                    values.Push(operand1 / operand2);
                    break;
            }
        }

        private void button17_Click(object sender, EventArgs e)
        {
            display.Text = "";
            currentExpression = "";
        }
    }
}
