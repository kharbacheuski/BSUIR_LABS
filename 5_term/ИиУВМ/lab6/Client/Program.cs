using System.Net.Sockets;
using InTheHand.Net;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Sockets;

class Program
{
    static void Main()
    {

        // Запрос у пользователя Bluetooth-адреса сервера
        Console.Write("Введите Bluetooth-адрес сервера (в формате XX:XX:XX:XX:XX:XX): ");
        string serverAddress = Console.ReadLine();

        BluetoothClient bluetoothClient = new BluetoothClient();

        // Установка соединения
        var address = BluetoothAddress.Parse(serverAddress);
        bluetoothClient.Connect(address, BluetoothService.SerialPort);

        Console.WriteLine("Соединение установлено!");

        // Получение потока для приема файла
        NetworkStream networkStream = bluetoothClient.GetStream();

        // Получение размера файла
        byte[] fileSizeBytes = new byte[sizeof(long)];
        networkStream.Read(fileSizeBytes, 0, fileSizeBytes.Length);
        long fileSize = BitConverter.ToInt64(fileSizeBytes, 0);

        // Получение файла
        string savePath = "D:\\track.wav";
        ReceiveFile(networkStream, fileSize, savePath);

        // Закрытие соединения
        networkStream.Close();
        bluetoothClient.Close();

        var player = new System.Media.SoundPlayer(savePath);
        player.Play();

        Console.Read();
    }

    static void ReceiveFile(Stream stream, long fileSize, string savePath)
    {
        using (FileStream fileStream = File.OpenWrite(savePath))
        {
            var bytes = new List<byte>();

            byte[] buffer = new byte[1024 * 1024 * 1024];
            int bytesRead;
            long bytesReceived = 0;

            while (bytesReceived < fileSize)
            {
                bytesRead = stream.Read(buffer, 0, buffer.Length);
                bytes.AddRange(buffer.Take(bytesRead));
                bytesReceived += bytesRead;
            }

            fileStream.Write(bytes.ToArray(), 0, (int)bytesReceived);
        }

        Console.WriteLine("Файл успешно получен!");
    }
}