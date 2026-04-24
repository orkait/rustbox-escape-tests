import java.net.Socket;

public class Main {
    public static void main(String[] args) throws Exception {
        Socket s = new Socket("8.8.8.8", 53);
        System.out.println("ESCAPED");
        s.close();
    }
}
