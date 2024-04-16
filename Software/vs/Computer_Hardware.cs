using System;
using System.Diagnostics;
using System.Net;
using System.Windows.Forms;
using OpenHardwareMonitor.Hardware;
using System.IO.Ports;

namespace Helloworld
{
    //From2024.4.10 By Mr.Han
    public partial class Form1 : Form
    {
        private readonly Timer timer = new Timer();
        private HardwareMonitor hardwareMonitor;
        private SerialPort serialPort = new SerialPort();

        public Form1()
        {
            InitializeComponent();
            InitializeComponents();
        }

        private void InitializeComponents()
        {
            textBox1.ScrollBars = ScrollBars.Vertical;
            InitializeTimer();
            InitializeSerialPort();

            hardwareMonitor = new HardwareMonitor();
            hardwareMonitor.StartMonitoring();

            string hostName = Dns.GetHostName();
            label1.Text = hostName;
            IPAddress[] localIPs = Dns.GetHostAddresses(hostName);
            textBox2.Text = string.Join(Environment.NewLine, Array.ConvertAll(localIPs, ip => ip.ToString()));
            timer.Start();
        }

        private void InitializeTimer()
        {
            timer.Interval = 500;
            timer.Tick += Timer_Tick;
        }

        private void InitializeSerialPort()
        {
            serialPort.PortName = "COM9";
            serialPort.BaudRate = 115200;
            serialPort.Parity = Parity.None;
            serialPort.DataBits = 8;
            serialPort.StopBits = StopBits.One;

            serialPort.Open();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            var monitorData = hardwareMonitor.GetMonitorData();
            DisplayMonitorData(monitorData);
            SendDataToSerialPort(monitorData);
        }

        private void DisplayMonitorData(MonitorData monitorData)
        {
            textBox1.Text = $"CPU 使用率: {monitorData.CpuUsage}%\r\n";
            textBox1.Text += $"CPU 温度: {monitorData.CpuTemperature} °C\r\n";
            textBox1.Text += $"GPU 使用率: {monitorData.GpuUsage}%\r\n";
            textBox1.Text += $"GPU 温度: {monitorData.GpuTemperature} °C\r\n";
            textBox1.Text += $"内存使用率: {monitorData.MemoryUsage}%\r\n";
        }
        private void SendDataToSerialPort(MonitorData monitorData)
        {
            try
            {
                // 将监视数据转换为字节数组
                byte[] dataBytes = new byte[]
                {
                    0x5A,
                    (byte)monitorData.CpuUsage,
                    (byte)monitorData.CpuTemperature,
                    (byte)monitorData.GpuUsage,
                    (byte)monitorData.GpuTemperature,
                    (byte)monitorData.MemoryUsage
                };

                // 计算CRC校验位
                byte crc = CalculateCRC(dataBytes);

                // 将CRC校验位添加到数据字节数组中
                byte[] sendData = new byte[dataBytes.Length + 2];
                Array.Copy(dataBytes, sendData, dataBytes.Length);
                sendData[dataBytes.Length] = crc;
                sendData[dataBytes.Length + 1] = 0xA5; // 添加A5
                                                       
                serialPort.Write(sendData, 0, sendData.Length); // 发送数据到串口
                Console.WriteLine(value: $"sendData {sendData}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error sending data to serial port: {ex.Message}");
            }
        }

        private byte CalculateCRC(byte[] data)
        {
            byte crc = 0;
            foreach (byte b in data)
            {
                crc ^= b;
            }
            return crc;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            timer.Stop();
            hardwareMonitor.StopMonitoring();

            if (serialPort.IsOpen)
            {
                serialPort.Close();
            }
        }
    }

    public class HardwareMonitor
    {
        private Computer computer = new Computer();

        public void StartMonitoring()
        {
            computer.Open();
            computer.GPUEnabled = true;
            computer.CPUEnabled = true;
        }

        public void StopMonitoring()
        {
            computer.Close();
        }

        public MonitorData GetMonitorData()
        {
            MonitorData monitorData = new MonitorData();

            foreach (var hardwareItem in computer.Hardware)
            {
                if (hardwareItem.HardwareType == HardwareType.CPU)
                {
                    hardwareItem.Update();
                    foreach (var sensor in hardwareItem.Sensors)
                    {
                        if (sensor.SensorType == SensorType.Load && sensor.Name == "CPU Total")
                        {
                            monitorData.CpuUsage = sensor.Value ?? 0;
                        }
                        else if (sensor.SensorType == SensorType.Temperature && sensor.Name == "CPU Package")
                        {
                            monitorData.CpuTemperature = sensor.Value ?? 0;
                        }
                    }
                }
                else if (hardwareItem.HardwareType == HardwareType.GpuNvidia || hardwareItem.HardwareType == HardwareType.GpuAti)
                {
                    hardwareItem.Update();
                    foreach (var sensor in hardwareItem.Sensors)
                    {
                        if (sensor.SensorType == SensorType.Load && sensor.Name == "GPU Core")
                        {
                            monitorData.GpuUsage = sensor.Value ?? 0;
                        }
                        else if (sensor.SensorType == SensorType.Temperature && sensor.Name == "GPU Core")
                        {
                            monitorData.GpuTemperature = sensor.Value ?? 0;
                        }
                    }
                }
            }

            monitorData.MemoryUsage = GetMemoryUsage();

            return monitorData;
        }

        private float GetMemoryUsage()
        {
            float memoryUsage = 0;
            try
            {
                PerformanceCounter ramCounter = new PerformanceCounter("Memory", "Available MBytes");
                float availableMemoryMB = ramCounter.NextValue();
                float totalMemoryMB = (float)(new Microsoft.VisualBasic.Devices.ComputerInfo().TotalPhysicalMemory / (1024 * 1024));
                memoryUsage = ((totalMemoryMB - availableMemoryMB) / totalMemoryMB) * 100;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error getting memory usage: {ex.Message}");
            }
            return memoryUsage;
        }
    }

    public class MonitorData
    {
        public float CpuUsage { get; set; }
        public float CpuTemperature { get; set; }
        public float GpuUsage { get; set; }
        public float GpuTemperature { get; set; }
        public float MemoryUsage { get; set; }
    }
}

