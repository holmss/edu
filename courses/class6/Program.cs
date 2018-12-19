using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace app121218
{
    class Program
    {
        static void Main(string[] args)
        {
            Random rnd = new Random();
            int[] nums = new int[4];
            //---------------------------------------------
            //int[] nums = new int[4] { 1, 2, 3, 5 };
            //int[] nums = new int[] { 1, 2, 3, 5 };
            //int[] nums = new[] { 1, 2, 3, 5 };
            //int[] nums = { 1, 2, 3, 5 };
            
            //for (int i = 0; i < nums.Length; i++)
            //{
            //    Console.Write(nums[i] + " ");
            //}

            //foreach (int i in nums)
            //{
            //    Console.Write(i + " ");
            //}

            //for (int i = 0; i < nums.Length; i++)
            //{
            //    nums[i] = Convert.ToInt32(Console.ReadLine());
            //}

            for (int i = 0; i < nums.Length; i++)
            {
                nums[i] = rnd.Next(0,100);
            }

            foreach (int i in nums)
            {
                Console.Write(i + " ");
            }
        }
    }
}
