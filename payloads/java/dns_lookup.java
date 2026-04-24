import java.net.InetAddress;

public class Main {
    public static void main(String[] args) throws Exception {
        InetAddress addr = InetAddress.getByName("google.com");
        System.out.println("ESCAPED: " + addr);
    }
}
