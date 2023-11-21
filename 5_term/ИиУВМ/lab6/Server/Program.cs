using System.Net.Sockets;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;

class Program
{
    static void Main()
    {
        // Запуск сервера Bluetooth
        BluetoothListener bluetoothListener = new BluetoothListener(BluetoothService.SerialPort);
        bluetoothListener.Start();

        Console.WriteLine("Ожидание подключения (84:1B:77:17:7E:8C)...");

        // Ожидание подключения клиента
        BluetoothClient bluetoothClient = bluetoothListener.AcceptBluetoothClient();
        Console.WriteLine("Успешное подключение!");

        // Получение потока для отправки файла
        NetworkStream networkStream = bluetoothClient.GetStream();

        // Замените "путь_к_вашему_файлу" на реальный путь к файлу
        string filePath = "Z:\\music\\Ost.Battlefield2";
        SendFile(filePath, networkStream);

        // Закрытие соединения
        networkStream.Close();
        bluetoothClient.Close();
        bluetoothListener.Stop();
    }

    static void SendFile(string filePath, Stream stream)
    {
        // Отправка размера файла
        FileInfo fileInfo = new FileInfo(filePath);
        byte[] fileSizeBytes = BitConverter.GetBytes(fileInfo.Length);
        stream.Write(fileSizeBytes, 0, fileSizeBytes.Length);

        // Отправка файла
        using (FileStream fileStream = File.OpenRead(filePath))
        {
            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = fileStream.Read(buffer, 0, buffer.Length)) > 0)
            {
                stream.Write(buffer, 0, bytesRead);
            }
        }

        Console.WriteLine("Файл успешно отправлен!");
    }
}