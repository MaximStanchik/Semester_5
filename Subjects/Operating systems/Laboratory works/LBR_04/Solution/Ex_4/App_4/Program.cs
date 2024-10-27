using System;
using System.Threading;

class Program
{
    static void ThreadZed()
    {
        for (int i = 0; i < 10; i++)
        {
            Console.Write(" (Z-{0}) ", Thread.CurrentThread.ManagedThreadId);
            Thread.Sleep(1000);
        }
        Console.WriteLine(" Поток Z завершается ");
    }

    static void ThreadWithParam(object o)
    {
        for (int i = 0; i < 20; i++)
        {
            Console.Write(" ({0}-{1}) ", o.ToString(), Thread.CurrentThread.ManagedThreadId);
            Thread.Sleep(1000);
        }
        Console.WriteLine(" Поток {0} завершается", o.ToString());
    }

    static void Main(string[] args)
    {
        var t1 = new Thread(ThreadZed);
        var t1a = new Thread(ThreadWithParam);
        var t1b = new Thread(ThreadWithParam);

        t1.IsBackground = true;
        t1a.IsBackground = true;
        t1b.IsBackground = true;

        t1.Start();
        t1a.Start("Максим"); 
        t1b.Start("Станчик"); 

        for (int i = 0; i < 5; i++)
        {
            Console.Write(" (*-{0}) ", Thread.CurrentThread.ManagedThreadId);
            Thread.Sleep(1000);
        }

        Console.WriteLine("Главный поток завершается");
    }
}