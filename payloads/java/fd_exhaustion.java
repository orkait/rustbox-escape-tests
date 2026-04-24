import java.io.FileInputStream;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) throws Exception {
        ArrayList<FileInputStream> fds = new ArrayList<>();
        while (true) {
            fds.add(new FileInputStream("/dev/null"));
        }
    }
}
