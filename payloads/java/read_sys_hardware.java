import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.stream.Stream;

public class Main {
    public static void main(String[] args) throws Exception {
        try (Stream<Path> paths = Files.walk(Paths.get("/sys"), 2)) {
            paths.forEach(System.out::println);
        }
        System.out.println("ESCAPED");
    }
}
