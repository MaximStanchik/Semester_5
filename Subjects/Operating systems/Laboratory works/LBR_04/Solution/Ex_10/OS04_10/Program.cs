using System;
using System.Linq;
using System.Threading.Tasks;

class Program
{
    const int TaskCount = 10;
    const int ThreadLifeTime = 10; 
    const int ObservationTime = 30; 
    static int[,] Matrix = new int[TaskCount, ObservationTime];
    static DateTime StartTime;
//Maxim Stanchik
    static void Work(int id)
    {
        for (int i = 0; i < ThreadLifeTime * 20; i++)
        {
            DateTime CurrentTime = DateTime.Now;
            int ElapsedSeconds = (int)(CurrentTime - StartTime).TotalSeconds;

            if (ElapsedSeconds >= 0 && ElapsedSeconds < ObservationTime)
            {
                Matrix[id, ElapsedSeconds] += 50; 
            }

            MySleep(50); 
        }
    }

    static void Main(string[] args)
    {
        Task[] tasks = new Task[TaskCount];
        StartTime = DateTime.Now; 

        Console.WriteLine("A student ... is creating tasks...");

        for (int i = 0; i < TaskCount; i++)
        {
            int taskId = i;
            if (i == 0)
            {
                tasks[i] = Task.Run(() => Work(taskId)); 
            }
            else
            {
                tasks[i] = tasks[i - 1].ContinueWith(_ => Work(taskId));
            }
        }

        Console.WriteLine("A student ... is waiting for tasks to finish...");
        Task.WaitAll(tasks);

        Console.WriteLine("\nResults:");
        Console.WriteLine("Sec | " + string.Join(" | ", Enumerable.Range(0, TaskCount).Select(i => $"Task {i}")));
        Console.WriteLine(new string('-', 40));

        for (int s = 0; s < ObservationTime; s++)
        {
            Console.Write($"{s,3} | ");
            for (int th = 0; th < TaskCount; th++)
            {
                Console.Write($"{Matrix[th, s],5} | ");
            }
            Console.WriteLine();
        }
    }

    static void MySleep(int milliseconds)
    {
        DateTime endTime = DateTime.Now.AddMilliseconds(milliseconds);
        while (DateTime.Now < endTime)
        {
            ComputeFibonacci(20); 
        }
    }

    static long ComputeFibonacci(int n)
    {
        if (n <= 1)
            return n;
        return ComputeFibonacci(n - 1) + ComputeFibonacci(n - 2);
    }
}