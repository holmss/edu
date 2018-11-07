using System;
using System.Collections.Generic;

namespace Example
{
    class Program
    {
        static void Main()
        {
            while (true)
                Console.WriteLine(Brackets.Check());

            // string[] s = new string[3];//? Структура и модификаторы доступа
            // for (int i = 0; i < 3; i++)
            // {
            //     Console.Write("IN>> ");
            //     s[i] = Console.ReadLine();
            // }
            // foreach (var item in Library.Create(s))
            //     Console.WriteLine(item.toStr());
        }
    }
}
