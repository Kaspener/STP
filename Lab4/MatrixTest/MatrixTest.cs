using Lab4;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace MatrixTest
{
    [TestClass]
    public class MatrixTest
    {
        [TestMethod]
        public void Constructor_ValidInput_CreatesMatrix()
        {
            int[,] data = { { 1, 2 }, { 3, 4 } };
            Matrix matrix = new Matrix(data);

            Assert.AreEqual(2, matrix.I);
            Assert.AreEqual(2, matrix.J);
            Assert.AreEqual(1, matrix[0, 0]);
            Assert.AreEqual(4, matrix[1, 1]);
        }

        [TestMethod]
        public void Constructor_InvalidInput_ThrowsException_EmptyMatrix()
        {
            int[,] data = { };

            Assert.ThrowsException<ArgumentException>(() => new Matrix(data));
        }

        [TestMethod]
        public void Equals_TwoEqualMatrices_ReturnsTrue()
        {
            Matrix matrix1 = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });
            Matrix matrix2 = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });

            Assert.IsTrue(matrix1.Equals(matrix2));
        }

        [TestMethod]
        public void Equals_TwoDifferentMatrices_ReturnsFalse()
        {
            Matrix matrix1 = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });
            Matrix matrix2 = new Matrix(new int[,] { { 5, 6 }, { 7, 8 } });

            Assert.IsFalse(matrix1.Equals(matrix2));
        }

        [TestMethod]
        public void Equals_TwoDifferentSizes()
        {
            Matrix matrix1 = new Matrix(new int[,] { { 1, 2 }, { 3, 4 }, { 6, 2 } });
            Matrix matrix2 = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });

            Assert.ThrowsException<InvalidOperationException>(() => matrix1 == matrix2);
        }

        [TestMethod]
        public void Equals_TwoDifferentTypes()
        {
            Matrix matrix1 = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });

            Assert.IsFalse(matrix1.Equals(new int[,] { { 1, 2 }, { 3, 4 } }));
        }

        [TestMethod]
        public void Equals_Null()
        {
            Matrix matrix1 = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });

            Assert.IsFalse(matrix1.Equals(null));
        }

        [TestMethod]
        public void Inequals_TwoDifferentMatrices_ReturnsTrue()
        {
            Matrix matrix1 = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });
            Matrix matrix2 = new Matrix(new int[,] { { 1, 2 }, { 3, 5 } });

            Assert.IsTrue(matrix1 != matrix2);
        }

        [TestMethod]
        public void Add_TwoMatrices_ReturnsCorrectResult()
        {
            Matrix matrix1 = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });
            Matrix matrix2 = new Matrix(new int[,] { { 5, 6 }, { 7, 8 } });
            Matrix result = matrix1 + matrix2;

            Assert.AreEqual(new Matrix(new int[,] { { 6, 8 }, { 10, 12 } }), result);
        }

        [TestMethod]
        public void Add_TwoMatrices_DifferentI()
        {
            Matrix matrix1 = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });
            Matrix matrix2 = new Matrix(new int[,] { { 5, 6 }, { 7, 8 }, { 6, 2} });
            Assert.ThrowsException<InvalidOperationException>(() => matrix1 + matrix2);
        }

        [TestMethod]
        public void Subtract_TwoMatrices_ReturnsCorrectResult()
        {
            Matrix matrix1 = new Matrix(new int[,] { { 5, 6 }, { 7, 8 } });
            Matrix matrix2 = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });
            Matrix result = matrix1 - matrix2;

            Assert.AreEqual(new Matrix(new int[,] { { 4, 4 }, { 4, 4 } }), result);
        }

        [TestMethod]
        public void Subtract_TwoMatrices_DifferentI()
        {
            Matrix matrix1 = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });
            Matrix matrix2 = new Matrix(new int[,] { { 5, 6 }, { 7, 8 }, { 1, 2} });
            Assert.ThrowsException<InvalidOperationException>(() => matrix1 - matrix2);
        }

        [TestMethod]
        public void Multiply_TwoMatrices_ReturnsCorrectResult()
        {
            Matrix matrix1 = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });
            Matrix matrix2 = new Matrix(new int[,] { { 5, 6 }, { 7, 8 } });
            Matrix result = matrix1 * matrix2;

            Assert.AreEqual(new Matrix(new int[,] { { 19, 22 }, { 43, 50 } }), result);
        }

        [TestMethod]
        public void Multiply_TwoMatrices_WrongSizes()
        {
            Matrix matrix1 = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });
            Matrix matrix2 = new Matrix(new int[,] { { 5, 6 }, { 7, 8 }, { 1, 2 } });
            Assert.ThrowsException<InvalidOperationException>(() => matrix1 * matrix2);
        }

        [TestMethod]
        public void Min_ReturnsMinimumElement()
        {
            Matrix matrix = new Matrix(new int[,] { { 5, 3 }, { 7, 1 } });
            int minElement = matrix.Min();

            Assert.AreEqual(1, minElement);
        }

        [TestMethod]
        public void Transp_ReturnsTransposedMatrix()
        {
            Matrix matrix = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });
            Matrix result = matrix.Transp();

            Assert.AreEqual(new Matrix(new int[,] { { 1, 3 }, { 2, 4 } }), result);
        }

        [TestMethod]
        public void Transp_ErrorSize()
        {
            Matrix matrix = new Matrix(new int[,] { { 1, 2 }, { 3, 4 }, { 5, 6 } });

            Assert.ThrowsException<InvalidOperationException>(() => matrix.Transp());
        }

        [TestMethod]
        public void ToString_ReturnsCorrectStringRepresentation()
        {
            Matrix matrix = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });
            string result = matrix.ToString();

            Assert.AreEqual("{{1,2},{3,4}}", result);
        }

        [TestMethod]
        public void Indexer_ValidIndexes_ReturnsCorrectElement()
        {
            Matrix matrix = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });
            Assert.AreEqual(1, matrix[0, 0]);
            Assert.AreEqual(4, matrix[1, 1]);
        }

        [TestMethod]
        public void Indexer_InvalidIndexes_ThrowsException()
        {
            Matrix matrix = new Matrix(new int[,] { { 1, 2 }, { 3, 4 } });

            Assert.ThrowsException<IndexOutOfRangeException>(() => { var element = matrix[2, 2]; });
        }
    }
}
