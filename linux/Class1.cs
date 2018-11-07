using System;
using System.Collections.Generic;

namespace Example
{
    public class Progaem
    {
        public static void XMain()

        {
            Console.Write(">>");

            string inp = Console.ReadLine();
            bool result = false;
            if (inp != null)
            {
                char[] myInp = inp.ToCharArray();

                //Stack<int> resultStack = new Stack<int>();
                List<int> resultArr = new List<int>();
                bool forceStop = false;
                for (int i = 0; i < myInp.Length; i++)
                {
                    char temp = myInp[i];


                    if (temp == '(')
                    {
                        //resultStack.Push(1);
                        resultArr.Add(1);
                        Console.Write(" +");
                    }
                    else if (temp == ')')
                    {
                        if (resultArr.Count > 0)//resultStack.Count > 0)
                        {
                            //int k = resultStack.Pop();
                            resultArr.RemoveAt(resultArr.Count - 1);
                            Console.Write(" -");
                        }
                        else
                        {
                            forceStop = true;
                            break;
                        }
                    }
                }
                if (resultArr.Count == 0 && !forceStop) //resultStack.Count == 0)
                {
                    result = true;
                }
            }
            Console.WriteLine();
            Console.WriteLine(result.ToString());
        }

        public static void MyMain()
        {
            Console.Write(">>");
            char[] s = (Console.ReadLine()).ToCharArray();
            if (s.Length != 0)
            {
                bool ind = true, closer = true;

                List<int> square = new List<int>();
                List<int> round = new List<int>();

                for (int i = 0; i < s.Length; i++)
                {
                    char temp = s[i];

                    if (temp == '(')
                    {

                        round.Add(1);
                        Console.Write(" +");
                    }
                    else if (temp == ')')
                    {
                        if (round.Count > 0)
                        {

                            round.RemoveAt(round.Count - 1);
                            Console.Write(" -");
                        }
                        else
                        {
                            closer = false;
                            break;
                        }
                    }
                }
                if (round.Count == 0 && !ind && closer)
                {
                    closer = true;
                }
            }

        }
    }
}
