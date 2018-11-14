using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _1411
{
    class Example
    {
        //static void Swap (int a, int b)
        //{
        //    a = a + b;
        //    b = a - b;
        //    a = a - b;

        //    Console.WriteLine(a + " " + b);
        //}

        static void Main(string[] args)
        {
            //var x = "hello";

            //Console.WriteLine((x is string).ToString());

            //---------------------------------------------

            //float i = 1.0f, j = 2.7f;

            //i = i + 3;
            //i += 3;

            //j = i;
            //i = j;

            //Console.WriteLine(i);

            //---------------------------------------------

            //int x = Convert.ToInt32(Console.ReadLine());
            //int x = 1 * 1000 + 2 * 100 + 3 * 10 + 4;
            int x = 1234;
            int j;
            //int i = x % 10;

            int[] arr = new int[4];

            for (int i = arr.Length - 1; i >= 0; i--)
            {
                j = x % 10;
                arr[i] = j;
                x /= 10;
            }

            //Swap(arr[2], arr[3]);


            //int temp;

            //temp = arr[2];
            //arr[2] = arr[3];
            //arr[3] = temp;

            //Console.WriteLine(arr[2]);
            //Console.WriteLine(arr[3]);

            arr[2] = arr[2] + arr[3];
            arr[3] = arr[2] - arr[3];
            arr[2] = arr[2] - arr[3];

            for (int i = 0; i < arr.Length; i++)
            {
                Console.Write(arr[i]);
            }

            //Console.WriteLine(arr[2]);
            //Console.WriteLine(arr[3]);

            Console.WriteLine();

            //x /= 10; // x = x / 10;
            //x %= 10; // x = x % 10;

            //Console.WriteLine(i + " " + x);

            //Console.WriteLine(x % 10);

            //---------------------------------------

            //int x = 3, y = 4;

            //x = y;

        }
    }
}
