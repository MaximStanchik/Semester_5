using System;
using System.Threading;
//Maxim Stanchik
class Program
{
    const int ThreadCount = 10;
    const int ThreadLifeTime = 10;
    const int ObservationTime = 30; 
    static int[,] Matrix = new int[ThreadCount, ObservationTime]; 
    static DateTime StartTime = DateTime.Now; 

    static void WorkThread(object o)
    {
        int id = (int)o;
        for (int i = 0; i < ThreadLifeTime; i++)
        {
            DateTime CurrentTime = DateTime.Now;
            int ElapsedSeconds = (int)Math.Round(CurrentTime.Subtract(StartTime).TotalSeconds);
            if (ElapsedSeconds < ObservationTime)
            {
                Matrix[id, ElapsedSeconds] += 1; 
            }
            MySleep(1000); 
        }
    }

    static Double MySleep(int ms)
    {
        double sum = 0;
        for (int t = 0; t < ms; ++t)
        {
            sum += Math.Sin(t); 
        }
        return sum;
    }

    static void Main(string[] args)
    {
        Thread[] threads = new Thread[ThreadCount];

        for (int i = 0; i < ThreadCount; ++i)
        {
            threads[i] = new Thread(WorkThread);
            threads[i].Start(i);
        }

        Console.WriteLine("Ожидание завершения потоков...");
        for (int i = 0; i < ThreadCount; ++i)
        {
            threads[i].Join(); 
        }

        Console.WriteLine("Время (с) | " + string.Join(" | ", Array.ConvertAll(Enumerable.Range(0, ThreadCount).ToArray(), x => $"Поток {x}")));
        Console.WriteLine(new string('-', 60));
        for (int s = 0; s < ObservationTime; s++)
        {
            Console.Write($"{s,10}: |");
            for (int th = 0; th < ThreadCount; th++)
            {
                Console.Write($" {Matrix[th, s],5} |");
            }
            Console.WriteLine();
        }
    }
}