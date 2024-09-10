using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;

namespace UnitTestLab1
{
    [TestClass]
    public class TestingConbert
    {
        [TestMethod]
        public void ConvertHEX()
        {
            //arrange
            int footing = 16;
            string number = "153AF";
            //act
            int result = Lab1.Program.ConvertToDecimal(footing, number);
            //assert
            Assert.AreEqual(86959, result);
        }

        [TestMethod]
        public void ConvertBIN()
        {
            //arrange
            int footing = 2;
            string number = "10001110";
            //act
            int result = Lab1.Program.ConvertToDecimal(footing, number);
            //assert
            Assert.AreEqual(142, result);
        }

        [TestMethod]
        public void ConvertDEC()
        {
            //arrange
            int footing = 10;
            string number = "1254236";
            //act
            int result = Lab1.Program.ConvertToDecimal(footing, number);
            //assert
            Assert.AreEqual(1254236, result);
        }

        [TestMethod]
        public void ConvertException()
        {
            //arrange
            int footing = 2;
            string number = "1254236";
            //act
            //assert
            Assert.ThrowsException<ArgumentException>(() => Lab1.Program.ConvertToDecimal(footing, number));
        }
    }

    [TestClass]
    public class TestFindMaxElement
    {
        [TestMethod]
        public void FindMax() 
        {
            //arrange
            int[] array = { 3, 6, 23, 2, 56, 7, 4, 3, 2 };
            //act
            var result = Lab1.Program.FindMaxElement(array);
            //assert
            Assert.AreEqual((56, 4), result);
        }

        [TestMethod]
        public void FindMaxFromEquals()
        {
            //arrange
            int[] array = { 3,3,3,3,3,3,3,3,3,3 };
            //act
            var result = Lab1.Program.FindMaxElement(array);
            //assert
            Assert.AreEqual((3, 0), result);
        }

        [TestMethod]
        public void FindMaxExceptionZeroLenght()
        {
            //arrange
            int[] array = { };
            //act
            //assert
            Assert.ThrowsException<ArgumentException>(() => Lab1.Program.FindMaxElement(array));
        }
        [TestMethod]
        public void FindMaxExceptionNullArray()
        {
            //arrange
            //act
            //assert
            Assert.ThrowsException<ArgumentException>(() => Lab1.Program.FindMaxElement(null));
        }
    }

    [TestClass]
    public class TestFindMaxOddElement
    {
        [TestMethod]
        public void FindMax()
        {
            //arrange
            int[] array = { 3, 6, 23, 2, 56, 7, 4, 3, 2 };
            int index;
            //act
            int value = Lab1.Program.FindMaxOddElementAtOddIndex(array, out index);
            //assert
            Assert.AreEqual((7, 5), (value, index));
        }

        [TestMethod]
        public void NoFindMax()
        {
            //arrange
            int[] array = { 3, 6, 23, 2, 56, 8, 4, 12, 2 };
            int index;
            //act
            //assert
            Assert.ThrowsException<ArgumentException>(() => Lab1.Program.FindMaxOddElementAtOddIndex(array, out index), "Нет нечетных элементов на нечетных индексах");
        }

        [TestMethod]
        public void FindMaxExceptionZeroLenght()
        {
            //arrange
            int[] array = { };
            int index;
            //act
            //assert
            Assert.ThrowsException<ArgumentException>(() => Lab1.Program.FindMaxOddElementAtOddIndex(array, out index), "Массив не должен быть null или пустым");
        }
        [TestMethod]
        public void FindMaxExceptionNullArray()
        {
            //arrange
            int index;
            //act
            //assert
            Assert.ThrowsException<ArgumentException>(() => Lab1.Program.FindMaxOddElementAtOddIndex(null, out index), "Массив не должен быть null или пустым");
            
        }
    }
}
