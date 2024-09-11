using Lab2;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace UnitTestLab2
{
    [TestClass]
    public class GetMax
    {
        [TestMethod]
        public void GetMaxC()
        {
            //arrange
            double a = 3.5;
            double b = 5;
            double c = 12.3;
            //act
            double result = Lab2.Program.GetMax(a, b, c);
            //assert
            Assert.AreEqual(c, result);
        }

        [TestMethod]
        public void GetMaxB()
        {
            //arrange
            double a = 3.5;
            double b = 51.2;
            double c = 12.3;
            //act
            double result = Lab2.Program.GetMax(a, b, c);
            //assert
            Assert.AreEqual(b, result);
        }

        [TestMethod]
        public void GetMaxA()
        {
            //arrange
            double a = 133.5;
            double b = 133.5;
            double c = 133.5;
            //act
            double result = Lab2.Program.GetMax(a, b, c);
            //assert
            Assert.AreEqual(a, result);
        }
        [TestMethod]
        public void GetMaxC2()
        {
            //arrange
            double a = 133.5;
            double b = 51.2;
            double c = 183.3;
            //act
            double result = Lab2.Program.GetMax(a, b, c);
            //assert
            Assert.AreEqual(c, result);
        }
    }

    [TestClass]
    public class ProductOfEvenIndexSum
    {
        [TestMethod]
        public void OneElement()
        {
            //arrange
            double[,] A = { { 5.0 } };
            //act
            double result = Lab2.Program.ProductOfEvenIndexSum(A);
            //assert
            Assert.AreEqual(5.0, result);
        }
        [TestMethod]
        public void TwoSizeLenghts()
        {
            //arrange
            double[,] A = {
                { 2.0, 3.0 },
                { 4.0, 5.0 }
            };
            //act
            double result = Lab2.Program.ProductOfEvenIndexSum(A);
            //assert
            Assert.AreEqual(10.0, result);
        }
        [TestMethod]
        public void ZeroElements()
        {
            //arrange
            double[,] A = { { } };
            //act
            double result = Lab2.Program.ProductOfEvenIndexSum(A);
            //assert
            Assert.AreEqual(0, result);
        }
    }

    [TestClass]
    public class FindMinOnAndBelowMainDiagonal
    {
        [TestMethod]
        public void OneElement()
        {
            //arrange
            double[,] A = { { 5.0 } };
            //act
            double result = Lab2.Program.FindMinOnAndBelowMainDiagonal(A);
            //assert
            Assert.AreEqual(5.0, result);
        }

        [TestMethod]
        public void ManyElement()
        {
            //arrange
            double[,] A = { 
                { 5.0, 3.2 },
                { 3.5, 5.2 } 
            };
            //act
            double result = Lab2.Program.FindMinOnAndBelowMainDiagonal(A);
            //assert
            Assert.AreEqual(3.5, result);
        }

        [TestMethod]
        public void NullArray()
        {
            //arrange
            //act
            //assert
            Assert.ThrowsException<ArgumentException>(() => Lab2.Program.FindMinOnAndBelowMainDiagonal(null));
        }

        [TestMethod]
        public void ZeroLengthArray()
        {
            //arrange
            double[,] A = { };
            //act
            //assert
            Assert.ThrowsException<ArgumentException>(() => Lab2.Program.FindMinOnAndBelowMainDiagonal(A));
        }
        [TestMethod]
        public void ZeroLengthSubArray()
        {
            //arrange
            double[,] A = { { } };
            //act
            //assert
            Assert.ThrowsException<ArgumentException>(() => Lab2.Program.FindMinOnAndBelowMainDiagonal(A));
        }
    }
}
