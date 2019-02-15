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
        static SerialPort port;
        static FileStream fs;

        static void Main(string[] args)
        {
            port = new SerialPort("COM35");
            port.BaudRate = 115200;
            port.Parity = Parity.None;


            port.StopBits = StopBits.One;
            port.DataBits = 8;
            port.Handshake = Handshake.None;
            port.RtsEnable = false;
            port.NewLine = "\xA";

            port.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);

            port.Open();

            using ( fs = File.Create("out.txt"))
            {

                bool _continue = true;
                while(_continue) {
                    Console.Write("?>");
                    string in_str = Console.ReadLine();
                    string[] word = in_str.Split(new char[] { ' ' });
                    switch( word[0])
                    {
                        case "quit":
                        case "exit":
                            _continue = false;
                            break;
                        case "write":
                            port.WriteLine( in_str);
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
            port.Close();
        }

        private static void DataReceivedHandler(
                        object sender,
                        SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;

            string indata = sp.ReadExisting();
            //            Console.WriteLine("Data Received:");
            Console.Write(indata);
            indata.Replace("\xA", "\xA\xD");
            byte[] bytes = Encoding.ASCII.GetBytes( indata);
            fs.Write( bytes, 0, bytes.Length);

        }
    }
}
