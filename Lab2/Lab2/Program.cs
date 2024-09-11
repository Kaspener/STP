using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    public class Program
    {
        public static double GetMax(double a, double b, double c)
        {
            if (a >= b)
            {
                if (a >= c)
                    return a;
                return c;
            }
            if (b >= c)
                return b;
            return c;
        }

        public static double ProductOfEvenIndexSum(double[,] A)
        {
            double product = 1.0;
            bool found = false;

            for (int i = 0; i < A.GetLength(0); i++)
            {
                for (int j = 0; j < A.GetLength(1); j++)
                {
                    if ((i + j) % 2 == 0)
                    {
                        product *= A[i, j];
                        found = true;
                    }
                }
            }
            if (!found)
                product = 0;
            return product;
        }

        public static double FindMinOnAndBelowMainDiagonal(double[,] A)
        {
            if (A == null || A.GetLength(0) == 0 || A.GetLength(1) == 0)
            {
                throw new ArgumentException("Null array or empty");
            }

            double min = A[0, 0];

            for (int i = 0; i < A.GetLength(0); i++)
            {
                for (int j = 0; j <= i; j++)
                {
                    if (A[i, j] < min)
                    {
                        min = A[i, j];
                    }
                }
            }

            return min;
        }
    }
}
