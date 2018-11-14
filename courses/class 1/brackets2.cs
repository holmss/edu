using System;
using System.Collections.Generic;

namespace Example
{
    public class Progaem
    {
        public static void Main()
        {
            Console.Write(">>");

            string inp = Console.ReadLine();
            bool result = false;
            if (inp != null)
            {
                char[] myInp = inp.ToCharArray();
                
                List<int> resultArr = new List<int>();
                bool forceStop = false;
                for (int i = 0; i < myInp.Length; i++)
                {
                    char temp = myInp[i];


                    if (temp == '(')
                    {
                        resultArr.Add(1);
                        Console.Write(" +");
                    }
                    else if (temp == ')')
                    {
                        if (resultArr.Count > 0)
                        {
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
                if (resultArr.Count == 0 && !forceStop)
                {
                    result = true;
                }
            }
            
            Console.WriteLine();
            Console.WriteLine(result.ToString());

            //Console.ReadKey();
        }

        //public static void Main()
        //{
        //    Console.Write(">>");
        //    char[] s = (Console.ReadLine()).ToCharArray();
        //    if (s.Length != 0)
        //    {
        //        bool ind = true, closer = true;

        //        List<int> square = new List<int>();
        //        List<int> round = new List<int>();

        //        for (int i = 0; i < s.Length; i++)
        //        {
        //            char temp = s[i];

        //            if (temp == '(')
        //            {

        //                round.Add(1);
        //                Console.Write(" +");
        //            }
        //            else if (temp == ')')
        //            {
        //                if (round.Count > 0)
        //                {

        //                    round.RemoveAt(round.Count - 1);
        //                    Console.Write(" -");
        //                }
        //                else
        //                {
        //                    closer = false;
        //                    break;
        //                }
        //            }

        //            if (temp == '[')
        //            {

        //                square.Add(1);
        //                Console.Write(" +");
        //            }
        //            else if (temp == ']')
        //            {
        //                if (square.Count > 0)
        //                {

        //                    square.RemoveAt(square.Count - 1);
        //                    Console.Write(" -");
        //                }
        //                else
        //                {
        //                    closer = false;
        //                    break;
        //                }
        //            }
        //        }
        //        if (round.Count == 0 && square.Count == 0 && !ind && closer)
        //        {
        //            closer = true;
        //        }
        //        Console.WriteLine(" " + closer);
        //    }
        //    //Console.ReadKey();
        //}
    }
}
