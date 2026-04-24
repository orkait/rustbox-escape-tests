import java.nio.file.Files;
import java.nio.file.Path;

public class Main {
    public static void main(String[] args) throws Exception {
        String content = Files.readString(Path.of("/etc/passwd"));
        System.out.println("ESCAPED");
        System.out.println(content);
    }
}
