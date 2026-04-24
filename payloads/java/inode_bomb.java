import java.io.File;

public class Main {
    public static void main(String[] args) throws Exception {
        for (int i = 0; i < 100000; i++) {
            new File("/tmp/inode_" + i).createNewFile();
        }
        System.out.println("ESCAPED");
    }
}
