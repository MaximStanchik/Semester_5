using System; // пространство имен для базовых типов
using System.Threading; // пространство имен для работы с потоками

class Program
{
    const int ThreadCount = 10; // кол-во потоков
    const int ThreadLifeTime = 30; // время жизни каждого потока в секундах
    const int ObservationTime = 30; // общее время наблюдения в секундах
    static int[,] Matrix = new int[ThreadCount, ObservationTime]; // матрица для хранения результатов работы потоков
    static DateTime StartTime = DateTime.Now; // время начала выполнения программы

    static void WorkThread(object o) // метод который будет выполнять каждый поток
    {
        int id = (int)o; // идентификатор потока, который передается как параметр
        for (int i = 0; i < ThreadLifeTime * 20; i++) // цикл
        {
            DateTime CurrentTime = DateTime.Now; // получение текущего времени
            int ElapsedSeconds = (int)CurrentTime.Subtract(StartTime).TotalSeconds; // преобразуем в int кол-во секунд что прошли
            if (ElapsedSeconds >= 0 && ElapsedSeconds < ObservationTime) // проверка, что время находится в пределах наблюдения
            {
                Matrix[id, ElapsedSeconds] += 50; // обновление значения в матрице для текущего потока и времени
            }
            MySleep(50); // задержка на 50 милисекунд
        }
    }

    static void Main(string[] args)
    {
        Thread[] t = new Thread[ThreadCount]; // массив для хранения потоков
        for (int i = 0; i < ThreadCount; ++i)  // цикл для создания потоков
        {
            object o = i; // передаем индекс потока в качестве идентификатора
            t[i] = new Thread(WorkThread); // создание нового потока, указываем метод который поток будет выполнять

            if (i % 2 == 0) // тут мы задаем приоритет для каждого потока
            {
                t[i].Priority = ThreadPriority.BelowNormal;  
            }
            else
            {
                t[i].Priority = ThreadPriority.Normal;  
            }
            t[i].Start(o); // запуск потока
        }

        Console.WriteLine("Ожидание завершения потоков...");
        for (int i = 0; i < ThreadCount; ++i)
            t[i].Join(); // ожидаем завершения каждого потока

        Console.WriteLine("Результаты работы потоков:");
        for (int s = 0; s < ObservationTime; s++) // цикл по времени наблюдения
        {
            Console.Write("{0,3}: ", s); // вывод номера текущей секунды
            for (int th = 0; th < ThreadCount; th++) // цил по количеству потоков
            {
                Console.Write("{0,5}", Matrix[th, s]); // вывод значения из матрицы для текущего потока и времени
            }
            Console.WriteLine();
        }
    }

    static void MySleep(int ms) // метод для задержки
    {
        Thread.Sleep(ms); // задержка на указанное кол-во миллисекунд
    }
}
