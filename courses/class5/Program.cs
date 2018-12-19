using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//что такое метод? 
// какой метод является точкой входа программы?

/* Методы объфявляются в классах или структурах путем указания модификатора доступа
 * а также: возвращаемого значения и имени метода, а после указания в скобках через запятую параметров
 * Методы вызываются через "."*/ 

//программка для быстрой печати - VerseQ

namespace app2811
{
    public class Math
    {
        public static int Factorial(int i)
        {
            if (i == 2)
            {
                return 2;
            }
            int m = i * Factorial(i - 1);
            return m;
        }

        public static int Power(int num, int pow)
        {
            int n = 1;
            for (int k = 0; k < pow; k++)
            {
                n *= num; //n = n * num
            }
            return n;
        }

        public static void Print(int a)
        {
            Console.WriteLine(a);
        }

        public static bool IsEven(int a)
        {
            if (a % 2 == 0)
            {
                return true;
            }
            return false;
        }

        public static int KSum(ref int k)
        {
            k++;
            return k;
        }
    }

    class Program
    {
        static void Main()
        {
            //int n = Convert.ToInt32(Console.ReadLine());

            //Console.WriteLine(Math.Factorial(n));

            //int y = Convert.ToInt32(Console.ReadLine());
            //Console.WriteLine(Math.Power(n, y));

            //Math.Print(y);

            //bool b = false;
            //b = Math.IsEven(n);

            //switch (b)
            //{
            //    case true:
            //        Console.WriteLine("Number " + n + " is even");
            //        break;
            //    case false:
            //        Console.WriteLine("Number " + n + " is not even");
            //        break;
            //}

            //int k = 1;
            //Console.WriteLine(Math.KSum(ref k));
            //Console.WriteLine(k);

            try
            {
                int m = 5;
                //int n = m / 0;
            }
            catch
            {
                Console.WriteLine("Can`t execute m/0");
            }
            finally
            {
                Console.WriteLine("Finally we`re here");
            }
            //Console.WriteLine(n);
        }
    }
}
