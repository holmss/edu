using System;
using System.Collections.Generic;

namespace Example
{
    public class Library
    {
        public struct Book
        {

            private string Name;
            private int Year;
            private string Author;
            public Book(string[] info) //? как в вашем СИ-хештег сделать нормальный конструктор???
            {
                //! null
                //! not enouth arguments
                Name = info[0];
                int.TryParse(info[1], out Year);
                Author = info[2];
            }

            public string toStr() => Name + '\t' + Year.ToString() + '\t' + Author;
        }

        public static List<Book> Create(string[] books)
        {
            List<Book> lib = new List<Book>();

            //! null array
            foreach (string book in books)
                lib.Add(new Book(book.Split(' ', 3)));
            // catch
            // {
            //     Console.WriteLine("Wrong format!");
            //     return null;
            // }

            return lib;
        }
    }
}