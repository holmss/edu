using System;

namespace Example
{
    public class Brackets
    {
        public static bool Check()
        {

            int square = 0, round = 0;
            bool ind = false;
            Console.Write(">> ");
            string s = Console.ReadLine();

            //! null
            foreach (char i in s)
            {
                NewMethod(ref square, ref round, ref ind, i);
                if (round == 0)
                    ind = false;
                if (round < 0 || square < 0)
                    break;
                if (ind && square == 0 && round != 0)
                    break;
            }
            return (round == 0 && square == 0 ? true : false);
        }

        private static void NewMethod(ref int square, ref int round, ref bool ind, char i)
        {
            switch (i)
            {
                case ')':
                    round--; break;
                case '(':
                    round++; break;
                case '[':
                    square++; ind = true; break;
                case ']':
                    square--; ind = true; break;
                default:
                    break;
            }
        }
    }
}

