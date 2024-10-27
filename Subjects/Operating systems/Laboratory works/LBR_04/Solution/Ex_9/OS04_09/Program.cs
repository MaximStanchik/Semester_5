using System;
using System.Threading.Tasks;

class Program
{
    const int TaskCount = 10; 
    const int TaskLifeTime = 10;
    const int ObservationTime = 30; 
    static int[,] Matrix = new int[TaskCount, ObservationTime]; 
    static DateTime StartTime = DateTime.Now;

    static async Task Work(int id)
    {
        for (int i = 0; i < TaskLifeTime; i++)
        {
            await MySleep(1000);

            int ElapsedSeconds = (int)Math.Round((DateTime.Now - StartTime).TotalSeconds);
            if (ElapsedSeconds < ObservationTime)
            {
                Matrix[id, ElapsedSeconds] += 1;
            }
        }
    }

    static async Task<double> MySleep(int ms)
    {
        await Task.Delay(ms);
        return 0; 
    }

    static async Task Main(string[] args)
    {
        Task[] tasks = new Task[TaskCount];

        Console.WriteLine("A student ... is creating tasks...");

        for (int i = 0; i < TaskCount; i++)
        {
            tasks[i] = Work(i); 
        }

        Console.WriteLine("A student ... is waiting for tasks to finish...");
        await Task.WhenAll(tasks);

        Console.WriteLine("Время (с) | " + string.Join(" | ", Array.ConvertAll(Enumerable.Range(0, TaskCount).ToArray(), x => $"Задача {x}")));
        Console.WriteLine(new string('-', 60));
        for (int s = 0; s < ObservationTime; s++)
        {
            Console.Write($"{s,10}: |");
            for (int th = 0; th < TaskCount; th++)
            {
                Console.Write($" {Matrix[th, s],5} |");
            }
            Console.WriteLine();
        }
    }
}