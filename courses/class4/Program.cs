using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace app51218
{
    public class Triangle
    {
        public double square;

        public static double Perimetr(double a, double b, double c)
        {
            return a + b + c;
        }

        public static double Square(double a, double b, double c)
        {
            double p = Triangle.Perimetr(a, b, c) / 2;

            return Math.Sqrt(p * (p - a) * (p - b) * (p - c));
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Triangle triangle = new Triangle();
            //double a, b, c;
            char a = Convert.ToChar(Console.ReadLine());
            bool b;
            ulong p;    //unsigned long (0 -> 2^64 - 1)
            uint t;     //unsigned int (0 -> 2^32 - 1)
            int j;      //int (-2^16 -> 2^16 - 1)

            Console.WriteLine(a);

            //Console.WriteLine("Enter the triangle sides: ");

            //a = Convert.ToDouble(Console.ReadLine());
            //b = Convert.ToDouble(Console.ReadLine());
            //c = Convert.ToDouble(Console.ReadLine());

            //triangle.square = Triangle.Square(a, b, c);
            //Console.WriteLine(triangle.square);
            //Console.WriteLine(Math.PI);
            //Console.WriteLine(String.Format("{0:0}", Math.PI));
        }
    }
}
