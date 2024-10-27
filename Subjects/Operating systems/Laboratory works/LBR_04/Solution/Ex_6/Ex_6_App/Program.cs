using System;
using System.Threading;

// Maxim Stanchik
class Program
{
    static int Count = 0;
    static readonly object lockObject = new object(); 

    static void WorkThread()
    {
        for (int i = 0; i < 5000000; ++i)
        {
            lock (lockObject)
            {
                Count++;
            }
        }
    }

    static void Main(string[] args)
    {
        Thread[] t = new Thread[20];

        for (int i = 0; i < 20; ++i)
        {
            t[i] = new Thread(WorkThread);
            t[i].Start();
        }

        for (int i = 0; i < 20; ++i)
        {
            t[i].Join();
        }

        Console.WriteLine($"Результат Count: {Count}");
        Console.WriteLine($"Ожидаемое значение: {20 * 5000000}");
    }
}