import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class F_BadHash {
    public static class Pair {
        public String f;
        public int s;

        public Pair(String f, int s) {
            this.f = f;
            this.s = s;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int k = sc.nextInt();
        StringBuilder sb;
        for (int i = 0; i < k; ++i) {
            sb = new StringBuilder();
            for (int j = 0; j < 11; ++j) {
                if ((i & (1 << j)) > 0) {
                    sb.append("ba");
                } else {
                    sb.append("cB");
                }
            }
            System.out.println(sb.toString());
//            System.out.println(sb.toString().hashCode());
        }

        /*StringBuilder sb;
        StringBuilder sb1;

        kek: for (int a = 'A'; a <= 'z'; a++) {
            for (int b = 'A'; b < a; b++) {
                for (int c = 'A'; c <= 'z'; c++) {
                    for (int d = 'A'; d < c && !(a == c && b == d); d++) {
                        sb = new StringBuilder();
                        sb.append((char)a);
                        sb.append((char)b);
                        sb1 = new StringBuilder();
                        sb1.append((char)c);
                        sb1.append((char)d);
                        if (sb.toString().hashCode() == sb1.toString().hashCode()) {
                            System.out.println(sb.toString());
                            System.out.println(sb1.toString());
                            System.out.println("\n\n\n");
                            // break kek;
                        }
                    }
                }
            }
        }

        List<Character> chars = List.of('a', 'f');
        List<Pair> list = new ArrayList<>();
        List<Pair> suck = new ArrayList<>();
        int len = 2;
        for (int i = 0; i < (1 << len); ++i) {
            sb = new StringBuilder();
            for (int j = len-1; j >= 0; --j) {
                if ((i & (1 << j)) > 0) {
                    sb.append('A');
                } else {
                    sb.append('f');
                }
            }
            String str = sb.toString();
            int hash = str.hashCode();
            int cnt = 0;
            for (Pair pair : list) {
                if (pair.s == hash) {
                    cnt++;
                }
            }
            if (cnt > 0) {
                suck.add(new Pair(str, cnt));
            }
            list.add(new Pair(str, hash));
//            System.out.println(str);
//            System.out.println(str.hashCode());
        }
        System.out.println(suck.size());
//        int k = sc.nextInt();
        System.out.println("babababababababa".hashCode());
        System.out.println("cBcBcBcBcBcBcBcB".hashCode());
        System.out.println("bababababababacB".hashCode());
        System.out.println("cBcBcBcBcBcBcBba".hashCode());
        System.out.println("babababababacBba".hashCode());
        System.out.println("cBcBcBcBcBcBbacB".hashCode());
        System.out.println("babababababacBcB".hashCode());
        System.out.println("cBcBcBcBcBcBbaba".hashCode());
*/

//
//        System.out.println("aAaAaAaAaAaAaAaA".hashCode());
//        System.out.println("aAaAaAaAaAaAaAbB".hashCode());
//        System.out.println("aAaAaAaAaAaAbBaA".hashCode());
//        System.out.println("aAaAaAaAaAaAbBbB".hashCode());
//
//        System.out.println("bBbBbBbBbBbBbBbB".hashCode());
//        System.out.println("bBbBbBbBbBbBbBaA".hashCode());
//        System.out.println("bBbBbBbBbBbBaAbB".hashCode());
//        System.out.println("bBbBbBbBbBbBaAaA".hashCode());
//        sc.close();
    }
}
