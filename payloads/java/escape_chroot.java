import java.io.File;

public class Main {
    public static void main(String[] args) {
        File f = new File("../../..");
        String[] entries = f.list();
        if (entries != null && entries.length > 0) {
            System.out.println("ESCAPED");
            for (String e : entries) {
                System.out.println(e);
            }
        }
    }
}
