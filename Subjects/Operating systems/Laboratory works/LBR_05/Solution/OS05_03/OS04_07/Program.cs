using System;
using System.Threading;

// Maxim Stanchik
class Program
{
    const int ThreadCount = 10;
    const int ThreadLifeTime = 30;
    const int ObservationTime = 30;
    static int[,] Matrix = new int[ThreadCount, ObservationTime];
    static DateTime StartTime = DateTime.Now;

    static void WorkThread(object o)
    {
        int id = (int)o;
        for (int i = 0; i < ThreadLifeTime * 20; i++)
        {
            DateTime CurrentTime = DateTime.Now;
            int ElapsedSeconds = (int)CurrentTime.Subtract(StartTime).TotalSeconds;
            if (ElapsedSeconds >= 0 && ElapsedSeconds < ObservationTime)
            {
                Matrix[id, ElapsedSeconds] += 50;
            }
            MySleep(50);
        }
    }

    static void Main(string[] args)
    {
        Thread[] t = new Thread[ThreadCount];

        for (int i = 0; i < ThreadCount; ++i)
        {
            object o = i;
            t[i] = new Thread(WorkThread);

            if (i % 5 == 0)
            {
                t[i].Priority = ThreadPriority.Lowest;
            }
            else
            {
                t[i].Priority = ThreadPriority.Highest;
            }

            t[i].Start(o);
        }

        Console.WriteLine("Ожидание завершения потоков...");

        for (int i = 0; i < ThreadCount; ++i)
            t[i].Join();

        Console.WriteLine("Результаты работы потоков:");
        for (int s = 0; s < ObservationTime; s++)
        {
            Console.Write("{0,3}: ", s);
            for (int th = 0; th < ThreadCount; th++)
            {
                Console.Write("{0,5}", Matrix[th, s]);
            }
            Console.WriteLine();
        }
    }


    static void MySleep(int ms)
    {
        Thread.Sleep(ms);
    }
}