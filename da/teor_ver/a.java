import java.io.*;
import java.util.StringTokenizer;
 
/**
 * Created by Alexandr Volkov on 09.04.2017.
 */
public class Markchain {
    String fileName = "markchain";
    FastScanner in;
    PrintWriter out;
 
    private double[][] matrixMultiply(double[][] v1, double[][] v2) {
        final int rank = v1.length;
        double[][] b = new double[rank][rank];
        for (int i = 0; i < rank; i++) {
            for (int j = 0; j < rank; j++) {
                for (int k = 0; k < rank; k++)
                    b[i][j] += v1[i][k] * v2[k][j];
            }
        }
        return b;
    }
 
    private boolean isEqualsMatrix(double[][] v1, double[][] v2) {
        int rank = v1.length;
        for (int i = 0; i < rank; i++) {
            for (int j = 0; j < rank; j++) {
                if (!(Math.abs(v1[i][j] - v2[i][j]) <= 0.00001)) {
                    return false;
                }
            }
        }
        return true;
    }
    public void solve() throws IOException {
        int n = in.nextInt();
        double p[][] = new double[n][n];
        double s[][] = new double[n][n];
        double k[][] = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                k[i][j] = s[i][j] = p[i][j] = in.nextDouble();
            }
        }
        k = matrixMultiply(p , p);
        while (!isEqualsMatrix(s, k)) {
            s = k;
            k = matrixMultiply(k , k);
        }
        for (int i = 0; i < n; i++){
            out.println(s[0][i]);
        }
    }
 
    public void run() {
        try {
            in = new FastScanner(new File(fileName + ".in"));
            out = new PrintWriter(new File(fileName + ".out"));
 
            solve();
 
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
 
    class FastScanner {
        BufferedReader br;
        StringTokenizer st;
 
        FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }
 
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
 
        int nextInt() {
            return Integer.parseInt(next());
        }
 
        double nextDouble() {
            return Double.parseDouble(next());
        }
    }
 
    public static void main(String[] arg) {
        new Markchain().run();
    }
}