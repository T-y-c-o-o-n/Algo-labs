import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.Scanner;

public class B_Map {
    public static void main(String[] args) {
        Map map = new HashMap();
        try (Scanner in = new Scanner(new File("map.in"));
             PrintWriter out = new PrintWriter(
                     new BufferedWriter(
                             new OutputStreamWriter(
                                     new FileOutputStream(
                                             new File("map.out")
                                     ),
                                     StandardCharsets.UTF_8
                             )
                     )
             )) {
            while (in.hasNext()) {
                String type = in.next();
                String x = in.next();
                if (type.equals("put")) {
                    String y = in.next();
                    map.put(x, y);
                }
                if (type.equals("delete")) {
                    map.delete(x);
                }
                if (type.equals("get")) {
                    String res = map.get(x);
                    if (res == null) {
                        out.println("none");
                    } else {
                        out.println(res);
                    }
                }
            }
        } catch (IOException e) {
            System.out.println("очень жаль, вы проиграли");
        }
    }

    public interface Map {
        void put(String key, String value);
        void delete(String key);
        String get(String key);
    }

    public static class HashMap implements Map {
        private Entry[][] arr = new Entry[50000][2];
        private int[] size = new int[50000];

        private int getHash(String val) {
            return Math.abs(val.hashCode()) % 50000;
        }

        public void put(String key, String value) {
            int ind = getHash(key);
            for (int i = 0; i < size[ind]; i++) {
                if (arr[ind][i].key.equals(key)) {
                    arr[ind][i].value = value;
                    return;
                }
            }
            if (size[ind] == arr[ind].length) {
                arr[ind] = Arrays.copyOf(arr[ind], arr[ind].length * 2);
            }
            arr[ind][size[ind]++] = new Entry(key, value);
        }

        public void delete(String key) {
            int ind = getHash(key);
            for (int i = 0; i < size[ind]; i++) {
                if (arr[ind][i].key.equals(key)) {
                    arr[ind][i].value = null;
                    return;
                }
            }
        }

        public String get(String key) {
            int ind = getHash(key);
            for (int i = 0; i < size[ind]; i++) {
                if (arr[ind][i].key.equals(key)) {
                    return arr[ind][i].value;
                }
            }
            return null;
        }


        public interface MapEntry {
            String getKey();
            String getValue();
        }

        public static class Entry implements MapEntry {
            private String key;
            private String value;

            private Entry(String key, String value) {
                this.key = key;
                this.value = value;
            }

            public String getKey() {
                return key;
            }

            public String getValue() {
                return value;
            }
        }
    }
}