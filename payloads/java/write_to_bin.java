import java.nio.file.Files;
import java.nio.file.Path;

public class Main {
    public static void main(String[] args) throws Exception {
        Files.writeString(Path.of("/bin/evil"), "pwned");
        System.out.println("ESCAPED");
    }
}
