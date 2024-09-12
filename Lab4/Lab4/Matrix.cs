using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading.Tasks;

namespace Lab4
{
    public class Matrix : IMatrix
    {
        private readonly int[,] matrix;

        public int I { get; }
        public int J { get; }

        public Matrix(int[,] matrix)
        {
            if (matrix.GetLength(0) < 1 || matrix.GetLength(1) < 1)
            {
                throw new ArgumentException("The number of I and J must be greater than 0");
            }
            this.matrix = (int[,])matrix.Clone();
            I = matrix.GetLength(0);
            J = matrix.GetLength(1);
        }

        public int this[int i, int j]
        {
            get
            {
                if (i < 0 || i >= I || j < 0 || j >= J)
                    throw new IndexOutOfRangeException("Indexes are out of range of acceptable values");
                return matrix[i, j];
            }
        }

        public static Matrix operator +(Matrix a, Matrix b)
        {
            if (a.I != b.I || a.J != b.J) 
            {
                throw new InvalidOperationException("Matrices must be of the same sizes");
            }

            int[,] result = new int[a.I, a.J];

            for (int i = 0; i < a.I; ++i)
            {
                for(int j = 0; j < a.J; ++j)
                {
                    result[i, j] = a.matrix[i, j] + b.matrix[i, j];
                }
            }
            return new Matrix(result);
        }

        public static Matrix operator -(Matrix a, Matrix b)
        {
            if (a.I != b.I || a.J != b.J)
            {
                throw new InvalidOperationException("Matrices must be of the same sizes");
            }

            int[,] result = new int[a.I, a.J];

            for (int i = 0; i < a.I; ++i)
            {
                for (int j = 0; j < a.J; ++j)
                {
                    result[i, j] = a.matrix[i, j] - b.matrix[i, j];
                }
            }
            return new Matrix(result);
        }

        public static Matrix operator *(Matrix a, Matrix b)
        {
            if (a.J != b.I)
                throw new InvalidOperationException("Matrices are not consistent for multiplication");

            int[,] result = new int[a.I, b.J];
            for (int i = 0; i < a.I; i++)
            {
                for (int j = 0; j < b.J; j++)
                {
                    for (int k = 0; k < a.J; k++)
                    {
                        result[i, j] += a[i, k] * b[k, j];
                    }
                }
            }
            return new Matrix(result);
        }

        public static bool operator ==(Matrix a, Matrix b)
        {
            if (a.I != b.I || a.J != b.J)
                throw new InvalidOperationException("Matrices are not consistent for multiplication");

            for (int i = 0; i < a.I; i++)
            {
                for (int j = 0; j < a.J; j++)
                {
                    if (a[i, j] != b[i, j]) return false;
                }
            }
            return true;
        }

        public static bool operator !=(Matrix a, Matrix b) => !(a == b);

        public IMatrix Transp()
        {
            if (I != J)
            {
                throw new InvalidOperationException("Matrix must have the same number of rows and columns");
            }
            int[,] result = new int[J, I];
            for (int i = 0; i < I; i++)
            {
                for (int j = 0; j < J; j++)
                {
                    result[j, i] = matrix[i, j];
                }
            }
            return new Matrix(result);
        }

        public int Min()
        {
            int min = matrix[0, 0];
            foreach (int num in matrix)
            {
                min = Math.Min(min, num);
            }
            return min;
        }

        public override string ToString()
        {
            string str = "{";
            for (int i = 0; i < I; ++i)
            {
                str += "{";
                for (int j = 0; j < J - 1; ++j)
                {
                    str += matrix[i, j].ToString() + ",";
                }
                str += matrix[i, J - 1].ToString() + "}";
                if (i != I - 1) str += ",";
            }
            str += "}";
            return str;
        }
        
        public override bool Equals(object obj)
        {
            if (obj == null || GetType() != obj.GetType())
                return false;

            Matrix other = obj as Matrix;

            return this == other;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }
}
