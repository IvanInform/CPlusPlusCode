using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DelegatesAndEvents
{
    class Program
    {
        public delegate void MyDel();
        public delegate int secondDel(int x);
        public static event MyDel myEvent;
        public static event secondDel EventTwo;
        public delegate void AnominouseDelegate(int x);
        public static void Main(string[] args)
        {
            myEvent += Hello;
            myEvent += Bye;
            secondDel testdel = new secondDel(divide);
            Console.WriteLine( testdel(10) ); 
            myEvent+=delegate(){Console.WriteLine("This is anonimous delegate");};
            myEvent();
            EventTwo += new secondDel(Mult);
            Console.WriteLine(EventTwo(10));
            EventTwo -= Mult;
             EventTwo += new secondDel(new Program().myFunct);
             Console.WriteLine( EventTwo(20)); 
            AnominouseDelegate del=delegate(int x){
            for (var i=0;i<5;i++)
            {Console.WriteLine("Hello and {0}", x);
            }
            };
            testdel(20);

            Person ivan = new Person();
            
            ivan.cashEvent += delegate()
            {
                Console.WriteLine("Cash is" +
                    "substracted");
            };
           ivan.Cash = 1000;
        }

      public static int Mult(int x){
      return x*x;
      }
      public static int divide(int x) { return 1000 / x; }
      public  Func<int, int> myFunct =x=> x * x * x; 
        static void Hello() {
            Console.WriteLine("Hello World"); 
        }
        static void Bye()
        {
            Console.WriteLine("Bye World"); 
        }
        
        class Person {
            private int cash;
            public delegate void MyEventHander();
            public event MyEventHander cashEvent;
            public int Cash {
                get { return cash; }
                set {
                    if (value >= 100) {
                        if (cashEvent != null) { 
                            cashEvent();}
                                
                    }
                    this.cash = value; }
            }
        }
    }
}
