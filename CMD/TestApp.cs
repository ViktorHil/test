using System;
using System.Windows.Forms;

class TestApp {
	static int Main(string[] args) {
		if ( args == null) {
			Console.WriteLine("Hello CS!");
		} else {
			Console.WriteLine("args!");
			int i = 0;
			foreach( var v in args) {
				Console.WriteLine("arg[{0}]:\"{1}\"", i, args[i]);
				i++;
			}
		}
		MessageBox.Show("Hello...");
		return 0;
	}
}


