//
//  Code is poetry.
//
//  Created by Nick aka black-dragon74 on 23-12-2020
//

package com.blackdragon74;

import java.util.Arrays;
import java.util.HashMap;

class Ques1 {
    public static void main(String[] args) {
        System.out.println("Name: Niraj\nReg: 181015001\nPlace: NOYB");
    }
}

class Ques2 {
    public static void main(String[] args) {
        if (args.length != 0) {
            System.out.println("Java is an object oriented programming language");
        }
    }
}

class Ques3 {
    public static void main(String[] args) {
        int a = Integer.parseInt(args[0]);
        int b = Integer.parseInt(args[1]);

        System.out.println(a + b);
        System.out.println(a - b);
        System.out.println(a * b);
        System.out.println(a / b);
    }
}

class Ques4 {
    public static void main(String[] args) {
        int numElems = Integer.parseInt(args[0]);
        int sum = 0;

        for (int i = 1; i <= numElems; i++) {
            sum += Integer.parseInt(args[i]);
        }

        System.out.println(sum);
    }
}

class Ques5 {
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);

        if (n == 0 || n == 1) {
            System.out.println(n);
        } else {
            int fact = 1;

            for (int i = 2; i <= n; i++) {
                fact *= i;
            }

            System.out.println(fact);
        }
        System.exit(0);
    }
}

class Ques6 {
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);

        int sum = 0;
        while (n != 0) {
            int curr = n % 10;
            sum += curr;
            n /= 10;
        }

        System.out.println(sum);
        System.exit(0);
    }
}

class Ques7 {
    static int fib(int n) {
        if (n <= 1)
            return n;

        return fib(n - 1) + fib(n - 2);     // Current num is sum of nums at i-1 and i-2 indices
    }

    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        System.out.println(fib(n));
    }
}

class Ques8 {
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);

        int rev = 0;
        while (n != 0) {
            rev = rev * 10 + n % 10;
            n /= 10;
        }

        System.out.println(rev);
    }
}

class Ques9 {
    public static void main(String[] args) {
        double nf = 1.23;
        int n = (int) nf;

        System.out.println(n);
    }
}

class Ques10 {
    public static void main(String[] args) {
        int a = 10;
        a += 10;

        double b = a;   // int converted to double

        System.out.println(b);
    }
}

class Ques11 {
    public static void main(String[] args) {
        boolean useMe = args.length == 0;
        System.out.println(useMe ? "Used you" : "Didn't use you");
    }
}

class Ques12 {
    static int global = 0;

    @SuppressWarnings("unused")
    public static void main(String[] args) {
        int local;
        System.out.println(global);
    }

    @SuppressWarnings("unused")
    static void something() {
        // Can't access local here, but global can still be accessed
        System.out.println("Global from other function: " + global);
        // local = 0;
    }
}

class Ques13 {
    public static void main(String[] args) {
        int[] array = {1, 2, 3, 4, 4, 5, 5, 6, 6, 7};
        int[] sortedArray = Arrays.stream(array).sorted().toArray();

        for (int elem : sortedArray) {
            System.out.println(elem);
        }
    }
}

class Ques14 {
    public static void main(String[] args) {
        int numRows = Integer.parseInt(args[0]);
        int numCols = Integer.parseInt(args[1]);

        int[][] matrix = new int[numRows][numCols];
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                matrix[i][j] = i + j + (int) Math.PI;
            }
        }

        int sum = 0, mul = 1;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                sum += matrix[i][j];
                mul *= matrix[i][j];
            }
        }

        System.out.printf("Sum is: %d, Mul is: %d", sum, mul);
    }
}

class Ques15 {
    public static void main(String[] args) {
        int marks = Integer.parseInt(args[0]);

        if (marks >= 60) {
            System.out.println("1st class");
        } else if (marks >= 50) {   // && marks <= 59 is not needed, you figure why!
            System.out.println("2nd class");
        } else if (marks >= 40) {
            System.out.println("3rd class");
        } else {
            System.out.println("Failed!");
        }
    }
}

class Ques16 {
    public static boolean checkLeapYear(int year) {
        if (year % 4 == 0) {
            if (year % 100 == 0) {
                return year % 400 == 0;
            } else {
                return true;
            }
        } else {
            return false;
        }
    }

    public static void main(String[] args) {
        int year = Integer.parseInt(args[0]);

        System.out.println(checkLeapYear(year));
    }
}

class Ques17 {
    public static void main(String[] args) {
        String myStr = "They don't know that they know we know they know";
        HashMap<String, Integer> map = new HashMap<>();

        for (String word : myStr.split(" ")) {
            word = word.toLowerCase();
            if (map.containsKey(word))
                map.put(word, (map.get(word)) + 1);
            else
                map.put(word, 1);
        }

        for (String key : map.keySet()) {
            System.out.println(key + " occurred " + map.get(key) + " times.");
        }
    }
}

class Ques18 {
    static class Square {
        private final int side;

        public Square(int side) {
            this.side = side;
        }

        public int getSide() {
            return side;
        }

        public int getArea() {
            return side * side;
        }
    }

    static class Rectangle extends Square {
        private final int width;

        public Rectangle(int l, int b) {
            super(l);
            this.width = b;
        }

        @Override
        public int getArea() {
            return super.getSide() * width;
        }
    }

    public static void main(String[] args) {
        Square s = new Square(5);
        Rectangle r = new Rectangle(5, 4);

        System.out.println("Area of square: " + s.getArea());
        System.out.println("Area of rectangle: " + r.getArea());
    }
}

class Ques19 {
    static class MyObj {
        private final int id;

        public MyObj(int id) {
            this.id = id;
        }

        public int getId() {
            return this.id;
        }
    }

    static MyObj createTest() {
        return new MyObj(2974);
    }

    public static void main(String[] args) {
        MyObj t = createTest();  // Returned an object of type `MyObj`
        System.out.println(t.getId());
    }
}

class Ques20 {
    static class RecursiveFactorial {
        private final int number;

        private int getFact(int n) {
            if (n <= 0)
                return 1;

            return n * getFact(n - 1);
        }

        public RecursiveFactorial(int n) {
            this.number = n;
        }

        public int getFactorial() {
            return getFact(number);
        }
    }

    public static void main(String[] args) {
        RecursiveFactorial fo5 = new RecursiveFactorial(5);
        System.out.println(fo5.getFactorial());
    }
}

// EOF

