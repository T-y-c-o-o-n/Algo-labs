import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.Scanner;

public class A_Set {
    public static void main(String[] args) {
        Set set = new HashSet();
        try (Scanner in = new Scanner(new File("set.in"));
                PrintWriter out = new PrintWriter(
                new BufferedWriter(
                        new OutputStreamWriter(
                                new FileOutputStream(
                                        new File("set.out")
                                ),
                                StandardCharsets.UTF_8
                        )
                )
        )) {
            while (in.hasNext()) {
                String type = in.next();
                int x = in.nextInt();
                if (type.equals("insert")) {
                    set.insert(x);
                }
                if (type.equals("delete")) {
                    set.delete(x);
                }
                if (type.equals("exists")) {
                    out.println(set.exists(x));
                }
            }
        } catch (IOException e) {
            System.out.println("очень жаль, вы проиграли");
        }
    }

    public interface Set {
        void insert(int x);
        void delete(int x);
        boolean exists(int x);
    }

    public static class HashSet implements Set {
        private int[][] arr = new int[50000][2];
        private int[] size = new int[50000];
        public static final int tabu = -2000000000;

        private int getHash(int val) {
            return Math.abs(Integer.hashCode(val)) % 50000;
        }

        public void insert(int val) {
            if (!exists(val)) {
                int ind = getHash(val);
                if (size[ind] == arr[ind].length) {
                    arr[ind] = Arrays.copyOf(arr[ind], arr[ind].length * 2);
                }
                arr[ind][size[ind]++] = val;
            }
        }

        public void delete(int val) {
            int ind = getHash(val);
            for (int i = 0; i < size[ind]; ++i) {
                if (arr[ind][i] == val) {
                    arr[ind][i] = tabu;
                }
            }
        }

        public boolean exists(int val) {
            int ind = getHash(val);
            for (int i = 0; i < size[ind]; ++i) {
                if (arr[ind][i] == val) {
                    return true;
                }
            }
            return false;
        }
     }
}
