using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace app2111
{
    class Program
    {
        static void Main(string[] args)
        {
            //data types

            /*int i;
            uint ui;

            //string s = Console.ReadLine();

            i = Convert.ToInt32(Console.ReadLine());
            ui = Convert.ToUInt32(Console.ReadLine());

            ui = 4294967295;

            //ui = ui - Convert.ToUInt32(i);
            Console.WriteLine(ui);*/

            //if-else

            /*string name = Console.ReadLine();
            int age = Convert.ToInt32(Console.ReadLine());

            if(name == "Alexandr" && age == 18)
            {
                Console.WriteLine("Hello, Sasha");
            }
            if ((name == "Alexandr" || name == "Alexey") && age == 18)
            {
                Console.WriteLine("Hello, Alex");
            }
            else if (name == "Ekaterina" && age == 18)
            {
                Console.WriteLine("Hello, Katya");
            }
            else if (name == "Ekaterna" && age == 18)
            {
                Console.WriteLine("Hello, Katerina");
            }
            else if (name == "Maria" && age == 18)
            {
                Console.WriteLine("Hello, Masha");
            }
            else if(age >= 18)
            {
                Console.WriteLine("Hello, " + name);
            }
            else
            {
                Console.WriteLine("You`re not 18");
            }*/

            //switch-case

            //string name = Console.ReadLine();

            //switch (name)
            //{
            //    case "Alexandr":
            //        Console.WriteLine("Hello, Alex");
            //        break;
            //    case "Ekaterina":
            //        Console.WriteLine("Hello, Katya");
            //        break;
            //    default:
            //        Console.WriteLine("Hello, " + name);
            //        break;
            //}

            /*int i = Convert.ToInt32(Console.ReadLine());

            switch (i)
            {
                case 1:
                    Console.WriteLine(++i); //i++ 
                    break;
                case 2:
                    Console.WriteLine(i *= 4);  //i = i * 2
                    break;
                case 3:
                    Console.WriteLine(i *= i);  //i = i * i
                    break;
                default:
                    Console.WriteLine(i);
                    break;
            }*/

            // ?:

            /*int i = Convert.ToInt32(Console.ReadLine());
            bool b;

            b = i == 1 ? false : true;
            Console.WriteLine(b);*/


            //for

            //for (int i = 0; i < 10; i++)
            //{
            //    Console.Write(i + " ");
            //}

            //bool b = true;
            ////int i = 0;

            //for (; b;)    //b == true (!b => b == false)
            //{
            //    string h = Console.ReadLine();
            //    if (h == "stop")
            //        b = false;
            //}

            //while (b)
            //{
            //    string h = Console.ReadLine();
            //    if (h == "stop")
            //        b = false;
            //}

            while (true)
            {
                Console.WriteLine("Hello World ");
            }

            //for(; ; )
            //{
            //    Console.Write("Hello World ");
            //}
        }
    }
}
