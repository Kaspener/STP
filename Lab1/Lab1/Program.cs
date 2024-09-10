using System;

namespace Lab1
{
    public class Program
    {
        static void Main(string[] args) { }

        public static int ConvertToDecimal(int b, string s)
        {
            int result = 0;
            int power = 1;

            for (int i = s.Length - 1; i >= 0; i--)
            {
                int digitValue;
                if (char.IsDigit(s[i]))
                {
                    digitValue = s[i] - '0';
                }
                else
                {
                    digitValue = char.ToUpper(s[i]) - 'A' + 10;
                }

                if (digitValue >= b)
                {
                    throw new ArgumentException($"Цифра '{s[i]}' недопустима для системы счисления с основанием {b}");
                }

                result += digitValue * power;
                power *= b;
            }

            return result;
        }

        public static (int maxValue, int index) FindMaxElement(int[] array)
        {
            if (array == null || array.Length == 0)
            {
                throw new ArgumentException("Массив не должен быть null или пустым");
            }

            int maxValue = array[0];
            int maxIndex = 0;

            for (int i = 1; i < array.Length; i++)
            {
                if (array[i] > maxValue)
                {
                    maxValue = array[i];
                    maxIndex = i;
                }
            }

            return (maxValue, maxIndex);
        }

        public static int FindMaxOddElementAtOddIndex(int[] array, out int index)
        {
            if (array == null || array.Length == 0)
            {
                throw new ArgumentException("Массив не должен быть null или пустым");
            }

            int maxValue = int.MinValue;
            index = -1;

            for (int i = 1; i < array.Length; i += 2)
            {
                if (array[i] % 2 != 0)
                {
                    if (array[i] > maxValue)
                    {
                        maxValue = array[i];
                        index = i;
                    }
                }
            }

            if (index == -1)
            {
                throw new ArgumentException("Нет нечетных элементов на нечетных индексах");
            }

            return maxValue;
        }
    }
}
