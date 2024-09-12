using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab4
{
    public interface IMatrix
    {
        int I { get; }
        int J { get; }

        int this[int i, int j] { get; }

        IMatrix Transp();

        int Min();

        string ToString();
    }
}
