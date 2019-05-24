using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.IO;

namespace SerialRW
{
    class Program
    {
        static SerialPort mcomm_port;
        static SerialPort tcu_port;
        static byte[] mcomm_buffer;
        static byte[] tcu_buffer;
        static FileStream fs;

        static void Main(string[] args)
        {
            mcomm_port = new SerialPort("COM35");
            mcomm_port.BaudRate = 230400;
            mcomm_port.Parity = Parity.None;
            mcomm_port.StopBits = StopBits.One;
            mcomm_port.DataBits = 8;
            mcomm_port.Handshake = Handshake.None;
            mcomm_port.RtsEnable = false;
            mcomm_port.NewLine = "\x7E";
            mcomm_buffer = new byte[128000];

            tcu_port = new SerialPort("COM26");
            tcu_port.BaudRate = 230400;
            tcu_port.Parity = Parity.None;
            tcu_port.StopBits = StopBits.One;
            tcu_port.DataBits = 8;
            tcu_port.Handshake = Handshake.None;
            tcu_port.RtsEnable = false;
            tcu_port.NewLine = "\x7E";
            tcu_buffer = new byte[128000];

            mcomm_port.DataReceived += new SerialDataReceivedEventHandler(McommDataReceivedHandler);
            tcu_port.DataReceived += new SerialDataReceivedEventHandler(TcuDataReceivedHandler);

            mcomm_port.Open();
            tcu_port.Open();

            using (fs = File.Create("out.txt"))
            {

                bool _continue = true;
                while (_continue)
                {
                    Console.Write("?>");
                    string in_str = Console.ReadLine();
                    string[] word = in_str.Split(new char[] { ' ' });
                    switch (word[0])
                    {
                        case "quit":
                        case "exit":
                            _continue = false;
                            break;
                        case "write":
                            mcomm_port.WriteLine(in_str);
                            break;

                        default:
                            Console.WriteLine("Unknown command. Type 'quit' to exit");
                            break;
                    }
                }
                //                Console.WriteLine("?:");
                //                Console.WriteLine();
                //                Console.ReadKey();
            }
            mcomm_port.Close();
            tcu_port.Close();
        }

        private static void McommDataReceivedHandler(
                        object sender,
                        SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            int size = sp.Read(mcomm_buffer, 0, mcomm_buffer.Length);
            tcu_port.Write(mcomm_buffer, 0, size);

//            Console.WriteLine(System.Text.Encoding.UTF8.GetString( mcomm_buffer, 0, size));
//            Console.Write("?>");
            //            string indata = sp.ReadExisting();
            //            tcu_port.Write(indata);

            //            Console.WriteLine("Data Received:");
            //            Console.Write(indata);
            //            indata.Replace("\xA", "\xA\xD");
            //            byte[] bytes = Encoding.ASCII.GetBytes(indata);
            //            fs.Write(bytes, 0, bytes.Length);

        }
        private static void TcuDataReceivedHandler(
                        object sender,
                        SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            int size = sp.Read(tcu_buffer, 0, tcu_buffer.Length);
            mcomm_port.Write(tcu_buffer, 0, size);

            //            string indata = sp.ReadExisting();


            //            mcomm_port.Write(indata);
            //            Console.WriteLine(indata);
        }
    }
}
